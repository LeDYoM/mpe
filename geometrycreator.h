#ifndef GEOMETRYCREATOR_H
#define GEOMETRYCREATOR_H

#include "singleton.h"
#include "memm.h"

class RenderBuffer;

class GeometryCreator : public Singleton<GeometryCreator>
{
public:
    GeometryCreator();
    virtual ~GeometryCreator();

    ptr<RenderBuffer> exampleQuad();
};

#endif // GEOMETRYCREATOR_H
