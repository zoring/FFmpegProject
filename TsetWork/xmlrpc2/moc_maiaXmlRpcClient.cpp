/****************************************************************************
** Meta object code from reading C++ file 'maiaXmlRpcClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "maiaXmlRpcClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaXmlRpcClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MaiaXmlRpcClient_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaiaXmlRpcClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaiaXmlRpcClient_t qt_meta_stringdata_MaiaXmlRpcClient = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MaiaXmlRpcClient"
QT_MOC_LITERAL(1, 17, 9), // "sslErrors"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 43, 5), // "reply"
QT_MOC_LITERAL(5, 49, 16), // "QList<QSslError>"
QT_MOC_LITERAL(6, 66, 6), // "errors"
QT_MOC_LITERAL(7, 73, 13) // "replyFinished"

    },
    "MaiaXmlRpcClient\0sslErrors\0\0QNetworkReply*\0"
    "reply\0QList<QSslError>\0errors\0"
    "replyFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaiaXmlRpcClient[] = {

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
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void MaiaXmlRpcClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaiaXmlRpcClient *_t = static_cast<MaiaXmlRpcClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        case 1: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MaiaXmlRpcClient::*_t)(QNetworkReply * , const QList<QSslError> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaiaXmlRpcClient::sslErrors)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MaiaXmlRpcClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaXmlRpcClient.data,
      qt_meta_data_MaiaXmlRpcClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaiaXmlRpcClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaiaXmlRpcClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaXmlRpcClient.stringdata0))
        return static_cast<void*>(const_cast< MaiaXmlRpcClient*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaXmlRpcClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MaiaXmlRpcClient::sslErrors(QNetworkReply * _t1, const QList<QSslError> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
