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

void MaterialManager::initialize()
{
    VERBOSE_MESSAGE("Initializing MaterialManager");
    _defaultMaterial = new Material();
    _defaultMaterial->setAsDefault();
    VERBOSE_MESSAGE("MaterialManager initialized");
}

void MaterialManager::deinitialize()
{
    VERBOSE_MESSAGE("Destroying MaterialManager");
    if (_defaultMaterial)
    {
        delete _defaultMaterial;
        _defaultMaterial = nullptr;
    }
}

void MaterialManager::setProjectionMatrix(const QMatrix4x4 &projectionMatrix)
{
    _projectionMatrix = projectionMatrix;
}

Material::Material() {}
Material::~Material() {}

void Material::setAsDefault()
{
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
}
