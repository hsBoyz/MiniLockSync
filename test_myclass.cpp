#include <QtCore>
#include <QtTest>

#include "myclass.h"

class test_MyClass : public QObject
{
    Q_OBJECT

private slots:
    void myInt();
};

void test_MyClass::myInt()
{
    MyClass myClass;
    QCOMPARE(myClass.myInt(), 0);
}
 
QTEST_GUILESS_MAIN(test_MyClass)
 
#include "test_myclass.moc"