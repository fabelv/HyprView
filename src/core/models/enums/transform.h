#pragma once

namespace core {

enum class Transform {
    Normal = 0,
    Rotate90 = 1,
    Rotate180 = 2,
    Rotate270 = 3,
    Flipped = 4,
    FlippedRotate90 = 5,
    FlippedRotate180 = 6,
    FlippedRotate270 = 7
};

inline int degrees(Transform type) {
    switch (type) {
        case Transform::Rotate90:
        case Transform::FlippedRotate90:
            return 90;
        case Transform::Rotate180:
        case Transform::FlippedRotate180:
            return 180;
        case Transform::Rotate270:
        case Transform::FlippedRotate270:
            return 270;
        case Transform::Normal:
        case Transform::Flipped:
        default:
            return 0;
    }
}

} // namespace core

