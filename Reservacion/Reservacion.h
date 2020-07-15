#ifndef PS_RESERVACION_H
#define PS_RESERVACION_H

#include "string"
using namespace std;

class Reservacion {
    int id_reservacion;
    int id_habitacion;
    int id_cliente;
    string fecha;
    int estado;
};


#endif //PS_RESERVACION_H
