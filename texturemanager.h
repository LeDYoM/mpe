#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QtCore>
#include "singleton.h"
#include "opengluser.h"
#include "memm.h"

class QOpenGLTexture;

class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager();
    virtual ~TextureManager();
};

class Texture : public OpenGLUser
{
public:
    Texture(const QString file);
    virtual ~Texture();
private:
    ptr<QOpenGLTexture> _texture{nullptr};
};

#endif // TEXTUREMANAGER_H
