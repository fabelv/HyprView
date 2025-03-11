#include <QApplication>
#include "components/main_layout.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainLayout window;
    window.show();  // Show the main UI

    return app.exec();
}

