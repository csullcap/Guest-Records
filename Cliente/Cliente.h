//
// Created by Jerbo on 18/06/2020.
//

#ifndef PS_CLIENTE_H
#define PS_CLIENTE_H
#include "string"

using namespace std;

struct Cliente {

    int id_cliente;
    int id_hotel;
    string nombre;
    string apellidos;
    int estado;
    string telefono;
    string toString() {
        return "Nombre:" + nombre +
               " " + apellidos + ", telefono: " + telefono + "\n";
    }
};

#endif //PS_CLIENTE_H
