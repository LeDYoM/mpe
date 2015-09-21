#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <list>
#include "openglmanager.h"
#include "singleton.h"
#include <QMatrix4x4>

class QOpenGLShaderProgram;
using QOpenGLShaderProgramPtr = QOpenGLShaderProgram *;

class Material : public OpenGLUser
{
public:
    Material();
    virtual ~Material();

    void startMaterialRendering();
    void endMaterialRendering();

    Q_DISABLE_COPY(Material)
    friend class MaterialManager;

    QOpenGLShaderProgramPtr program() const { return m_program; }
private:

    QOpenGLShaderProgramPtr m_program;

    void setAsDefault();
};

class MaterialManager : public OpenGLUser, public Singleton<MaterialManager>
{
public:
    MaterialManager();
    virtual ~MaterialManager();

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

class ShaderManager : public OpenGLUser, public Singleton<ShaderManager>
{
public:
    ShaderManager();
    virtual ~ShaderManager();

    inline QOpenGLShaderProgramPtr defaultShader() const { return _defaultShader; }

private:
    QOpenGLShaderProgram *_defaultShader{nullptr};
};

#endif // MATERIALMANAGER_H
