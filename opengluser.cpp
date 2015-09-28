#include "opengluser.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

QOpenGLContext *OpenGLUser::_context{nullptr};
QOpenGLFunctions *OpenGLUser::_openGLFunctions{nullptr};

void OpenGLUser::setContext(QOpenGLContext *context)
{
    _context = context;
    _openGLFunctions = _context->functions();
}
