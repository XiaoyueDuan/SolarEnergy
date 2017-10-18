#pragma once

#include <QtWidgets/QOpenGLWidget>  
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <vector>
// opengl help function
#include <QOpenGLShaderProgram>


//OpenGL Mathematics ����������ѧ�任  
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
	QCursor cursor; // ��������״
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

	QOpenGLShaderProgram shaderCube;
	QOpenGLShaderProgram shaderCoor;
	GLuint NumVAOGw = 2;                //VAO����Ŀ  
	GLuint NumVBOGw = 2;                //VBO����Ŀ  
	GLuint NumEBOGw = 1;                //EBO����Ŀ  
	std::vector<GLuint> IDVAO;
	std::vector<GLuint> IDVBO;
	std::vector<GLuint> IDEBO;

};