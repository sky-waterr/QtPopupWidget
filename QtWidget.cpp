#include "QtWidget.h"

QtWidget::QtWidget(QWidget *parent)
    : QWidget(parent)
    , m_child()
{
    ui.setupUi(this);

    connect(ui.infoBtn, &QPushButton::clicked, this, &QtWidget::SlotOnClickInfoBtn);
    connect(ui.warningBtn, &QPushButton::clicked, this, &QtWidget::SlotOnClickWarningBtn);
    connect(ui.errorBtn, &QPushButton::clicked, this, &QtWidget::SlotOnClickErrorBtn);
    WaterInfoWidget::GetInstance(this);

    int x = 0; // ��� x ����
    int y = this->height() - WaterInfoWidget::GetInstance()->height(); // �·� y ����
    WaterInfoWidget::GetInstance()->move(this->x() + x, this->y() + y);

    m_child = QSharedPointer<QtChildWidget>(new QtChildWidget(this));
    m_child->show();
}

QtWidget::~QtWidget()
{
}

void QtWidget::closeEvent(QCloseEvent* event)
{
    WaterInfoWidget::GetInstance()->DestroyInstance();
}

void QtWidget::SlotOnClickInfoBtn()
{
    WaterInfoWidget::GetInstance()->ShowMsg(MSG_INFO, "Parent-Widget click");
}

void QtWidget::SlotOnClickWarningBtn()
{
    WaterInfoWidget::GetInstance()->ShowMsg(MSG_WARNING, "Parent-Widget click");
}

void QtWidget::SlotOnClickErrorBtn()
{
    WaterInfoWidget::GetInstance()->ShowMsg(MSG_ERROR, "Parent-Widget click");
}
