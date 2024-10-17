#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->xSpin->setMaximum(ui->area->sizeHint().width());
    ui->ySpin->setMaximum(ui->area->sizeHint().height());
    ui->controlWidget->setAutoFillBackground(true);
    ui->table->horizontalHeader()->setStretchLastSection(true);

    connect(ui->colorBtn, &QPushButton::released, this,
            [this]() {
                QColorDialog colorDialog;
                curColor = colorDialog.getColor();
                QString style = QString("background-color:rgb(%1,%2,%3)")
                                    .arg(curColor.red())
                                    .arg(curColor.green())
                                    .arg(curColor.blue());
                ui->colorBtn->setStyleSheet(style);
            });

    connect(ui->pointBtn, &QPushButton::released, this, &MainWindow::addPoint);
    connect(ui->finishBtn, &QPushButton::released, this, &MainWindow::render);
    connect(ui->newBtn, &QPushButton::released, this, &MainWindow::resetTable);
}

void MainWindow::addPoint() {
    int x = ui->xSpin->value();
    int y = ui->ySpin->value();
    int row = ui->table->rowCount();
    ui->table->insertRow(row);
    ui->table->setItem(row, 0, new QTableWidgetItem(QString::number(x)));

    ui->table->setItem(row, 1, new QTableWidgetItem(QString::number(y)));
    ui->table->setItem(row, 2, new QTableWidgetItem());
    ui->table->item(row, 2)->setBackground(curColor);

    ui->xSpin->setValue(0);
    ui->ySpin->setValue(0);
    if (row >= 2) {
        ui->finishBtn->setEnabled(true);
    }
}

void MainWindow::render() {
    std::vector<QPoint> points;
    std::vector<QColor> colors;
    for (size_t i = 0; i < ui->table->rowCount(); ++i) {
        int x = ui->table->item(i, 0)->text().toInt();
        int y = ui->table->item(i, 1)->text().toInt();
        points.emplace_back(x, y);
        colors.push_back(ui->table->item(i, 2)->background().color());
    }
    ui->table->setRowCount(0);
    ui->finishBtn->setEnabled(false);
    ui->controlWidget->setVisible(false);
    if (curPoly != nullptr) {
        int layer = ui->area->removePolygon(curPoly);
        ui->area->addPolygon(points, colors, layer);
    } else {
        ui->area->addPolygon(points, colors);
    }
    ui->area->repaint();
    curPoly = nullptr;
}

void MainWindow::resetTable() {
    ui->xSpin->setValue(0);
    ui->ySpin->setValue(0);
    ui->finishBtn->setEnabled(false);
    ui->table->setRowCount(0);
    ui->controlWidget->setVisible(true);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (ui->area->underMouse() && !ui->controlWidget->underMouse()) {
        curPoly = ui->area->getPolygonByPoint(QCursor::pos());
        if (curPoly == nullptr) {
            return;
        }
        resetTable();
        ui->finishBtn->setEnabled(true);
        auto points = curPoly->getVertices();
        auto colors = curPoly->getColors();

        for (size_t i = 0; i < std::size(points); ++i) {
            int row = ui->table->rowCount();
            ui->table->insertRow(row);
            ui->table->setItem(row, 0, new
                               QTableWidgetItem(QString::number(points[i].first)));
            ui->table->setItem(row, 1, new
                               QTableWidgetItem(QString::number(points[i].second)));
            ui->table->setItem(row, 2, new QTableWidgetItem());
            ui->table->item(row, 2)->setBackground(colors[i]);
        }
    }
}

void MainWindow::on_table_cellClicked(int row, int col) {
    if (col != 2) {
        return;
    }
    QColorDialog colorPicker;
    QColor newColor = colorPicker.getColor();
    ui->table->item(row, 2)->setBackground(newColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

