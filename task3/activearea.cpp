#include "activearea.h"
#include <algorithm>

ActiveArea::ActiveArea(QWidget *parent) : QWidget(parent) {
}

void ActiveArea::addPolygon(const std::vector<QPoint>& points,
                            const std::vector<QColor>& colors,
                            int layer) {
    polygons_.emplace_back(points, colors, layer);
}

void ActiveArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.begin(this);
    for (const auto& elem : polygons_) {
        elem.draw(painter);
    }
    painter.end();
}

std::shared_ptr<Polygon> ActiveArea::getPolygonByPoint(QPoint point) const {
    QPoint target{0, 0};
    std::vector<std::shared_ptr<Polygon>> candidates;

    for (const auto& poly : polygons_) {
        if (poly.isInside(point)) {
            candidates.push_back(std::make_shared<Polygon>(poly));
        }
    }

    if (!std::size(candidates)) {
        return nullptr;
    }

    size_t idx_max = 0;
    int layer_max = 0;
    for (size_t i = 0; i < std::size(candidates); ++i) {
        if (candidates[i]->getLayer() > layer_max) {
            layer_max = candidates[i]->getLayer();
            idx_max = i;
        }
    }
    return candidates[idx_max];
}

int ActiveArea::removePolygon(std::shared_ptr<Polygon> ptr) {
    int layer = ptr->getLayer();
    auto poly = std::find_if(polygons_.begin(), polygons_.end(),
                             [layer](const Polygon& p) { return p.getLayer() == layer;});
    polygons_.erase(poly);
    return layer;
}
