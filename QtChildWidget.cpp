#include "QtChildWidget.h"

QtChildWidget::QtChildWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &QtChildWidget::SlotOnClickInfoBtn);
}

QtChildWidget::~QtChildWidget()
{}

void QtChildWidget::SlotOnClickInfoBtn()
{
    WaterInfoWidget::GetInstance()->ShowMsg(MSG_INFO, "Child-Widget click");
}
