#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <memory>
#include <QPainter>
#include <QLineF>
#include <QPointF>

class Polygon
{
public:
    Polygon(const std::vector<QPoint>& points,
            const std::vector<QColor>& colors,
            int layer);

    void draw(QPainter &painter) const;
    bool isInside(QPoint &point) const;
    int getLayer() const;
    std::vector<std::pair<int, int>> getVertices() const;
    std::vector<QColor> getColors() const;

private:
    struct Edge;

    struct Vertex {
        std::weak_ptr<Edge> e1;
        std::weak_ptr<Edge> e2;
        QPoint point;
    };

    struct Edge {
        std::weak_ptr<Vertex> v1;
        std::weak_ptr<Vertex> v2;
        QColor color;
        QLineF vec;
    };


    std::vector<std::shared_ptr<Vertex>> vertices_;
    std::vector<std::shared_ptr<Edge>> edges_;

    int layer_;
    static inline int max_layer_ = 0;
};

#endif // POLYGON_H
