#include "transform.h"

int Transform::degrees(Transform::Type type) {
    switch (type) {
        case Rotate90:
        case FlippedRotate90:
            return 90;
        case Rotate180:
        case FlippedRotate180:
            return 180;
        case Rotate270:
        case FlippedRotate270:
            return 270;
        case Normal:
        case Flipped:
        default:
            return 0;
    }
}
