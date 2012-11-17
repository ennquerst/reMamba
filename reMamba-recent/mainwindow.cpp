#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fate = new Fate();
    ui->verticalLayout->addWidget(fate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
