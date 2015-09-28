#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <QVector3D>
#include <QVector4D>
#include <QColor>

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

class RenderBuffer
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
    inline ptr<BufferData> getBuffer(BufferType bt) const { return buffers[bt]; }

private:
    std::vector<ptr<BufferData>> buffers{(size_t)(BufferType::InternalBufferCount)};
};

#endif // RENDERBUFFER_H
