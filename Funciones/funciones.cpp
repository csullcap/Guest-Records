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

bool iniciarSesion(Administrador &admin, Conexion bd_conexion);

void menu_principal(Administrador &admin, Conexion bd_conexion);

void servicioDeHotel(Administrador &admin, Conexion bd_conexion);

void gotoxy(int x, int y);

void imprimir_rectangle(char a);

void mostrarMenuAdministrador(Administrador &administrador, Conexion bd);

void mostrarMenuClientes(Administrador &administrador, Conexion bd);

inline bool iniciarSesion(Administrador &admin, Conexion bd_conexion) {
    string user;
    string password;
    char op_iniciar_sesion = 0;
    bool autentificacion = false;
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
            } else {
                if (password.length() > 0) {
                    cout << "\b \b";
                    password = password.substr(0, password.length() - 1);
                }
            }
            caracter = _getch();
        }
        //getline(cin, password);
        if (bd_conexion.inicioSesion(admin, user, password)) {
            cout << endl << endl << "Cuenta valida" << endl;
            cout << "Espere un momento ";
            Sleep(1000);
            cout << ".";
            Sleep(1000);
            cout << ".";
            Sleep(1000);
            cout << ".";
            autentificacion = true;
        } else {
            cout << endl << endl << "Usuario o contraseña invalidos" << endl;
            cout << "Desea intertar nuevamente (1)Si (2)No" << endl;
            cout << "Opcion: ";
            cin >> op_iniciar_sesion;
        }
        system("cls");
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
        cout << "Menu Principal" << endl;
        cout << "(1) Reservaciones" << endl;
        cout << "(2) Servicio de Hotel" << endl;
        cout << "(3) Turnos" << endl;
        cout << "(4) Administradores" << endl;
        cout << "(5) Clientes" << endl;
        cout << "(6) Servicios" << endl;
        cout << "(7) Salir" << endl;
        cout << "Opcion : ";
        cin >> op_menu_principal;
        switch (op_menu_principal) {

            case '1':
                system("cls");
                cout << "SERVICIO DE RESERVACIONES" << endl;
                system("pause");
                break;

            case '2':
                system("cls");
                cout << "SERVICIO DE HOTEL" << endl;
                servicioDeHotel(admin, bd_conexion);
                break;

            case '3':
                system("cls");
                cout << "TURNOS" << endl;
                system("pause");
                break;

            case '4':
                system("cls");
                cout << "ADMINISTRADORES" << endl;
                system("pause");
                mostrarMenuAdministrador(admin, bd_conexion);
                break;

            case '5':
                system("cls");
                cout << "CLIENTES" << endl;
                system("pause");
                mostrarMenuClientes(admin, bd_conexion);
                break;

            case '6':
                system("cls");
                cout << "SERVICIOS" << endl;
                system("pause");
                break;

            case '7':
                cout << "Salio del menu principal" << endl;
                system("pause");
                system("cls");
                break;

            default:
                system("cls");
                cin.ignore(256, '\n');
                cout << "Opcion Invalida";
                break;
        }

    } while (op_menu_principal != '7');
}

inline void servicioDeHotel(Administrador &admin, Conexion bd_conexion) {
    char op_servicio_de_hotel = 0;
    do {
        cout << "Menu Principal" << endl;
        cout << "(1) Agregar Registro de hospedaje" << endl;
        cout << "(2) Ver Registros pendientes" << endl;
        cout << "(3) Ver Estado de las habitaciones" << endl;
        cout << "(4) Ver todos los registros" << endl;
        cout << "(5) Salir" << endl;
        cout << "Opcion : ";
        cin >> op_servicio_de_hotel;
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
                cout << "Estado de las habitaciones" << endl;
                bd_conexion.estadoHabitacion();
                system("pause");
                break;

            case '4':
                system("cls");
                cout << "Registros pendientes" << endl;
                system("pause");
                break;

            case '5':
                cout << "Ver todos los registros" << endl;
                system("pause");
                system("cls");
                break;

            default:
                system("cls");
                cin.ignore(256, '\n');
                cout << "Opcion Invalida";
                break;
        }
        system("cls");

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
    for (int x = 1; x <= 79; x++) {
        gotoxy(x, 0);
        putchar('=');
        gotoxy(x, 24);
        putchar('=');
    }

    for (int y = 1; y <= 24; y++) {
        gotoxy(0, y);
        putchar('=');
        gotoxy(79, y);
        putchar('=');
    }
}

inline void mostrarMenuAdministrador(Administrador &administrador, Conexion bd) {

    int opcion;

    do {
        cout << "Menu Principal Administradores" << endl;
        cout << "(1) Añadir" << endl;
        cout << "(2) Modificar" << endl;
        cout << "(3) Eliminar" << endl;
        cout << "(4) Ver Todos" << endl;
        cout << "(5) Salir" << endl;
        cout << "Opcion : ";
        cin >> opcion;
        system("cls");

        if (opcion == 1) {
            auto adminNuevo = Administrador();
            cout << "Nombre" << endl;
            cin >> adminNuevo.nombre;
            cout << "Apellidos" << endl;
            cin >> adminNuevo.apellidos;
            cout << "Username" << endl;
            cin >> adminNuevo.username;
            cout << "Password" << endl;
            cin >> adminNuevo.contra;
            cout << "Telefono" << endl;
            cin >> adminNuevo.telefono;
            bd.insertarNuevoAdministrador(adminNuevo);
        } else if (opcion == 2) {
            cout << "Ingrese nombre a buscar:\n" << endl;
            string n;
            cin >> n;
            auto adminModificar = bd.buscarPorNombre(n);
            if (adminModificar.id_administrador != 0) {
                cout << "Dato a modificar: " << endl;
                cout << "(1) Nombre" << endl;
                cout << "(2) Apellidos" << endl;
                cout << "(3) Username" << endl;
                cout << "(4) Telefono" << endl;
                cout << "(5) Salir" << endl;
                cout << "Opcion : ";
                int tipoModificacion;
                cin >> tipoModificacion;
                if (tipoModificacion == 1) {
                    cout << "Nombre actual:" + adminModificar.nombre << endl;
                    cout << "Ingrese nuevo nombre:" << endl;
                    cin >> adminModificar.nombre;
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 2) {
                    cout << "Nombre actual:" + adminModificar.nombre << endl;
                    cout << "Ingrese nuevo Apellido:" << endl;
                    cin >> adminModificar.apellidos;
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 3) {
                    cout << "Nombre actual:" + adminModificar.nombre << endl;
                    cout << "Ingrese nuevo Username:" << endl;
                    cin >> adminModificar.username;
                    bd.actualizarAdministrador(adminModificar);
                } else if (tipoModificacion == 4) {
                    cout << "Nombre actual:" + adminModificar.nombre << endl;
                    cout << "Ingrese nuevo Telefono:" << endl;
                    cin >> adminModificar.telefono;
                    bd.actualizarAdministrador(adminModificar);
                }
            } else {
                cout << "Usuario no encontrado." << endl;
            }
            system("pause");

        } else if (opcion == 3) {
            cout << "Ingrese nombre a buscar:\n" << endl;
            string n;
            cin >> n;
            auto adminModificar = bd.buscarPorNombre(n);
            if (adminModificar.id_administrador != 0) {
                cout << "Eliminar administrador: " + adminModificar.toString() + "\n (1) Si \n(2) No " << endl;
                int eliminar;
                cin >> eliminar;
                if (eliminar == 1) {
                    bd.eliminarAdministrador(adminModificar.id_administrador);
                }
            } else {
                cout << "Usuario no encontrado." << endl;
            }


        } else if (opcion == 4) {
            cout << "\n Lista de Administradores\n" << endl;
            auto admins = bd.getAdministradores();
            for (auto &admin : admins) {
                cout << admin.toString();
            }
            cout << endl;
            system("pause");
        }
    } while (opcion != 5);
    menu_principal(administrador, bd);
}

inline void mostrarMenuClientes(Administrador &administrador, Conexion bd) {
    int opcion;

    do {
        cout << "Menu Principal Clientes" << endl;
        cout << "(1) Añadir" << endl;
        cout << "(2) Modificar" << endl;
        cout << "(3) Eliminar" << endl;
        cout << "(4) Ver Todos" << endl;
        cout << "(5) Salir" << endl;
        cout << "Opcion : ";
        cin >> opcion;
        system("cls");

        if (opcion == 1) {
            auto clienteNuevo = Cliente();
            cout << "Nombre" << endl;
            cin >> clienteNuevo.nombre;
            cout << "Apellidos" << endl;
            getline(cin, clienteNuevo.apellidos);
            getline(cin, clienteNuevo.telefono);
            bd.insertarNuevoCliente(clienteNuevo);
            system("pause");
        }
        else if (opcion == 2) {
            cout << "Ingrese nombre a buscar:\n" << endl;
            string n;
            cin >> n;
            auto clienteModificar = bd.buscarClientePorNombre(n);
            if (clienteModificar.id_cliente != 0) {
                cout << "Dato a modificar: " << endl;
                cout << "(1) Nombre" << endl;
                cout << "(2) Apellidos" << endl;
                cout << "(3) Telefono" << endl;
                cout << "(4) Salir" << endl;
                cout << "Opcion : ";
                int tipoModificacion;
                cin >> tipoModificacion;
                if (tipoModificacion == 1) {
                    cout << "Nombre actual:" + clienteModificar.nombre << endl;
                    cout << "Ingrese nuevo nombre:" << endl;
                    cin >> clienteModificar.nombre;
                    bd.actualizarCliente(clienteModificar);
                } else if (tipoModificacion == 2) {
                    cout << "Nombre actual:" + clienteModificar.nombre << endl;
                    cout << "Ingrese nuevo Apellido:" << endl;
                    cin >> clienteModificar.apellidos;
                    bd.actualizarCliente(clienteModificar);
                } else if (tipoModificacion == 3) {
                    cout << "Nombre actual:" + clienteModificar.nombre << endl;
                    cout << "Ingrese nuevo Telefono:" << endl;
                    cin >> clienteModificar.telefono;
                    bd.actualizarCliente(clienteModificar);
                }
            } else {
                cout << "Usuario no encontrado." << endl;
            }
            system("pause");

        } else if (opcion == 3) {
            cout << "Ingrese nombre a buscar:\n" << endl;
            string n;
            cin >> n;
            auto clienteModificar = bd.buscarClientePorNombre(n);
            if (clienteModificar.id_cliente != 0) {
                cout << "Eliminar cliente: " + clienteModificar.toString() + "\n (1) Si \n(2) No " << endl;
                int eliminar;
                cin >> eliminar;
                if (eliminar == 1) {
                    bd.eliminarCliente(clienteModificar.id_cliente);
                }
            } else {
                cout << "Usuario no encontrado." << endl;
            }


        } else if (opcion == 4) {
            cout << "\n Lista de Clientes\n" << endl;
            auto clientes = bd.getClientes();
            for (auto &cliente : clientes) {
                cout << cliente.toString();
            }
            cout << endl;
            system("pause");
        }
    } while (opcion != 5);
    menu_principal(administrador, bd);
}
