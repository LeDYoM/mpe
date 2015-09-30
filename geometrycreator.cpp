#include "geometrycreator.h"
#include "renderbuffer.h"

GeometryCreator::GeometryCreator()
{

}

GeometryCreator::~GeometryCreator()
{

}

ptr<RenderBuffer> GeometryCreator::exampleQuad()
{
    ptr<RenderBuffer> rBuffer = createptr<RenderBuffer>();

    rBuffer->setColorsBuffer(
        { Qt::red, Qt::green, Qt::blue,
          Qt::red, Qt::green, Qt::blue,
        });

    rBuffer->setPositionsBuffer(std::vector<QVector3D>
    {
        { -1.0f, -1.0f,  0.0f}, // v0
        {  1.0f, -1.0f,  0.0f}, // v1
        {  1.0f,  1.0f,  0.0f}, // v2

        {  1.0f,  1.0f,  0.0f}, // v0
        { -1.0f,  1.0f,  0.0f}, // v1
        { -1.0f, -1.0f,  0.0f} // v2
    });

    return rBuffer;

}

