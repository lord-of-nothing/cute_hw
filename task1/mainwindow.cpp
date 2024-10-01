#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->copyTextButton, &QPushButton::released, this, &MainWindow::moveText);
    ui->stickyButton->setCheckable(true);
    connect(ui->stickyButton, &QPushButton::released, this, [this](){qWarning() << "lower button clicked";});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveText() {
    qWarning() << "upper button clicked";
    QString data = ui->textInput->toPlainText();
    qWarning() << "text: " << data;
    ui->textOutput->setPlainText(data);
    qWarning() << "lower text updated";
}
