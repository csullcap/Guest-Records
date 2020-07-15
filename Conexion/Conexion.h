#ifndef PS_CONEXION_H
#define PS_CONEXION_H

#include <mysql.h>
#include <iostream>
#include "../Hotel/Hotel.h"
#include "../Administrador/Administrador.h"

using namespace std;
class Conexion {

    private:
        char * ip = (char*)"sql10.freemysqlhosting.net";
        char * usr = (char*)"sql10352889";
        char * pass = (char*)"ug7jc4mGXp";
        char * db = (char*)"sql10352889";

    public:
        Conexion();
        void iniciarConexion();
        void finalizarConexion();
        Hotel getDatosHotel(int id);
        bool inicioSesion(Administrador &admin,string username,string contra);
        int getfilas(string tabla);
        void addReciboHospedaje(Administrador admin);
        void registrosPendientes();
        void estadoHabitacion();
};
#endif //PS_CONEXION_H
