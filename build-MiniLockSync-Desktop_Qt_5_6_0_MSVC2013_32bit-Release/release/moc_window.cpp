/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[15];
    char stringdata0[405];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Window"
QT_MOC_LITERAL(1, 7, 19), // "on_pushHome_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 27), // "on_pushCloudService_clicked"
QT_MOC_LITERAL(4, 56, 26), // "on_pushManageCloud_clicked"
QT_MOC_LITERAL(5, 83, 28), // "on_pushCPULimitation_clicked"
QT_MOC_LITERAL(6, 112, 29), // "on_pushChangePassword_clicked"
QT_MOC_LITERAL(7, 142, 28), // "on_pushButton_addDir_clicked"
QT_MOC_LITERAL(8, 171, 31), // "on_pushButton_deleteDir_clicked"
QT_MOC_LITERAL(9, 203, 32), // "on_pushButton_addWorkDir_clicked"
QT_MOC_LITERAL(10, 236, 32), // "on_pushButton_addSaveDir_clicked"
QT_MOC_LITERAL(11, 269, 28), // "on_pushManageSaveDir_clicked"
QT_MOC_LITERAL(12, 298, 33), // "on_pushButton_deleteDir_2_cli..."
QT_MOC_LITERAL(13, 332, 29), // "on_pushButton_confirm_clicked"
QT_MOC_LITERAL(14, 362, 42) // "on_pushButton_setdefaultopena..."

    },
    "Window\0on_pushHome_clicked\0\0"
    "on_pushCloudService_clicked\0"
    "on_pushManageCloud_clicked\0"
    "on_pushCPULimitation_clicked\0"
    "on_pushChangePassword_clicked\0"
    "on_pushButton_addDir_clicked\0"
    "on_pushButton_deleteDir_clicked\0"
    "on_pushButton_addWorkDir_clicked\0"
    "on_pushButton_addSaveDir_clicked\0"
    "on_pushManageSaveDir_clicked\0"
    "on_pushButton_deleteDir_2_clicked\0"
    "on_pushButton_confirm_clicked\0"
    "on_pushButton_setdefaultopenaction_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushHome_clicked(); break;
        case 1: _t->on_pushCloudService_clicked(); break;
        case 2: _t->on_pushManageCloud_clicked(); break;
        case 3: _t->on_pushCPULimitation_clicked(); break;
        case 4: _t->on_pushChangePassword_clicked(); break;
        case 5: _t->on_pushButton_addDir_clicked(); break;
        case 6: _t->on_pushButton_deleteDir_clicked(); break;
        case 7: _t->on_pushButton_addWorkDir_clicked(); break;
        case 8: _t->on_pushButton_addSaveDir_clicked(); break;
        case 9: _t->on_pushManageSaveDir_clicked(); break;
        case 10: _t->on_pushButton_deleteDir_2_clicked(); break;
        case 11: _t->on_pushButton_confirm_clicked(); break;
        case 12: _t->on_pushButton_setdefaultopenaction_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata0))
        return static_cast<void*>(const_cast< Window*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
