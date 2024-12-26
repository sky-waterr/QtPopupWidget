#pragma once

#include <qmainwindow.h>
#include "WaterInfoWidget.h"
#include "ui_QtChildWidget.h"

class QtChildWidget : public QMainWindow
{
    Q_OBJECT

public:
    QtChildWidget(QWidget *parent = nullptr);
    ~QtChildWidget();

private slots:
    void SlotOnClickInfoBtn();

private:
    Ui::QtChildWidgetClass ui;
};
