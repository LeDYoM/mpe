#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "openglmanager.h"

#include <QVector3D>
#include <QColor>

#include <unordered_map>
#include <string>
#include <vector>
#include "memm.h"
#include "buffertype.h"

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class Material;
class QOpenGLShaderProgram;

class BufferData
{
public:
    inline BufferData(int tupleSize,const std::vector<float> &data):_tupleSize{tupleSize},_data{data} { }
    inline int tupleSize() const { return _tupleSize; }
    inline int numElements() const { return _data.size() / _tupleSize; }
    inline const std::vector<float> &data() const { return _data; }
private:
    int _tupleSize;
    std::vector<float> _data;
};

class RenderBuffer : public OpenGLUser
{
public:
    RenderBuffer();
    virtual ~RenderBuffer();
    void setPositionsBuffer(const std::vector<QVector3D> &data);
    void setColorsBuffer(const std::vector<QColor> &data);
    void setColorsBuffer(const std::vector<QVector4D> &data);
    void setColorsBuffer(const std::vector<QVector3D> &data);
    void setNormalsBuffer(const std::vector<QVector3D> &data);
    void setBuffer(BufferType type, const std::vector<float> &data,int tupleSize);
    /*
    inline const std::vector<float> &positions() const { return buffers[BufferType::Positions]; }
    inline const std::vector<float> &colors() const { return buffers[BufferType::Colors]; }
    inline const std::vector<float> &normals() const { return buffers[BufferType::Normals]; }
    */
    inline ptr<BufferData> getBuffer(BufferType bt) const { return buffers[bt]; }

private:
    std::vector<ptr<BufferData>> buffers{(size_t)(BufferType::InternalBufferCount)};
};

class Shader;

class AttributeBinder : public OpenGLUser
{
public:
    AttributeBinder(ptr<BufferData> data,ptr<Shader> shader ,int index);
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
};

#endif // RENDERBUFFER_H
