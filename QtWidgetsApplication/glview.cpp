#include "glview.h"
#include <fstream>
#include <GL/glu.h>

unsigned int VAO, VBO;
unsigned int shaderProgram;

float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
};

GLview::GLview(QWidget *parent): QOpenGLWidget(parent)
{
	//initializeGL();
}

GLview::~GLview()
{}

void GLview::onDataImport()
{
	std::ifstream fin("C:\\Users\\Y05895\\Desktop\\3D�ۺ�����.asc");
	if (!fin)
	{
		return;
	}
	while (!fin.eof())
	{

	}

}

void GLview::initializeGL()
{
	//step 1.��ʼ����ָ��OpenGL����.
	initializeOpenGLFunctions();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glColor3f(0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0);

	
}

void GLview::resizeGL(int w, int h)
{
}

void drawCube()
{
	glBegin(GL_POINTS);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
}

void GLview::paintGL()
{

	//�����ɫ����
	//glClear(GL_COLOR_BUFFER_BIT);


	////��OpenGL�ӿںʹ��ڱ�����ͬ
	//glViewport(0, 0, width(), height());

	////����ģ�͹۲����
	////glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glScalef(zoom, zoom, zoom);

	////Ϊ����ʾ����޸ĵ��Ĭ�ϴ�С
	//glPointSize(3.0f);

	////���������ģʽ

	//glBegin(GL_POINTS);
	//{
	//	//std::ifstream fin("C:\\Users\\Y05895\\Desktop\\3D�ۺ�����.txt");
	//	//if (fin)
	//	{
	//		glVertex3f(0.0, 0.0, 0.0);
	//		glVertex3f(0.0, 1.0, 0.0);
	//		glVertex3f(0.0, 2.0, 0.0);
	//		glVertex3f(0.0, 3.0, 0.0);

	//		glVertex3f(0.0, 0.0, 0.0);
	//		glVertex3f(1.0, 0.0, 0.0);
	//		glVertex3f(2.0, 0.0, 0.0);
	//		glVertex3f(3.0, 0.0, 0.0);

	//		//glColor3f(1, 0, 0);
	//		glVertex3f(0.0, 0.0, 0.0);
	//		glVertex3f(-1.0, 0.0, 0.0);
	//		glVertex3f(-2.0, 0.0, 0.0);
	//		glVertex3f(-3.0, 0.0, 0.0);

	//		glVertex3f(0.0, 0.0, 0.0);
	//		glVertex3f(0.0, -1.0, 0.0);
	//		glVertex3f(0.0, -2.0, 0.0);
	//		glVertex3f(0.0, -3.0, 0.0);
	//	}

	//	//fin.close();
	//}
	////��������
	//glEnd();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(zoom, zoom, zoom);

	//Ϊ����ʾ����޸ĵ��Ĭ�ϴ�С
	glPointSize(3.0f);
	glPushMatrix();
	glMultMatrixf(m_transform.constData());
	drawCube();
	//glBegin(GL_POINTS);
	//{

	//	{
	//		
	//		glVertex3f(0.0, -3.0, 0.0);
	//	}

	//}
	//��������
	glEnd();
	glPopMatrix();
}

void GLview::rotate(int dx, int dy)
{
	m_rotation.setX(m_rotation.x() + dy);
	m_rotation.setY(m_rotation.y() + dx);

	QQuaternion xRot = QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x());//x��y��z�������ת�Ƕ�
	QQuaternion yRot = QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y());
	m_transform.setToIdentity();
	m_transform.translate(m_translation);
	m_transform.rotate(xRot * yRot);
}

void GLview::translate(int dx, int dy)
{
	m_translation.setX(m_translation.x() + dx * 0.01);
	m_translation.setY(m_translation.y() - dy * 0.01);
	//���任��������Ϊ��λ����
	m_transform.setToIdentity();
	//��������ƽ�Ƶ���ȷ��λ��
	m_transform.translate(m_translation);
	//����ת�任����Ӧ�õ�m_transform��
	m_transform.rotate(QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x()));
	m_transform.rotate(QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y()));
}


void GLview::mouseMoveEvent(QMouseEvent * event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) 
	{
		rotate(dx, dy);
	}
	else if (event->buttons() & Qt::RightButton) 
	{
		translate(dx, dy);
	}

	m_lastPos = event->pos();
	update();
}

void GLview::mousePressEvent(QMouseEvent * event)
{
	m_lastPos = event->pos();
}

void GLview::wheelEvent(QWheelEvent * event)
{
	int dir = event->delta() > 0 ? 1 : -1;

	float lastZoom = zoom;

	//���ݹ��ַ������Ŵ���
	(dir > 0) ? (zoom *= (1 + 0.1f)) : (zoom *= (1 - 0.1f));

	if (zoom > 100.0f || zoom < 0.1f)
		zoom = lastZoom;

	//����ͬʱ����ƽ��
	/*translation.x -= (zoom / lastZoom - 1.0f) * ((2.0f * x - width) /
		width - translation.x);

	translation.y += (zoom / lastZoom - 1.0f) * ((2.0f * y - height) /
		height + translation.y);

	if (deviceContext)
		render();


	cursor.x = x;
	cursor.y = y;

	zoom = renderer.getZoom();*/

	update();
}
