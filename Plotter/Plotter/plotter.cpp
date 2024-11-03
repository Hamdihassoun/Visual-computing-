#include <QPushButton> 
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "plotter.h"
#include "canvas.h"

#define MAX_WIDTH 180

/** c'tor */
Plotter::Plotter(QWidget *parent)
	: QWidget(parent)
{
	// instantiate Canvas and button
	viewport = new Canvas();
    btnDrawFunc = new QPushButton("&Draw Function");

	// instantiate elements for setting world window
    ledMinX = new QLineEdit("-20");
    ledMinX->setMaximumWidth(MAX_WIDTH);
	lblMinX = new QLabel("World MinX");
	lblMinX->setBuddy(ledMinX);

    ledMinY = new QLineEdit("-20");
    ledMinY->setMaximumWidth(MAX_WIDTH);
	lblMinY = new QLabel("World MinY");
	lblMinY->setBuddy(ledMinY);

    ledMaxX = new QLineEdit("20");
    ledMaxX->setMaximumWidth(MAX_WIDTH);
	lblMaxX = new QLabel("World MaxX");
	lblMaxX->setBuddy(ledMaxX);

    ledMaxY = new QLineEdit("20");
    ledMaxY->setMaximumWidth(MAX_WIDTH);
	lblMaxY = new QLabel("World MaxY");
	lblMaxY->setBuddy(ledMaxY);

	// create layout and add gui elements to it
	QGridLayout *mainLayout = new QGridLayout;

	mainLayout->addWidget(viewport, 0, 0, 1, 3);
    mainLayout->addWidget(btnDrawFunc, 1, 0);
    mainLayout->addWidget(lblMinX, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(ledMinX, 1, 2);
    mainLayout->addWidget(lblMinY, 2, 1, Qt::AlignRight);
    mainLayout->addWidget(ledMinY, 2, 2);
    mainLayout->addWidget(lblMaxX, 3, 1, Qt::AlignRight);
    mainLayout->addWidget(ledMaxX, 3, 2);
    mainLayout->addWidget(lblMaxY, 4, 1, Qt::AlignRight);
    mainLayout->addWidget(ledMaxY, 4, 2);

	// add layout to this widget instance
	setLayout(mainLayout);

    // update world dimensions as initialized in textfields
    drawBtnPressed();
	
	// connect button click event to draw handler
    connect(btnDrawFunc, SIGNAL(clicked()), this, SLOT(drawBtnPressed()));
}

/** d'tor */
Plotter::~Plotter()
{
}

/** method for handling button clicked event */
void Plotter::drawBtnPressed()
{
	QPointF min, max;

	min.setX(ledMinX->text().toFloat());
	min.setY(ledMinY->text().toFloat());

	max.setX(ledMaxX->text().toFloat());
	max.setY(ledMaxY->text().toFloat());

	// update world window in canvas instance
	viewport->setWorld(min, max);

	// force redraw
	update();
}
