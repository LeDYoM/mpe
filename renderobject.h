#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "opengluser.h"
#include "memm.h"
#include "buffertype.h"
#include <vector>

class Shader;
class BufferData;
class QOpenGLBuffer;
class RenderBuffer;
class Material;
class QMatrix4x4;
class QOpenGLVertexArrayObject;

class AttributeBinder : public OpenGLUser
{
public:
    AttributeBinder(ptr<BufferData> data,ptr<Shader> shader ,BufferType bufferType);
    virtual ~AttributeBinder();
private:
    ptr<QOpenGLBuffer> buffer{nullptr};
};

class RenderObject : public OpenGLUser
{
public:
    RenderObject(ptr<RenderBuffer> rBuffer, ptr<Material> material);
    virtual ~RenderObject();

    void render(const QMatrix4x4 *projectionMatrix);
private:
    std::vector<ptr<AttributeBinder>> bindings;
    ptr<RenderBuffer> _rBuffer{nullptr};
    ptr<Material> _material{nullptr};
    ptr<QOpenGLVertexArrayObject> _vao{nullptr};
    int _vertexCount{0};
};

#endif // RENDEROBJECT_H
