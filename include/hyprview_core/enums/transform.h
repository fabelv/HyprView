#define TRANSFORM_ENUM_LIST \
    X(Normal)               \
    X(Rotate90)             \
    X(Rotate180)            \
    X(Rotate270)            \
    X(Flipped)              \
    X(FlippedRotate90)      \
    X(FlippedRotate180)     \
    X(FlippedRotate270)

// transform.hpp
#pragma once
#include <ostream>
#include <string>

namespace core {

enum class Transform {
#define X(name) name,
    TRANSFORM_ENUM_LIST
#undef X
};

inline std::string toString(Transform type) {
    switch (type) {
#define X(name)           \
    case Transform::name: \
        return #name;
        TRANSFORM_ENUM_LIST
#undef X
        default:
            return "Unknown";
    }
}

inline std::ostream& operator<<(std::ostream& os, Transform type) { return os << toString(type); }

}  // namespace core
