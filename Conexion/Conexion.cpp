#include "Conexion.h"
#include <string>
#define convertToString(x) #x
#include "../Habitacion/Habitacion.h"
#include "../ReciboHospedaje/ReciboHospedaje.h"
#include "../Cliente/Cliente.h"
#include "../ReciboHospedaje_Cliente/ReciboHospedaje_Cliente.h"

MYSQL mysql,*connection;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

Conexion::Conexion() {
    iniciarConexion();
}
void Conexion::iniciarConexion() {
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, ip, usr, pass, db, 3306, NULL, 0);
    if (connection==NULL){
        cout<<mysql_error(&mysql)<<endl;
    }
}

void Conexion::finalizarConexion() {
    mysql_close(&mysql);
}

Hotel Conexion::getDatosHotel(int id) {
    Hotel aux;
    string query ="SELECT * FROM hotel WHERE id_hotel="+to_string(id);
    query_state=mysql_query(connection, query.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        aux.id_hotel=atoi(row[0]);
        aux.nombre=row[1];
        aux.direccion=row[2];
        aux.telefono=row[3];
    }
    return aux;
}

bool Conexion::inicioSesion(Administrador &admin, string username, string contra) {
    string query ="SELECT * FROM administrador WHERE username='"+username+"' AND contra='"+contra+"'";
    query_state=mysql_query(connection, query.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        if(result->row_count==0)
            return false;
        else{
            row = mysql_fetch_row(result);
            admin.id_administrador=atoi(row[0]);
            admin.id_hotel=atoi(row[1]);
            admin.nombre=row[2];
            admin.apellidos=row[3];
            admin.username=row[4];
            admin.contra=row[5];
            admin.telefono=row[6];
        return true;
        }
    }
    else{
        cout<<"Ocurrio un problema"<<endl;
    }
    return false;
}

int Conexion::getfilas(string tabla) {
    int filas;
    string query ="SELECT * FROM "+tabla+"";
    query_state=mysql_query(connection, query.c_str());
    if(!query_state) {
        result = mysql_store_result(connection);
        filas=result->row_count;
    }
    return filas;
}

void Conexion::addReciboHospedaje(Administrador admin) {
    ReciboHospedaje aux;
    aux.id_recibohospedaje=getfilas("recibohospedaje")+1;
    cout<<"Nuevo Registro"<<endl;
    cout<<"Nro de Habitacion: ";
    cin>>aux.id_habitacion;
    aux.id_administrador =admin.id_administrador;
    aux.costo=0;
    aux.estado=0;
    string query="INSERT INTO recibohospedaje (id_recibohospedaje,id_habitacion,id_administrador,costo,estado,fecha_inicio) VALUES ("+to_string(aux.id_recibohospedaje)+","+to_string(aux.id_habitacion)+","+to_string(aux.id_administrador)+","+to_string(aux.costo)+","+to_string(aux.estado)+",CURDATE())";
    query_state=mysql_query(connection, query.c_str());
    if(!query_state) {
        cout<<"Registro exitoso"<<endl;
        cout<<"Registro de Clientes :"<<endl;
        char rpta='1';
        ReciboHopedaje_Cliente temp;
        do{
            temp.id_recibohospedaje=aux.id_recibohospedaje;
            cout<<"Ingrese el codigo del cliente : ";
            cin>>temp.id_cliente;
            query="INSERT INTO reciboshospedaje_clientes (id_recibohospedaje,id_cliente) VALUES ("+to_string(temp.id_recibohospedaje)+","+to_string(temp.id_cliente)+")";
            query_state=mysql_query(connection, query.c_str());
            if(!query_state) {
                cout<<"Registro exitoso"<<endl;
                cout<<"Desea ingresar mas clientes (1)SI (2)NO : ";
                cin>>rpta;
            }
            else{
                cout<<"Ocurrio un problema"<<endl;
                cout<<"Intente de nuevo"<<endl;
            }
        }while(rpta!='2');
        cout<<"Se Termino el Registro de Hospedaje Exitosamente"<<endl;
        system("pause");
        system("cls");
    }
    else{
        cout<<"Ocurrio un problema"<<endl;
    }
}

void Conexion::registrosPendientes() {
    string query ="SELECT * FROM recibohospedaje WHERE estado= 0";
    query_state=mysql_query(connection, query.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        if(result->row_count==0){
            cout <<"vacio"<<endl;
        }
        else{
            while(row = mysql_fetch_row(result)){
                cout<<"id:" <<row[0]<< " Habitacion: "<< row[1]<<" Fecha Inscripcion: "<<row[6]<<endl;
            }
        }

    }
    else{
        cout<<"Ocurrio un problema"<<endl;

    }
}

void Conexion::estadoHabitacion() {
    string query ="SELECT * FROM habitacion";
    query_state=mysql_query(connection, query.c_str());
    if(!query_state){
        result = mysql_store_result(connection);
        if(result->row_count==0){
            cout <<"vacio"<<endl;
        }
        else{
            while(row = mysql_fetch_row(result)){
                cout<<"Nro Habitacion : " <<row[0]<< " Estado: ";
                if(atoi(row[4])==1)
                    cout<<"Ocupado"<<endl;
                if(atoi(row[4])==0)
                    cout<<"Libre"<<endl;
                if(atoi(row[4])==2)
                    cout<<"En Mantenimiento"<<endl;
            }
        }

    }
    else{
        cout<<"Ocurrio un problema"<<endl;

    }
}








