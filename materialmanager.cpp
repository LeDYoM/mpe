#include "materialmanager.h"
#include "shadermanager.h"
#include "log.h"

MaterialManager::MaterialManager()
{
    VERBOSE_MESSAGE("Initializing MaterialManager");
    _defaultMaterial = createptr<Material>();
    _defaultMaterial->setAsDefault();
    VERBOSE_MESSAGE("MaterialManager initialized");
}

MaterialManager::~MaterialManager()
{
    VERBOSE_MESSAGE("Destroying MaterialManager");
    if (_defaultMaterial)
    {
//        _defaultMaterial.get_deleter
        _defaultMaterial = nullptr;
    }
    VERBOSE_MESSAGE("MaterialManager destroyed");
}

void MaterialManager::setProjectionMatrix(const QMatrix4x4 &projectionMatrix)
{
    _projectionMatrix = projectionMatrix;
}

void MaterialManager::setActiveMaterial(ptr<Material> material)
{
    if (!material)
    {
        releaseActiveMaterial();
        return;
    }

    if (_activeRenderMaterial != material)
    {
        _activeRenderMaterial = material;
        ShaderManager::GetInstance()->setCurrentActiveShader(_activeRenderMaterial->shader());
    }
}

void MaterialManager::releaseActiveMaterial()
{
    if (_activeRenderMaterial)
    {
        ShaderManager::GetInstance()->unsetShader();
        _activeRenderMaterial = nullptr;
    }
}

Material::Material() {}
Material::~Material() {}

void Material::setAsDefault()
{
    _shader = ShaderManager::GetInstance()->defaultShader();
}

