#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "openglmanager.h"

#include <QVector3D>
#include <QColor>

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class Material;
class QOpenGLShaderProgram;

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
    bool addBuffer(const std::string name, const std::vector<float> &data,int tupleSize);
    bool addBuffer(const std::string name, const std::vector<QVector3D> &data);
    bool addBuffer(const std::string name, const std::vector<QColor> &data);
    void setIndicesBuffer(const std::vector<short> &indices);
    BufferData *getBuffer(const std::string name) const;
    void create();
    void create2(QOpenGLShaderProgram *program);
    void render();
    void release();
    void bind();

private:
    std::vector<short> indicesData;
    QOpenGLVertexArrayObject *vao{nullptr};
    QOpenGLBuffer *indicesBuffer{nullptr};
    bool exists(const std::string &key_);
    int _numElements{0};
    std::unordered_map<std::string,BufferData*> _data;

    friend class Renderer;
};

class RenderBufferObject
{
public:
    inline RenderBufferObject(RenderBuffer *vdb,QOpenGLShaderProgram *sh):_vertexDataBuffer{vdb},_shader{sh} {}
    virtual ~RenderBufferObject() {}

    void create();
private:
    RenderBuffer *_vertexDataBuffer;
    QOpenGLShaderProgram *_shader;
    QOpenGLVertexArrayObject *vao{nullptr};
    QVector<QOpenGLBuffer*> bufferData;
};

#endif // RENDERBUFFER_H
