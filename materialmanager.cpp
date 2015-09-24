#include "materialmanager.h"
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>

#include "log.h"
#include "mpeapplication.h"

static const char *vertexShaderSource =
    "in vec4 posAttr;\n"
    "in vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "in lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

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


ShaderManager::ShaderManager()
{
    addShader("default",vertexShaderSource,fragmentShaderSource);
}

ShaderManager::~ShaderManager()
{
    _defaultShader->program()->release();
}

bool ShaderManager::addShader(const char *name, const char *vertexCode, const char *fragmentCode)
{
    Q_UNUSED(name);
    ptr<QOpenGLShaderProgram> temp = createptr<QOpenGLShaderProgram>();
    temp->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode);
    temp->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode);
    temp->link();
    _defaultShader = createptr<Shader>(temp);
    return true;
}

void ShaderManager::setCurrentActiveShader(ptr<Shader> shader)
{
    currentActiveShader = shader;
    currentActiveShader->program()->bind();
}

void ShaderManager::unsetShader()
{
    if (currentActiveShader)
    {
        currentActiveShader->program()->release();
    }
}



Shader::Shader(ptr<QOpenGLShaderProgram> program)
    : _program{program}
{

}

Shader::~Shader()
{

}
