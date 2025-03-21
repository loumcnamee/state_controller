#include "ControlSlider.h"
#include <QPainter>
#include <QString>
#include <QFontMetrics>

ControlSlider::ControlSlider(QWidget *parent) : QSlider(parent) {
    // Constructor implementation
}

ControlSlider::~ControlSlider() {
    // Destructor implementation
}

void ControlSlider::paintEvent(QPaintEvent *event) {
    QSlider::paintEvent(event);

    auto painter = new QPainter(this);
    painter->setPen(QPen(Qt::black));

    auto rect = this->geometry();

    int numTicks = (maximum() - minimum())/tickInterval();

    QFontMetrics fontMetrics = QFontMetrics(this->font());

    if (this->orientation() == Qt::Horizontal) {

        int fontHeight = fontMetrics.height();

        for (int i=0; i<=numTicks; i++){

            int tickNum = minimum() + (tickInterval() * i);

            auto tickX = ((rect.width()/numTicks) * i);// - (fontMetrics.averageCharWidth());
            auto tickY = rect.height() - fontHeight;

            painter->drawText(QPoint(tickX, tickY),
                              QString::number(tickNum));
        }

    } else if (this->orientation() == Qt::Vertical) {

        int fontHeight = fontMetrics.height();
        int fontWidth = fontMetrics.averageCharWidth();

        for (int i=0; i<=numTicks; i++){

            int tickNum = minimum() + (tickInterval() * i);

            auto tickY = ((rect.height()/numTicks) * i) - (fontHeight/2);
            auto tickX = rect.width() - fontWidth;

            painter->drawText(QPoint(tickX, tickY),
                              QString::number(tickNum));
        }
    } else {
        return;
    }

    painter->drawRect(rect);
    painter->end();
}
