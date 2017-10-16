#ifndef OPENGLWINDOW_H  
#define OPENGLWINDOW_H  

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions_3_3_Core>  

class openglwindow : public QOpenGLWidget,
	protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	openglwindow(QWidget *parent = 0);
	~openglwindow();

	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QCursor cursor; // 管理光标形状


};

#endif // OPENGLWINDOW_H 