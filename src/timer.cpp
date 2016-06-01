#include "timer.h"
#include <QScopedPointer>


int Timer::SECONDS = 0.25 * 60;

Timer::Timer(QObject *parent) : QObject(parent)
{
    m_Qtimer = new QTimer(this);

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
    //Use QScopedPointer to delete object and ptr when leaving scope
    {
        QThread *thread = new QThread();
        QScopedPointer<Worker> worker(new Worker());
        worker.data()->moveToThread(thread);
        connect(thread, SIGNAL(started()), worker.data(), SLOT(process())) ;
        connect(worker.data(), SIGNAL(finished()), thread, SLOT(quit()));
        thread->start();
    }

}
