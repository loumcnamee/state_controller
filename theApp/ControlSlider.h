
#ifndef CONTROLSLIDER_H
#define CONTROLSLIDER_H

#include <QtWidgets/QSlider>


class ControlSlider : public QSlider {
    Q_OBJECT

public:
    explicit ControlSlider(QWidget *parent = nullptr);
    ~ControlSlider();

protected:
    void paintEvent(QPaintEvent *event) override;

    // Add any additional methods or properties here

private:
    // Add any private members here
};


#endif // CONTROLSLIDER_H