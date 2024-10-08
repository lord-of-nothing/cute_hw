#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <QTextStream>

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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint position = QCursor::pos();
    QString text = QString("Current cursor position: %1 %2").arg(position.x()).arg(position.y());
    // QTextStream(stdout) << text << Qt::endl;
    ui->currentLocationLabel->setText(text);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // QTextStream(stdout) << "click!" << Qt::endl;
    QPoint position = QCursor::pos();
    ui->lastClickLabel->setText(QString("Last click position: %1 %2").arg(position.x()).arg(position.y()));
}
