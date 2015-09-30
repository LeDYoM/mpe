#include "shadermanager.h"
#include <QOpenGLShaderProgram>

static const char *vertexShaderSource =
    "in lowp vec4 posAttr;\n"
    "in lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform lowp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "in lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

ShaderManager::ShaderManager()
{
//    addShader("default",vertexShaderSource,fragmentShaderSource);
      addShaderFromFile("default",":/standard.vert",":/standard.frag");
}

ShaderManager::~ShaderManager()
{
    _defaultShader->release();
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

bool ShaderManager::addShaderFromFile(const char *name, const char *vsFile, const char *fsFile)
{
    Q_UNUSED(name);
    ptr<QOpenGLShaderProgram> temp = createptr<QOpenGLShaderProgram>();
    temp->addShaderFromSourceFile(QOpenGLShader::Vertex, vsFile);
    temp->addShaderFromSourceFile(QOpenGLShader::Fragment, fsFile);
    temp->link();
    _defaultShader = createptr<Shader>(temp);
    return true;
}

void ShaderManager::setCurrentActiveShader(ptr<Shader> shader)
{
    currentActiveShader = shader;
    currentActiveShader->bind();
}

void ShaderManager::unsetShader()
{
    if (currentActiveShader)
    {
        currentActiveShader->release();
    }
}



Shader::Shader(ptr<QOpenGLShaderProgram> program)
    : _program{program}
{

}

Shader::~Shader()
{
    if (_program)
    {
        _program->release();
    }
}

void Shader::enableAttributeAndSetBuffer(BufferType bufferType, int tupleSize)
{
    enableAttribute(bufferType);
    _program->setAttributeBuffer( (int)bufferType, GL_FLOAT, 0, tupleSize , 0 );
}

void Shader::enableAttribute(BufferType bufferType)
{
    _program->enableAttributeArray( (int)bufferType );
}

void Shader::disableAttribute(BufferType bufferType)
{
    _program->disableAttributeArray((int)bufferType);
}

void Shader::setProjectionMatrix(const QMatrix4x4 *pMatrix)
{
    _program->setUniformValue("matrix",*pMatrix);
}

void Shader::bind()
{
    _program->bind();
}

void Shader::release()
{
    _program->release();
}
