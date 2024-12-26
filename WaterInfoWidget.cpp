#include "WaterInfoWidget.h"

QSharedPointer<WaterInfoWidget> WaterInfoWidget::m_instance = nullptr;
QMutex WaterInfoWidget::m_mutex;

WaterInfoWidget::WaterInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // ���ô���һֱ����ǰ�����ޱ߿�
}

WaterInfoWidget::~WaterInfoWidget()
{
    // ����ջ�ڵ�Item������ת����widgetɾ��
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
    // ˫����ʵ�ֵ���
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
    // ������Ϣ����
    WaterMsgWidget *widget = new WaterMsgWidget(this);
    widget->SetMsg(flag, msg);
    ui.verticalLayout->insertWidget(ui.verticalLayout->count(), widget);
    connect(widget, &WaterMsgWidget::SigTimerOut, this, &WaterInfoWidget::RemoveWidget);

    // ������Ϣ���ڵ�λ��
    QMargins margins = ui.verticalLayout->contentsMargins();
    int yDistance = ui.verticalLayout->spacing() + widget->height();

    if (ui.verticalLayout->count() > 1) {
        this->resize(this->width(), this->height() + yDistance);
        this->move(this->pos().x(), this->pos().y() - yDistance);
        this->update(); // ��ʱ����widget״̬����֤��������Ч������
    }

    QRect curRect = widget->geometry();
    curRect.setX(curRect.x() + margins.left());
    curRect.setY(this->height() - yDistance);

    // ���ý��붯��
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
        this->update(); // ��ʱ����widget״̬����֤��������Ч������
    }
}
