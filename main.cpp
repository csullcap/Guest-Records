#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "Funciones/funciones.cpp"
#include "Conexion/Conexion.h"
#include "Administrador/Administrador.h"
#include <clocale>

using namespace std;
namespace std {
    template <typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits> &
    tab(basic_ostream<_CharT, _Traits> &__os) {
        return __os.put(__os.widen('\t'));
    }
}

int main() {
    system("color 81");
    setlocale(LC_ALL,"spanish");
    Conexion bd_conexion;
    Hotel hotel=bd_conexion.getDatosHotel(1);
    Administrador administrador;
    char op_main;
    do {
//        int x = dimensiones::ancho;
        system(("mode con: cols=" +to_string(dimensiones::ancho)+" lines="+to_string(dimensiones::alto)).c_str());
        imprimir_rectangle('=');
        goto2xy(8,8);
        cout <<"Hotel : "<<tab<<hotel.nombre<<tab<< endl;
        goto2xy(8,9);
        cout <<"Direccion: "<<tab<<hotel.direccion<<tab<<endl;
        goto2xy(8,10);
        cout <<"Telefono :"<<tab<<hotel.telefono<<tab<<endl<<endl;
        goto2xy(8,11);
        cout <<"Seleccione la opcion"<<tab<<endl;
        goto2xy(8,12);
        cout <<"(1) Iniciar Sesion"<<tab<<endl;
        goto2xy(8,13);
        cout <<"(2) Cerrar"<<tab<<endl;
        goto2xy(8,14);
        cout <<"Opcion : ";
        cin>>op_main;
        switch (op_main) {
            case '1':
                system("cls");
                if(iniciarSesion(administrador,bd_conexion)){
                    goto2xy(4,8);
                    cout<<"Bienvenido al sistema "+administrador.nombre<<" "<<administrador.apellidos<<endl;
                    menu_principal(administrador,bd_conexion);
                }
                break;

            case '2':
                system("cls");
                cout<<"Fin del programa"<<endl;
                break;

            default:
                system("cls");
                cin.ignore(256,'\n');
                cout<< "Opcion Invalida";
                break;
        }
    }while (op_main!='2');
    bd_conexion.finalizarConexion();
    return 0;
}
