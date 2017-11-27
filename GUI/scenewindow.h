#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions>  
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <vector>
#include "camera.h"
#include "model.h"

#include "convert_type.h"
#include "../ClassedSunRay/solar_scene.h"

struct CubeDes {
	int number;
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
	void initReceHelioParam();

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
	//the context of the opengl
	QOpenGLContext *glContext;
	QOpenGLFunctions_3_3_Core *glFuncs;
	//store the model
	Model modelObj;

	Camera camera;		 //camera function
	QCursor cursor;      // cusor shape
	GLfloat lastX = 0;   // the cursor last x position 
	GLfloat lastY = 0;   // the cursor last y position 

	//shader program
	QOpenGLShaderProgram shaderSky;
	QOpenGLShaderProgram shaderLand;
	QOpenGLShaderProgram shaderCoor;
	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderMesh;

	GLuint numVAO = 3;     //VAO number 
	GLuint numVBO = 3;     //VBO number 
	GLuint numEBO = 0;     //EBO number  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;
	//texture
	QOpenGLTexture *texture_grassland;
	QOpenGLTexture *texture_skybox;
	QOpenGLTexture *textures_stone;
	QOpenGLTexture *textures_metal;
	//vector
	CubeDes helioDes;
	CubeDes receDes;

};