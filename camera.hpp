#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>

class Scene;

class Camera : public QObject
{
    Q_OBJECT

public:
    explicit Camera(Scene *parent = nullptr);
};

#endif // CAMERA_H
