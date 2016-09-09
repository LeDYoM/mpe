#ifndef SCENE_H
#define SCENE_H

#include <QObject>

class Camera;

class Scene : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Camera* camera READ camera)
public:
    explicit Scene(QObject *parent = 0);
    Camera *camera() const { return m_camera; }


private:
    Camera *m_camera;
};

#endif // SCENE_H
