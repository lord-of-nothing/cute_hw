#include "polygon.h"
#include <QRandomGenerator>

int Polygon::getLayer() const {
    return layer_;
}

Polygon::Polygon(const std::vector<QPoint>& points,
                 const std::vector<QColor>& colors,
                 int layer) {
    if (layer == -1) {
        layer_ = max_layer_++;
    } else {
        layer_ = layer;
    }
    for (size_t i = 0; i < std::size(points); ++i) {
        std::shared_ptr<Vertex> v(new Vertex);
        vertices_.push_back(v);
        std::shared_ptr<Edge> e(new Edge);
        edges_.push_back(e);
    }
    for (size_t i = 0; i < std::size(points); ++i) {
        vertices_[i]->e1 = edges_[i];
        vertices_[i]->e2 = edges_[(i + 1) % std::size(points)];
        vertices_[i]->point = points[i];

        edges_[i]->v1 = vertices_[i];
        edges_[i]->v2 = vertices_[(i + 1) % std::size(points)];
        edges_[i]->color = colors[i];
        edges_[i]->vec.setPoints(points[i], points[(i + 1) % std::size(points)]);
    }

}

void Polygon::draw(QPainter &painter) const {
    QPen pen;
    pen.setWidth(3);
    for (const auto& edge : edges_) {
        pen.setColor(edge->color);
        painter.setPen(pen);
        painter.drawLine(edge->vec);
    }
}

bool Polygon::isInside(QPoint &point) const {
    int x = QRandomGenerator::global()->bounded(0, 2000);
    int y = QRandomGenerator::global()->bounded(0, 2000);
    QLineF ray{point, QPoint(x, y)};
    int count = 0;
    for (int i = 0; i < std::size(edges_); ++i) {
        QPointF intersection;
        auto result = ray.intersects(edges_[i]->vec, &intersection);
        if (result != 1) {
            continue;
        }
        if (intersection == point) {
            return true;
        }
        if (edges_[i]->v1.lock()->point == intersection ||
            edges_[i]->v2.lock()->point == intersection) {
            i = 0;
            x = QRandomGenerator::global()->bounded(0, 2000);
            y = QRandomGenerator::global()->bounded(0, 2000);
            ray.setP2(QPoint(x, y));
            continue;
        }
        ++count;
    }
    return count % 2 != 0;
}

std::vector<std::pair<int, int>> Polygon::getVertices() const {
    std::vector<std::pair<int, int>> result;
    for (const auto& v : vertices_) {
        result.emplace_back(v->point.x(), v->point.y());
    }
    return result;
}

std::vector<QColor> Polygon::getColors() const {
    std::vector<QColor> result;
    for (const auto& e : edges_) {
        result.push_back(e->color);
    }
    return result;
}
