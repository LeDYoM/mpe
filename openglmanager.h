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

class Renderer : public OpenGLUser
{
public:
    inline Renderer() {}
    virtual ~Renderer() {}

    void render(Material *material,RenderBuffer *rBuffer);
    void render2(Material *material,RenderBuffer *rBuffer);
    inline void setProjectionMatrix(const QMatrix4x4 *projectionMatrix) { _projectionMatrix = projectionMatrix; }
private:
    const QMatrix4x4 *_projectionMatrix{nullptr};
};

#endif // OPENGLMANAGER_H
