/****************************************************************************
** Meta object code from reading C++ file 'trafficsimulator.h'
**
** Created: Tue Mar 13 01:17:34 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../traffic_simulator/main/trafficsimulator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trafficsimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrafficSimulator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   18,   17,   17, 0x0a,
      52,   18,   17,   17, 0x0a,
      80,   18,   17,   17, 0x0a,
     108,   17,   17,   17, 0x0a,
     120,   17,   17,   17, 0x0a,
     147,   17,   17,   17, 0x0a,
     179,  171,   17,   17, 0x0a,
     204,   17,   17,   17, 0x0a,
     220,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TrafficSimulator[] = {
    "TrafficSimulator\0\0afficher\0"
    "OnAfficherVelocite(bool)\0"
    "OnAfficherForceMoteur(bool)\0"
    "OnAfficherFrottements(bool)\0OnHorloge()\0"
    "OnLectureArretSimulation()\0"
    "OnOuvertureSimulation()\0vitesse\0"
    "OnReglageVitesseSim(int)\0OnZoomArriere()\0"
    "OnZoomAvant()\0"
};

void TrafficSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TrafficSimulator *_t = static_cast<TrafficSimulator *>(_o);
        switch (_id) {
        case 0: _t->OnAfficherVelocite((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->OnAfficherForceMoteur((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->OnAfficherFrottements((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->OnHorloge(); break;
        case 4: _t->OnLectureArretSimulation(); break;
        case 5: _t->OnOuvertureSimulation(); break;
        case 6: _t->OnReglageVitesseSim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->OnZoomArriere(); break;
        case 8: _t->OnZoomAvant(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TrafficSimulator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TrafficSimulator::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TrafficSimulator,
      qt_meta_data_TrafficSimulator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrafficSimulator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrafficSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrafficSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrafficSimulator))
        return static_cast<void*>(const_cast< TrafficSimulator*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TrafficSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
