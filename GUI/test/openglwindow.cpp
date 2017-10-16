#include "openglwindow.h"  
#include <iostream>  
#include <QtGui/QMouseEvent> 

//OpenGL Mathematics 用来进行数学变换  
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>  

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

const GLuint NumVertexShader = 2;       //顶点着色器的数目  
const GLuint NumFragmentShader = 1;     //片段着色器的数目  
const GLuint NumShaderProgram = 2;      //着色器程序的数目  
const GLuint NumVAO = 2;                //VAO的数目  
const GLuint NumVBO = 2;                //VBO的数目  
const GLuint NumEBO = 1;                //EBO的数目  

GLuint IDVertexShader[NumVertexShader];
GLuint IDFragmentShader[NumFragmentShader];
GLuint IDShaderProgram[NumShaderProgram];
GLuint IDVAO[NumVAO];
GLuint IDVBO[NumVBO];
GLuint IDEBO[NumEBO];

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


openglwindow::openglwindow(QWidget *parent)
	:QOpenGLWidget(parent)
{
	//设置OpenGL的版本信息  
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3, 3);
	setFormat(format);
	// 设置光标形状
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);


}

openglwindow::~openglwindow()
{

}

void openglwindow::initializeGL()
{
	//初始化OpenGL函数  
	initializeOpenGLFunctions();

	//设置全局变量  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/******************************* 顶点着色器创建 *******************************/
	/* 第一个顶点着色器 */
	IDVertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(IDVertexShader[0], 1, &vertexShaderSource, nullptr);
	glCompileShader(IDVertexShader[0]);
	//检查编译是否出错  
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(IDVertexShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDVertexShader[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/******************************* 片段着色器创建 *******************************/
	/* 第一个片元着色器 */
	IDFragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(IDFragmentShader[0], 1, &fragmentShaderSource, nullptr);
	glCompileShader(IDFragmentShader[0]);
	//检查编译是否出错  
	glGetShaderiv(IDFragmentShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDFragmentShader[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/********************************* 链接着色器 *********************************/
	/* 第一个着色器程序 */
	IDShaderProgram[0] = glCreateProgram();
	glAttachShader(IDShaderProgram[0], IDVertexShader[0]);
	glAttachShader(IDShaderProgram[0], IDFragmentShader[0]);
	glLinkProgram(IDShaderProgram[0]);
	//检查链接错误  
	glGetProgramiv(IDShaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(IDShaderProgram[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/* 第二个顶点着色器 */
	IDVertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(IDVertexShader[1], 1, &vertexShaderSource1, nullptr);
	glCompileShader(IDVertexShader[1]);
	//检查编译是否出错  
	glGetShaderiv(IDVertexShader[1], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDVertexShader[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* 第二个着色器程序 */
	IDShaderProgram[1] = glCreateProgram();
	glAttachShader(IDShaderProgram[1], IDVertexShader[1]);
	glAttachShader(IDShaderProgram[1], IDFragmentShader[0]);
	glLinkProgram(IDShaderProgram[1]);
	//检查链接错误  
	glGetProgramiv(IDShaderProgram[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(IDShaderProgram[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//删除着色器对象（生成着色器程序之后不再需要）  
	glDeleteShader(IDVertexShader[0]);
	glDeleteShader(IDVertexShader[1]);
	glDeleteShader(IDFragmentShader[0]);

	/******************************** 设置顶点数据 ********************************/
	//彩色正方体  
	GLfloat vertices[] =
	{
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 0.8f, 0.5f, 0.2f,
		-0.5f,  0.5f, -0.5f, 0.2f, 0.8f, 0.5f
	};
	GLuint indices[] =
	{
		0, 1, 2, 2, 3, 0,   //前  
		4, 5, 6, 6, 7, 4,   //后  
		0, 4, 7, 7, 3, 0,   //左  
		1, 5, 6, 6, 2, 1,   //右  
		0, 4, 5, 5, 1, 0,   //上  
		3, 7, 6, 6, 2, 3    //下  
	};

	//绘制坐标数据  
	GLfloat coorVertices[] =
	{
		0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.05f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.05f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  0.0f,  0.05f, 0.0f, 0.0f, 1.0f
	};

	/****************************************************************************/
	/**************************** VAO\VBO\顶点属性指针 ****************************/
	/****************************************************************************/

	/* 创建相关对象 */
	glGenVertexArrays(NumVAO, IDVAO);
	glGenBuffers(NumVBO, IDVBO);
	glGenBuffers(NumEBO, IDEBO);

	/* 显示立方体 */
	glBindVertexArray(IDVAO[0]);    //开始记录状态信息  

	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IDEBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);           //结束记录状态信息  
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   //在VAO后解绑，是为了不让VAO把解绑EBO的信息包含进入  
	/* 显示立方体 */

										
	/* 显示坐标信息 */
	glBindVertexArray(IDVAO[1]);    //开始记录状态信息  

	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coorVertices), coorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);           //结束记录状态信息  
	/* 坐标 */

	/* 固定属性区域 */
	glEnable(GL_DEPTH_TEST);        //开启深度测试 


}

void openglwindow::paintGL()
{
	//清理屏幕  
	glClear(GL_COLOR_BUFFER_BIT);

	//实现参数的刷新  
	update();

	//渲染彩色正方体  
	glUseProgram(IDShaderProgram[0]);

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(IDShaderProgram[0], "model");
	GLint viewLoc = glGetUniformLocation(IDShaderProgram[0], "view");
	GLint projLoc = glGetUniformLocation(IDShaderProgram[0], "projection");
	view = glm::lookAt(cameraPos, worldCentrol, cameraUp);
	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100000.0f);
	model = glm::translate(model, transVec);
	model = glm::rotate(model, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));   //按住左键，上下拖动鼠标让立方体绕x轴旋转  
	model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));     //按住左键，左右拖动鼠标让立方体绕y轴旋转  
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(IDVAO[0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//渲染立方体
	//画坐标  
	glUseProgram(IDShaderProgram[1]);

	glm::mat4 viewCoor;
	glm::mat4 projectionCoor;
	glm::mat4 modelCoor;
	GLint modelCoorLoc = glGetUniformLocation(IDShaderProgram[1], "modelCoor");
	GLint viewCoorLoc = glGetUniformLocation(IDShaderProgram[1], "viewCoor");
	GLint projCoorLoc = glGetUniformLocation(IDShaderProgram[1], "projectionCoor");
	viewCoor = glm::lookAt(cameraPos, worldCentrol, cameraUp);
	projectionCoor = glm::perspective(glm::radians(45.0f), 5.0f / 3.0f, 0.1f, 100000.0f);
	//modelCoor = glm::translate(modelCoor, glm::vec3(-0.38f, -0.28f, glm::length(cameraPos) - 0.8f));  
	modelCoor = glm::translate(modelCoor, glm::vec3(-0.48f, -0.28f, glm::length(cameraPos) - 0.8f));
	modelCoor = glm::rotate(modelCoor, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	modelCoor = glm::rotate(modelCoor, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewCoorLoc, 1, GL_FALSE, glm::value_ptr(viewCoor));
	glUniformMatrix4fv(projCoorLoc, 1, GL_FALSE, glm::value_ptr(projectionCoor));
	glUniformMatrix4fv(modelCoorLoc, 1, GL_FALSE, glm::value_ptr(modelCoor));
	glBindVertexArray(IDVAO[1]);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);




	//强制刷新缓冲区，保证命令被执行  
	glFlush();
}

void openglwindow::resizeGL(int width, int height)
{
	//未使用  
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void openglwindow::mouseMoveEvent(QMouseEvent *event)
{
	//鼠标左键用来实现对物体的旋转功能  
	if (event->buttons() == Qt::LeftButton)
	{
		//设置光标形状  
		cursor.setShape(Qt::ClosedHandCursor);
		setCursor(cursor);
		//计算yaw,pitch值的改变量  
		GLfloat xoffset = event->x() - lastX;
		GLfloat yoffset = event->y() - lastY;
		lastX = event->x();
		lastY = event->y();

		GLfloat sensitivity = 0.4f;     //旋转时的灵敏度  
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		//可以用来设置俯仰角的上下界  
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	//鼠标右键用来实现对移动物体（即局部坐标在世界坐标中的移动）  
	else if (event->buttons() == Qt::RightButton)
	{
		//计算x,y方向的偏移量  
		GLfloat xoffset = event->x() - lastX;
		GLfloat yoffset = event->y() - lastY;
		lastX = event->x();
		lastY = event->y();

		GLfloat sensitivity = 0.01f;    //移动时的灵敏度  
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		//仅需在x-y平面内移动即可  
		transVec += glm::vec3(xoffset, -yoffset, 0.0f);
	}
}

//滚轮实现对物体的放大缩小，摄像机距离远近（放大缩小）  
void openglwindow::wheelEvent(QWheelEvent *event)
{
	GLfloat sensitivity = 0.0005f;
	cameraPos *= (1.0f - event->delta() * sensitivity);
}

void openglwindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//设置光标形状  
		cursor.setShape(Qt::PointingHandCursor);
		setCursor(cursor);
	}
	else if (event->button() == Qt::RightButton)
	{
		//设置光标形状  
		cursor.setShape(Qt::SizeAllCursor);
		setCursor(cursor);
	}
	//记录点击光标时的位置  
	lastX = event->x();
	lastY = event->y();
}

void openglwindow::mouseReleaseEvent(QMouseEvent *event)
{
	//设置光标形状  
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);
}