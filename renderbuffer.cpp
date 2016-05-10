#include "renderbuffer.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "mpeapplication.h"
#include "materialmanager.h"
#include "log.h"

RenderBuffer::RenderBuffer()
{
}

RenderBuffer::~RenderBuffer()
{

}

static std::vector<float> fromVQ3(const std::vector<QVector3D> &data)
{
    std::vector<float> temp;
    for (const QVector3D &v : data)
    {
        temp.push_back(v.x());
        temp.push_back(v.y());
        temp.push_back(v.z());
    }
    return temp;
}

static std::vector<float> fromVQ4(const std::vector<QVector4D> &data)
{
    std::vector<float> temp;
    for (const QVector4D &v : data)
    {
        temp.push_back(v.x());
        temp.push_back(v.y());
        temp.push_back(v.z());
        temp.push_back(v.w());
    }
    return temp;
}

static std::vector<float> fromVQC(const std::vector<QColor> &data)
{
    std::vector<float> temp;
    for (const QColor &v : data)
    {
        temp.push_back(v.redF());
        temp.push_back(v.greenF());
        temp.push_back(v.blueF());
        temp.push_back(v.alphaF());
    }
    return temp;
}

void RenderBuffer::setPositionsBuffer(const std::vector<QVector3D> &data)
{
    setBuffer(BufferType::Positions,fromVQ3(data),3);
}

void RenderBuffer::setColorsBuffer(const std::vector<QColor> &data)
{
    setBuffer(BufferType::Colors,fromVQC(data),4);
}

void RenderBuffer::setColorsBuffer(const std::vector<QVector4D> &data)
{
    setBuffer(BufferType::Colors,fromVQ4(data),4);
}

void RenderBuffer::setColorsBuffer(const std::vector<QVector3D> &data)
{
    setBuffer(BufferType::Colors,fromVQ3(data),3);
}

void RenderBuffer::setNormalsBuffer(const std::vector<QVector3D> &data)
{
    setBuffer(BufferType::Normals,fromVQ3(data),3);
}

void RenderBuffer::setBuffer(BufferType type, const std::vector<float> &data,int tupleSize)
{
    buffers[(int)type] = createptr<BufferData>(tupleSize,data);
}

RenderObject::RenderObject(ptr<RenderBuffer> rBuffer, ptr<Material> material)
{
    _rBuffer = rBuffer;
    _material = material;

    DEBUG_MESSAGE("Creating RenderObject");

    _vao = createptr<QOpenGLVertexArrayObject>( );
    _vao->create();
    _vao->bind();

    _material->shader()->bind();
    _vertexCount = _rBuffer->getBuffer(BufferType::Positions)->numElements();
    for (int i=0;i<(int)BufferType::InternalBufferCount;++i)
    {
        bindings.push_back(createptr<AttributeBinder>(_rBuffer->getBuffer((BufferType)i),_material->shader(),(BufferType)i));
    }

    _material->shader()->release();
    _vao->release();
    DEBUG_MESSAGE(" RenderObject created");
}

RenderObject::~RenderObject()
{
    DEBUG_MESSAGE("Destroying RenderObject");
    if (_vao)
        _vao->release();
}

void RenderObject::render(const QMatrix4x4 *projectionMatrix)
{
    ptr<Shader> shader = _material->shader();
    _vao->bind();
    shader->bind();
    shader->setProjectionMatrix(projectionMatrix);

    glFunctions()->glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
    shader->release();
    _vao->release();
}


AttributeBinder::~AttributeBinder()
{
    if (buffer)
        buffer->release();
}

AttributeBinder::AttributeBinder(sptr<BufferData> data, sptr<Shader> shader, BufferType bufferType)
{
    Q_ASSERT(shader);
    if (data)
    {
        buffer = createptr<QOpenGLBuffer>();
        buffer->setUsagePattern( QOpenGLBuffer::StaticDraw );
        buffer->create();
        buffer->bind();
        Q_ASSERT(data->data().size()>0);
        buffer->allocate( &(data->data()[0]), data->data().size() * sizeof(float) );
        shader->enableAttributeAndSetBuffer(bufferType,data->tupleSize());
    }
    else
    {
        shader->disableAttribute(bufferType);
    }
}
