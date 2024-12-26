#pragma once

#include <QtWidgets/QWidget>
#include "WaterInfoWidget.h"
#include "QtChildWidget.h"
#include "ui_QtWidget.h"

class QtWidget : public QWidget
{
    Q_OBJECT

public:
    QtWidget(QWidget *parent = nullptr);
    ~QtWidget();

public:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void SlotOnClickInfoBtn();
    void SlotOnClickWarningBtn();
    void SlotOnClickErrorBtn();

private:
    Ui::QtWidgetClass ui;
    QSharedPointer<QtChildWidget> m_child;
};
