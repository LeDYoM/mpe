#include "renderobject.h"
#include "shadermanager.h"
#include "log.h"
#include "materialmanager.h"
#include "renderbuffer.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

RenderObject::RenderObject(ptr<RenderBuffer> rBuffer, ptr<Material> material)
{
    DEBUG_MESSAGE("Creating RenderObject");
    _rBuffer = rBuffer;
    _material = material;

    _vao = createptr<QOpenGLVertexArrayObject>( );
    _vao->create();
    _vao->bind();

    _material->shader()->bind();
    _vertexCount = rBuffer->getBuffer(BufferType::Positions)->numElements();
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
    Shader *shader = _material->shader().get();
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

AttributeBinder::AttributeBinder(ptr<BufferData> data, ptr<Shader> shader, BufferType bufferType)
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

