#include "timer.h"
#include "window.h"

int Timer::SECONDS = 0.125 * 60;

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

    QThread *thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), this, SLOT(callWindow()));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), this, SLOT(deleteWorker()));
    thread->start();
}

void Timer::deleteWorker() {
    FileWindow::GetInstance().set_StatusBar_finished();
    Window::GetInstance().set_StatusBar_finished();
    delete worker;
}

void Timer::callWindow() {
    FileWindow::GetInstance().set_StatusBar_started();
    Window::GetInstance().set_StatusBar_started();
}
