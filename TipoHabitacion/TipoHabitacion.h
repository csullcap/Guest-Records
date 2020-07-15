
#ifndef PS_TIPOHABITACION_H
#define PS_TIPOHABITACION_H
#include "string"

using namespace std;

struct TipoHabitacion {
    int id_tipohabitacion;
    int id_hotel;
    string nombre;
    string caracteristicas;
    double precioxhora;
};


#endif //PS_TIPOHABITACION_H
