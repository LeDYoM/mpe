#ifndef OPENGLMANAGER_H
#define OPENGLMANAGER_H

#include <QMatrix4x4>

class QOpenGLContext;
class QOpenGLFunctions;
class RenderBuffer;
class Material;

class OpenGLUser
{
public :
    OpenGLUser() {}
    virtual ~OpenGLUser() {}

    static void setContext(QOpenGLContext *context);
    static inline QOpenGLContext *__context() { return _context; }
    static inline QOpenGLFunctions *glFunctions() { return _openGLFunctions; }
private:
    static QOpenGLContext *_context;
    static QOpenGLFunctions *_openGLFunctions;
};

#endif // OPENGLMANAGER_H
