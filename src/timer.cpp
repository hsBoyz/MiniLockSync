#include "timer.h"


int Timer::SECONDS = 5 * 60;

Timer::Timer(QObject *parent) : QObject(parent)
{
    m_Qtimer = new QTimer(this);
    worker = new Worker();

    QObject::connect(m_Qtimer, SIGNAL(timeout()), this, SLOT(process()));
}

void Timer::start() {
    m_Qtimer->start(SECONDS * 1000);
}

void Timer::stop() {
    m_Qtimer->stop();
}

void Timer::process() {
    qDebug() << "Timer process: Sync";

    QThread *thread = new QThread();

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process())) ;
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    thread->start();
}
