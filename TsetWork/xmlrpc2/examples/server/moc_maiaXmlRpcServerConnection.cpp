/****************************************************************************
** Meta object code from reading C++ file 'maiaXmlRpcServerConnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maiaXmlRpcServerConnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaXmlRpcServerConnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MaiaXmlRpcServerConnection_t {
    QByteArrayData data[9];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaiaXmlRpcServerConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaiaXmlRpcServerConnection_t qt_meta_stringdata_MaiaXmlRpcServerConnection = {
    {
QT_MOC_LITERAL(0, 0, 26), // "MaiaXmlRpcServerConnection"
QT_MOC_LITERAL(1, 27, 9), // "getMethod"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "method"
QT_MOC_LITERAL(4, 45, 9), // "QObject**"
QT_MOC_LITERAL(5, 55, 14), // "responseObject"
QT_MOC_LITERAL(6, 70, 12), // "const char**"
QT_MOC_LITERAL(7, 83, 12), // "responseSlot"
QT_MOC_LITERAL(8, 96, 14) // "readFromSocket"

    },
    "MaiaXmlRpcServerConnection\0getMethod\0"
    "\0method\0QObject**\0responseObject\0"
    "const char**\0responseSlot\0readFromSocket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaiaXmlRpcServerConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MaiaXmlRpcServerConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaiaXmlRpcServerConnection *_t = static_cast<MaiaXmlRpcServerConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getMethod((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject**(*)>(_a[2])),(*reinterpret_cast< const char**(*)>(_a[3]))); break;
        case 1: _t->readFromSocket(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MaiaXmlRpcServerConnection::*_t)(QString , QObject * * , const char * * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaiaXmlRpcServerConnection::getMethod)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MaiaXmlRpcServerConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaXmlRpcServerConnection.data,
      qt_meta_data_MaiaXmlRpcServerConnection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaiaXmlRpcServerConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaiaXmlRpcServerConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaXmlRpcServerConnection.stringdata0))
        return static_cast<void*>(const_cast< MaiaXmlRpcServerConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaXmlRpcServerConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MaiaXmlRpcServerConnection::getMethod(QString _t1, QObject * * _t2, const char * * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
