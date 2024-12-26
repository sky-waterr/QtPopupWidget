#pragma once

#include <QWidget>
#include <QMutex>
#include <qtimer.h>
#include <qdebug.h>
#include "WaterMsgWidget.h"
#include "ui_WaterInfoWidget.h"

class WaterInfoWidget : public QWidget
{
    Q_OBJECT

public:
    WaterInfoWidget(QWidget *parent = nullptr);
    ~WaterInfoWidget();
    static QSharedPointer<WaterInfoWidget> GetInstance(QWidget* parent = nullptr);  // 单例模式
    static void DestroyInstance();  // 清除父窗口的指针
    void ShowMsg(const WaterMsgFlag flag, const QString& msg);

private slots:
    void RemoveWidget();

private:
    Ui::WaterInfoWidgetClass ui;
    static QSharedPointer<WaterInfoWidget> m_instance;
    static QMutex m_mutex;
};
