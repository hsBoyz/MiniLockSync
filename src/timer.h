#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <worker.h>
#include <QDebug>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = 0);

private:
    QTimer *m_Qtimer;
    Worker *worker;

    const int SECONDS = 15;
signals:

public slots:
    void test();
};

#endif // TIMER_H
