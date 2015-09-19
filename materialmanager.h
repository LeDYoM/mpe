#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <list>
#include "openglmanager.h"
#include <QMatrix4x4>

class QOpenGLShaderProgram;

class Material : public OpenGLUser
{
public:
    Material();
    virtual ~Material();

    void startMaterialRendering();
    void endMaterialRendering();

    Q_DISABLE_COPY(Material)
    friend class MaterialManager;

    QOpenGLShaderProgram *program() const { return m_program; }
private:

    QOpenGLShaderProgram *m_program;

    void setAsDefault();
};

class MaterialManager : public OpenGLUser
{
public:
    MaterialManager() {}
    virtual ~MaterialManager() {}

    virtual void initialize();
    virtual void deinitialize();

    Q_DISABLE_COPY(MaterialManager)

    inline Material *defaultMaterial() const { return _defaultMaterial; }
    void setProjectionMatrix(const QMatrix4x4 &projectionMatrix);
    inline const QMatrix4x4 &projectionMatrix() const { return _projectionMatrix; }



private:
    std::list<Material*> materials;
    Material *_defaultMaterial;
    QMatrix4x4 _projectionMatrix;

    friend class Renderer;
};

#endif // MATERIALMANAGER_H
