#include "preference.h"

preference::preference(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

preference::~preference()
{
}
void preference::on_toolButton_DEM_clicked()
{
	QString name = QFileDialog::getOpenFileName(this, "kkkk", "");
	ui.lineEdit_DEM->setText(name);
}