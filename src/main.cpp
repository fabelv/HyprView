#include <qapplication.h>
#include <qlabel.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QLabel label("Hello, World!");
    label.setAlignment(Qt::AlignCenter);
    label.resize(400, 200);
    label.show();

    return app.exec();
}
