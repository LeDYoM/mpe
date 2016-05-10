#include "mpeglwidget.h"
#include "log.h"
#include "mpeopenglcontext.hpp"
#include <QOpenGLFunctions>

MPEGLWidget::MPEGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat fmt(QSurfaceFormat::defaultFormat());
//    fmt.setVersion(4,0);
//    fmt.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(fmt);
}

MPEGLWidget::~MPEGLWidget()
{
}

void MPEGLWidget::initializeGL()
{
    MPEOpenGLContext::setContext(QOpenGLWidget::context());
    QOpenGLFunctions *f = glFunctions();

    DEBUG_MESSAGE("-----------------------------------------------------------");
    DEBUG_MESSAGE("Created OpenGL context:");
    DEBUG_MESSAGE("Window OpenGl: " << QOpenGLWidget::context()->format().majorVersion() << "." << format().minorVersion());
    DEBUG_MESSAGE("Context valid: " << QOpenGLWidget::context()->isValid());
    DEBUG_MESSAGE("Really used OpenGl: " << QOpenGLWidget::context()->format());
    DEBUG_MESSAGE("Is Core profile: " << (QOpenGLWidget::context()->format().profile() == QSurfaceFormat::CoreProfile));
    DEBUG_MESSAGE("OpenGl information: VENDOR:       " << (const char*)f->glGetString(GL_VENDOR));
    DEBUG_MESSAGE("                    RENDERDER:    " << (const char*)f->glGetString(GL_RENDERER));
    DEBUG_MESSAGE("                    VERSION:      " << (const char*)f->glGetString(GL_VERSION));
    DEBUG_MESSAGE("                    GLSL VERSION: " << (const char*)f->glGetString(GL_SHADING_LANGUAGE_VERSION));

    connect(QOpenGLWidget::context(), &QOpenGLContext::aboutToBeDestroyed, this, &MPEGLWidget::destroyGL);

    f->glClearColor(1.0f, .0f, 1.0f, 1.0f);
}

void MPEGLWidget::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings:
//    m_projection.setToIdentity();
//    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

    const qreal retinaScale = 1;
    glFunctions()->glViewport(0, 0, 640 * retinaScale, 480 * retinaScale);

    glFunctions()->glClear(GL_COLOR_BUFFER_BIT);

    m_projection.setToIdentity();
    m_projection.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    m_projection.translate(0, 0, -2);
    m_projection.rotate(100.0f * m_frame / 60, 0, 1, 0);
}

void MPEGLWidget::paintGL()
{
    ++m_frame;

    // Draw the scene:
    glFunctions()->glClear(GL_COLOR_BUFFER_BIT);

    updateFps();
    update();
}

void MPEGLWidget::destroyGL()
{
}

void MPEGLWidget::updateFps()
{
    ++m_frame;
    ++m_fps_frame;

    if (_fpsTimer.remainingTime() < 1)
    {
        last_fps = m_fps_frame;
        m_fps_frame = 0;
        DEBUG_MESSAGE("Hey"<<last_fps);
        _fpsTimer.start(1000);
    }
}
