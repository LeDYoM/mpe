#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "buffertype.h"
#include "opengluser.h"
#include "memm.h"
#include <QMatrix4x4>
#include "singleton.h"

class QOpenGLShaderProgram;

class Shader : public OpenGLUser
{
public:
    Shader(ptr<QOpenGLShaderProgram> program);
    virtual ~Shader();
    inline int getAttributeIndex(BufferType bf) const { return attributeIndices[bf]; }
//    inline ptr<QOpenGLShaderProgram> program() const { return _program; }

    void enableAttributeAndSetBuffer(BufferType bufferType,int tupleSize);
    void enableAttribute(BufferType bufferType);
    void disableAttribute(BufferType bufferType);
    void setProjectionMatrix(const QMatrix4x4 *pMatrix);
    void bind();
    void release();
private:
    std::vector<int> attributeIndices= {0,1,2};
    ptr<QOpenGLShaderProgram> _program{nullptr};

};

class ShaderManager : public OpenGLUser, public Singleton<ShaderManager>
{
public:
    ShaderManager();
    virtual ~ShaderManager();

    inline ptr<Shader> defaultShader() const { return _defaultShader; }
    bool addShader(const char *name,const char *vertexCode,const char *fragmentCode);
    bool addShaderFromFile(const char *name,const char *vsFile,const char *fsFile);

    void setCurrentActiveShader(ptr<Shader> shader);
    void unsetShader();

    inline ptr<Shader> activeShader() const { return currentActiveShader; }

private:
    ptr<Shader> _defaultShader{nullptr};
    ptr<Shader> currentActiveShader{nullptr};
};

#endif // SHADERMANAGER_H
