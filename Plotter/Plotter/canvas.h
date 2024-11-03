#ifndef CANVAS_H
#define CANVAS_H
#include <QFrame>

class Canvas : public QFrame
{
	Q_OBJECT

public:
	Canvas(QWidget *parent = 0);
	~Canvas();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void setWorld(const QPointF &min, const QPointF &max);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event);



	QPoint  WC_to_DC(const QPointF &wc);
	QPointF DC_to_WC(const QPoint  &dc);

private:
    QPointF wMin, wMax;
    QPoint lastMousePosition;
    bool mousePressed;
};

#endif // CANVAS_H
