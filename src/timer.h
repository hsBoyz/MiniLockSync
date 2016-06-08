#ifndef TIMER_H
#define TIMER_H

#include "worker.h"
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>

class Window;

class Timer : public QObject
{
    Q_OBJECT
public:

    static Timer &GetInstance() {
        static Timer Instanz;
        return Instanz;
    }

    static int SECONDS;

    void start();
    void stop();

private:
    Timer(QObject *parent = 0);
    Timer(const Timer&);
    Timer &operator=(const Timer&);

    QTimer *m_Qtimer;
    Worker *worker;


private slots:
    void deleteWorker();
    void callWindow();

signals:

public slots:
    void process();
};

#endif // TIMER_H
