#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class Canvas;

class Plotter : public QWidget
{
	Q_OBJECT

public:
	Plotter(QWidget *parent = 0);
	~Plotter();

private slots:
	void drawBtnPressed();

private:
	Canvas *viewport;

    QPushButton *btnDrawFunc;
	QLabel *lblMinX;
	QLabel *lblMaxX;
	QLabel *lblMinY;
	QLabel *lblMaxY;
	QLineEdit *ledMinX;
	QLineEdit *ledMaxX;
	QLineEdit *ledMinY;
	QLineEdit *ledMaxY;
};

#endif // PLOTTER_H
