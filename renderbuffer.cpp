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

bool RenderBuffer::addBuffer(const std::string name, const std::vector<float> &data,int tupleSize)
{
    if (!exists(name))
    {
        _data[name] = new BufferData(tupleSize);
        _data[name]->setData(data);
//        _data[name]->create();
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

void RenderBuffer::setIndicesBuffer(const std::vector<short> &indices)
{
    indicesData = indices;
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

void RenderBuffer::create2(QOpenGLShaderProgram *program)
{
    DEBUG_MESSAGE("Creating RenderBuffer");

    vao = new QOpenGLVertexArrayObject( );
    vao->create();
    vao->bind();

    program->bind();

    for (auto& item : _data)
    {
        DEBUG_MESSAGE("   Adding buffer" << item.first.c_str() << " with " << item.second->numElements() << " elements");
        item.second->create();
        item.second->bind();
//        glFunctions()->glEnableVertexAttribArray();
        program->enableAttributeArray( item.first.c_str() );
        program->setAttributeBuffer( item.first.c_str(), GL_FLOAT, 0, item.second->tupleSize() , 0 );

        int ne = item.second->numElements();
        if (ne > _numElements)
        {
            _numElements = ne;
        }
    }

    program->release();
    vao->release();
    DEBUG_MESSAGE(" RenderBuffer created with num elements: " << _numElements);
}

void RenderBuffer::release()
{
    vao->release();
}

void RenderBuffer::bind()
{
    vao->bind();
}

bool RenderBuffer::exists(const std::string &key_)
{
    return _data.find(key_) != _data.end();
}

void BufferData::setData(const std::vector<float> &data)
{
    _data = data;
}

void BufferData::setData(const float *data, int size)
{
    std::vector<float> temp(size);
    for (int i=0;i<size;++i)
    {
        temp.push_back(data[i]);
    }

    setData(temp);
}

void BufferData::create()
{
    buffer = new QOpenGLBuffer();
    buffer->setUsagePattern( QOpenGLBuffer::StaticDraw );
    buffer->create();
    buffer->bind();
    buffer->allocate( &(_data[0]), _data.size() * sizeof(float) );
}

void BufferData::bind()
{
    buffer->bind();
}


void RenderBufferObject::create()
{

}
