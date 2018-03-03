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
#include "ui_preference.h"

class preference : public QWidget
{
	Q_OBJECT

public:
	preference(QWidget *parent = Q_NULLPTR);
	~preference();

private:
	Ui::preference ui;
	public slots:

	void on_checkBox_linear_checked();
	void on_checkBox_nneighbor_checked();
	void on_checkBox_BCO_checked();
	void on_checkBox_DEM_Folder_checked();
	void on_checkBox_Default_elivation_checked();
	void on_checkBox_Rcs_checked();
	void on_checkBox_Lmvm_checked();
	void on_toolButton_DEM_clicked();

};
