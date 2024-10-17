#ifndef ACTIVEAREA_H
#define ACTIVEAREA_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "polygon.h"
#include "mainwindow.h"

class ActiveArea : public QWidget
{
public:
    explicit ActiveArea(QWidget *parent = nullptr);
    void addPolygon(const std::vector<QPoint>& points,
                    const std::vector<QColor>& colors,
                    int layer = -1);
    std::shared_ptr<Polygon> getPolygonByPoint(QPoint point) const;
    int removePolygon(std::shared_ptr<Polygon>);
protected:
    void paintEvent(QPaintEvent *event);
private:

    std::vector<Polygon> polygons_;
    Ui::MainWindow* ui;

};

#endif // ACTIVEAREA_H
