#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <list>
#include "singleton.h"
#include "memm.h"
#include <QMatrix4x4>
#include "buffertype.h"
#include "globalwrapperh.h"

class Shader;

class Material
{
public:
    Material();
    virtual ~Material();

    CLASS_NO_COPY(Material)
    void bind();
    void release();

    inline ptr<Shader> shader() const { return _shader; }
    void setAsDefault();

private:

    ptr<Shader> _shader;

};

class MaterialManager : public Singleton<MaterialManager>
{
public:
    MaterialManager();
    virtual ~MaterialManager();

    CLASS_NO_COPY(MaterialManager)

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
};

#endif // MATERIALMANAGER_H
