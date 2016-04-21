/****************************************************************************
** Meta object code from reading C++ file 'filewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Test/filewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileWindow_t {
    QByteArrayData data[22];
    char stringdata0[369];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileWindow_t qt_meta_stringdata_FileWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FileWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 58, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(5, 82, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(6, 106, 13), // "setFileModels"
QT_MOC_LITERAL(7, 120, 13), // "setListWidget"
QT_MOC_LITERAL(8, 134, 14), // "dragEnterEvent"
QT_MOC_LITERAL(9, 149, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(10, 166, 1), // "e"
QT_MOC_LITERAL(11, 168, 14), // "dragLeaveEvent"
QT_MOC_LITERAL(12, 183, 13), // "dragMoveEvent"
QT_MOC_LITERAL(13, 197, 9), // "dropEvent"
QT_MOC_LITERAL(14, 207, 11), // "QDropEvent*"
QT_MOC_LITERAL(15, 219, 27), // "on_listView_2_doubleClicked"
QT_MOC_LITERAL(16, 247, 5), // "index"
QT_MOC_LITERAL(17, 253, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(18, 277, 23), // "on_listView_2_activated"
QT_MOC_LITERAL(19, 301, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(20, 325, 21), // "on_removeFile_clicked"
QT_MOC_LITERAL(21, 347, 21) // "on_listView_2_clicked"

    },
    "FileWindow\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_4_clicked\0setFileModels\0"
    "setListWidget\0dragEnterEvent\0"
    "QDragEnterEvent*\0e\0dragLeaveEvent\0"
    "dragMoveEvent\0dropEvent\0QDropEvent*\0"
    "on_listView_2_doubleClicked\0index\0"
    "on_pushButton_5_clicked\0on_listView_2_activated\0"
    "on_pushButton_6_clicked\0on_removeFile_clicked\0"
    "on_listView_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    1,  100,    2, 0x08 /* Private */,
      11,    1,  103,    2, 0x08 /* Private */,
      12,    1,  106,    2, 0x08 /* Private */,
      13,    1,  109,    2, 0x08 /* Private */,
      15,    1,  112,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    1,  116,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,
      20,    0,  120,    2, 0x08 /* Private */,
      21,    1,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 14,   10,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,

       0        // eod
};

void FileWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileWindow *_t = static_cast<FileWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->setFileModels(); break;
        case 5: _t->setListWidget(); break;
        case 6: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 7: _t->dragLeaveEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 8: _t->dragMoveEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 9: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 10: _t->on_listView_2_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_5_clicked(); break;
        case 12: _t->on_listView_2_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_6_clicked(); break;
        case 14: _t->on_removeFile_clicked(); break;
        case 15: _t->on_listView_2_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FileWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileWindow.data,
      qt_meta_data_FileWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileWindow.stringdata0))
        return static_cast<void*>(const_cast< FileWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
