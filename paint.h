#pragma once

#include <QWidget>
#include <QPainter>

class Colours : public QWidget {

public:
    QString command;
    explicit Colours(QWidget *parent = nullptr);
    void next(int t);
    void reset();
    void quit();
protected:
    void paintEvent(QPaintEvent *e) override;

private:
    int w = 10000, h = 10000;
    QPixmap pm;
    void doPainting();
};