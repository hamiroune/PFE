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
#include <QtWidgets/QMainWindow>
#include "ui_Window.h"

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);

private:
	Ui::WindowClass ui;
	public slots :
		 
	QString on_actionInput_PAN_Image_clicked();
	QString on_actionInput_XS_Image_clicked();

	void on_actionTo_leave_Ctrl_Q_clicked();
	void on_action_preference_clicked();
	QString on_actionOutput_Image_clicked();
	
};
