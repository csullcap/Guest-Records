#include <iostream>
#include <windows.h>

#include <conio.h>
#define ENTER 13
#define BACKSPACE 8
#include "../Administrador/Administrador.h"
#include "../Conexion/Conexion.h"
#include "../Habitacion/Habitacion.h"
#include "../ReciboHospedaje/ReciboHospedaje.h"

using namespace std;
bool iniciarSesion(Administrador& admin,Conexion bd_conexion);
void menu_principal(Administrador& admin,Conexion bd_conexion);
void servicioDeHotel(Administrador& admin,Conexion bd_conexion);
void gotoxy(int x,int y);
void imprimir_rectangle(char a);

inline bool iniciarSesion(Administrador& admin,Conexion bd_conexion) {
    string user;
    string password;
    char op_iniciar_sesion=0;
    bool autentificacion=false;
    do {
        cout << "Ingrese usuario" << endl;
        cin.ignore(256, '\n');
        getline(cin, user);
        cout << "Ingrese Contraseña" << endl;
        char caracter;
        caracter = _getch();
        password = "";
        while (caracter != ENTER) {
            if (caracter != BACKSPACE) {
                password.push_back(caracter);
                cout << "*";
            }
            else {
                if (password.length() > 0) {
                    cout << "\b \b";
                    password = password.substr(0, password.length() - 1);
                }
            }
            caracter = _getch();
        }
        //getline(cin, password);
        if(bd_conexion.inicioSesion(admin,user,password)) {
            cout<<endl<<endl<<"Cuenta valida"<<endl;
            cout<<"Espere un momento ";
            Sleep(1000);
            cout<<".";
            Sleep(1000);
            cout<<".";
            Sleep(1000);
            cout<<".";
            autentificacion=true;
        }
        else{
            cout<<endl<<endl<<"Usuario o contraseña invalidos"<<endl;
            cout<<"Desea intertar nuevamente (1)Si (2)No"<<endl;
            cout<<"Opcion: ";
            cin>>op_iniciar_sesion;
        }
        system("cls");
    }while ((!autentificacion )^(op_iniciar_sesion=='2'));
    if(autentificacion){
        return true;
    }
    if(op_iniciar_sesion=='2'){
        return false;
    }
    return false;
}

inline void menu_principal(Administrador& admin,Conexion bd_conexion) {
    char op_menu_principal=0;
    do{
        cout<<"Menu Principal"<< endl;
        cout<<"(1) Reservaciones"<<endl;
        cout<<"(2) Servicio de Hotel"<<endl;
        cout<<"(3) Turnos"<<endl;
        cout<<"(4) Administradores"<<endl;
        cout<<"(5) Clientes"<<endl;
        cout<<"(6) Servicios"<<endl;
        cout<<"(7) Salir"<<endl;
        cout<<"Opcion : ";
        cin>>op_menu_principal;
        switch (op_menu_principal) {

            case '1':
                system("cls");
                cout<<"SERVICIO DE RESERVACIONES"<<endl;
                system("pause");
                break;

            case '2':
                system("cls");
                cout<<"SERVICIO DE HOTEL"<<endl;
                servicioDeHotel(admin,bd_conexion);
                break;

            case '3':
                system("cls");
                cout<<"TURNOS"<<endl;
                system("pause");
                break;

            case '4':
                system("cls");
                cout<<"ADMINISTRADORES"<<endl;
                system("pause");
                break;

            case '5':
                system("cls");
                cout<<"CLIENTES"<<endl;
                system("pause");
                break;

            case '6':
                system("cls");
                cout<<"SERVICIOS"<<endl;
                system("pause");
                break;

            case '7':
                cout<<"Salio del menu principal"<<endl;
                system("pause");
                system("cls");
                break;

            default:
                system("cls");
                cin.ignore(256,'\n');
                cout<< "Opcion Invalida";
                break;
        }

    }while(op_menu_principal!='7');
}

inline void servicioDeHotel(Administrador& admin,Conexion bd_conexion){
    char op_servicio_de_hotel=0;
    do{
        cout<<"Menu Principal"<< endl;
        cout<<"(1) Agregar Registro de hospedaje"<<endl;
        cout<<"(2) Ver Registros pendientes"<<endl;
        cout<<"(3) Ver Estado de las habitaciones"<<endl;
        cout<<"(4) Ver todos los registros"<<endl;
        cout<<"(5) Salir"<<endl;
        cout<<"Opcion : ";
        cin>>op_servicio_de_hotel;
        switch (op_servicio_de_hotel) {
            case '1':
                system("cls");
                bd_conexion.addReciboHospedaje(admin);
                break;

            case '2':
                system("cls");
                bd_conexion.registrosPendientes();
                system("pause");
                break;

            case '3':
                system("cls");
                cout<<"Estado de las habitaciones"<<endl;
                bd_conexion.estadoHabitacion();
                system("pause");
                break;

            case '4':
                system("cls");
                cout<<"Registros pendientes"<<endl;
                system("pause");
                break;

            case '5':
                cout<<"Ver todos los registros"<<endl;
                system("pause");
                system("cls");
                break;

            default:
                system("cls");
                cin.ignore(256,'\n');
                cout<< "Opcion Invalida";
                break;
        }
        system("cls");

    }while(op_servicio_de_hotel!='5');

}
inline void gotoxy(int x,int y){
    HANDLE hcon;
    hcon =GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon,dwPos);
}

inline void imprimir_rectangle(char a){
        putchar ('=');
        for(int x=1; x<=79; x++){
            gotoxy (x,0);
            putchar ('=');
            gotoxy (x,24);
            putchar ('=');
        }

        for(int y=1; y<=24; y++){
            gotoxy (0,y);
            putchar ('=');
            gotoxy (79,y);
            putchar ('=');
        }
}
