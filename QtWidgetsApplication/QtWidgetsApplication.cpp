#include "QtWidgetsApplication.h"

QtWidgetsApplication::QtWidgetsApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	QObject::connect(ui.FileImport, SIGNAL(triggered()), ui.openGLWidget, SLOT(onDataImport()));
}

QtWidgetsApplication::~QtWidgetsApplication()
{
}
