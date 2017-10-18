#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <vector>
// opengl help function
#include "shader_s.h"
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
	QCursor cursor; // 管理光标形状
	/*******************************************************************************
	* 鼠标操作的一些设置
	******************************************************************************/

	//相机位置及朝向，用来构造ViewMatrix，进行“世界空间”到“观察空间”的转换  
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);   //相机位置  
	glm::vec3 worldCentrol = glm::vec3(0.0f, 0.0f, 0.0f);   //世界坐标原点，相机始终朝向这个方向  
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);   //相机的顶部始终朝向y轴  

														//构建ModelMatrix，进行“局部空间”到“世界空间”的转换  
	glm::vec3 transVec = glm::vec3(0.0f, 0.0f, 0.0f);   //局部坐标在世界坐标中的平移量  

	GLfloat yaw = 0.0f;       //偏航角  
	GLfloat pitch = 0.0f;     //俯仰角  
	GLfloat lastX = 0;        //光标上次x值  
	GLfloat lastY = 0;        //光标上次y值  

	/*******************************************************************************
	* 着色器、着色器程序、VAO（顶点数组对象）、VBO（顶点缓冲对象）、EBO(索引缓冲对象)
	******************************************************************************/

	Shader shaderCube;
	Shader shaderCoor;
	GLuint NumVAOGw = 2;                //VAO的数目  
	GLuint NumVBOGw = 2;                //VBO的数目  
	GLuint NumEBOGw = 1;                //EBO的数目  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;

	/*******************************************************************************
	* 着色器源码
	******************************************************************************/
	const GLchar *vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 1) in vec3 vColor;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec3 Color;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view * model * vec4(vPosition, 1.0);\n"
		"Color = vColor;\n"
		"}\n";

	const GLchar *fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 Color;\n"
		"out vec4 fColor;\n"
		"void main()\n"
		"{\n"
		"fColor = vec4(Color, 1.0f);\n"
		"}\n";

	const GLchar *vertexShaderSource1 =         //绘制三维坐标  
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 1) in vec3 vColor;\n"
		"out vec3 Color;\n"
		"uniform mat4 modelCoor;\n"
		"uniform mat4 viewCoor;\n"
		"uniform mat4 projectionCoor;\n"
		"void main()\n"
		"{\n"
		"Color = vColor;\n"
		"gl_Position = projectionCoor * viewCoor * modelCoor * vec4(vPosition, 1.0);\n"
		"}\n";

};