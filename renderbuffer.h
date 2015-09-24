#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "openglmanager.h"

#include <QVector3D>
#include <QColor>

#include <unordered_map>
#include <string>
#include <vector>
#include "memm.h"

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class Material;
class QOpenGLShaderProgram;

enum class BufferDataType
{

};

class BufferData
{
public:
    inline BufferData(int tupleSize):_tupleSize{tupleSize} { }
    void setData(const std::vector<float> &data);
    void setData(const float *data,int size);
    void create();
    void bind();
    inline int tupleSize() const { return _tupleSize; }
    inline int numElements() const { return _data.size() / _tupleSize; }
private:
    QOpenGLBuffer *buffer;
    std::vector<float> _data;
    int _tupleSize;
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
    inline BufferData *positions() const { return _positionsBuffer; }
    inline BufferData *colors() const { return _colorBuffer; }
    inline BufferData *normals() const { return _normalsBuffer; }
    inline int numElements() const { return _numElements; }

private:
    int _numElements{0};
    BufferData *_positionsBuffer{nullptr};
    BufferData *_colorBuffer{nullptr};
    BufferData *_normalsBuffer{nullptr};

    friend class Renderer;
};

class RenderObject : public OpenGLUser
{
public:
    RenderObject(ptr<RenderBuffer> rBuffer, ptr<Material> material);
    virtual ~RenderObject();

    void render(const QMatrix4x4 *projectionMatrix);
private:
    ptr<RenderBuffer> _rBuffer{nullptr};
    ptr<Material> _material{nullptr};
    ptr<QOpenGLVertexArrayObject> _vao{nullptr};
};

#endif // RENDERBUFFER_H
