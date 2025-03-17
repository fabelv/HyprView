#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QString text = QString("Hello from Qt %1!").arg(QT_VERSION_STR);
    QLabel label(text);
    label.show();
    
    return app.exec();
}

