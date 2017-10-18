#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <vector>
// opengl help function
#include <QOpenGLShaderProgram>


//OpenGL Mathematics 用来进行数学变换  
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>  

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
	
	//相机位置及朝向，用来构造ViewMatrix，进行“世界空间”到“观察空间”的转换  
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);   //相机位置  
	glm::vec3 worldCentrol = glm::vec3(0.0f, 0.0f, 0.0f);   //世界坐标原点，相机始终朝向这个方向  
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);   //相机的顶部始终朝向y轴   
	glm::vec3 transVec = glm::vec3(0.0f, 0.0f, 0.0f);   //局部坐标在世界坐标中的平移量(构建ModelMatrix，进行“局部空间”到“世界空间”的转换)

	QCursor cursor; // 管理光标形状
	//相机位置及朝向，用来构造ViewMatrix，进行“世界空间”到“观察空间”的转换 
	QVector3D cameraPos1 = QVector3D(0.0f, 0.0f, 3.0f);    //相机位置
	QVector3D worldCentrol1 = QVector3D(0.0f, 0.0f, 0.0f); //世界坐标原点，相机朝向
	QVector3D cameraUp1 = QVector3D(0.0f, 1.0f, 0.0f);     //相机的顶部朝向y轴
	QVector3D transVec1 = QVector3D(0.0f, 0.0f, 0.0f);     //局部坐标在世界坐标中的平移量(构建ModelMatrix，进行“局部空间”到“世界空间”的转换)

	GLfloat yaw = 0.0f;       //偏航角  
	GLfloat pitch = 0.0f;     //俯仰角  
	GLfloat lastX = 0;        //光标上次x值  
	GLfloat lastY = 0;        //光标上次y值  

	/*******************************************************************************
	* 着色器、着色器程序、VAO（顶点数组对象）、VBO（顶点缓冲对象）、EBO(索引缓冲对象)
	******************************************************************************/

	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderCoor;
	GLuint NumVAOGw = 2;                //VAO的数目  
	GLuint NumVBOGw = 2;                //VBO的数目  
	GLuint NumEBOGw = 1;                //EBO的数目  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;

};