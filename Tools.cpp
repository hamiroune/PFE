#include "Tools.h"
#include "Window.h"
#include "preference.h"
#include "Radiometrics.h"

Tools::Tools(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Tools::~Tools()
{
}
void Tools::Pansharpening_run()
{
	qDebug() << "succes-1";
	typedef otb::Image<float, 2>                   ImageType;
	typedef otb::VectorImage<float, 2>             VectorImageType;
	typedef otb::ImageFileReader<ImageType>         ReaderType;
	typedef otb::ImageFileReader<VectorImageType>   ReaderVectorType;
	typedef otb::VectorImage<unsigned short int, 2> VectorIntImageType;
	typedef otb::ImageFileWriter<VectorIntImageType> WriterType;

	QString Algorithm;
	Window w;
	preference p;
	Radiometrics r;
	ReaderVectorType::Pointer readerPAN = ReaderVectorType::New();
	ReaderVectorType::Pointer readerXS = ReaderVectorType::New();
	WriterType::Pointer writer = WriterType::New();
	readerPAN->SetFileName(w.on_actionInput_PAN_Image_clicked().toStdString());
	readerXS->SetFileName(w.on_actionInput_XS_Image_clicked().toStdString());
	writer->SetFileName(w.on_actionOutput_Image_clicked().toStdString());

	typedef otb::BCOInterpolateImageFunction<VectorImageType> InterpolatorType;
	typedef otb::GenericRSResampleImageFilter<VectorImageType, VectorImageType>  ResamplerType;
	typedef otb::StreamingResampleImageFilter<VectorImageType, VectorImageType>  BasicResamplerType;
	typedef otb::MultiToMonoChannelExtractROI<float, float> ExtractFilterType;

	ExtractFilterType::Pointer channelSelect = ExtractFilterType::New();
	channelSelect->SetChannel(1);
	channelSelect->SetInput(readerPAN->GetOutput());
	channelSelect->UpdateOutputInformation();

	qDebug() << "succes01";
	// Set up output image informations
	ImageType::Pointer panchro = channelSelect->GetOutput();
	VectorImageType::SpacingType spacing = panchro->GetSpacing();
	VectorImageType::IndexType   start = panchro->GetLargestPossibleRegion().GetIndex();
	VectorImageType::SizeType    size = panchro->GetLargestPossibleRegion().GetSize();
	VectorImageType::PointType   origin = panchro->GetOrigin();

	// Resample filter
	ResamplerType::Pointer    resampler = ResamplerType::New();
	InterpolatorType::Pointer interpolator = InterpolatorType::New();
	resampler->SetInterpolator(interpolator);
	VectorImageType::SpacingType defSpacing;
	defSpacing[0] = 10 * spacing[0];
	defSpacing[1] = 10 * spacing[1];
	resampler->SetDisplacementFieldSpacing(defSpacing);
	resampler->SetInput(readerXS->GetOutput());
	resampler->SetOutputOrigin(origin);
	resampler->SetOutputSpacing(spacing);
	resampler->SetOutputSize(size);
	resampler->SetOutputStartIndex(start);
	resampler->SetOutputKeywordList(panchro->GetImageKeywordlist());
	resampler->SetOutputProjectionRef(panchro->GetProjectionRef());
	VectorImageType::PixelType defaultValue;
	readerXS->UpdateOutputInformation();
	itk::NumericTraits<VectorImageType::PixelType>::SetLength(defaultValue, readerXS->GetOutput()->GetNumberOfComponentsPerPixel());
	resampler->SetEdgePaddingValue(defaultValue);
	Algorithm = ui.comboBox_Alghorithm->currentText();

	qDebug() << "succes0";
	if (p.checkBox_Rcs->ischecked())
	{
		typedef otb::SimpleRcsPanSharpeningFusionImageFilter	<ImageType, VectorImageType, VectorIntImageType> FusionFilterType;

		FusionFilterType::Pointer fusion = FusionFilterType::New();
		fusion->SetPanInput(panchro);
		fusion->SetXsInput(resampler->GetOutput());

		writer->SetInput(fusion->GetOutput());
		try
		{
			writer->Update();
		}
		catch (itk::ExceptionObject& excep)
		{
			qDebug() << "Exception caught ! " << excep.what();
			return;
		}
	}
	else
		if (p.checkBox_Lmvm->isChecked())
		{
			typedef otb::LmvmPanSharpeningFusionImageFilter		<ImageType, VectorImageType, VectorIntImageType, double> LmvmFilterType;

			LmvmFilterType::Pointer fusion = LmvmFilterType::New();
			fusion->SetPanInput(panchro);
			fusion->SetXsInput(resampler->GetOutput());
			int radiusx = ui.spinBox_X->value();
			int radiusy = ui.spinBox_Y->value();
			typedef otb::Image<ImageType::InternalPixelType> InternalFloatImageType;
			InternalFloatImageType::SizeType radius;
			radius[0] = radiusx;
			radius[1] = radiusy;
			fusion->SetRadius(radius);
			itk::Array<double> filterCoeffs;
			filterCoeffs.SetSize((2 * radius[0] + 1) * (2 * radius[1] + 1));
			filterCoeffs.Fill(1);
			fusion->SetFilter(filterCoeffs);

			writer->SetInput(fusion->GetOutput());
			try
			{
				writer->Update();
			}
			catch (itk::ExceptionObject& excep)
			{
				return;
			}
		}
	qDebug() << "succes";

}

void Tools::Orthorectification_run()
{
	qDebug() << "succes01";
	typedef otb::Image<unsigned int, 2> ImageType;
	typedef otb::VectorImage<unsigned int, 2> VectorImageType;
	typedef otb::ImageFileReader<VectorImageType> ReaderType;
	typedef otb::ImageFileReader<VectorImageType>   ReaderVectorType;
	//typedef otb::StreamingImageFileWriter<VectorImageType> WriterType;
	typedef otb::ImageFileWriter<VectorImageType> WriterType;


	QString interpolationMode;

	ReaderVectorType::Pointer readerPan = ReaderVectorType::New();
	ReaderVectorType::Pointer readerXS = ReaderVectorType::New();
	WriterType::Pointer writer = WriterType::New();
	readerPan->SetFileName(ui.lineEdit_Input->text().toStdString());
	//readerXS->SetFileName(ui.lineEdit_input_ortho_m->text().toStdString());
	writer->SetFileName(ui.lineEdit_Output->text().toStdString());

	VectorImageType::Pointer inImage = readerPan->GetOutput();
	inImage->UpdateOutputInformation();
	QString useDEM = ui.comboBox_DEM->currentText();
	if (useDEM == "Set default elevation")
		otb::DEMHandler::Instance()->SetDefaultHeightAboveEllipsoid(ui.spinBox_Elivation->value());
	qDebug() << "succes001";
	if (useDEM == "add DEM directory")
		otb::DEMHandler::Instance()->OpenDEMDirectory(ui.lineEdit_DEM->text().toStdString());
	qDebug() << "succes002";
	// Compute the output image spacing and size
	typedef otb::ImageToGenericRSOutputParameters<VectorImageType> OutputParametersEstimatorType;
	OutputParametersEstimatorType::Pointer genericRSEstimator = OutputParametersEstimatorType::New();
	genericRSEstimator->EstimateIsotropicSpacingOn();
	genericRSEstimator->SetInput(inImage);
	genericRSEstimator->SetOutputProjectionRef(inImage->GetProjectionRef());
	genericRSEstimator->Compute();

	typedef otb::GenericRSResampleImageFilter<VectorImageType, VectorImageType>     ResampleFilterType;
	// Resampler Instantiation
	ResampleFilterType::Pointer m_ResampleFilter = ResampleFilterType::New();
	m_ResampleFilter->SetInput(inImage);
	// Set the output projection Ref
	m_ResampleFilter->SetInputProjectionRef(inImage->GetProjectionRef());
	m_ResampleFilter->SetInputKeywordList(inImage->GetImageKeywordlist());
	m_ResampleFilter->SetOutputProjectionRef(inImage->GetProjectionRef());

	// Get Interpolator
	if (ui.radioButton_Linear->isChecked())
	{
		qDebug() << "succes02";
		typedef itk::LinearInterpolateImageFunction<VectorImageType, double> LinearInterpolationType;
		LinearInterpolationType::Pointer interpolator = LinearInterpolationType::New();
		m_ResampleFilter->SetInterpolator(interpolator);
	}
	else
		if (ui.radioButton_NNeighbor->isChecked())
		{
			qDebug() << "succes03";
			typedef itk::NearestNeighborInterpolateImageFunction<VectorImageType, double> NearestNeighborInterpolationType;
			NearestNeighborInterpolationType::Pointer interpolator = NearestNeighborInterpolationType::New();
			m_ResampleFilter->SetInterpolator(interpolator);
		}
		else
			if (ui.radioButton_BCO->isChecked())
			{
				qDebug() << "succes04";
				typedef otb::BCOInterpolateImageFunction<VectorImageType> InterpolatorType;
				InterpolatorType::Pointer interpolator = InterpolatorType::New();
				m_ResampleFilter->SetInterpolator(interpolator);
			}

	// Set Output information
	m_ResampleFilter->SetOutputSize(genericRSEstimator->GetOutputSize());
	m_ResampleFilter->SetOutputSpacing(genericRSEstimator->GetOutputSpacing());
	m_ResampleFilter->SetOutputOrigin(genericRSEstimator->GetOutputOrigin());

	// Build the default pixel
	VectorImageType::PixelType defaultValue;
	itk::NumericTraits<VectorImageType::PixelType>::SetLength(defaultValue, readerPan->GetOutput()->GetNumberOfComponentsPerPixel());
	m_ResampleFilter->SetEdgePaddingValue(defaultValue);

	writer->SetInput(m_ResampleFilter->GetOutput());
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject& excep)
	{

		return;

	}
	qDebug() << "succes0";
}

void Tools::NDVI_run()
{
	typedef double  PixelType;
	typedef otb::VectorImage<PixelType, 2>  InputImageType;
	typedef otb::Image<PixelType, 2>  OutputImageType;
	typedef otb::ImageList<OutputImageType>  ImageListType;
	typedef otb::VectorImageToImageListFilter<InputImageType, ImageListType> VectorImageToImageListType;
	typedef otb::ImageFileReader<InputImageType>  ReaderType;
	typedef otb::ImageFileWriter<OutputImageType> WriterType;
	//We can now define the type for the filter :
	typedef otb::BandMathImageFilter<OutputImageType>  FilterType;
	//We instantiate the filter, the reader, and the writer :
	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();
	FilterType::Pointer filter = FilterType::New();
	reader->SetFileName(ui.lineEdit_Input->text().toStdString());
	writer->SetFileName(ui.lineEdit_Output->text().toStdString());
	//We need now to extract now each band from the input otb::VectorImage, it illustrates the use of the otb::VectorImageToImageList.Each extracted layer are inputs of the otb::BandMathImageFilter :
	VectorImageToImageListType::Pointer imageList = VectorImageToImageListType::New();
	imageList->SetInput(reader->GetOutput());
	imageList->UpdateOutputInformation();
	{
		double Blue = ui.spinBox_Blue->value();
		filter->SetNthInput(Blue, imageList->GetOutput()->GetNthElement(Blue));

		double Green = ui.spinBox_Green->value();
		filter->SetNthInput(Green, imageList->GetOutput()->GetNthElement(Green));

		double Red = ui.spinBox_Red->value();
		filter->SetNthInput(Red, imageList->GetOutput()->GetNthElement(Red));

		double NIR = ui.spinBox_NIR->value();
		filter->SetNthInput(NIR, imageList->GetOutput()->GetNthElement(NIR));
	}
	//Now we can define the mathematical expression to perform on the layers(b1, b2, b3, b4).The filter takes advantage of the parsing capabilities of the muParser library and allows setting the expression as on a digital calculator.
	//The expression below returns 255 if the ratio(NIR - RED) / (NIR + RED) is greater than 0.4 and 0 if not.
	filter->SetExpression("if((NIR-Red)/(NIR+Red) > 0.4, 255, 0)");

	//#ifdef OTB_MUPARSER_HAS_CXX_LOGICAL_OPERATORS
	//filter->SetExpression("((NIR-Red)/(NIR+Red) > 0.4) ? 255 : 0");
	//#else
	//filter->SetExpression("if((NIR-Red)/(NIR+Red) > 0.4, 255, 0)");
	//#endif
	writer->SetInput(filter->GetOutput());
	writer->Update();
}

void Tools::NDWI_run()
{
	typedef double  PixelType;
	typedef otb::VectorImage<PixelType, 2>  InputImageType;
	typedef otb::Image<PixelType, 2>  OutputImageType;
	typedef otb::ImageList<OutputImageType>  ImageListType;
	typedef otb::VectorImageToImageListFilter<InputImageType, ImageListType> VectorImageToImageListType;
	typedef otb::ImageFileReader<InputImageType>  ReaderType;
	typedef otb::ImageFileWriter<OutputImageType> WriterType;
	//We can now define the type for the filter :
	typedef otb::BandMathImageFilter<OutputImageType>  FilterType;
	//We instantiate the filter, the reader, and the writer :
	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();
	FilterType::Pointer filter = FilterType::New();
	reader->SetFileName(ui.lineEdit_Input->text().toStdString());
	writer->SetFileName(ui.lineEdit_Output->text().toStdString());
	//We need now to extract now each band from the input otb::VectorImage, it illustrates the use of the otb::VectorImageToImageList.Each extracted layer are inputs of the otb::BandMathImageFilter :
	VectorImageToImageListType::Pointer imageList = VectorImageToImageListType::New();
	imageList->SetInput(reader->GetOutput());
	imageList->UpdateOutputInformation();
	{
		double Blue = ui.spinBox_Blue->value();
		filter->SetNthInput(Blue, imageList->GetOutput()->GetNthElement(Blue));

		double Green = ui.spinBox_Green->value();
		filter->SetNthInput(Green, imageList->GetOutput()->GetNthElement(Green));

		double Red = ui.spinBox_Red->value();
		filter->SetNthInput(Red, imageList->GetOutput()->GetNthElement(Red));

		double NIR = ui.spinBox_NIR->value();
		filter->SetNthInput(NIR, imageList->GetOutput()->GetNthElement(NIR));
	}
	//Now we can define the mathematical expression to perform on the layers(b1, b2, b3, b4).The filter takes advantage of the parsing capabilities of the muParser library and allows setting the expression as on a digital calculator.
	//The expression below returns 255 if the ratio(Green - NIR) / (Green - NIR ) is greater than 0.4 and 0 if not.
	filter->SetExpression("if((Green - NIR) / (Green - NIR ) > 0.4, 255, 0)");

	//#ifdef OTB_MUPARSER_HAS_CXX_LOGICAL_OPERATORS
	//filter->SetExpression("((Green - NIR) / (Green - NIR ) ? 255 : 0");
	//#else
	//filter->SetExpression("if((Green - NIR) / (Green - NIR ) > 0.4, 255, 0)");
	//#endif
	writer->SetInput(filter->GetOutput());
	writer->Update();
}

void Tools::SHADOW_run()
{
	typedef double  PixelType;
	typedef otb::VectorImage<PixelType, 2>  InputImageType;
	typedef otb::Image<PixelType, 2>  OutputImageType;
	typedef otb::ImageList<OutputImageType>  ImageListType;
	typedef otb::VectorImageToImageListFilter<InputImageType, ImageListType> VectorImageToImageListType;
	typedef otb::ImageFileReader<InputImageType>  ReaderType;
	typedef otb::ImageFileWriter<OutputImageType> WriterType;
	//We can now define the type for the filter :
	typedef otb::BandMathImageFilter<OutputImageType>  FilterType;
	//We instantiate the filter, the reader, and the writer :
	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();
	FilterType::Pointer filter = FilterType::New();
	reader->SetFileName(ui.lineEdit_Input->text().toStdString());
	writer->SetFileName(ui.lineEdit_Output->text().toStdString());
	//We need now to extract now each band from the input otb::VectorImage, it illustrates the use of the otb::VectorImageToImageList.Each extracted layer are inputs of the otb::BandMathImageFilter :
	VectorImageToImageListType::Pointer imageList = VectorImageToImageListType::New();
	imageList->SetInput(reader->GetOutput());
	imageList->UpdateOutputInformation();
	{
		double Blue = ui.spinBox_Blue->value();
		filter->SetNthInput(Blue, imageList->GetOutput()->GetNthElement(Blue));

		double Green = ui.spinBox_Green->value();
		filter->SetNthInput(Green, imageList->GetOutput()->GetNthElement(Green));

		double Red = ui.spinBox_Red->value();
		filter->SetNthInput(Red, imageList->GetOutput()->GetNthElement(Red));

		double NIR = ui.spinBox_NIR->value();
		filter->SetNthInput(NIR, imageList->GetOutput()->GetNthElement(NIR));
	}
	//Now we can define the mathematical expression to perform on the layers(b1, b2, b3, b4).The filter takes advantage of the parsing capabilities of the muParser library and allows setting the expression as on a digital calculator.
	//The expression below returns 255 if the ratio(Green - NIR) / (Green - NIR ) is greater than 0.4 and 0 if not.
	filter->SetExpression("if((Green - NIR) / (Green - NIR ) > 0.4, 255, 0)");

	//#ifdef OTB_MUPARSER_HAS_CXX_LOGICAL_OPERATORS
	//filter->SetExpression("((Green - NIR) / (Green - NIR ) ? 255 : 0");
	//#else
	//filter->SetExpression("if((Green - NIR) / (Green - NIR ) > 0.4, 255, 0)");
	//#endif
	writer->SetInput(filter->GetOutput());
	writer->Update();
}

void Tools::on_pushButton_Execute_clicked()
{
	if (ui.radioButton_calcule->isChecked())
	{

	}
	if (ui.radioButton_binair->isChecked())
	{

	}
	if (ui.radioButton_remove->isChecked())
	{

	}
}

void Tools::on_pushButton_exit_clicked()
{
	exit(1);
}

