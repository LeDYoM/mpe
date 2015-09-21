#include "openglmanager.h"
#include "materialmanager.h"
#include "renderbuffer.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

QOpenGLContext *OpenGLUser::_context{nullptr};
QOpenGLFunctions *OpenGLUser::_openGLFunctions{nullptr};

void OpenGLUser::setContext(QOpenGLContext *context)
{
    _context = context;
    _openGLFunctions = _context->functions();
}

void Renderer::render(Material *material, RenderBuffer *rBuffer)
{
    if (!rBuffer->vao)
        rBuffer->create();

    rBuffer->vao->bind();
//    glFunctions()->glVertexAttribPointer();
    QOpenGLShaderProgram *program = material->program();
    program->bind();
    program->setUniformValue("matrix", *_projectionMatrix);

    for (auto& item : rBuffer->_data)
    {
        item.second->bind();
        material->program()->enableAttributeArray( item.first.c_str() );
        material->program()->setAttributeBuffer( item.first.c_str(), GL_FLOAT, 0, item.second->tupleSize() , 0 );
    }

    glFunctions()->glDrawArrays(GL_TRIANGLES, 0, rBuffer->_numElements);
    program->release();
    rBuffer->vao->release();
}

void Renderer::render2(Material *material, RenderBuffer *rBuffer)
{
    if (!rBuffer->vao)
        rBuffer->create2(material->program());

    rBuffer->vao->bind();
    material->program()->bind();
    material->program()->setUniformValue("matrix", *_projectionMatrix);
    glFunctions()->glDrawArrays(GL_TRIANGLES, 0, rBuffer->_numElements);
    material->program()->release();
    rBuffer->vao->release();

}
