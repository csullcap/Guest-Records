//
// Created by Jerbo on 4/08/2020.
//

enum dimensiones : int {
    ancho = 88,
    alto = 25
};
enum posicion : int {
    Y_DEFAULT = 8,
    X_DEFAULT = 12,

};

static int  Y_Current = 7;

static MYSQL mysql, *connection;
static MYSQL_RES *result;
static MYSQL_ROW row;
static int query_state;


static void gotoxy(int posicion, int current);

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

static void gotoxy(int posicion, int current) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = posicion;
    dwPos.Y = current;
    SetConsoleCursorPosition(hcon, dwPos);
}

