#include <iostream>
#include <thread>
#include "modules/cpu/Kernel.h"
#include "modules/sync/ProductorConsumidor.h"

using namespace std;

int main() {
    int opcion;

    cout << "===== SIMULADOR DE SISTEMAS OPERATIVOS =====\n";
    cout << "Selecciona la simulacion que deseas ejecutar:\n";
    cout << "1. Planificador Round Robin\n";
    cout << "2. Problema Productor-Consumidor\n";
    cout << "--------------------------------------------\n";
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        cout << "\n--- Simulacion del planificador Round Robin ---\n";
        int quantum = 3;
        Kernel kernel(quantum);

        // Crear algunos procesos de prueba
        kernel.crearProceso(5);
        kernel.crearProceso(9);
        kernel.crearProceso(4);

        // Iniciar la simulacion
        kernel.iniciarSimulacion();
    } 
    else if (opcion == 2) {
        cout << "\n--- Simulacion del problema Productor-Consumidor ---\n";
        ProductorConsumidor sistema(5); // Buffer con 5 espacios

        // Crear hilos para productor y consumidor
        thread productor(&ProductorConsumidor::producir, &sistema);
        thread consumidor(&ProductorConsumidor::consumir, &sistema);

        productor.join();
        consumidor.join();
    } 
    else {
        cout << "Opcion no valida. Intenta de nuevo.\n";
    }

    cout << "\nSimulacion finalizada.\n";
    return 0;
}

