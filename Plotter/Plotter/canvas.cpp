#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QMouseEvent>
#include <QWidget>
#include "canvas.h"

Canvas::Canvas(QWidget *parent)
	: QFrame(parent),
	  wMin(0, 0), wMax(1, 1)
{
	setFrameStyle(QFrame::Box);

}

Canvas::~Canvas()
{
}

QSize Canvas::minimumSizeHint() const
{
	return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
	return QSize(640, 480);
}

void Canvas::setWorld(const QPointF &min, const QPointF &max)
{
	wMin.rx() = min.x();
	wMin.ry() = min.y();

	wMax.rx() = max.x();
	wMax.ry() = max.y();
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);	// draws black border

    QPainter painter(this);
    QPainterPath pp,path;

    // first draw white background
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);

    // TODO; implement the following drawing functionality!
    // draw axis of abscissas (as given in world coords)
    // finally draw the function (also given in world coords)
    painter.setPen(Qt::black);
    painter.drawLine(WC_to_DC(QPointF(wMin.x(), 0)), WC_to_DC(QPointF(wMax.x(), 0))); // x-Achse
    painter.drawLine(WC_to_DC(QPointF(0, wMin.y())), WC_to_DC(QPointF(0, wMax.y()))); // y-Achse

    // Sinus-Funktion
    float xMin = -M_PI, xMax = M_PI;
    float dx = (xMax - xMin) / 100000.0;
    float x = xMin;
    float y = sin(x);

    // Startpunkt  Sinuskurve
    pp.moveTo(WC_to_DC(QPointF(x, y)));

    for (int i = 1; i <= 100000; ++i) {
        x += dx;
        y = sin(x);
        pp.lineTo(WC_to_DC(QPointF(x, y)));
    }

    //  zeichnen
    painter.setPen(Qt::black);
    painter.drawPath(pp);


    //Herzkurve

    float tMax = 2 * M_PI;
    int steps = 1000000;
    float dt = tMax / steps;

    // Startpunkt  Herzkurve
    float t = 0.0;
    float x_herz = 16 * std::pow(std::sin(t), 3);
    float y_herz = 13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t);
    path.moveTo(WC_to_DC(QPointF(x_herz, y_herz)));

    for (int i = 1; i <= steps; ++i) {
        t += dt;
        x_herz = 16 * std::pow(std::sin(t), 3);
        y_herz = 13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t);
        path.lineTo(WC_to_DC(QPointF(x_herz, y_herz)));
    }

    painter.fillPath(path, QColor(255, 181, 192));

    //  zeichnen
    painter.setPen(Qt::blue);
    painter.drawPath(path);
    painter.drawPath(pp);
    if (mousePressed) {
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);
        painter.drawEllipse(lastMousePosition, 5, 5);

    }

}
void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
        mousePressed = true;
        update();
    }
}
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed) {
        lastMousePosition = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        mousePressed = false;
        update();
    }
}


QPoint Canvas::WC_to_DC(const QPointF &wc)
{
	float wx0 = wMin.x(), 
		  wx1 = wMax.x(), 
		  wy0 = wMin.y(), 
		  wy1 = wMax.y();


	// TODO; calculate window-viewport transformation for point (x, y)!
    //größe der bildschirm
    int dx0 = 0, dx1 = width();
    int dy0 = height(), dy1 = 0;

    // Transformation berechnen
    int x = dx0 + (wc.x() - wx0) * (dx1 - dx0) / (wx1 - wx0);
    int y = dy0 + (wc.y() - wy0) * (dy1 - dy0) / (wy1 - wy0);



	return QPoint(x, y);
}



QPointF Canvas::DC_to_WC(const QPoint &dc)
{
	// TODO; calculate inverse transform (optional)

    float wx0 = wMin.x(), wx1 = wMax.x();
    float wy0 = wMin.y(), wy1 = wMax.y();

    // Bildschirmgröß
    int dx0 = 0, dx1 = width();
    int dy0 = height(), dy1 = 0;

    // Inverse Transformation berechnen
    float x = wx0 + (dc.x() - dx0) * (wx1 - wx0) / (dx1 - dx0);
    float y = wy0 + (dc.y() - dy0) * (wy1 - wy0) / (dy1 - dy0);
    return QPointF(x, y);
}
