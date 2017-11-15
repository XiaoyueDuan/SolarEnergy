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
	//opengl 的 context
	QOpenGLContext *glContext;
	QOpenGLFunctions_3_3_Core *glFuncs;
	Model modelObj;

	QCursor cursor; // 管理光标形状
	GLfloat lastX = 0;        //光标上次x值  
	GLfloat lastY = 0;        //光标上次y值  
	Camera camera; //camera function

				   //着色器交互程序
	QOpenGLShaderProgram shaderSky;
	QOpenGLShaderProgram shaderLand;
	QOpenGLShaderProgram shaderCoor;
	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderMesh;

	GLuint NumVAOGw = 3;                //VAO的数目  
	GLuint NumVBOGw = 3;                //VBO的数目  
	GLuint NumEBOGw = 0;                //EBO的数目  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;
	//纹理
	QOpenGLTexture *texture_grassland;
	QOpenGLTexture *texture_skybox;
	QOpenGLTexture *textures_stone;
	QOpenGLTexture *textures_metal;
	//vector
	HelioDes helio;

};