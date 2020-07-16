#ifndef PS_ADMINISTRADOR_H
#define PS_ADMINISTRADOR_H

#include "string"

using namespace std;

struct Administrador {
    int id_administrador;
    int id_hotel;
    string nombre;
    string apellidos;
    string username;
    string contra;
    string telefono;

    string toString() {
        return "Nombre:" + nombre +
               " " + apellidos + ", username: " + username + ", telefono: " + telefono + "\n";
    }
};

#endif //PS_ADMINISTRADOR_H
