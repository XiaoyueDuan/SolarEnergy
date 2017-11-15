#include <iostream>  
#include <QtGui/QMouseEvent> 
#include <QtMath>

#include "scenewindow.h" 

SceneWindow::SceneWindow(QWidget *parent)
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
	setFocusPolicy(Qt::StrongFocus); //��Ӧ����
	setCursor(cursor);
	//init the texture
	textures_stone = nullptr;
	texture_skybox = nullptr;
	//init the helio param
	initHelioParam();

}

SceneWindow::~SceneWindow()
{
	if (textures_stone)
		delete textures_stone;
	if (texture_skybox)
		delete texture_skybox;
	if (texture_grassland)
		delete texture_grassland;
}

void SceneWindow::initializeGL()
{
	//��ʼ��OpenGL����  
	initializeOpenGLFunctions();
	//����ȫ�ֱ���  
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	initShader();
	initVAO();
	initTexture();
	glContext = QOpenGLContext::currentContext();
	glFuncs = glContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
	if (!glFuncs) {
		qWarning() << "Could not obtain required OpenGL context version";
		exit(1);
	}
	// ���� mesh����
	modelObj.loadModel("Resources/rock/rock.obj", glFuncs);
	//modelObj.loadModel("./Resources/nanosuit/nanosuit.obj", glFuncs);

	/* �̶��������� */
	glEnable(GL_DEPTH_TEST);        //������Ȳ��� 

}

void SceneWindow::paintGL()
{
	//������Ļ  
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//ʵ�ֲ�����ˢ��  
	update();
	float width = this->width();
	float height = this->height();
	glDepthMask(GL_FALSE); // ��ֹд����Ȼ�����
	QMatrix4x4 view;
	QMatrix4x4 projection;
	view = camera.GetViewMatrix();
	projection.perspective(camera.Zoom, width/height, 1.0f, 100000.0f);

	//��Ⱦskybox  
	texture_skybox->bind();
	shaderSky.bind();
	QMatrix4x4 model;
	model.scale(QVector3D(100000, 100000, 100000));
	shaderCube.setUniformValue("view", view);
	shaderCube.setUniformValue("projection", projection);
	shaderCube.setUniformValue("model", model);
	glBindVertexArray(IDVAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE); // ��ֹд����Ȼ�����

	//��Ⱦcube
	textures_stone->bind();
	shaderCube.bind();
	view = camera.GetViewMatrix();
	QMatrix4x4 modelCube;
	modelCube.translate(QVector3D(0.0f, 100.0f, 0.0f));
	shaderCube.setUniformValue("view", view);
	shaderCube.setUniformValue("projection", projection);
	shaderCube.setUniformValue("model", modelCube);
	glBindVertexArray(IDVAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//��Ⱦ����
	texture_grassland->bind();
	shaderLand.bind();
	QMatrix4x4 model3;
	model3.scale(100000, 1.0, 100000);
	shaderCube.setUniformValue("view", view);
	shaderCube.setUniformValue("projection", projection);
	shaderCube.setUniformValue("model", model3);
	glBindVertexArray(IDVAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	//������  
	shaderCoor.bind();
	QMatrix4x4 modelCoor1;
	modelCoor1.setToIdentity();
	modelCoor1.translate(QVector3D(-0.8f, -0.8f, -0.8f));
	modelCoor1 *= camera.GetRotated();
	shaderCoor.setUniformValue("model", modelCoor1);
	glBindVertexArray(IDVAO[2]);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);

	//���ƶ��վ�
	textures_metal->bind();
	shaderCube.bind();
	shaderCube.setUniformValue("view", view);
	shaderCube.setUniformValue("projection", projection);
	glBindVertexArray(IDVAO[0]);
	for (size_t i = 0; i < helio.helioNum; i++) {
		QMatrix4x4 modelCube;
		modelCube.translate(helio.pos[i]);
		modelCube.scale(helio.geo[i]);
		shaderCube.setUniformValue("model", modelCube);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);

	//����mehs�ṹ
	shaderMesh.bind();
	QMatrix4x4 modelMesh;
	shaderMesh.setUniformValue("view", view);
	shaderMesh.setUniformValue("projection", projection);
	shaderMesh.setUniformValue("model", modelMesh);
	modelObj.Draw(shaderMesh);

	//ǿ��ˢ�»���������֤���ִ��  
	glFlush();
}

void SceneWindow::resizeGL(int width, int height)
{
	/*Q_UNUSED(width);
	Q_UNUSED(height);*/
	glViewport(0, 0, width, height);
}

void SceneWindow::initHelioParam() {
	helio.helioNum = 3;
	helio.pos.push_back(QVector3D(100, 3, 0));
	helio.geo.push_back(QVector3D(3, 1, 1));
	helio.norm.push_back(QVector3D(1, 0, 0));

	helio.pos.push_back(QVector3D(200, 3, 0));
	helio.geo.push_back(QVector3D(1, 2, 1));
	helio.norm.push_back(QVector3D(0, 1, 0));

	helio.pos.push_back(QVector3D(300, 3, 0));
	helio.geo.push_back(QVector3D(1, 1, 2));
	helio.norm.push_back(QVector3D(0, 0, 1));



}

void SceneWindow::mouseMoveEvent(QMouseEvent *event)
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
		camera.ProcessMouseMovement(xoffset, yoffset);  //�������offset
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
		camera.ProcessKeyboard(LEFT, xoffset);
		camera.ProcessKeyboard(UP, yoffset);
	}
}
//����ʵ�ֶ�����ķŴ���С
void SceneWindow::wheelEvent(QWheelEvent *event)
{
	GLfloat sensitivity = 0.005f;
	camera.ProcessMouseScroll(event->delta() * sensitivity);
}

void SceneWindow::mousePressEvent(QMouseEvent *event)
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

void SceneWindow::mouseReleaseEvent(QMouseEvent *event)
{
	//���ù����״  
	cursor.setShape(Qt::ArrowCursor);
	setCursor(cursor);
}

void SceneWindow::keyPressEvent(QKeyEvent *event)
{
	float velocity = 0.1f;
	if (event->key() == Qt::Key_W) {
		camera.ProcessKeyboard(FORWARD, velocity);
	}
	else if (event->key() == Qt::Key_S) {
		camera.ProcessKeyboard(BACKWARD, velocity);
	}
	else if (event->key() == Qt::Key_A) {
		camera.ProcessKeyboard(LEFT, velocity);
	}
	else if (event->key() == Qt::Key_D) {
		camera.ProcessKeyboard(RIGHT, velocity);
	}
	else if (event->key() == Qt::Key_Q) {
		camera.ProcessKeyboard(UP, velocity);
	}
	else if (event->key() == Qt::Key_E) {
		camera.ProcessKeyboard(DOWN, velocity);
	}
}

void SceneWindow::initShader() {
	//��ʼ����������ɫ������
	shaderCube.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/simple.vert");
	shaderCube.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/simple.frag");
	shaderCube.link();
	//sky
	shaderSky.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/skybox.vert");
	shaderSky.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/skybox.frag");
	shaderSky.link();
	//land
	shaderLand.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/land.vert");
	shaderLand.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/land.frag");
	shaderLand.link();

	//��ʼ��������ɫ������
	shaderCoor.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/coordinate.vert");
	shaderCoor.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/coordinate.frag");
	shaderCoor.link();

	//��ʼ��mesh����
	shaderMesh.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/model_loading.vert");
	shaderMesh.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/model_loading.frag");
	shaderMesh.link();
}

void SceneWindow::initVAO() {
	//��ʼ��VAO VBO EBO
	IDVAO.resize(NumVAOGw);
	IDVBO.resize(NumVBOGw);
	IDEBO.resize(NumEBOGw);
	/******************************** ���ö������� ********************************/
	//������������������� ��ͬ���ò�ͬ��������˲���ҪEBO
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	GLfloat landVertices[] = {
		-1.0f, 0.0f, -1.0f,  0.0f, 1.0f,
		1.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		-1.0f, 0.0f,  1.0f,  0.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,  0.0f, 1.0f
	};
	//������������  
	GLfloat coorVertices[] = {
		0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.1f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.1f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  0.0f,  0.1f, 0.0f, 0.0f, 1.0f
	};
	// VAO��VBO
	/* ������ض��� */
	glGenVertexArrays(NumVAOGw, &IDVAO[0]);
	glGenBuffers(NumVBOGw, &IDVBO[0]);
	/* ������ */
	glBindVertexArray(IDVAO[0]);  //��ʼ��¼״̬��Ϣ  
	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*  ����ƽ��  */
	glBindVertexArray(IDVAO[1]);  //��ʼ��¼״̬��Ϣ  
	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(landVertices), landVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* ��ʾ������Ϣ */
	glBindVertexArray(IDVAO[2]);    //��ʼ��¼״̬��Ϣ  
	glBindBuffer(GL_ARRAY_BUFFER, IDVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coorVertices), coorVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);           //������¼״̬��Ϣ  


}

void SceneWindow::initTexture() {
	//���������Ϣ 
	textures_stone = new QOpenGLTexture(QImage(QString(":/Resources/images/stone1.jpg")).mirrored());
	textures_metal = new QOpenGLTexture(QImage(QString(":/Resources/images/metal.png")).mirrored());
	texture_grassland = new QOpenGLTexture(QImage(QString(":/Resources/images/grassland.jpg")).mirrored());
	texture_grassland->generateMipMaps();
	texture_grassland->setWrapMode(QOpenGLTexture::MirroredRepeat);
	texture_grassland->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_grassland->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
	//��պ�����
	// Load all skybox texture images
	const QImage posx = QImage(":/Resources/images/skybox/posx.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	const QImage posy = QImage(":/Resources/images/skybox/posy.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	const QImage posz = QImage(":/Resources/images/skybox/posz.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	const QImage negx = QImage(":/Resources/images/skybox/negx.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	const QImage negy = QImage(":/Resources/images/skybox/negy.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	const QImage negz = QImage(":/Resources/images/skybox/negz.jpg").mirrored().convertToFormat(QImage::Format_RGBA8888);
	texture_skybox = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
	texture_skybox->create();
	texture_skybox->setSize(posx.width(), posx.height(), posx.depth());
	texture_skybox->setFormat(QOpenGLTexture::SRGB_BP_UNorm);
	texture_skybox->allocateStorage();
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)posx.constBits(), 0);
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)posy.constBits(), 0);
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)posz.constBits(), 0);
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)negx.constBits(), 0);
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)negy.constBits(), 0);
	texture_skybox->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
		QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
		(const void*)negz.constBits(), 0);
	texture_skybox->generateMipMaps();
	texture_skybox->setWrapMode(QOpenGLTexture::ClampToEdge);
	texture_skybox->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_skybox->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
}