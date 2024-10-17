#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "polygon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_table_cellClicked(int row, int col);
private:
    Ui::MainWindow *ui;
    QColor curColor = Qt::black;
    std::shared_ptr<Polygon> curPoly = nullptr;

    void addPoint();
    void render();
    void mousePressEvent(QMouseEvent* event);
    void resetTable();
};
#endif // MAINWINDOW_H
