#include "main_layout.h"
#include "ui_main_layout.h"

MainLayout::MainLayout(QWidget *parent) : QWidget(parent){
    /*ui->setupUi(this);  // Loads main_layout.ui*/
}

MainLayout::~MainLayout() {
    delete ui;
}
