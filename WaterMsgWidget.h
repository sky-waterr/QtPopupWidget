#pragma once

#include <QWidget>
#include <QPropertyAnimation>
#include <qtimer.h>
#include "ui_WaterMsgWidget.h"

const int WIDGET_KEEP_TIME = 4000;

enum WaterMsgFlag
{
    MSG_INFO = 0,
    MSG_WARNING,
    MSG_ERROR
};

class WaterMsgWidget : public QWidget
{
    Q_OBJECT

public:
    WaterMsgWidget(QWidget *parent = nullptr);
    ~WaterMsgWidget();
    void SetMsg(const WaterMsgFlag flag, const QString& msg);

signals:
    void SigTimerOut();

private:
    Ui::WaterMsgWidgetClass ui;
    QTimer m_timer;
};
