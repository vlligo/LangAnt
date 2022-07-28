#include <QPainter>
#include "paint.h"

Colours::Colours(QWidget* parent) : QWidget(parent), pm(10000, 10000) {
    pm.fill();
}

void Colours::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    doPainting();
}

void Colours::doPainting() {
    QPainter painter(this);
    painter.setPen(Qt::black);

    painter.drawPixmap(0, 0, w, h, pm);
}

void Colours::next(int t) {
    QPainter painter(&pm);
    painter.setPen(Qt::black);
    painter.drawRect(0 + t / 10, 0 + t / 10, 100 + t / 100, 100 + t / 100);
    update();
}

void Colours::reset() {
    pm.fill();
    update();
}

void Colours::quit() {
//    this->destroy();
    this->close();
}
