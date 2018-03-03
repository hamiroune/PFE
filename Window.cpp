#include "Window.h"
#include "preference.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
QString Window::on_actionInput_PAN_Image_clicked()
{
	QString name = QFileDialog::getOpenFileName(this, "kkkk", "");
	return name;
}
QString Window::on_actionInput_XS_Image_clicked()
{
	QString name = QFileDialog::getOpenFileName(this, "kkkk", "");
	return name;
}

void Window::on_actionTo_leave_Ctrl_Q_clicked()
{//appele d'une fenetre pour enregister l'image
	exit(1);
}
void Window::on_action_preference_clicked() 
{
	preference p;
	p.show();
}
QString Window::on_actionOutput_Image_clicked()
{
	QString name = QFileDialog::getOpenFileName(this, "kkkk", "");
	return name;
}
