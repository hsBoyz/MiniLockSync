/****************************************************************************
** Meta object code from reading C++ file 'qtapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_qtApp_t {
    QByteArrayData data[13];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qtApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qtApp_t qt_meta_stringdata_qtApp = {
    {
QT_MOC_LITERAL(0, 0, 5), // "qtApp"
QT_MOC_LITERAL(1, 6, 7), // "setIcon"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 13), // "iconActivated"
QT_MOC_LITERAL(4, 29, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(5, 63, 6), // "reason"
QT_MOC_LITERAL(6, 70, 17), // "loginButton_click"
QT_MOC_LITERAL(7, 88, 21), // "genPasswdButton_click"
QT_MOC_LITERAL(8, 110, 17), // "startButton_click"
QT_MOC_LITERAL(9, 128, 15), // "addButton_click"
QT_MOC_LITERAL(10, 144, 25), // "encryptFolderAction_click"
QT_MOC_LITERAL(11, 170, 23), // "decryptFileAction_click"
QT_MOC_LITERAL(12, 194, 23) // "encryptFileAction_click"

    },
    "qtApp\0setIcon\0\0iconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0loginButton_click\0genPasswdButton_click\0"
    "startButton_click\0addButton_click\0"
    "encryptFolderAction_click\0"
    "decryptFileAction_click\0encryptFileAction_click"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qtApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void qtApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        qtApp *_t = static_cast<qtApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setIcon(); break;
        case 1: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 2: _t->loginButton_click(); break;
        case 3: _t->genPasswdButton_click(); break;
        case 4: _t->startButton_click(); break;
        case 5: _t->addButton_click(); break;
        case 6: _t->encryptFolderAction_click(); break;
        case 7: _t->decryptFileAction_click(); break;
        case 8: _t->encryptFileAction_click(); break;
        default: ;
        }
    }
}

const QMetaObject qtApp::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_qtApp.data,
      qt_meta_data_qtApp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *qtApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qtApp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_qtApp.stringdata0))
        return static_cast<void*>(const_cast< qtApp*>(this));
    return QDialog::qt_metacast(_clname);
}

int qtApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
