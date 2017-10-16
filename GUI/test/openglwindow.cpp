#include "openglwindow.h"  
#include <iostream>  
#include <QtGui/QMouseEvent> 

//OpenGL Mathematics ����������ѧ�任  
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>  

/*******************************************************************************
* ��������һЩ����
******************************************************************************/

//���λ�ü�������������ViewMatrix�����С�����ռ䡱�����۲�ռ䡱��ת��  
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);   //���λ��  
glm::vec3 worldCentrol = glm::vec3(0.0f, 0.0f, 0.0f);   //��������ԭ�㣬���ʼ�ճ����������  
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);   //����Ķ���ʼ�ճ���y��  

													//����ModelMatrix�����С��ֲ��ռ䡱��������ռ䡱��ת��  
glm::vec3 transVec = glm::vec3(0.0f, 0.0f, 0.0f);   //�ֲ����������������е�ƽ����  

GLfloat yaw = 0.0f;       //ƫ����  
GLfloat pitch = 0.0f;     //������  
GLfloat lastX = 0;        //����ϴ�xֵ  
GLfloat lastY = 0;        //����ϴ�yֵ  


						/*******************************************************************************
						* ��ɫ������ɫ������VAO������������󣩡�VBO�����㻺����󣩡�EBO(�����������)
						******************************************************************************/

const GLuint NumVertexShader = 2;       //������ɫ������Ŀ  
const GLuint NumFragmentShader = 1;     //Ƭ����ɫ������Ŀ  
const GLuint NumShaderProgram = 2;      //��ɫ���������Ŀ  
const GLuint NumVAO = 2;                //VAO����Ŀ  
const GLuint NumVBO = 2;                //VBO����Ŀ  
const GLuint NumEBO = 1;                //EBO����Ŀ  

GLuint IDVertexShader[NumVertexShader];
GLuint IDFragmentShader[NumFragmentShader];
GLuint IDShaderProgram[NumShaderProgram];
GLuint IDVAO[NumVAO];
GLuint IDVBO[NumVBO];
GLuint IDEBO[NumEBO];

/*******************************************************************************
* ��ɫ��Դ��
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

const GLchar *vertexShaderSource1 =         //������ά����  
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
	//����OpenGL�İ汾��Ϣ  
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3, 3);
	setFormat(format);
	// ���ù����״
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);


}

openglwindow::~openglwindow()
{

}

void openglwindow::initializeGL()
{
	//��ʼ��OpenGL����  
	initializeOpenGLFunctions();

	//����ȫ�ֱ���  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/******************************* ������ɫ������ *******************************/
	/* ��һ��������ɫ�� */
	IDVertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(IDVertexShader[0], 1, &vertexShaderSource, nullptr);
	glCompileShader(IDVertexShader[0]);
	//�������Ƿ����  
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(IDVertexShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDVertexShader[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/******************************* Ƭ����ɫ������ *******************************/
	/* ��һ��ƬԪ��ɫ�� */
	IDFragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(IDFragmentShader[0], 1, &fragmentShaderSource, nullptr);
	glCompileShader(IDFragmentShader[0]);
	//�������Ƿ����  
	glGetShaderiv(IDFragmentShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDFragmentShader[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/********************************* ������ɫ�� *********************************/
	/* ��һ����ɫ������ */
	IDShaderProgram[0] = glCreateProgram();
	glAttachShader(IDShaderProgram[0], IDVertexShader[0]);
	glAttachShader(IDShaderProgram[0], IDFragmentShader[0]);
	glLinkProgram(IDShaderProgram[0]);
	//������Ӵ���  
	glGetProgramiv(IDShaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(IDShaderProgram[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/* �ڶ���������ɫ�� */
	IDVertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(IDVertexShader[1], 1, &vertexShaderSource1, nullptr);
	glCompileShader(IDVertexShader[1]);
	//�������Ƿ����  
	glGetShaderiv(IDVertexShader[1], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(IDVertexShader[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* �ڶ�����ɫ������ */
	IDShaderProgram[1] = glCreateProgram();
	glAttachShader(IDShaderProgram[1], IDVertexShader[1]);
	glAttachShader(IDShaderProgram[1], IDFragmentShader[0]);
	glLinkProgram(IDShaderProgram[1]);
	//������Ӵ���  
	glGetProgramiv(IDShaderProgram[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(IDShaderProgram[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//ɾ����ɫ������������ɫ������֮������Ҫ��  
	glDeleteShader(IDVertexShader[0]);
	glDeleteShader(IDVertexShader[1]);
	glDeleteShader(IDFragmentShader[0]);

	/******************************** ���ö������� ********************************/
	//��ɫ������  
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
		0, 1, 2, 2, 3, 0,   //ǰ  
		4, 5, 6, 6, 7, 4,   //��  
		0, 4, 7, 7, 3, 0,   //��  
		1, 5, 6, 6, 2, 1,   //��  
		0, 4, 5, 5, 1, 0,   //��  
		3, 7, 6, 6, 2, 3    //��  
	};

	//������������  
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
	/**************************** VAO\VBO\��������ָ�� ****************************/
	/****************************************************************************/

	/* ������ض��� */
	glGenVertexArrays(NumVAO, IDVAO);
	glGenBuffers(NumVBO, IDVBO);
	glGenBuffers(NumEBO, IDEBO);

	/* ��ʾ������ */
	glBindVertexArray(IDVAO[0]);    //��ʼ��¼״̬��Ϣ  

	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IDEBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);           //������¼״̬��Ϣ  
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   //��VAO������Ϊ�˲���VAO�ѽ��EBO����Ϣ��������  
	/* ��ʾ������ */

										
	/* ��ʾ������Ϣ */
	glBindVertexArray(IDVAO[1]);    //��ʼ��¼״̬��Ϣ  

	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coorVertices), coorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);           //������¼״̬��Ϣ  
	/* ���� */

	/* �̶��������� */
	glEnable(GL_DEPTH_TEST);        //������Ȳ��� 


}

void openglwindow::paintGL()
{
	//������Ļ  
	glClear(GL_COLOR_BUFFER_BIT);

	//ʵ�ֲ�����ˢ��  
	update();

	//��Ⱦ��ɫ������  
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
	model = glm::rotate(model, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));   //��ס����������϶��������������x����ת  
	model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));     //��ס����������϶��������������y����ת  
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(IDVAO[0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//��Ⱦ������
	//������  
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




	//ǿ��ˢ�»���������֤���ִ��  
	glFlush();
}

void openglwindow::resizeGL(int width, int height)
{
	//δʹ��  
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void openglwindow::mouseMoveEvent(QMouseEvent *event)
{
	//����������ʵ�ֶ��������ת����  
	if (event->buttons() == Qt::LeftButton)
	{
		//���ù����״  
		cursor.setShape(Qt::ClosedHandCursor);
		setCursor(cursor);
		//����yaw,pitchֵ�ĸı���  
		GLfloat xoffset = event->x() - lastX;
		GLfloat yoffset = event->y() - lastY;
		lastX = event->x();
		lastY = event->y();

		GLfloat sensitivity = 0.4f;     //��תʱ��������  
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		//�����������ø����ǵ����½�  
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	//����Ҽ�����ʵ�ֶ��ƶ����壨���ֲ����������������е��ƶ���  
	else if (event->buttons() == Qt::RightButton)
	{
		//����x,y�����ƫ����  
		GLfloat xoffset = event->x() - lastX;
		GLfloat yoffset = event->y() - lastY;
		lastX = event->x();
		lastY = event->y();

		GLfloat sensitivity = 0.01f;    //�ƶ�ʱ��������  
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		//������x-yƽ�����ƶ�����  
		transVec += glm::vec3(xoffset, -yoffset, 0.0f);
	}
}

//����ʵ�ֶ�����ķŴ���С�����������Զ�����Ŵ���С��  
void openglwindow::wheelEvent(QWheelEvent *event)
{
	GLfloat sensitivity = 0.0005f;
	cameraPos *= (1.0f - event->delta() * sensitivity);
}

void openglwindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//���ù����״  
		cursor.setShape(Qt::PointingHandCursor);
		setCursor(cursor);
	}
	else if (event->button() == Qt::RightButton)
	{
		//���ù����״  
		cursor.setShape(Qt::SizeAllCursor);
		setCursor(cursor);
	}
	//��¼������ʱ��λ��  
	lastX = event->x();
	lastY = event->y();
}

void openglwindow::mouseReleaseEvent(QMouseEvent *event)
{
	//���ù����״  
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);
}