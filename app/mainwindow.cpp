#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");

    if (fileName.isEmpty())
        return;

    QPixmap image(fileName);
    ui->originalImage->setPixmap(image);

    QString pt;
    pt.append("File Name: " + fileName + "\n");
    pt.append("Width: " + QString::number(image.width()) + "\n");
    pt.append("Height: " + QString::number(image.height()) + "\n");

    ui->properties->setText(pt);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

