/****************************************************************************
** Meta object code from reading C++ file 'maiaXmlRpcServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maiaXmlRpcServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaXmlRpcServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MaiaXmlRpcServer_t {
    QByteArrayData data[9];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaiaXmlRpcServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaiaXmlRpcServer_t qt_meta_stringdata_MaiaXmlRpcServer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MaiaXmlRpcServer"
QT_MOC_LITERAL(1, 17, 9), // "getMethod"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "method"
QT_MOC_LITERAL(4, 35, 9), // "QObject**"
QT_MOC_LITERAL(5, 45, 14), // "responseObject"
QT_MOC_LITERAL(6, 60, 12), // "const char**"
QT_MOC_LITERAL(7, 73, 12), // "responseSlot"
QT_MOC_LITERAL(8, 86, 13) // "newConnection"

    },
    "MaiaXmlRpcServer\0getMethod\0\0method\0"
    "QObject**\0responseObject\0const char**\0"
    "responseSlot\0newConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaiaXmlRpcServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x0a /* Public */,
       8,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void,

       0        // eod
};

void MaiaXmlRpcServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaiaXmlRpcServer *_t = static_cast<MaiaXmlRpcServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getMethod((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject**(*)>(_a[2])),(*reinterpret_cast< const char**(*)>(_a[3]))); break;
        case 1: _t->newConnection(); break;
        default: ;
        }
    }
}

const QMetaObject MaiaXmlRpcServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaXmlRpcServer.data,
      qt_meta_data_MaiaXmlRpcServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaiaXmlRpcServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaiaXmlRpcServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaXmlRpcServer.stringdata0))
        return static_cast<void*>(const_cast< MaiaXmlRpcServer*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaXmlRpcServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
