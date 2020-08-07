#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../Administrador/Administrador.h"
#include "../Conexion/Conexion.h"
#include "../Constantes/Constantes.h"

#define ENTER 13
#define BACKSPACE 8
using namespace std;
static int Y_DEFAULT = 9;
static int X_DEFAULT = 12;
static int Y_Current = 8;

bool iniciarSesion(Administrador &admin, Conexion bd_conexion);
void menu_principal(Administrador &admin, Conexion bd_conexion);
void servicioDeHotel(Administrador &admin, Conexion bd_conexion);
void gotoxy(int x, int y);
void imprimir_rectangle(char a);
void mostrarMenuAdministrador(Administrador &administrador, Conexion bd);
void mostrarMenuClientes(Administrador &administrador, Conexion bd);
void menuReservacion(Administrador &administrador, Conexion conexion);
void menuServicio(Administrador &administrador, Conexion conexion);
string tabularr(int n);
void tabularc(int n);

inline void centrar(bool reiniciarY = false, unsigned int count = 0, ...) {
    va_list ap;
    va_start(ap, count);
    if (reiniciarY) {
        Y_Current = Y_DEFAULT;
    }
    gotoxy(X_DEFAULT, Y_Current);
    Y_Current++;
    for (int j = 0; j < count; j++) {
        std::cout << va_arg(ap, char*);
    }
    va_end(ap);
}

inline bool iniciarSesion(Administrador &admin, Conexion bd_conexion) {
    string user;
    string password;
    char op_iniciar_sesion = '0';
    bool autentificacion = false;
    do {
        imprimir_rectangle('=');
        tabularc(4);
        cout<<tabularr(2)<<"Ingrese usuario"<<endl;
        cin.ignore(256, '\n');
        cout<<tabularr(2);
        getline(cin, user);
        cout<<tabularr(2)<<"Ingrese contraseña"<<endl;
        cout<<tabularr(2);
        char caracter;
        caracter = _getch();
        password = "";
        while (caracter != ENTER) {
            if (caracter != BACKSPACE) {
                password.push_back(caracter);
                cout << "*";
            } else {
                if (password.length() > 0) {
                    cout << "*" << "\b \b";
                    password = password.substr(0, password.length() - 1);
                }
            }
            caracter = _getch();
        }
        if (bd_conexion.inicioSesion(admin, user, password)) {
            cout<<endl;
            cout<<tabularr(2)<<"Espere un momento";
            Sleep(1000);
            cout << ".";
            Sleep(1000);
            cout << ".";
            Sleep(1000);
            cout << ".";
            autentificacion = true;
        } else {
            centrar(false, 4, "\n", "\n", "Usuario o contraseña invalidos", "\n");
            centrar(false, 2, "Desea intertar nuevamente (1)Si (2)No", "\n");
            centrar(false, 1, "Opcion: ");
            cin >> op_iniciar_sesion;
        }
        system("cls");
        imprimir_rectangle('=');
    } while ((!autentificacion) ^ (op_iniciar_sesion == '2'));
    if (autentificacion) {
        return true;
    }
    if (op_iniciar_sesion == '2') {
        return false;
    }
    return false;
}

inline void menu_principal(Administrador &admin, Conexion bd_conexion) {
    char op_menu_principal = 0;
    do {
        imprimir_rectangle('=');
        centrar(true, 2, "Menu Principal", "\n");
        centrar(false, 2, "(1) Reservaciones", "\n");
        centrar(false, 2, "(2) Servicio de Hotel", "\n");
        centrar(false, 2, "(3) Administradores", "\n");
        centrar(false, 2, "(4) Clientes", "\n");
        centrar(false, 2, "(5) Servicios", "\n");
        centrar(false, 2, "(6) Salir", "\n");
        centrar(false, 1, "Opcion : ");
        centrar(false, 1, "");
        cin >> op_menu_principal;
        switch (op_menu_principal) {
            case '1':
                system("cls");
                imprimir_rectangle('=');
                centrar(true, 2, "SERVICIO DE RESERVACIONES", "\n");
                menuReservacion(admin, bd_conexion);
                break;

            case '2':
                system("cls");
                imprimir_rectangle('=');
                centrar(true, 2, "SERVICIOS DE HOTEL", "\n");
                servicioDeHotel(admin, bd_conexion);
                break;

            case '3':
                system("cls");
                imprimir_rectangle('=');
                centrar(true, 2, "ADMINISTRADOR", "\n");
                mostrarMenuAdministrador(admin, bd_conexion);
                break;

            case '4':
                system("cls");
                imprimir_rectangle('=');
                centrar(true, 2, "CLIENTES", "\n");
                mostrarMenuClientes(admin, bd_conexion);
                break;

            case '5':
                system("cls");
                imprimir_rectangle('=');
                centrar(true, 2, "SERVICIOS", "\n");
                menuServicio(admin, bd_conexion);
                break;

            case '6':
                centrar(false, 2, "Salio del menu principal", "\n");
                system("pause");
                system("cls");
                imprimir_rectangle('=');
                break;

            default:
                system("cls");
                imprimir_rectangle('=');
                cin.ignore(256, '\n');
                centrar(true, 2, "Opcion Invalida", "\n");
                break;
        }

    } while (op_menu_principal != '6');
}

inline void servicioDeHotel(Administrador &admin, Conexion bd_conexion) {
    char op_servicio_de_hotel = 0;
    do {
        centrar(false, 2, "Menu Principal", "\n");
        centrar(false, 2, "(1) Agregar Registro de hospedaje", "\n");
        centrar(false, 2, "(2) Ver Registros pendientes", "\n");
        centrar(false, 2, "(3) Ver Estado de las habitaciones", "\n");
        centrar(false, 2, "(4) Ver todos los registros", "\n");
        centrar(false, 2, "(5) Salir", "\n");
        centrar(false, 1, "Opcion : ");
        cin >> op_servicio_de_hotel;
        switch (op_servicio_de_hotel) {
            case '1':
                system("cls");
                imprimir_rectangle('=');
                bd_conexion.addReciboHospedaje(admin);
                break;

            case '2':
                system("cls");
                char op_reg_pend;
                int id;
                imprimir_rectangle('=');
                centrar(false, 2, "Registro Pendientes", "\n");
                bd_conexion.registrosPendientes();
                cout<<endl<<"Que desea realizar?"<<endl;
                cout<<"(1)Terminar reservacion"<<endl;
                cout<<"(2)Agregar servicio a la reservacion"<<endl;
                cin>>op_reg_pend;
                switch (op_reg_pend) {
                    case '1':
                        cout<<"Ingrese el id:"<<endl;
                        cin>>id;
                        bd_conexion.terminar_registro(id);
                        break;
                    case '2':
                        char rpta;
                        cout<<"Ingrese el id:"<<endl;
                        cin>>id;
                        do{
                            bd_conexion.agregaradquirirservicio(id);
                            cout<<"Desea agregar otro servicio: (1)SI (2)NO"<<endl;
                            cin>>rpta;
                        }
                        while(rpta!='2');
                        break;
                    default:
                        cin.ignore(256, '\n');
                        centrar(false, 2, "Opcion Invalida");
                        break;
                }
                break;

            case '3':
                system("cls");
                imprimir_rectangle('=');
                centrar(false, 2, "Estado de las habitaciones", "\n");
                bd_conexion.estadoHabitacion();
                system("pause");
                break;

            case '4':
                system("cls");
                imprimir_rectangle('=');
                centrar(false, 2, "Ver todos los registros : ", "\n");
                bd_conexion.verTodosRegistros();
                system("pause");
                break;

            case '5':
                centrar(false, 2, "Salio del menu", "\n");
                system("pause");
                system("cls");
                imprimir_rectangle('=');
                break;

            default:
                system("cls");
                imprimir_rectangle('=');
                cin.ignore(256, '\n');
                centrar(false, 2, "Opcion Invalida");
                break;
        }
        system("cls");
        imprimir_rectangle('=');

    } while (op_servicio_de_hotel != '5');

}

inline void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

inline void imprimir_rectangle(char a) {
    putchar('=');
    for (int x = 1; x <= dimensiones::ancho-1; x++) {
        gotoxy(x, 0);
        putchar('=');
        gotoxy(x, dimensiones::alto-1);
        putchar('=');
    }

    for (int y = 1; y <= dimensiones::alto-1; y++) {
        gotoxy(0, y);
        putchar('|');
        gotoxy(dimensiones::ancho-1, y);
        putchar('|');
    }
    gotoxy(0,0);
}

inline void mostrarMenuAdministrador(Administrador &administrador, Conexion bd) {
    int opcion;
    do {
        system("cls");
        imprimir_rectangle('=');
        centrar(true, 2, "Menu Principal Administradores", "\n");
        centrar(false, 2, "(1) Agregar", "\n");
        centrar(false, 2, "(2) Modificar", "\n");
        centrar(false, 2, "(3) Eliminar", "\n");
        centrar(false, 2, "(4) Ver Todos", "\n");
        centrar(false, 2, "(5) Salir", "\n");
        centrar(false, 1, "Opcion : ");
        cin >> opcion;
        system("cls");
        imprimir_rectangle('=');
        centrar(true, 1, "");
        if (opcion == 1) {
            cin.ignore(256, '\n');
            auto adminNuevo = Administrador();
            centrar(false, 2, "Nombre", "\n");
            centrar(false, 1, "");
            getline(cin, adminNuevo.nombre);
            centrar(false, 2, "Apellidos", "\n");
            centrar(false, 1, "");
            getline(cin, adminNuevo.apellidos);
            centrar(false, 2, "Username", "\n");
            centrar(false, 1, "");
            getline(cin, adminNuevo.username);
            centrar(false, 2, "Password", "\n");
            centrar(false, 1, "");
            getline(cin, adminNuevo.contra);
            centrar(false, 2, "Telefono", "\n");
            centrar(false, 1, "");
            getline(cin, adminNuevo.telefono);
            bd.insertarNuevoAdministrador(adminNuevo);
        } else if (opcion == 2) {
            cin.ignore(256, '\n');
            centrar(false, 2, "Ingrese nombre a buscar:\n", "\n");
            string n;
            getline(cin, n);
            auto adminModificar = bd.buscarPorNombre(n);
            if (adminModificar.id_administrador != 0) {
                centrar(false, 2, "Dato a modificar: ", "\n");
                centrar(false, 2, "(1) Nombre", "\n");
                centrar(false, 2, "(2) Apellidos", "\n");
                centrar(false, 2, "(3) Username", "\n");
                centrar(false, 2, "(4) Telefono", "\n");
                centrar(false, 2, "(5) Salir", "\n");
                centrar(false, 2, "Opcion : ");
                int tipoModificacion;
                cin >> tipoModificacion;
                if (tipoModificacion == 1) {
                    centrar(false, 2, ("Nombre actual:" + adminModificar.nombre).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo nombre:", "\n");
                    getline(cin, adminModificar.nombre);
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 2) {
                    centrar(false, 2, ("Apellido actual:" + adminModificar.apellidos).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo Apellido:", "\n");
                    getline(cin, adminModificar.apellidos);
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 3) {
                    centrar(false, 2, ("Username actual:" + adminModificar.username).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo Username:", "\n");
                    getline(cin, adminModificar.username);
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 4) {
                    centrar(false, 2, ("Telefono actual:" + adminModificar.telefono).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo Telefono:", "\n");
                    getline(cin, adminModificar.telefono);
                    bd.actualizarAdministrador(adminModificar);
                }
            } else {
                centrar(false, 2, "Usuario no encontrado.", "\n");
            }
            system("pause");

        } else if (opcion == 3) {
            centrar(false, 2, "Ingrese nombre a buscar:\n", "\n");
            string n;
            getline(cin, n);
            auto adminModificar = bd.buscarPorNombre(n);
            if (adminModificar.id_administrador != 0) {
                centrar(false, 2,
                        ("Eliminar administrador: \n" + adminModificar.toString() + "\n (1) Si \n(2) No ").c_str(),
                        "\n");
                int eliminar;
                cin >> eliminar;
                if (eliminar == 1) {
                    bd.eliminarAdministrador(adminModificar.id_administrador);
                }
            } else {
                centrar(false, 2, "Usuario no encontrado.", "\n");
            }
        } else if (opcion == 4) {
            centrar(false, 2, "Lista de Administradores\n", "\n");
            auto admins = bd.getAdministradores();
            centrar(false, 1, "\n");
            for (auto &admin : admins) {
                centrar(false, 2, admin.toString().c_str(),"\n");
            }
            centrar(false, 1, "\n");
            system("pause");
        }
    } while (opcion != 5);
}

inline void mostrarMenuClientes(Administrador &administrador, Conexion bd) {
    int opcion;
    do {
        centrar(true, 2, "Menu Principal Clientes", "\n");
        centrar(false, 2, "(1) Agregar", "\n");
        centrar(false, 2, "(2) Modificar", "\n");
        centrar(false, 2, "(3) Eliminar", "\n");
        centrar(false, 2, "(4) Ver Todos", "\n");
        centrar(false, 2, "(5) Salir", "\n");
        centrar(false, 1, "Opcion : ");
        cin >> opcion;
        system("cls");
        imprimir_rectangle('=');
        centrar(true, 1, "");
        if (opcion == 1) {
            cin.ignore(256, '\n');
            auto clienteNuevo = Cliente();
            centrar(false, 2, "Nombre", "\n");
            getline(cin, clienteNuevo.nombre);
            centrar(false, 2, "Apellidos", "\n");
            getline(cin, clienteNuevo.apellidos);
            centrar(false, 2, "Telefono", "\n");
            getline(cin, clienteNuevo.telefono);
            bd.insertarNuevoCliente(clienteNuevo);
            system("pause");
        } else if (opcion == 2) {
            string n;
            cin.ignore(256, '\n');
            centrar(false, 2, "Ingrese nombre a buscar: ", "\n");
            getline(cin, n);
            auto clienteModificar = bd.buscarClientePorNombre(n);
            if (clienteModificar.id_cliente != 0) {
                centrar(false, 2, "Dato a modificar: ", "\n");
                centrar(false, 2, "(1) Nombre", "\n");
                centrar(false, 2, "(2) Apellidos", "\n");
                centrar(false, 2, "(3) Telefono", "\n");
                centrar(false, 2, "(4) Salir", "\n");
                centrar(false, 2, "Opcion : ");
                int tipoModificacion;
                cin >> tipoModificacion;
                if (tipoModificacion == 1) {
                    centrar(false, 2, ("Nombre actual : " + clienteModificar.nombre).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo nombre:", "\n");
                    getline(cin, clienteModificar.nombre);
                    bd.actualizarCliente(clienteModificar);
                } else if (tipoModificacion == 2) {
                    centrar(false, 2, ("Apellido actual : " + clienteModificar.apellidos).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo Apellido:", "\n");
                    getline(cin, clienteModificar.apellidos);
                    bd.actualizarCliente(clienteModificar);
                } else if (tipoModificacion == 3) {
                    centrar(false, 2, ("Telefono actual : " + clienteModificar.telefono).c_str(), "\n");
                    centrar(false, 2, "Ingrese nuevo Telefono :", "\n");
                    getline(cin, clienteModificar.telefono);
                    bd.actualizarCliente(clienteModificar);
                }
            } else {
                centrar(false, 2, "Usuario no encontrado.", "\n");
            }
            system("pause");

        } else if (opcion == 3) {
            centrar(false, 2, "Ingrese nombre a buscar:\n", "\n");
            string n;
            getline(cin, n);
            auto clienteModificar = bd.buscarClientePorNombre(n);
            if (clienteModificar.id_cliente != 0) {
                centrar(false, 2, ("Eliminar cliente: " + clienteModificar.toString() + "\n (1) Si \n(2) No ").c_str(),
                        "\n");
                int eliminar;
                cin >> eliminar;
                if (eliminar == 1) {
                    bd.eliminarCliente(clienteModificar.id_cliente);
                }
            } else {
                centrar(false, 2, "Usuario no encontrado.", "\n");
            }
        } else if (opcion == 4) {
            centrar(false, 2, "Lista de Clientes\n", "\n");
            auto clientes = bd.getClientes();
            for (auto &cliente : clientes) {
                centrar(false, 2, cliente.toString().c_str());
            }
            centrar(false, 2, "\n");
            system("pause");
        }
    } while (opcion != 5);
}

inline void menuReservacion(Administrador &admin, Conexion bd_conexion) {
    setlocale(LC_ALL,"Spanish");
    int cant = 0, op = 0;
    string aux,aux1,aux2,aux3;
    while(op != 4) {
        cout << "--Administracion de reservaciones--" << endl;
        cout << "  Seleccione una opcion:" << endl;
        cout << "  (1)Añadir reservacion" << endl;
        cout << "  (2)Ver reservaciones" << endl;
        cout << "  (3)Buscar reservaciones" << endl;
        cout << "  (4)Volver" << endl;
        cin >> op;
        switch(op) {
            case 1:
                system("cls");
                cout << "-Añadir reservacion-" << endl;
                cout << "  Ingrese ID de la reservacion: ";
                cin >> aux;
                cout << "  Lista de habitaciones" << endl;
                bd_conexion.consultaHabitaciones();
                cout << "  Ingrese el numero de la habitacion: ";
                cin >> aux1;
                cout << "  Lista de clientes" << endl;
                bd_conexion.consultaNombreClientes();
                cout << "  Ingrese ID del cliente: ";
                cin >> aux2;
                cout << "  Ingrese fecha (AAAA-MM-DD HH:MM:SS): ";
                cin.ignore();
                getline (cin,aux3);
                bd_conexion.agregarReservacion(aux,aux1,aux2,aux3);
                break;
            case 2:
                system("cls");
                //verReservaciones(reservaciones, cant);
                bd_conexion.consultaReservaciones();
                break;
            case 3:
                system("cls");
                cout << "-Buscar reservacion-" << endl;
                cout << "  Ingrese ID de la reservacion:";
                cin >> aux;
                //buscarReservacion(reservaciones, cant);
                bd_conexion.buscarReservacion(aux);
                cout << " ¿Que desea hacer?, seleccione una opcion:" << endl;
                cout << " (1)Modificar reservacion" << endl;
                cout << " (2)Cancelar reservacion" << endl;
                cout << " (3)Volver" << endl;
                cin >> op;
                if(op == 1){
                    cout << "  Ingrese los nuevos datos" << endl;
                    cout << "   Lista de habitaciones" << endl;
                    bd_conexion.consultaHabitaciones();
                    cout << "   Ingrese el numero de la habitacion: ";
                    cin >> aux1;
                    cout << "   Lista de clientes" << endl;
                    bd_conexion.consultaNombreClientes();
                    cout << "   Ingrese ID del cliente: ";
                    cin >> aux2;
                    cout << "   Ingrese fecha (AAAA-MM-DD HH:MM:SS): ";
                    cin.ignore();
                    getline (cin,aux3);
                    bd_conexion.modificarReservacion(aux,aux1,aux2,aux3);
                }else if(op == 2){
                    bd_conexion.eliminarReservacion(aux);
                }else if(op == 3){
                    break;
                }else{
                    cout << "Opcion incorrecta" << endl;
                }
                break;
            case 4:
                system("cls");
                break;

            default:
                cout << "Opcion incorrecta: Ingrese una valida o 4 para volver" << endl;
                break;
        }
        system("cls");
    }
    system("cls");
}

inline void menuServicio(Administrador &admin, Conexion bd_conexion) {
    setlocale(LC_ALL,"Spanish");
    int cant = 0, op = 0;
    string aux,aux1,aux2;
    while(op != 4) {
        cout << "--Administracion de servicios--" << endl;
        cout << "  Seleccione una opcion:" << endl;
        cout << "  (1)Añadir servicio" << endl;
        cout << "  (2)Ver servicio" << endl;
        cout << "  (3)Buscar servicios" << endl;
        cout << "  (4)Volver" << endl;
        cin >> op;
        switch(op) {
            case 1:
                system("cls");
                cout << "-Añadir servicio" << endl;
                cout << "  Ingrese ID del servicio: ";
                cin >> aux;
                cout << "  Ingrese el nombre del servicio: ";
                cin >> aux1;
                cout << "  Ingrese el precio: ";
                cin >> aux2;
                bd_conexion.agregarServicio(aux,aux1,aux2);
                break;
            case 2:
                system("cls");
                //verReservaciones(reservaciones, cant);
                bd_conexion.consultaServicios();
                break;
            case 3:
                system("cls");
                cout << "-Buscar servicio-" << endl;
                cout << "  Ingrese ID del servicio: ";
                cin >> aux;
                bd_conexion.buscarServicios(aux);
                cout << " ¿Que desea hacer?, seleccione una opcion:" << endl;
                cout << " (1)Modificar servicio" << endl;
                cout << " (2)Eliminar servicio" << endl;
                cout << " (3)Volver" << endl;
                cin >> op;
                if(op == 1){
                    cout << "  Ingrese los nuevos datos" << endl;
                    cout << "   Ingrese el nombre del servicio: ";
                    cin >> aux1;
                    cout << "   Ingrese el precio: ";
                    cin >> aux2;
                    bd_conexion.modificarServicio(aux,aux1,aux2);
                }else if(op == 2){
                    bd_conexion.eliminarServicio(aux);
                }else if(op == 3){
                    break;
                }else{
                    cout << "Opcion incorrecta" << endl;
                }
                break;
            case 4:
                system("cls");
                break;
            default:
                cout << "Opcion incorrecta: Ingrese una valida o 4 para volver" << endl;
                break;
        }system("cls");
    }
    system("cls");
}

inline string tabularr(int n){
    string g="";
    for(int i=0;i<n;i++){
        g=g+"\t";
    }
    return g;
}

inline void tabularc(int n){
    for(int i=0;i<n;i++){
        cout<<endl;
    }
}
