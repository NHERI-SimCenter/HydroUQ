/****************************************************************************
** Meta object code from reading C++ file 'scenemodifier.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../source/scenemodifier.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenemodifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SceneModifier_t {
    QByteArrayData data[9];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SceneModifier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SceneModifier_t qt_meta_stringdata_SceneModifier = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SceneModifier"
QT_MOC_LITERAL(1, 14, 11), // "enableTorus"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "enabled"
QT_MOC_LITERAL(4, 35, 10), // "enableCone"
QT_MOC_LITERAL(5, 46, 14), // "enableCylinder"
QT_MOC_LITERAL(6, 61, 12), // "enableCuboid"
QT_MOC_LITERAL(7, 74, 11), // "enablePlane"
QT_MOC_LITERAL(8, 86, 12) // "enableSphere"

    },
    "SceneModifier\0enableTorus\0\0enabled\0"
    "enableCone\0enableCylinder\0enableCuboid\0"
    "enablePlane\0enableSphere"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SceneModifier[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       5,    1,   50,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void SceneModifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SceneModifier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enableTorus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->enableCone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->enableCylinder((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->enableCuboid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->enablePlane((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->enableSphere((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SceneModifier::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SceneModifier.data,
    qt_meta_data_SceneModifier,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SceneModifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SceneModifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SceneModifier.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SceneModifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
