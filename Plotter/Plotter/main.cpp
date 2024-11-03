#include <QApplication>
#include "plotter.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    Plotter w;
	w.show();
	return app.exec();
}
