/****************************************************************************
** Meta object code from reading C++ file 'maiaObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maiaObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maiaObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MaiaObject_t {
    QByteArrayData data[10];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaiaObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaiaObject_t qt_meta_stringdata_MaiaObject = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MaiaObject"
QT_MOC_LITERAL(1, 11, 9), // "aresponse"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "QVariant&"
QT_MOC_LITERAL(4, 32, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 47, 5), // "reply"
QT_MOC_LITERAL(6, 53, 4), // "call"
QT_MOC_LITERAL(7, 58, 5), // "fault"
QT_MOC_LITERAL(8, 64, 13), // "parseResponse"
QT_MOC_LITERAL(9, 78, 8) // "response"

    },
    "MaiaObject\0aresponse\0\0QVariant&\0"
    "QNetworkReply*\0reply\0call\0fault\0"
    "parseResponse\0response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaiaObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    2,   39,    2, 0x06 /* Public */,
       7,    3,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantList,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 4,    2,    2,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    9,    5,

       0        // eod
};

void MaiaObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaiaObject *_t = static_cast<MaiaObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->aresponse((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        case 1: _t->call((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QList<QVariant>(*)>(_a[2]))); break;
        case 2: _t->fault((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QNetworkReply*(*)>(_a[3]))); break;
        case 3: _t->parseResponse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MaiaObject::*_t)(QVariant & , QNetworkReply * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaiaObject::aresponse)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MaiaObject::*_t)(const QString , const QList<QVariant> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaiaObject::call)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MaiaObject::*_t)(int , const QString & , QNetworkReply * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaiaObject::fault)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MaiaObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MaiaObject.data,
      qt_meta_data_MaiaObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaiaObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaiaObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaiaObject.stringdata0))
        return static_cast<void*>(const_cast< MaiaObject*>(this));
    return QObject::qt_metacast(_clname);
}

int MaiaObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MaiaObject::aresponse(QVariant & _t1, QNetworkReply * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MaiaObject::call(const QString _t1, const QList<QVariant> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MaiaObject::fault(int _t1, const QString & _t2, QNetworkReply * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
