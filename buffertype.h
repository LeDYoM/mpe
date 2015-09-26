#ifndef BUFFERTYPE
#define BUFFERTYPE

enum BufferType
{
    Positions=0,
    Colors=1,
    Normals=2,
    InternalBufferCount=3,
    UserDefined=0xff,
    Max=0xffff
};

#endif // BUFFERTYPE

