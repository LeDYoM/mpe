#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <list>
#include "openglmanager.h"
#include "singleton.h"
#include "memm.h"
#include <QMatrix4x4>

class QOpenGLShaderProgram;
class Shader;

class Material : public OpenGLUser
{
public:
    Material();
    virtual ~Material();

    Q_DISABLE_COPY(Material)
    friend class MaterialManager;
    void bind();
    void release();

    ptr<Shader> shader() const { return _shader; }
private:

    ptr<Shader> _shader;

    void setAsDefault();
};

class MaterialManager : public OpenGLUser, public Singleton<MaterialManager>
{
public:
    MaterialManager();
    virtual ~MaterialManager();

    Q_DISABLE_COPY(MaterialManager)

    inline ptr<Material> defaultMaterial() const { return _defaultMaterial; }
    void setProjectionMatrix(const QMatrix4x4 &projectionMatrix);
    inline const QMatrix4x4 &projectionMatrix() const { return _projectionMatrix; }
    void setActiveMaterial(ptr<Material> material);
    void releaseActiveMaterial();

private:
    std::list<ptr<Material>> materials;
    ptr<Material> _defaultMaterial{nullptr};
    QMatrix4x4 _projectionMatrix;

    ptr<Material> _activeRenderMaterial{nullptr};

    friend class Renderer;
};

class Shader : public OpenGLUser
{
public:
    Shader(ptr<QOpenGLShaderProgram> program);
    virtual ~Shader();
    inline int positionAttributeIndex() const { return _positionAttributeIndex; }
    inline int colorAttributeIndex() const { return _colorAttributeIndex; }
    inline int normalAttributeIndex() const { return _normalAttributeIndex; }
    inline ptr<QOpenGLShaderProgram> program() const { return _program; }

private:
    int _positionAttributeIndex{0};
    int _colorAttributeIndex{1};
    int _normalAttributeIndex{2};
    ptr<QOpenGLShaderProgram> _program{nullptr};

};

class ShaderManager : public OpenGLUser, public Singleton<ShaderManager>
{
public:
    ShaderManager();
    virtual ~ShaderManager();

    inline ptr<Shader> defaultShader() const { return _defaultShader; }
    bool addShader(const char *name,const char *vertexCode,const char *fragmentCode);

    void setCurrentActiveShader(ptr<Shader> shader);
    void unsetShader();

    inline ptr<Shader> activeShader() const { return currentActiveShader; }

private:
    ptr<Shader> _defaultShader{nullptr};
    ptr<Shader> currentActiveShader{nullptr};
};

#endif // MATERIALMANAGER_H
