#pragma once

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>


class clickable_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickable_qlabel(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *ev);

signals:
    void on_mousePressed();

};
