#pragma once
#include <QObject>
#include <QVariant>
#include "hyprview_core/enums/transform.h"

class TransformHelper : public QObject {
    Q_OBJECT
public:
    enum Transform {
#define X(name) name,
        TRANSFORM_ENUM_LIST
#undef X
    };
    Q_ENUM(Transform)

    Q_INVOKABLE static QVariantList transformModel() {
        QVariantList list;
#define X(name) list.append(QVariantMap{{"text", QStringLiteral(#name)}, {"value", QVariant::fromValue(TransformHelper::name)}});
        TRANSFORM_ENUM_LIST
#undef X
        return list;
    }

    static QString toString(Transform t) {
        switch (t) {
#define X(name) case name: return QStringLiteral(#name);
            TRANSFORM_ENUM_LIST
#undef X
            default: return QStringLiteral("Unknown");
        }
    }
};
