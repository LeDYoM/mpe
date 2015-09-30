#include "texturemanager.h"
#include <QImage>
#include <QOpenGLTexture>

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}


Texture::Texture(const QString file)
{
    QImage image(file);
    _texture = createptr<QOpenGLTexture>(image);
}

Texture::~Texture()
{
    if (_texture)
        _texture->release();
}
