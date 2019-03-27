#include "QtPluginRollup.h"

QtPluginRollup::QtPluginRollup(QWidget* /*parent*/)
	: QMaxParamBlockWidget()
	, ui(new Ui::PluginRollup())
{
	// At a minimum, we must call setupUi(). Other initialization can happen here.
	ui->setupUi(this);
}

// This is a widget that is not wired to a paramblock. It can still be used via the Qt Signal/Slot mechanism.
void QtPluginRollup::QtPluginRollup::on_pushButton_clicked()
{
	// We can access all the functionality in QtCore and QtGui, such as using various
	// dialogs.
	QMessageBox::information(this, "Hi", "Button pushed.");
}

QtPluginRollup::~QtPluginRollup()
{
	delete ui;
	ui = nullptr;
}
