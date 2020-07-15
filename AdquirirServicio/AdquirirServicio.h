#ifndef PS_ADQUIRIRSERVICIO_H
#define PS_ADQUIRIRSERVICIO_H
#include "../Servicio/Servicio.h"

struct  AdquirirServicio {
    int id_adquirirservicio;
    int id_servicio;
    int id_recibohospedaje;
    int cantidad;
    string fecha;
};


#endif //PS_ADQUIRIRSERVICIO_H
