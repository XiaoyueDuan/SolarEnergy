#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions> 
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <vector>
#include "camera.h"
#include "model.h"

struct HelioDes {
	int helioNum;
	std::vector<QVector3D> pos;
	std::vector<QVector3D> geo;
	std::vector<QVector3D> norm;
};




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
	void initHelioParam();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	//init function
	void initShader();
	void initVAO();
	void initTexture();


private:
	//opengl �� context
	QOpenGLContext *glContext;
	QOpenGLFunctions_3_3_Core *glFuncs;
	Model modelObj;

	QCursor cursor; // ��������״
	GLfloat lastX = 0;        //����ϴ�xֵ  
	GLfloat lastY = 0;        //����ϴ�yֵ  
	Camera camera; //camera function

				   //��ɫ����������
	QOpenGLShaderProgram shaderSky;
	QOpenGLShaderProgram shaderLand;
	QOpenGLShaderProgram shaderCoor;
	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderMesh;

	GLuint NumVAOGw = 3;                //VAO����Ŀ  
	GLuint NumVBOGw = 3;                //VBO����Ŀ  
	GLuint NumEBOGw = 0;                //EBO����Ŀ  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;
	//����
	QOpenGLTexture *texture_grassland;
	QOpenGLTexture *texture_skybox;
	QOpenGLTexture *textures_stone;
	QOpenGLTexture *textures_metal;
	//vector
	HelioDes helio;

};