#include "renderbuffer.h"
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
