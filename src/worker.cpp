#include "worker.h"

Worker::Worker()
{

}


void Worker::run()
{
    for(int i = 0; i < 100; i++) {
        qDebug() << i;

        thread()->msleep(100);
    }
}
