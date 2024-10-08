#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QBrush>
#include <QPushButton>

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

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.begin(this);
    QBrush brush(Qt::SolidPattern);
    QPen pen;
    pen.setWidth(10);

    if (ui->fillColorCombo->currentText() == "black") {
        brush.setColor(Qt::black);
    } else if (ui->fillColorCombo->currentText() == "red") {
        brush.setColor(Qt::red);
    } else if (ui->fillColorCombo->currentText() == "green") {
        brush.setColor(Qt::green);
    } else if (ui->fillColorCombo->currentText() == "blue"){
        brush.setColor(Qt::blue);
    } else {
        QPixmap texture("../../images/texture.jpg");
        brush.setTexture(texture);
    }

    if (ui->borderColorCombo->currentText() == "black border") {
        pen.setColor(Qt::black);
    } else if (ui->borderColorCombo->currentText() == "red border") {
        pen.setColor(Qt::red);
    } else if (ui->borderColorCombo->currentText() == "green border") {
        pen.setColor(Qt::green);
    } else {
        pen.setColor(Qt::blue);
    }

    if (ui->borderStyleCombo->currentText() == "no border") {
        pen.setStyle(Qt::NoPen);
    } else if (ui->borderStyleCombo->currentText() == "solid line") {
        pen.setStyle(Qt::SolidLine);
    } else if (ui->borderStyleCombo->currentText() == "dash line") {
        pen.setStyle(Qt::DashLine);
    } else {
        pen.setStyle(Qt::DotLine);
    }

    painter.setBrush(brush);
    painter.setPen(pen);

    if (ui->shapeCombo->currentText() == "rectangle") {
        painter.drawRect(100, 100, ui->spacer->sizeHint().width() - 200, height() - 200);
    } else if (ui->shapeCombo->currentText() == "line") {
        painter.drawLine(ui->spacer->sizeHint().width() - 100, 100, 100, height() - 100);
    } else if (ui->shapeCombo->currentText() == "triangle") {
        QPolygon triangle;
        triangle << QPoint(300, 100) << QPoint(ui->spacer->sizeHint().width() - 100, height() / 2) << QPoint(100, height() - 100);
        painter.drawPolygon(triangle);
    } else if (ui->shapeCombo->currentText() == "polygon") {
        QPolygon polygon;
        polygon << QPoint(75, 93) << QPoint(457, 88) << QPoint(ui->spacer->sizeHint().width() - 135, 345) << QPoint(100, height() - 100) << QPoint(234, 321);
        painter.drawPolygon(polygon);
    } else if (ui->shapeCombo->currentText() == "ellipse") {
        painter.drawEllipse(50, 100, ui->spacer->sizeHint().width() - 100, height() - 200);
    } else {
        int radius = height() - 100;
        painter.drawEllipse(50, 50, radius, radius);
    }
    painter.end();
}

void MainWindow::on_pushButton_clicked() {
    repaint();
}
