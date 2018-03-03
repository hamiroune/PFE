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
#include "ui_Radiometrics.h"

class Radiometrics : public QWidget
{
	Q_OBJECT

public:
	Radiometrics(QWidget *parent = Q_NULLPTR);
	~Radiometrics();

private:
	Ui::Radiometrics ui;
};
