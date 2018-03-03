#pragma once
#include <QtWidgets>
#include <QtGui>
#include <Qfile>
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbSimpleRcsPanSharpeningFusionImageFilter.h"
#include "otbLmvmPanSharpeningFusionImageFilter.h"
#include "otbPrintableImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "otbImageToVectorImageCastFilter.h"
#include "otbBayesianFusionFilter.h"
#include "otbImage.h"
#include "itkCastImageFilter.h"
#include "otbMultiChannelExtractROI.h"
#include "otbVectorRescaleIntensityImageFilter.h"
#include "otbMultiToMonoChannelExtractROI.h"
#include "otbGenericRSResampleImageFilter.h"
#include "otbBCOInterpolateImageFunction.h"
#include "otbOrthoRectificationFilter.h"
#include "otbMapProjections.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include <QWidget>
#include "ui_Tools.h"

class Tools : public QWidget
{
	Q_OBJECT

public:
	Tools(QWidget *parent = Q_NULLPTR);
	~Tools();

private:
	Ui::Tools ui;
	public slots:
	void on_pushButton_exit_clicked();
	void on_pushButton_Execute_clicked();
	void on_checkBox_Pansharpening_checked();
	void on_checkBox_Orthorectification_checked();
	void on_checkBox_NDVI_checked();
	void on_checkBox_NDWI_checked();
	void on_checkBox_SHADOW_checked();
	void on_checkBox_MeanShift_checked();
	void Pansharpening_run();
	void Orthorectification_run();
	void NDVI_run();
	void NDWI_run();
	void SHADOW_run();
};
