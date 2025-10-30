#include "Planificador.h"

// Constructor: inicializa el quantum
Planificador::Planificador(int q) : quantum(q) {}

// Agregar un proceso a la cola de listos
void Planificador::agregarProceso(Proceso* p) {
    colaListos.push(p);
    cout << "Proceso P" << p->getPID() << " agregado a la cola de listos." << endl;
}

// Ejecutar los procesos según el algoritmo Round Robin
void Planificador::ejecutarProcesos() {
    cout << "\n--- Iniciando planificación Round Robin ---\n";

    // Mientras haya procesos en la cola de listos
    while (!colaListos.empty()) {
        Proceso* actual = colaListos.front();
        colaListos.pop();

        cout << "\n>> Ejecutando P" << actual->getPID()
             << " (tiempo restante: " << actual->getTiempoRestante() << ")\n";

        // Ejecutar el proceso durante un quantum
        actual->ejecutar(quantum);

        // Si el proceso finalizó, lo marcamos como terminado
        if (actual->getEstado() == "Finalizado") {
            cout << "✅ P" << actual->getPID() << " ha finalizado su ejecución.\n";
        } 
        // Si aún le queda tiempo, se reencola
        else {
            cout << "🔁 P" << actual->getPID() << " se reencola (tiempo restante: "
                 << actual->getTiempoRestante() << ")\n";
            colaListos.push(actual);
        }
    }

    cout << "\n--- Todos los procesos han finalizado ---\n";
}

