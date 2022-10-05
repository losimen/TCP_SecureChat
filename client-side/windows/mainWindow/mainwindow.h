#pragma once

#include "iwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public IWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void do_parseResponce(QByteArray buffer);

private:
    Ui::MainWindow *ui;

};
