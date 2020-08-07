#include "Conexion.h"
#include <string>

#define convertToString(x) #x

#include "../Habitacion/Habitacion.h"
#include "../ReciboHospedaje/ReciboHospedaje.h"
#include "../Cliente/Cliente.h"
#include "../ReciboHospedaje_Cliente/ReciboHospedaje_Cliente.h"

MYSQL mysql, *connection;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

Conexion::Conexion() {
    iniciarConexion();
}

void Conexion::iniciarConexion() {
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, ip, usr, pass, db, 3306, NULL, 0);
    if (connection == NULL) {
        cout << mysql_error(&mysql) << endl;
    }
}

void Conexion::finalizarConexion() {
    mysql_close(&mysql);
}

Hotel Conexion::getDatosHotel(int id) {
    Hotel aux;
    string query = "SELECT * FROM hotel WHERE id_hotel=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux.id_hotel = atoi(row[0]);
        aux.nombre = row[1];
        aux.direccion = row[2];
        aux.telefono = row[3];
    }
    return aux;
}

bool Conexion::inicioSesion(Administrador &admin, string username, string contra) {
    string query = "SELECT * FROM administrador WHERE username='" + username + "' AND contra='" + contra + "'";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        if (result->row_count == 0)
            return false;
        else {
            row = mysql_fetch_row(result);
            admin.id_administrador = atoi(row[0]);
            admin.id_hotel = atoi(row[1]);
            admin.nombre = row[2];
            admin.apellidos = row[3];
            admin.username = row[4];
            admin.contra = row[5];
            admin.telefono = row[6];
            return true;
        }
    } else {
        cout << "Ocurrio un problema" << endl;
    }
    return false;
}

int Conexion::getfilas(string tabla) {
    int filas;
    string query = "SELECT * FROM " + tabla + "";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        filas = result->row_count;
    }
    return filas;
}

void Conexion::addReciboHospedaje(Administrador admin) {
    ReciboHospedaje aux;
    aux.id_recibohospedaje = getfilas("recibohospedaje") + 1;
    cout << "Nuevo Registro" << endl;
    cout << "Nro de Habitacion: ";
    cin >> aux.id_habitacion;
    aux.id_administrador = admin.id_administrador;
    aux.estado = 0;
    cout<<"Ingrese el numero de dias :"<<endl;
    cin>>aux.dias;
    aux.costo=gettipoHabitacion(aux.id_habitacion)*getcostoTipoHabitacion(aux.id_habitacion);
    string query =
            "INSERT INTO recibohospedaje (id_recibohospedaje,id_habitacion,id_administrador,dias,costo,estado,fecha_inicio) VALUES (" +
            to_string(aux.id_recibohospedaje) + "," + to_string(aux.id_habitacion)+ "," +
            to_string(aux.id_administrador) + "," +to_string(aux.dias)+","+ to_string(aux.costo) + "," + to_string(aux.estado) + ",CURDATE())";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Registro exitoso" << endl;
        cout << "Registro de Clientes :" << endl;
        char rpta = '1';
        ReciboHopedaje_Cliente temp;
        do {
            temp.id_recibohospedaje = aux.id_recibohospedaje;
            cout << "Ingrese el codigo del cliente : ";
            cin >> temp.id_cliente;
            query = "INSERT INTO reciboshospedaje_clientes (id_recibohospedaje,id_cliente) VALUES (" +
                    to_string(temp.id_recibohospedaje) + "," + to_string(temp.id_cliente) + ")";
            query_state = mysql_query(connection, query.c_str());
            if (!query_state) {
                cout <<endl<<"Registro exitoso" << endl;
                cout << "Desea ingresar mas clientes (1)SI (2)NO : ";
                cin >> rpta;
                cout<<endl;
            } else {
                cout << "Ocurrio un problema" << endl;
                cout << "Intente de nuevo" << endl;
            }
        } while (rpta != '2');
        cout << "Se Termino el Registro de Hospedaje Exitosamente" << endl;
        system("pause");
        system("cls");
    } else {
        cout << "Ocurrio un problema" << endl;
    }
}

void Conexion::registrosPendientes() {
    string query = "SELECT * FROM recibohospedaje WHERE estado= 0";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        if (result->row_count == 0) {
            cout << "vacio" << endl;
        } else {
            while (row = mysql_fetch_row(result)) {
                cout << "id:" << row[0] << " Habitacion: " << row[1] << " Fecha Inscripcion: " << row[6] << endl;
            }
        }

    } else {
        cout << "Ocurrio un problema" << endl;

    }
}

void Conexion::estadoHabitacion() {
    string query = "SELECT * FROM habitacion";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        if (result->row_count == 0) {
            cout << "vacio" << endl;
        } else {
            while (row = mysql_fetch_row(result)) {
                cout << "Nro Habitacion : " << row[0] << " Estado: ";
                if (atoi(row[4]) == 1)
                    cout << "Ocupado" << endl;
                if (atoi(row[4]) == 0)
                    cout << "Libre" << endl;
                if (atoi(row[4]) == 2)
                    cout << "En Mantenimiento" << endl;
            }
        }

    } else {
        cout << "Ocurrio un problema" << endl;

    }
}

void Conexion::insertarNuevoAdministrador(Administrador administrador) {
    string query =
            "insert into administrador VALUE (0,1,'" + administrador.nombre + "','" + administrador.apellidos + "','" +
            administrador.username + "','" + administrador.contra + "','" + administrador.telefono + "') ";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    }
}

std::vector<Administrador> Conexion::getAdministradores() {
    string query = "SELECT * FROM administrador";
    query_state = mysql_query(connection, query.c_str());

    vector<Administrador> administradores;
    if (!query_state) {
        result = mysql_store_result(connection);
        row = result->current_row;
        auto count = result->row_count;
        Sleep(1000);
        int pos = 0;
        auto rows = result->data_cursor;
        row = rows->data;
        for (int i = 0; i < count; ++i) {
            auto admin = Administrador();
            admin.id_administrador = atoi(row[0]);
            admin.id_hotel = atoi(row[1]);
            admin.nombre = row[2];
            admin.apellidos = row[3];
            admin.username = row[4];
            admin.contra = row[5];
            admin.telefono = row[6];
            administradores.push_back(admin);
            pos++;
            rows = rows->next;
            if (i != count - 1) {
                row = rows->data;
            }
        }
    }
    return administradores;
}

Administrador Conexion::buscarPorNombre(string s) {
    std::string query = "select * from administrador a where a.nombre like '" + s + "'";
    query_state = mysql_query(connection, query.c_str());
    auto admin = Administrador();
    if (!query_state) {
        result = mysql_store_result(connection);
        auto count = result->row_count;
        if (count != 0) {
            row = mysql_fetch_row(result);
            admin.id_administrador = atoi(row[0]);
            admin.id_hotel = atoi(row[1]);
            admin.nombre = row[2];
            admin.apellidos = row[3];
            admin.username = row[4];
            admin.contra = row[5];
            admin.telefono = row[6];
        }

    }
    return admin;
}

void Conexion::actualizarAdministrador(Administrador administrador) {
    std::string query =
            "update administrador set nombre ='" + administrador.nombre + "',apellidos='" + administrador.apellidos +
            "',username='" + administrador.username + "',telefono='" + administrador.telefono +
            "' where id_administrador = " + to_string(administrador.id_administrador) + " ";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    } else {
        cout << "Ocurrio un error";
    }
}

void Conexion::eliminarAdministrador(int i) {
    std::string query = "delete from administrador where id_administrador=" + to_string(i) + "";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    } else {
        cout << "Ocurrio un error";
    }
}

void Conexion::insertarNuevoCliente(Cliente cliente) {
    string query =
            "insert into cliente VALUE (0,1,'" + cliente.nombre + "','" + cliente.apellidos + "','" +
            to_string(cliente.estado) + "','" + cliente.telefono + "') ";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    }
}

Cliente Conexion::buscarClientePorNombre(string nombre) {
    std::string query = "select * from administrador a where a.nombre like '" + nombre + "'";
    query_state = mysql_query(connection, query.c_str());
    auto cliente = Cliente();
    if (!query_state) {
        result = mysql_store_result(connection);
        auto count = result->row_count;
        if (count != 0) {
            row = mysql_fetch_row(result);
            cliente.id_cliente = atoi(row[0]);
            cliente.id_hotel = atoi(row[1]);
            cliente.nombre = row[2];
            cliente.apellidos = row[3];
            cliente.estado = atoi(row[4]);
            cliente.telefono = row[5];
        }
    }
    return cliente;
}

void Conexion::actualizarCliente(Cliente cliente) {
    std::string query =
            "update cliente set nombre ='" + cliente.nombre + "',apellidos='" + cliente.apellidos +
            "',estado='" + to_string(cliente.estado) + "',telefono='" + cliente.telefono +
            "' where id_administrador = " + to_string(cliente.id_cliente) + " ";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    } else {
        cout << "Ocurrio un error";
    }
}

void Conexion::eliminarCliente(int i) {
    std::string query = "delete from cliente where id_cliente=" + to_string(i) + "";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        cout << "Exito!";
    } else {
        cout << "Ocurrio un error";
    }
}

std::vector<Cliente> Conexion::getClientes() {
    string query = "SELECT * FROM cliente";
    query_state = mysql_query(connection, query.c_str());
    vector<Cliente> clientes;
    if (!query_state) {
        result = mysql_store_result(connection);
        row = result->current_row;
        auto count = result->row_count;
        Sleep(1000);
        int pos = 0;
        auto rows = result->data_cursor;
        row = rows->data;
        for (int i = 0; i < count; ++i) {
            auto cliente = Cliente();
            cliente.id_cliente = atoi(row[0]);
            cliente.id_hotel = atoi(row[1]);
            cliente.nombre = row[2];
            cliente.apellidos = row[3];
            cliente.estado = atoi(row[4]);
            cliente.telefono = row[5];
            clientes.push_back(cliente);
            pos++;
            rows = rows->next;
            if (i != count - 1) {
                row = rows->data;
            }
        }
    }
    return clientes;
}

void Conexion::verTodosRegistros() {
    string query = "SELECT * FROM recibohospedaje";
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        if (result->row_count == 0) {
            cout << "vacio" << endl;
        } else {
            while (row = mysql_fetch_row(result)) {
                cout << "id:" << row[0] << " Habitacion: " << row[1] << " Fecha Inscripcion: " << row[6] << endl;
            }
        }
    } else {
        cout << "Ocurrio un problema" << endl;

    }
}

void Conexion::consultaHabitaciones(){
    string sql = "SELECT habitacion.`id_habitacion`, habitacion.`piso`, tipohabitacion.`nombre`, tipohabitacion.`precioxhora` FROM habitacion INNER JOIN tipohabitacion ON habitacion.id_tipohabitacion = tipohabitacion.id_tipohabitacion";
    int query_state = mysql_query(connection , sql.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "   nยบ habitacion: " << row[0] << "  piso: " << row[1] << "  tipo: " << row[2] << "  precio: " << row[3] << endl;
        }
        mysql_free_result(result);
    }else {
        cout << "Error: no se pudo conectar" << endl;
    }
}

void Conexion::consultaNombreClientes() {
    string sql = "SELECT id_cliente, nombre, apellidos FROM `cliente`";
    int query_state = mysql_query(connection , sql.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "   " << row[0] << "->" << row[1] << " " << row[2] << endl;
        }
        mysql_free_result(result);
    }
}

void Conexion::agregarReservacion(string idReservacion, string idHabitacion, string idCliente, string fecha){
    string est = "1";
    string sql = "INSERT INTO `reservacion`(`id_reservacion`, `id_habitacion`, `id_cliente`, `fecha`, `estado`) VALUES ("+ idReservacion +","+idHabitacion+","+idCliente+",'"+fecha+"',"+est+")";
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Agregado exitosamente" << endl;
    }
}

void Conexion::consultaReservaciones(){
    const char* sql = "SELECT reservacion.id_reservacion, reservacion.id_habitacion, cliente.nombre, cliente.apellidos, reservacion.fecha, reservacion.estado "
                      "FROM reservacion INNER JOIN cliente ON reservacion.id_cliente = cliente.id_cliente";
    int query_state = mysql_query(connection , sql);
    if(query_state == 0){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "------------------------------------" << endl;
            cout << "ID reservacion: " << row[0] << endl;
            cout << "Numero habitacion: " << row[1] <<endl;
            cout << "Cliente: " << row[2] << " " << row[3] << endl;
            cout << "Fecha: " << row[4] << endl;
            cout << "Estado registro: " << row[5] << endl;
            cout << "------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}

void Conexion::buscarReservacion(string id){
    string sql = "SELECT reservacion.id_reservacion, reservacion.id_habitacion, cliente.nombre, cliente.apellidos, reservacion.fecha, reservacion.estado "
                 "FROM reservacion INNER JOIN cliente ON reservacion.id_cliente = cliente.id_cliente WHERE id_reservacion = " + id;
    int qstate = mysql_query(connection , sql.c_str());
    if(qstate == 0){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "------------------------------------" << endl;
            cout << "ID reservacion: " << row[0] << endl;
            cout << "Numero habitacion: " << row[1] <<endl;
            cout << "Cliente: " << row[2] << " " << row[3] << endl;
            cout << "Fecha: " << row[4] << endl;
            cout << "Estado registro: " << row[5] << endl;
            cout << "------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}

void Conexion::modificarReservacion(string idReservacion, string idHabitacion, string idCliente, string fecha){
    string est = "1";
    string sql = "UPDATE `reservacion` SET `id_habitacion`="+idHabitacion+",`id_cliente`="+idCliente+",`fecha`='"+fecha+"',`estado`="+est+" WHERE `id_reservacion`="+ idReservacion;
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Agregado exitosamente" << endl;
    }
}
void Conexion::eliminarReservacion(string idReservacion){
    string sql = "DELETE FROM `reservacion` WHERE `id_reservacion`="+ idReservacion;
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Eliminado exitosamente" << endl;
    }
}

void Conexion::consultaServicios(){
    const char* sql = "SELECT servicio.id_servicio, servicio.nombre, servicio.precioxpersona "
                      "FROM servicio";
    int query_state = mysql_query(connection , sql);
    if(query_state == 0){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "------------------------------------" << endl;
            cout << "ID servicio: " << row[0] << endl;
            cout << "Nombre servicio: " << row[1] <<endl;
            cout << "Precio: " << row[2] << endl;
            cout << "------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}

void Conexion::agregarServicio(string idServicio, string nombre, string precio){
    string hotel = "1";
    string sql = "INSERT INTO `servicio`(`id_servicio`, `id_Hotel`, `nombre`, `precioxpersona`) VALUES ("+ idServicio +","+hotel+",'"+nombre+"',"+precio+")";
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Agregado exitosamente" << endl;
    }
}

void Conexion::buscarServicios(string id){
    string sql = "SELECT servicio.id_servicio, servicio.nombre, servicio.precioxpersona "
                 "FROM servicio WHERE id_servicio = " + id;
    int qstate = mysql_query(connection , sql.c_str());
    if(qstate == 0){
        result = mysql_store_result(connection);
        unsigned long filas = mysql_num_rows(result);
        if (filas == 0) {
            cout << "No hay datos" << endl;
        }
        for (int i = 0; i < filas; i++){
            row = mysql_fetch_row(result);
            cout << "------------------------------------" << endl;
            cout << "ID servicio: " << row[0] << endl;
            cout << "Nombre servicio: " << row[1] <<endl;
            cout << "Precio: " << row[2] << endl;
            cout << "------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}
void Conexion::modificarServicio(string idServicio, string nombre, string precio){
    string est = "1";
    string sql = "UPDATE `servicio` SET `nombre`= '"+nombre+"',`precioxpersona`= "+precio+" WHERE `id_servicio`= "+ idServicio;
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Agregado exitosamente" << endl;
    }
}
void Conexion::eliminarServicio(string idServicio){
    string sql = "DELETE FROM `servicio` WHERE `id_servicio`="+idServicio;
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Eliminado exitosamente" << endl;
    }
}

void Conexion::agregaradquirirservicio(int id) {
    AdquirirServicio aux;
    cout<<"Ingrese el ID del servicio"<<endl;
    cin>>aux.id_servicio;
    cout<<"Ingrese el la cantidad"<<endl;
    cin>>aux.cantidad;
    aux.id_recibohospedaje=id;
    string sql = "INSERT INTO adquirirservicio (id_servicio,id_recibohospedaje,cantidad,fecha) VALUES("+to_string(aux.id_servicio)+","+to_string(aux.id_recibohospedaje)+","+to_string(aux.cantidad)+",CURDATE())";
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Se realizo el registro de servicio exitosamente" << endl;
    }
}

void Conexion::terminar_registro(int id) {
    double costototal=getcostototal(id);
    string sql = "UPDATE `recibohospedaje` SET estado=1,costo="+to_string(costototal)+" WHERE `recibohospedaje`="+to_string(id);
    query_state = mysql_query(connection, sql.c_str());
    if (query_state != 0){
        cout << mysql_error(connection) << endl << endl;
    } else {
        cout << "Se termino el registro exitosamente" << endl;
    }
}

int Conexion::gettipoHabitacion(int id) {
    int aux;
    string query = "SELECT * FROM habitacion WHERE id_habitacion=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux=atoi(row[2]);
    }
    return aux;
}

double Conexion::getcostoTipoHabitacion(int id) {
    double aux;
    string query = "SELECT * FROM tipohabitacion WHERE id_tipohabitacion=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux=atof(row[4]);
    }
    return aux;
}

double Conexion::getcostototal(int id) {
    double aux=0;
    string query = "SELECT * FROM adquirirservicio WHERE id_recibohospedaje=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        while(row = mysql_fetch_row(result)) {
            aux = aux + getcostoServicio(atoi(row[1])) * atof(row[3]);
            }
        }
    return aux+getcostoRecibo(id);
}

double Conexion::getcostoServicio(int id) {
    double aux=0;
    string query = "SELECT * FROM servicio WHERE id_servicio=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux=atof(row[3]);
    }
    return aux;
}

double Conexion::getcostoRecibo(int id) {
    double aux=0;
    string query = "SELECT * FROM recibohospedaje WHERE id_recibohospedaje=" + to_string(id);
    query_state = mysql_query(connection, query.c_str());
    if (!query_state) {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux=atof(row[5]);
    }
    return aux;
}





