#ifndef PS_CONEXION_H
#define PS_CONEXION_H

#include <mysql.h>
#include <iostream>
#include <vector>
#include "../Hotel/Hotel.h"
#include "../Administrador/Administrador.h"
#include "../Cliente/Cliente.h"
#include "../Habitacion/Habitacion.h"
#include "../TipoHabitacion/TipoHabitacion.h"

using namespace std;
class Conexion {

    private:
        char * ip = (char*)"sql10.freemysqlhosting.net";
        char * usr = (char*)"sql10359017";
        char * pass = (char*)"n9RsYjIbRC";
        char * db = (char*)"sql10359017";

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
        std::vector<Administrador> getAdministradores();
        void insertarNuevoAdministrador(Administrador administrador);
        Administrador buscarPorNombre(string s);
        void actualizarAdministrador(Administrador administrador);
        void eliminarAdministrador(int i);
        void insertarNuevoCliente(Cliente cliente);
        Cliente buscarClientePorNombre(string nombre);
        void actualizarCliente(Cliente cliente);
        void eliminarCliente(int i);
        std::vector<Cliente> getClientes();
        void verTodosRegistros();
        void consultaHabitaciones();
        void consultaNombreClientes();
        void agregarReservacion(string idReservacion, string idHabitacion, string idCliente, string fecha);
        void consultaReservaciones();
        void buscarReservacion(string id);
        void modificarReservacion(string idReservacion, string idHabitacion, string idCliente, string fecha);
        void eliminarReservacion(string idReservacion);
        void consultaServicios();
        void buscarServicios(string id);
        void agregarServicio(string idServicio, string nombre, string precio);
        void modificarServicio(string idServicio, string nombre, string precio);
        void eliminarServicio(string idReservacion);
        void terminar_registro(int id);
        void agregaradquirirservicio(int id);
        int gettipoHabitacion(int id);
        double getcostoTipoHabitacion(int id);
        double getcostototal(int id);
        double getcostoServicio(int id);
        double getcostoRecibo(int id);
};
#endif //PS_CONEXION_H
