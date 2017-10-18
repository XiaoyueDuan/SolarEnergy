#include <iostream>  
#include <QtGui/QMouseEvent> 

#include "scenewindow.h" 

SceneWindow::SceneWindow(QWidget *parent)
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

SceneWindow::~SceneWindow()
{

}

void SceneWindow::initializeGL()
{
	//初始化OpenGL函数  
	initializeOpenGLFunctions();
	//设置全局变量  
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	//初始化立方体着色器程序
	shaderCube.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/simple.vert");
	shaderCube.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/simple.frag");
	shaderCube.link();
	//初始化坐标着色器程序
	shaderCoor.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/coordinate.vert");
	//shaderCoor.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource1);
	shaderCoor.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/simple.frag");
	shaderCoor.link();

	//初始化VAO VBO EBO
	IDVAO.resize(NumVAOGw);
	IDVBO.resize(NumVBOGw);
	IDEBO.resize(NumEBOGw);

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
	glGenVertexArrays(NumVAOGw, &IDVAO[0]);
	glGenBuffers(NumVBOGw, &IDVBO[0]);
	glGenBuffers(NumEBOGw, &IDEBO[0]);

	/* 显示立方体 */
	glBindVertexArray(IDVAO[0]);  //开始记录状态信息  
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
	

	/* 固定属性区域 */
	glEnable(GL_DEPTH_TEST);        //开启深度测试 


}

void SceneWindow::paintGL()
{
	//清理屏幕  
	glClear(GL_COLOR_BUFFER_BIT);

	//实现参数的刷新  
	update();

	//渲染彩色正方体  
	shaderCube.bind();

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	GLint modelLoc = shaderCube.uniformLocation("model");
	GLint viewLoc = shaderCube.uniformLocation("view");
	GLint projLoc = shaderCube.uniformLocation("projection");
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

	//画坐标  
	shaderCoor.bind();
	glm::mat4 viewCoor;
	glm::mat4 projectionCoor;
	glm::mat4 modelCoor;
	GLint modelCoorLoc = shaderCoor.uniformLocation("modelCoor");
	GLint viewCoorLoc = shaderCoor.uniformLocation("viewCoor");
	GLint projCoorLoc = shaderCoor.uniformLocation("projectionCoor");

	viewCoor = glm::lookAt(cameraPos, worldCentrol, cameraUp);
	projectionCoor = glm::perspective(glm::radians(45.0f), 5.0f / 3.0f, 0.1f, 100000.0f);
	//modelCoor = glm::translate(modelCoor, glm::vec3(-0.38f, -0.28f, glm::length(cameraPos) - 0.8f));  
	modelCoor = glm::translate(modelCoor, glm::vec3(-0.48f, -0.28f, glm::length(cameraPos) - 0.8f));
	modelCoor = glm::rotate(modelCoor, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	modelCoor = glm::rotate(modelCoor, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(viewCoorLoc, 1, GL_FALSE, glm::value_ptr(viewCoor));
	//glUniformMatrix4fv(projCoorLoc, 1, GL_FALSE, glm::value_ptr(projectionCoor));
	//glUniformMatrix4fv(modelCoorLoc, 1, GL_FALSE, glm::value_ptr(modelCoor));
	

	QMatrix4x4 viewCoor1;
	QMatrix4x4 projectionCoor1;
	QMatrix4x4 modelCoor1;
	viewCoor1.lookAt(cameraPos1, worldCentrol1, cameraUp1);
	projectionCoor1.perspective(45.0f, 5.0f / 3.0f,0.1f,100000.0f);
	//modelCoor1.translate(QVector3D(-0.48f, -0.28f, cameraPos1.length()-0.8f));
	modelCoor1.setToIdentity();
	modelCoor1.translate(QVector3D(-0.48f, -0.28f, cameraPos1.length() - 0.8f));
	modelCoor1.rotate(pitch, 1.0f, 0.0f, 0.0f);
	modelCoor1.rotate(yaw, 0.0f, 1.0f, 0.0f);

	shaderCoor.setUniformValue("viewCoor", viewCoor1);
	shaderCoor.setUniformValue("projectionCoor", projectionCoor1);
	shaderCoor.setUniformValue("modelCoor", modelCoor1);


	glBindVertexArray(IDVAO[1]);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);

	//强制刷新缓冲区，保证命令被执行  
	glFlush();
}

void SceneWindow::resizeGL(int width, int height)
{
	//未使用  
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void SceneWindow::mouseMoveEvent(QMouseEvent *event)
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
void SceneWindow::wheelEvent(QWheelEvent *event)
{
	GLfloat sensitivity = 0.0005f;
	cameraPos *= (1.0f - event->delta() * sensitivity);
	cameraPos1 *= (1.0f - event->delta() * sensitivity);
}

void SceneWindow::mousePressEvent(QMouseEvent *event)
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

void SceneWindow::mouseReleaseEvent(QMouseEvent *event)
{
	//设置光标形状  
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);
}