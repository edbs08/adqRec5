/****************************************************************************
** Meta object code from reading C++ file 'viewer_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../viewer_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewerWidget_t {
    QByteArrayData data[14];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewerWidget_t qt_meta_stringdata_ViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ViewerWidget"
QT_MOC_LITERAL(1, 13, 10), // "alphaSlide"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "loadFile"
QT_MOC_LITERAL(4, 34, 9), // "saveImage"
QT_MOC_LITERAL(5, 44, 14), // "SortingChanged"
QT_MOC_LITERAL(6, 59, 12), // "ColorChanged"
QT_MOC_LITERAL(7, 72, 5), // "index"
QT_MOC_LITERAL(8, 78, 15), // "update_slider_R"
QT_MOC_LITERAL(9, 94, 1), // "R"
QT_MOC_LITERAL(10, 96, 15), // "update_slider_G"
QT_MOC_LITERAL(11, 112, 1), // "G"
QT_MOC_LITERAL(12, 114, 15), // "update_slider_B"
QT_MOC_LITERAL(13, 130, 1) // "B"

    },
    "ViewerWidget\0alphaSlide\0\0loadFile\0"
    "saveImage\0SortingChanged\0ColorChanged\0"
    "index\0update_slider_R\0R\0update_slider_G\0"
    "G\0update_slider_B\0B"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewerWidget[] = {

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
       1,    1,   54,    2, 0x0a /* Public */,
       3,    0,   57,    2, 0x0a /* Public */,
       4,    0,   58,    2, 0x0a /* Public */,
       5,    1,   59,    2, 0x0a /* Public */,
       6,    1,   62,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void ViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewerWidget *_t = static_cast<ViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->alphaSlide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->loadFile(); break;
        case 2: _t->saveImage(); break;
        case 3: _t->SortingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ColorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->update_slider_R((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->update_slider_G((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->update_slider_B((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ViewerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewerWidget.data,
      qt_meta_data_ViewerWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewerWidget.stringdata0))
        return static_cast<void*>(const_cast< ViewerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
