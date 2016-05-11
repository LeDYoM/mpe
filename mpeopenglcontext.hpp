#ifndef OPENGLMANAGER_H
#define OPENGLMANAGER_H


class QOpenGLContext;
class QOpenGLFunctions;

class MPEOpenGLContext
{
public :
    MPEOpenGLContext() {}
    ~MPEOpenGLContext() {}

    Q_DISABLE_COPY(MPEOpenGLContext);
    void setContext(QOpenGLContext *context);
    inline QOpenGLContext *MPEglcontext() const { return m_context; }
    inline QOpenGLFunctions *glFunctions() const { return m_openGLFunctions; }
private:
    QOpenGLContext *m_context{nullptr};
    QOpenGLFunctions *m_openGLFunctions{nullptr};
};

class MPEOpenGLContextClient
{
public:
    MPEOpenGLContextClient(MPEOpenGLContext *provider): m_provider{provider} {}
    MPEOpenGLContextClient(MPEOpenGLContextClient *other): m_provider{other->m_provider} {}
    MPEOpenGLContextClient(const MPEOpenGLContextClient &other): m_provider{other.m_provider} {}
    ~MPEOpenGLContextClient() {}
    inline QOpenGLContext *context() const { return m_provider->MPEglcontext(); }
    inline QOpenGLFunctions *glFunctions() const { return m_provider->glFunctions(); }
    inline MPEOpenGLContext *provider() const { return m_provider; }
private:
    MPEOpenGLContext *m_provider;
};

#endif // OPENGLMANAGER_H
