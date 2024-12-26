#include "WaterMsgWidget.h"

WaterMsgWidget::WaterMsgWidget(QWidget *parent)
    : QWidget(parent)
    , m_timer()
{
    ui.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // 设置窗口一直在最前并且无边框

    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &WaterMsgWidget::SigTimerOut);
}

WaterMsgWidget::~WaterMsgWidget()
{
}

void WaterMsgWidget::SetMsg(const WaterMsgFlag flag, const QString& msg)
{
    if (flag == MSG_INFO) {
        ui.uIconLabel->setPixmap(QPixmap(":/QtPopupWidget/IconInfo.png"));
    } else if (flag == MSG_WARNING) {
        ui.uIconLabel->setPixmap(QPixmap(":/QtPopupWidget/IconWarning.png"));
    } else if (flag == MSG_ERROR) {
        ui.uIconLabel->setPixmap(QPixmap(":/QtPopupWidget/IconError.png"));
    }
    ui.uInfoLabel->setText(msg);
    m_timer.start(WIDGET_KEEP_TIME);
}
