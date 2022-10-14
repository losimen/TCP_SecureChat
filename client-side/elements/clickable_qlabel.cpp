#include "clickable_qlabel.h"


clickable_qlabel::clickable_qlabel(QWidget *parent):
    QLabel(parent)
{

}

void clickable_qlabel::mousePressEvent(QMouseEvent *ev)
{
    emit clickable_qlabel::on_mousePressed();
}
