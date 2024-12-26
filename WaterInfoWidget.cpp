#include "WaterInfoWidget.h"

QSharedPointer<WaterInfoWidget> WaterInfoWidget::m_instance = nullptr;
QMutex WaterInfoWidget::m_mutex;

WaterInfoWidget::WaterInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // 设置窗口一直在最前并且无边框
}

WaterInfoWidget::~WaterInfoWidget()
{
    // 清理栈内的Item，并且转换成widget删除
    while (ui.verticalLayout->count() != 0) {
        QLayoutItem* item = ui.verticalLayout->takeAt(ui.verticalLayout->count() - 1);
        if (item->widget() != nullptr) {
            delete item->widget();
        }
        delete item;
    }
}

QSharedPointer<WaterInfoWidget> WaterInfoWidget::GetInstance(QWidget* parent)
{
    // 双检锁实现单例
    if (m_instance == nullptr) {
        m_mutex.lock();
        if (m_instance == nullptr) {
            m_instance = QSharedPointer<WaterInfoWidget>(new WaterInfoWidget(parent));
        }
        m_mutex.unlock();
    }
    return m_instance;
}

void WaterInfoWidget::DestroyInstance()
{
    QMutexLocker locker(&m_mutex);
    if (m_instance) {
        m_instance.clear();
    }
}

void WaterInfoWidget::ShowMsg(const WaterMsgFlag flag, const QString& msg)
{
    // 创建消息窗口
    WaterMsgWidget *widget = new WaterMsgWidget(this);
    widget->SetMsg(flag, msg);
    ui.verticalLayout->insertWidget(ui.verticalLayout->count(), widget);
    connect(widget, &WaterMsgWidget::SigTimerOut, this, &WaterInfoWidget::RemoveWidget);

    // 计算消息窗口的位置
    QMargins margins = ui.verticalLayout->contentsMargins();
    int yDistance = ui.verticalLayout->spacing() + widget->height();

    if (ui.verticalLayout->count() > 1) {
        this->resize(this->width(), this->height() + yDistance);
        this->move(this->pos().x(), this->pos().y() - yDistance);
        this->update(); // 及时更新widget状态，保证后续动画效果流畅
    }

    QRect curRect = widget->geometry();
    curRect.setX(curRect.x() + margins.left());
    curRect.setY(this->height() - yDistance);

    // 设置进入动画
    QRect starRect = curRect;
    starRect.setX(starRect.x() + 200);
    QPropertyAnimation* animation = new QPropertyAnimation(widget, "geometry");
    animation->setDuration(150);
    animation->setStartValue(starRect);
    animation->setEndValue(curRect);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    this->show();
}

void WaterInfoWidget::RemoveWidget()
{
    WaterMsgWidget* widget = qobject_cast<WaterMsgWidget*>(sender());
    ui.verticalLayout->removeWidget(widget);
    widget->deleteLater();

    if (ui.verticalLayout->count() == 0) {
        this->close();
    } else {
        this->move(this->pos().x(), this->pos().y() + 50);
        this->resize(this->width(), this->height() - 50);
        this->update(); // 及时更新widget状态，保证后续动画效果流畅
    }
}
