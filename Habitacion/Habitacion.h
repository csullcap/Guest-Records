#ifndef PS_HABITACION_H
#define PS_HABITACION_H
#include "string"

using namespace std;

struct Habitacion {
    int id_habitacion;
    int id_hotel;
    int id_tipohabitacion;
    int piso;
    int estado;
};
#endif //PS_HABITACION_H
