/****************************************************************************
** Meta object code from reading C++ file 'filewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filewindow.h"
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
    QByteArrayData data[31];
    char stringdata0[445];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileWindow_t qt_meta_stringdata_FileWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FileWindow"
QT_MOC_LITERAL(1, 11, 13), // "setFileModels"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 26), // "returnDirectoryCleanedPath"
QT_MOC_LITERAL(4, 53, 4), // "path"
QT_MOC_LITERAL(5, 58, 23), // "returnDirNameFromString"
QT_MOC_LITERAL(6, 82, 17), // "returnRelativPath"
QT_MOC_LITERAL(7, 100, 13), // "copyDropFiles"
QT_MOC_LITERAL(8, 114, 4), // "from"
QT_MOC_LITERAL(9, 119, 10), // "folderName"
QT_MOC_LITERAL(10, 130, 12), // "relativePath"
QT_MOC_LITERAL(11, 143, 9), // "QFileInfo"
QT_MOC_LITERAL(12, 153, 8), // "fileinfo"
QT_MOC_LITERAL(13, 162, 10), // "fileExists"
QT_MOC_LITERAL(14, 173, 8), // "fileInfo"
QT_MOC_LITERAL(15, 182, 10), // "deleteFile"
QT_MOC_LITERAL(16, 193, 14), // "dragEnterEvent"
QT_MOC_LITERAL(17, 208, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(18, 225, 1), // "e"
QT_MOC_LITERAL(19, 227, 14), // "dragLeaveEvent"
QT_MOC_LITERAL(20, 242, 16), // "QDragLeaveEvent*"
QT_MOC_LITERAL(21, 259, 13), // "dragMoveEvent"
QT_MOC_LITERAL(22, 273, 15), // "QDragMoveEvent*"
QT_MOC_LITERAL(23, 289, 9), // "dropEvent"
QT_MOC_LITERAL(24, 299, 11), // "QDropEvent*"
QT_MOC_LITERAL(25, 311, 26), // "on_pushButton_back_clicked"
QT_MOC_LITERAL(26, 338, 21), // "on_listView_activated"
QT_MOC_LITERAL(27, 360, 5), // "index"
QT_MOC_LITERAL(28, 366, 25), // "on_listView_doubleClicked"
QT_MOC_LITERAL(29, 392, 32), // "on_pushButton_deleteFile_clicked"
QT_MOC_LITERAL(30, 425, 19) // "on_listView_clicked"

    },
    "FileWindow\0setFileModels\0\0"
    "returnDirectoryCleanedPath\0path\0"
    "returnDirNameFromString\0returnRelativPath\0"
    "copyDropFiles\0from\0folderName\0"
    "relativePath\0QFileInfo\0fileinfo\0"
    "fileExists\0fileInfo\0deleteFile\0"
    "dragEnterEvent\0QDragEnterEvent*\0e\0"
    "dragLeaveEvent\0QDragLeaveEvent*\0"
    "dragMoveEvent\0QDragMoveEvent*\0dropEvent\0"
    "QDropEvent*\0on_pushButton_back_clicked\0"
    "on_listView_activated\0index\0"
    "on_listView_doubleClicked\0"
    "on_pushButton_deleteFile_clicked\0"
    "on_listView_clicked"
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
       3,    1,   95,    2, 0x08 /* Private */,
       5,    1,   98,    2, 0x08 /* Private */,
       6,    1,  101,    2, 0x08 /* Private */,
       7,    4,  104,    2, 0x08 /* Private */,
      13,    2,  113,    2, 0x08 /* Private */,
      15,    3,  118,    2, 0x08 /* Private */,
      16,    1,  125,    2, 0x08 /* Private */,
      19,    1,  128,    2, 0x08 /* Private */,
      21,    1,  131,    2, 0x08 /* Private */,
      23,    1,  134,    2, 0x08 /* Private */,
      25,    0,  137,    2, 0x08 /* Private */,
      26,    1,  138,    2, 0x08 /* Private */,
      28,    1,  141,    2, 0x08 /* Private */,
      29,    0,  144,    2, 0x08 /* Private */,
      30,    1,  145,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 11,    8,    9,   10,   12,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    4,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 11,    9,   10,   14,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   18,
    QMetaType::Void, 0x80000000 | 22,   18,
    QMetaType::Void, 0x80000000 | 24,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   27,
    QMetaType::Void, QMetaType::QModelIndex,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   27,

       0        // eod
};

void FileWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileWindow *_t = static_cast<FileWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFileModels(); break;
        case 1: { QString _r = _t->returnDirectoryCleanedPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->returnDirNameFromString((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->returnRelativPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->copyDropFiles((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QFileInfo(*)>(_a[4]))); break;
        case 5: _t->fileExists((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QFileInfo(*)>(_a[2]))); break;
        case 6: _t->deleteFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QFileInfo(*)>(_a[3]))); break;
        case 7: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 8: _t->dragLeaveEvent((*reinterpret_cast< QDragLeaveEvent*(*)>(_a[1]))); break;
        case 9: _t->dragMoveEvent((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 10: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_back_clicked(); break;
        case 12: _t->on_listView_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->on_listView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: _t->on_pushButton_deleteFile_clicked(); break;
        case 15: _t->on_listView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFileInfo >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFileInfo >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFileInfo >(); break;
            }
            break;
        }
    }
}

const QMetaObject FileWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FileWindow.data,
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
    return QMainWindow::qt_metacast(_clname);
}

int FileWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
