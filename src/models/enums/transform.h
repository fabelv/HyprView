#pragma once

#include <QObject>

class Transform : public QObject {
    Q_OBJECT
public:
    enum Type {
        Normal = 0,
        Rotate90 = 1,
        Rotate180 = 2,
        Rotate270 = 3,
        Flipped = 4,
        FlippedRotate90 = 5,
        FlippedRotate180 = 6,
        FlippedRotate270 = 7
    };
    Q_ENUM(Type)

    static int degrees(Type type);
};

