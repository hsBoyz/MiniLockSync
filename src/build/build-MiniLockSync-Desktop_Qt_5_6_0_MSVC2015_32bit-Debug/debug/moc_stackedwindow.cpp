/****************************************************************************
** Meta object code from reading C++ file 'stackedwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stackedwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stackedwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StackedWindow_t {
    QByteArrayData data[10];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StackedWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StackedWindow_t qt_meta_stringdata_StackedWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "StackedWindow"
QT_MOC_LITERAL(1, 14, 17), // "pushManageClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "pushSettingsClicked"
QT_MOC_LITERAL(4, 53, 24), // "pushZurueckManageClicked"
QT_MOC_LITERAL(5, 78, 26), // "pushZurueckSettingsClicked"
QT_MOC_LITERAL(6, 105, 18), // "pushDropboxClicked"
QT_MOC_LITERAL(7, 124, 17), // "pushICloudClicked"
QT_MOC_LITERAL(8, 142, 25), // "pushZurueckDropboxClicked"
QT_MOC_LITERAL(9, 168, 24) // "pushZurueckICloudClicked"

    },
    "StackedWindow\0pushManageClicked\0\0"
    "pushSettingsClicked\0pushZurueckManageClicked\0"
    "pushZurueckSettingsClicked\0"
    "pushDropboxClicked\0pushICloudClicked\0"
    "pushZurueckDropboxClicked\0"
    "pushZurueckICloudClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StackedWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void StackedWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StackedWindow *_t = static_cast<StackedWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pushManageClicked(); break;
        case 1: _t->pushSettingsClicked(); break;
        case 2: _t->pushZurueckManageClicked(); break;
        case 3: _t->pushZurueckSettingsClicked(); break;
        case 4: _t->pushDropboxClicked(); break;
        case 5: _t->pushICloudClicked(); break;
        case 6: _t->pushZurueckDropboxClicked(); break;
        case 7: _t->pushZurueckICloudClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StackedWindow::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_StackedWindow.data,
      qt_meta_data_StackedWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StackedWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StackedWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StackedWindow.stringdata0))
        return static_cast<void*>(const_cast< StackedWindow*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int StackedWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
