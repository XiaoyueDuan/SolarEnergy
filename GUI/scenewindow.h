#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <vector>
#include <QOpenGLShaderProgram>

class SceneWindow : public QOpenGLWidget,
	protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	SceneWindow(QWidget *parent = 0);
	~SceneWindow();

	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:

	QCursor cursor; // ��������״
	//���λ�ü�������������ViewMatrix�����С�����ռ䡱�����۲�ռ䡱��ת�� 
	QVector3D cameraPos = QVector3D(0.0f, 0.0f, 3.0f);    //���λ��
	QVector3D worldCentrol = QVector3D(0.0f, 0.0f, 0.0f); //��������ԭ�㣬�������
	QVector3D cameraUp = QVector3D(0.0f, 1.0f, 0.0f);     //����Ķ�������y��
	QVector3D transVec = QVector3D(0.0f, 0.0f, 0.0f);     //�ֲ����������������е�ƽ����(����ModelMatrix�����С��ֲ��ռ䡱��������ռ䡱��ת��)

	GLfloat yaw = 0.0f;       //ƫ����  
	GLfloat pitch = 0.0f;     //������  
	GLfloat lastX = 0;        //����ϴ�xֵ  
	GLfloat lastY = 0;        //����ϴ�yֵ  

	/*******************************************************************************
	* ��ɫ������ɫ������VAO������������󣩡�VBO�����㻺����󣩡�EBO(�����������)
	******************************************************************************/
	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderCoor;
	GLuint NumVAOGw = 2;                //VAO����Ŀ  
	GLuint NumVBOGw = 2;                //VBO����Ŀ  
	GLuint NumEBOGw = 1;                //EBO����Ŀ  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;

};