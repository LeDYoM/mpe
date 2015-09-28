#ifndef OPENGLUSER_H
#define OPENGLUSER_H

class QOpenGLContext;
class QOpenGLFunctions;

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

#endif // OPENGLUSER_H
