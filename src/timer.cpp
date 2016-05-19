#include "timer.h"


Timer::Timer(QObject *parent) : QObject(parent)
{
    m_Qtimer = new QTimer(this);
    //worker = new Worker();
    QObject::connect(m_Qtimer, SIGNAL(timeout()), this, SLOT(test()));
    m_Qtimer->start(SECONDS * 1000);
}

void Timer::test() {
    qDebug() << "Timer start() ";
}
