#ifndef MAIN_LAYOUT_H
#define MAIN_LAYOUT_H

#include <QWidget>
#include "ui_main_layout.h"

namespace Ui {
class MainLayout;
}

class MainLayout : public QWidget {
    Q_OBJECT

public:
    explicit MainLayout(QWidget *parent = nullptr);
    ~MainLayout();

private:
    Ui::MainLayout *ui;
};

#endif 
