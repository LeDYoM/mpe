#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <list>
#include "openglmanager.h"
#include "memm.h"
#include <QMatrix4x4>
#include "buffertype.h"

class QOpenGLShaderProgram;
class Shader;

class Material : public MPEOpenGLContextClient
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

    sptr<Shader> _shader;

    void setAsDefault();
};

class MaterialManager : public MPEOpenGLContextClient
{
public:
    MaterialManager(MPEOpenGLContext *parent);
    ~MaterialManager();

    Q_DISABLE_COPY(MaterialManager)

    inline sptr<Material> defaultMaterial() const { return _defaultMaterial; }
    void setProjectionMatrix(const QMatrix4x4 &projectionMatrix);
    inline const QMatrix4x4 &projectionMatrix() const { return _projectionMatrix; }
    void setActiveMaterial(ptr<Material> material);
    void releaseActiveMaterial();

private:
    std::list<ptr<Material>> materials;
    ptr<Material> _defaultMaterial{nullptr};
    QMatrix4x4 _projectionMatrix;

    sptr<Material> _activeRenderMaterial{nullptr};
};

class Shader : public MPEOpenGLContextClient
{
public:
    Shader(ShaderManager *sManager,sptr<QOpenGLShaderProgram> program);
    virtual ~Shader();
    inline int getAttributeIndex(BufferType bf) const { return attributeIndices[bf]; }
//    inline sptr<QOpenGLShaderProgram> program() const { return _program; }

    void enableAttributeAndSetBuffer(BufferType bufferType,int tupleSize);
    void enableAttribute(BufferType bufferType);
    void disableAttribute(BufferType bufferType);
    void setProjectionMatrix(const QMatrix4x4 *pMatrix);
    void bind();
    void release();
private:
    std::vector<int> attributeIndices= {0,1,2};
    sptr<QOpenGLShaderProgram> _program{nullptr};

};

class ShaderManager : public MPEOpenGLContextClient
{
public:
    ShaderManager(MPEOpenGLContext *parent);
    virtual ~ShaderManager();

    inline sptr<Shader> defaultShader() const { return _defaultShader; }
    bool addShader(const char *name,const char *vertexCode,const char *fragmentCode);

    void setCurrentActiveShader(sptr<Shader> shader);
    void unsetShader();

    inline ptr<Shader> activeShader() const { return currentActiveShader; }

private:
    sptr<Shader> _defaultShader{nullptr};
    sptr<Shader> currentActiveShader{nullptr};
};

#endif // MATERIALMANAGER_H
