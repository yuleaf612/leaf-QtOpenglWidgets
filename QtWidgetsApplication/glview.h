#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <QtOpenGL>


class GLview  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	GLview(QWidget *parent);
	~GLview();

public slots:
	void onDataImport();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	//void resizeEvent(QResizeEvent *event) override;
	//void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	//void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	/*void leaveEvent(QEvent *event) override;
	void timerEvent(QTimerEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void exportedGIF();
	std::function<void(const bool &)> enableControlsFunction = 0;
	bool init = false;
	std::function<void()> showNormalFunction = 0;*/
	float zoom = 1.0f;
	QPoint m_lastPos;
	QVector3D m_rotation;
	QVector3D m_translation;
	QMatrix4x4 m_transform;

private:
	void rotate(int dx, int dy);
	void translate(int dx, int dy);
};
