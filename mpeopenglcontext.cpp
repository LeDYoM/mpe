#include "mpeopenglcontext.hpp"
#include <QOpenGLContext>

void MPEOpenGLContext::setContext(QOpenGLContext *context)
{
    m_context = context;
    m_openGLFunctions = context->functions();
}
