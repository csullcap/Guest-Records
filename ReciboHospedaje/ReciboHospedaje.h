#ifndef PS_RECIBOHOSPEDAJE_H
#define PS_RECIBOHOSPEDAJE_H
#include "string"
#include "../Cliente/Cliente.h"
#include "../Administrador/Administrador.h"
#include "../AdquirirServicio/AdquirirServicio.h"
#include <vector>
using namespace std;

struct ReciboHospedaje {
    int id_recibohospedaje;
    int id_habitacion;
    int id_reservacion;
    int id_administrador;
    int costo=0;
    int estado; //0 activo 1 terminado 2 cancelado
    string fecha_inicio;
    string fecha_final;
};

#endif //PS_RECIBOHOSPEDAJE_H
