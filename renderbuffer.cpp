#include "renderbuffer.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "mpeapplication.h"
#include "materialmanager.h"
#include "log.h"

RenderBuffer::RenderBuffer():OpenGLUser()
{
    //setMaterial(mpeApp->materialManager()->defaultMaterial());
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

/*
bool RenderBuffer::addBuffer(const std::string name, const std::vector<float> &data,int tupleSize)
{
    if (!exists(name))
    {
        _data[name] = new BufferData(tupleSize);
        _data[name]->setData(data);
        return true;
    }
    return false;
}

bool RenderBuffer::addBuffer(const std::string name, const std::vector<QVector3D> &data)
{
    std::vector<float> temp;
    for (const QVector3D &v : data)
    {
        temp.push_back(v.x());
        temp.push_back(v.y());
        temp.push_back(v.z());
    }

    return addBuffer(name,temp,3);
}

bool RenderBuffer::addBuffer(const std::string name, const std::vector<QColor> &data)
{
    std::vector<float> temp;
    for (const QColor &v : data)
    {
        temp.push_back(v.redF());
        temp.push_back(v.greenF());
        temp.push_back(v.blueF());
        temp.push_back(v.alphaF());
    }

    return addBuffer(name,temp,4);
}

BufferData *RenderBuffer::getBuffer(const std::string index) const
{
    return (*(_data.find(index))).second;
}


void RenderBuffer::create()
{
    DEBUG_MESSAGE("Creating RenderBuffer");

    vao = new QOpenGLVertexArrayObject( );
    vao->create();
    vao->bind();

    for (auto& item : _data)
    {
        DEBUG_MESSAGE("   Adding buffer" << item.first.c_str() << " with " << item.second->numElements() << " elements");
        item.second->create();
        int ne = item.second->numElements();
        if (ne > _numElements)
        {
            _numElements = ne;
        }
    }

    vao->release();
    DEBUG_MESSAGE(" RenderBuffer created with num elements: " << _numElements);
}
*/

/*
void BufferData::create()
{
    buffer = new QOpenGLBuffer();
    buffer->setUsagePattern( QOpenGLBuffer::StaticDraw );
    buffer->create();
    buffer->bind();
    buffer->allocate( &(_data[0]), _data.size() * sizeof(float) );
}
*/


RenderObject::RenderObject(ptr<RenderBuffer> rBuffer, ptr<Material> material)
{
    _rBuffer = rBuffer;
    _material = material;

    DEBUG_MESSAGE("Creating RenderObject");

    _vao = createptr<QOpenGLVertexArrayObject>( );
    _vao->create();
    _vao->bind();

    _material->shader()->program()->bind();

    for (int i=0;i<(int)BufferType::InternalBufferCount;++i)
    {
        bindings.push_back(createptr<AttributeBinder>(_rBuffer->getBuffer((BufferType)i),_material->shader(),i));
    }

    /*
    _rBuffer->positions()->create();
    _rBuffer->positions()->bind();
    _material->shader()->program()->enableAttributeArray(_material->shader()->positionAttributeIndex());
    _material->shader()->program()->setAttributeBuffer(_material->shader()->positionAttributeIndex(),
                                                       GL_FLOAT, 0, _rBuffer->positions()->tupleSize() , 0);

    _rBuffer->colors()->create();
    _rBuffer->colors()->bind();
    _material->shader()->program()->enableAttributeArray(_material->shader()->colorAttributeIndex());
    _material->shader()->program()->setAttributeBuffer(_material->shader()->colorAttributeIndex(),
                                                       GL_FLOAT, 0, _rBuffer->colors()->tupleSize() , 0);
*/
    /*
    for (auto& item : _data)
    {
        DEBUG_MESSAGE("   Adding buffer" << item.first.c_str() << " with " << item.second->numElements() << " elements");
        item.second->create();
        item.second->bind();
        program->enableAttributeArray( item.first.c_str() );
        program->setAttributeBuffer( item.first.c_str(), GL_FLOAT, 0, item.second->tupleSize() , 0 );

        int ne = item.second->numElements();
        if (ne > _numElements)
        {
            _numElements = ne;
        }
    }
*/
    _material->shader()->program()->release();
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
    _vao->bind();
    ptr<QOpenGLShaderProgram> program = _material->shader()->program();
    program->bind();
    program->setUniformValue("matrix", *projectionMatrix);

    glFunctions()->glDrawArrays(GL_TRIANGLES, 0, _rBuffer->getBuffer(BufferType::Positions)->numElements());
    program->release();
    _vao->release();
}


AttributeBinder::~AttributeBinder()
{
    if (buffer)
        buffer->release();
}

AttributeBinder::AttributeBinder(ptr<BufferData> data, ptr<Shader> shader, int index)
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
        shader->program()->enableAttributeArray( index );
        shader->program()->setAttributeBuffer( index, GL_FLOAT, 0, data->tupleSize() , 0 );
    }
    else
    {
        shader->program()->disableAttributeArray( index );
    }
}
