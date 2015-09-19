#ifndef MPEGLWIDGET_H
#define MPEGLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QTimer>

#include "openglmanager.h"

class MaterialManager;

class MPEGLWidget : public QOpenGLWidget, public OpenGLUser
{
    Q_OBJECT
public:
    explicit MPEGLWidget(QWidget *parent = 0);
    virtual ~MPEGLWidget();
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h) override;
    virtual void paintGL() override;
    virtual void destroyGL();

    inline MaterialManager *materialManager() const { return _materialManager; }
private:
    void updateFps();
    QMatrix4x4 m_projection;
    MaterialManager *_materialManager{nullptr};
    unsigned int m_frame{0};
    unsigned int m_fps_frame{0};
    unsigned int last_fps{0};
    QTimer _fpsTimer;
};

#endif // MPEGLWIDGET_H
