#include "Kernel.h"
#include <iostream>
using namespace std;

Kernel::Kernel(int quantum) : planificador(quantum) {}

void Kernel::crearProceso(int tiempoEjecucion) {
    int id = procesos.size() + 1;
    Proceso* nuevo = new Proceso(id, tiempoEjecucion);
    procesos.push_back(nuevo);
    planificador.agregarProceso(nuevo);
}

void Kernel::iniciarSimulacion() {
    planificador.ejecutarProcesos();
}

class Kernel {
private:
    vector<PCB*> procesos;
    Planificador planificador;

public:
    Kernel(int quantum) : planificador(quantum) {}

    void crearProceso(vector<int> rafagasCPU) {
        int id = procesos.size() + 1;
        PCB* nuevo = new PCB(id, rafagasCPU);
        procesos.push_back(nuevo);
        planificador.agregarProceso(nuevo);
    }

    void listarProcesos() {
        cout << "\n--- Lista de procesos ---\n";
        for (auto p : procesos)
            p->mostrarInfo();
    }

    void iniciarSimulacion() {
        planificador.ejecutarProcesos();
    }
};
