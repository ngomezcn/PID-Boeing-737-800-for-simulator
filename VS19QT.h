#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VS19QT.h"

class VS19QT : public QMainWindow
{
    Q_OBJECT

public:
    VS19QT(QWidget *parent = Q_NULLPTR);

private:
    Ui::VS19QTClass ui;
};
