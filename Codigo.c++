#include <iostream>
#include <limits>
#include <climits>
#include <string>

using namespace std;

// Estructura adaptada para los Pedidos (Lista)
struct NodoPedido {
    int idPedido;
    NodoPedido* siguiente;
};

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int pedirEntero(const string& mensaje, int minOpcion = INT_MIN, int maxOpcion = INT_MAX) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor < minOpcion || valor > maxOpcion) {
                cout << "  Error: Ingrese un valor entre " << minOpcion << " y " << maxOpcion << "." << endl;
            } else {
                limpiarEntrada();
                return valor;
            }
        } else {
            cout << "  Error: Entrada no valida, intente de nuevo." << endl;
            limpiarEntrada();
        }
    }
}

// ==========================================
// ----- LISTA: REGISTRO DE PEDIDOS -----
// ==========================================
NodoPedido* cabeza = NULL; 

bool sinPedidos() {
    return cabeza == NULL;
}

void mostrarPedidos() {
    if (sinPedidos()) {
        cout << "  No hay pedidos pendientes." << endl;
        return;
    }
    cout << "  Pedidos a preparar (IDs): ";
    NodoPedido* actual = cabeza;
    while (actual != NULL) {
        cout << "[Pedido #" << actual->idPedido << "]";
        if (actual->siguiente != NULL) cout << " -> ";
        actual = actual->siguiente;
    }
    cout << endl;
}

void pedidoUrgente(int id) {
    NodoPedido* nuevo = new NodoPedido;
    nuevo->idPedido = id;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    cout << "  Pedido URGENTE #" << id << " registrado al inicio." << endl;
}

void nuevoPedido(int id) {
    NodoPedido* nuevo = new NodoPedido;
    nuevo->idPedido = id;
    nuevo->siguiente = NULL;
    
    if (sinPedidos()) {
        cabeza = nuevo;
    } else {
        NodoPedido* actual = cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    cout << "  Pedido #" << id << " registrado en la lista." << endl;
}

void despacharPrimerPedido() {
    if (sinPedidos()) {
        cout << "  No hay pedidos para despachar." << endl;
        return;
    }
    NodoPedido* borrar = cabeza;
    cabeza = cabeza->siguiente;
    cout << "  Se despacho el pedido #" << borrar->idPedido << " exitosamente." << endl;
    delete borrar;
}

void cancelarUltimoPedido() {
    if (sinPedidos()) {
        cout << "  No hay pedidos para cancelar." << endl;
        return;
    }
    if (cabeza->siguiente == NULL) {
        cout << "  Se cancelo el unico pedido #" << cabeza->idPedido << "." << endl;
        delete cabeza;
        cabeza = NULL;
        return;
    }
    NodoPedido* actual = cabeza;
    NodoPedido* anterior = NULL;
    while (actual->siguiente != NULL) {
        anterior = actual;
        actual = actual->siguiente;
    }
    anterior->siguiente = NULL;
    cout << "  Se cancelo el ultimo pedido #" << actual->idPedido << "." << endl;
    delete actual;
}

void limpiarTodosLosPedidos() {
    while (!sinPedidos()) {
        NodoPedido* borrar = cabeza;
        cabeza = cabeza->siguiente;
        delete borrar;
    }
    cout << "  Se han limpiado todos los pedidos del registro." << endl;
}

void menuPedidos() {
    while (true) {
        cout << "\n--- MENU DE PEDIDOS (LISTA) ---" << endl;
        cout << "1. Ingresar pedido urgente (Al inicio)" << endl;
        cout << "2. Ingresar nuevo pedido (Al final)" << endl;
        cout << "3. Despachar primer pedido" << endl;
        cout << "4. Cancelar ultimo pedido" << endl;
        cout << "5. Ver todos los pedidos pendientes" << endl;
        cout << "6. Borrar todo el registro de pedidos" << endl;
        cout << "0. Volver a la caja principal" << endl;
        int opcion = pedirEntero("Seleccione una opcion: ", 0, 6);

        switch (opcion) {
            case 1: pedidoUrgente(pedirEntero("  Ingrese ID del pedido urgente: ")); break;
            case 2: nuevoPedido(pedirEntero("  Ingrese ID del nuevo pedido: ")); break;
            case 3: despacharPrimerPedido(); break;
            case 4: cancelarUltimoPedido(); break;
            case 5: mostrarPedidos(); break;
            case 6: limpiarTodosLosPedidos(); break;
            case 0: return;
        }
    }
}

// ==========================================
// ----- PILA: ALMACEN DE SACOS DE HARINA -----
// ==========================================
const int MAX_SACOS = 100;
int almacenHarina[MAX_SACOS];
int sacoTope = -1;

bool almacenVacio() { return sacoTope == -1; }
bool almacenLleno() { return sacoTope == MAX_SACOS - 1; }

void apilarSaco(int loteID) {
    if (almacenLleno()) {
        cout << "  Error: El almacen de harina esta lleno." << endl;
        return;
    }
    almacenHarina[++sacoTope] = loteID;
    cout << "  Saco de harina (Lote " << loteID << ") apilado en el almacen." << endl;
}

void usarSaco() {
    if (almacenVacio()) {
        cout << "  Error: No hay sacos de harina en el almacen!" << endl;
        return;
    }
    cout << "  Se abrio y uso el saco de harina (Lote " << almacenHarina[sacoTope] << ") que estaba arriba." << endl;
    sacoTope--;
}

void verSacoArriba() {
    if (almacenVacio()) {
        cout << "  El almacen de harina esta vacio." << endl;
    } else {
        cout << "  Saco listo para usar (Arriba): Lote " << almacenHarina[sacoTope] << endl;
    }
}

void mostrarAlmacen() {
    if (almacenVacio()) {
        cout << "  El almacen esta vacio." << endl;
        return;
    }
    cout << "  Pila de Sacos (Arriba -> Abajo): ";
    for (int i = sacoTope; i >= 0; i--) {
        cout << "[Lote " << almacenHarina[i] << "]";
        if (i > 0) cout << " | ";
    }
    cout << endl;
}

void vaciarAlmacen() {
    sacoTope = -1;
    cout << "  Se vacio todo el almacen de harina." << endl;
}

void menuAlmacen() {
    while (true) {
        cout << "\n--- ALMACEN DE HARINA (PILA) ---" << endl;
        cout << "1. Guardar nuevo saco de harina (Push)" << endl;
        cout << "2. Usar saco de harina (Pop)" << endl;
        cout << "3. Ver que saco esta arriba" << endl;
        cout << "4. Ver todos los sacos apilados" << endl;
        cout << "5. Cuantos sacos quedan?" << endl;
        cout << "0. Volver a la caja principal" << endl;
        int opcion = pedirEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
            case 1: apilarSaco(pedirEntero("  Ingrese numero de Lote del saco: ")); break;
            case 2: usarSaco(); break;
            case 3: verSacoArriba(); break;
            case 4: mostrarAlmacen(); break;
            case 5: cout << "  Total de sacos en almacen: " << (sacoTope + 1) << endl; break;
            case 0: return;
        }
    }
}

// ==========================================
// ----- COLA: FILA DE CLIENTES -----
// ==========================================
const int MAX_CLIENTES = 100;
int filaClientes[MAX_CLIENTES];
int turnoFrente = 0;
int turnoAtras = 0;
int cantidadClientes = 0;

bool sinClientes() { return cantidadClientes == 0; }
bool filaLlena() { return cantidadClientes == MAX_CLIENTES; }

void llegaCliente(int ticket) {
    if (filaLlena()) {
        cout << "  La panaderia esta muy llena, no entran mas clientes." << endl;
        return;
    }
    filaClientes[turnoAtras] = ticket;
    turnoAtras = (turnoAtras + 1) % MAX_CLIENTES;
    cantidadClientes++;
    cout << "  Cliente con ticket #" << ticket << " se formo en la fila." << endl;
}

void atenderCliente() {
    if (sinClientes()) {
        cout << "  No hay clientes en la fila, panadero descansando." << endl;
        return;
    }
    cout << "  Se atendio y cobro al cliente con ticket #" << filaClientes[turnoFrente] << "." << endl;
    turnoFrente = (turnoFrente + 1) % MAX_CLIENTES;
    cantidadClientes--;
}

void mostrarFila() {
    if (sinClientes()) {
        cout << "  La fila esta vacia." << endl;
        return;
    }
    cout << "  Fila actual (Caja <- Ultimo): ";
    int indice = turnoFrente;
    for (int i = 0; i < cantidadClientes; i++) {
        cout << "[Ticket " << filaClientes[indice] << "]";
        if (i < cantidadClientes - 1) cout << " <- ";
        indice = (indice + 1) % MAX_CLIENTES;
    }
    cout << endl;
}

void cerrarFila() {
    turnoFrente = 0;
    turnoAtras = 0;
    cantidadClientes = 0;
    cout << "  Se cerro la panaderia, todos los clientes fueron retirados." << endl;
}

void menuClientes() {
    while (true) {
        cout << "\n--- ATENCION A CLIENTES (COLA) ---" << endl;
        cout << "1. Llega un nuevo cliente a la fila (Encolar)" << endl;
        cout << "2. Atender al primer cliente (Desencolar)" << endl;
        cout << "3. Ver toda la fila de clientes" << endl;
        cout << "4. Cuantos clientes estan esperando?" << endl;
        cout << "0. Volver a la caja principal" << endl;
        int opcion = pedirEntero("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
            case 1: llegaCliente(pedirEntero("  Ingrese numero de ticket del cliente: ")); break;
            case 2: atenderCliente(); break;
            case 3: mostrarFila(); break;
            case 4: cout << "  Clientes en fila: " << cantidadClientes << endl; break;
            case 0: return;
        }
    }
}

// ==========================================
// ----- MAIN: SISTEMA DE LA PANADERIA -----
// ==========================================
int main() {
    cout << "==========================================\n";
    cout << "   BIENVENIDO A LA PANADERIA 'EL CAUSA'   \n";
    cout << "==========================================\n";
    
    while (true) {
        cout << "\n--- CAJA PRINCIPAL ---" << endl;
        cout << "1. Gestionar Pedidos (LISTA)" << endl;
        cout << "2. Gestionar Almacen de Harina (PILA)" << endl;
        cout << "3. Atencion de Clientes (COLA)" << endl;
        cout << "0. Cerrar Panaderia (Salir)" << endl;
        int opcion = pedirEntero("Seleccione un area de trabajo: ", 0, 3);

        switch (opcion) {
            case 1:
                menuPedidos();
                break;
            case 2:
                menuAlmacen();
                break;
            case 3:
                menuClientes();
                break;
            case 0:
                limpiarTodosLosPedidos();
                vaciarAlmacen();
                cerrarFila();
                cout << "Cerrando sistema de la panaderia. !Buen trabajo hoy, bro!" << endl;
                return 0;
        }
    }
}