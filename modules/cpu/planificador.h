#pragma once
#include <queue>
#include <iostream>
#include "Proceso.h"
using namespace std;

class Planificador {
private:
    queue<Proceso*> colaListos;
    int quantum;
    int ticksRestantes;
    Proceso* actual;

public:
    Planificador(int q) : quantum(q), ticksRestantes(0), actual(nullptr) {}

    void agregarProceso(Proceso* p) {
        p->setEstado(LISTO);
        colaListos.push(p);
        cout << "Proceso " << p->getNombre() << " agregado a la cola de listos.\n";
    }

    void tick() {
        if (!actual && colaListos.empty()) {
            cout << "No hay procesos listos.\n";
            return;
        }

        if (!actual && !colaListos.empty()) {
            actual = colaListos.front();
            colaListos.pop();
            actual->setEstado(EJECUTANDO);
            ticksRestantes = quantum;
            cout << "Ejecutando proceso " << actual->getNombre() << "\n";
        }

        if (actual) {
            actual->ejecutarTick();
            ticksRestantes--;

            if (actual->terminado()) {
                actual->setEstado(TERMINADO);
                cout << "Proceso " << actual->getNombre() << " ha terminado.\n";
                delete actual;
                actual = nullptr;
            } 
            else if (ticksRestantes == 0) {
                cout << "Quantum expirado para " << actual->getNombre() << ".\n";
                actual->setEstado(LISTO);
                colaListos.push(actual);
                actual = nullptr;
            }
        }
    }

    void ejecutarN(int n) {
        for (int i = 0; i < n; i++) {
            cout << "----- Tick " << i + 1 << " -----\n";
            tick();
        }
    }

    void kill(int id) {
        if (actual && actual->getId() == id) {
            cout << "Proceso " << actual->getNombre() << " terminado manualmente.\n";
            delete actual;
            actual = nullptr;
            return;
        }

        queue<Proceso*> temp;
        bool eliminado = false;

        while (!colaListos.empty()) {
            Proceso* p = colaListos.front();
            colaListos.pop();
            if (p->getId() == id) {
                cout << "Proceso " << p->getNombre() << " eliminado.\n";
                delete p;
                eliminado = true;
            } else temp.push(p);
        }
        colaListos = temp;

        if (!eliminado)
            cout << "No se encontró proceso con ID " << id << ".\n";
    }

    void mostrarProcesos() {
        cout << "\n=== Procesos ===\n";
        if (actual)
            cout << "EJECUTANDO: " << actual->getNombre() << " (rafagas restantes: " << actual->getRafagas() << ")\n";
        else
            cout << "CPU libre.\n";

        queue<Proceso*> temp = colaListos;
        if (temp.empty()) cout << "Cola de listos vacía.\n";
        while (!temp.empty()) {
            Proceso* p = temp.front();
            temp.pop();
            cout << "LISTO: " << p->getNombre() << " (" << p->getRafagas() << " ráfagas restantes)\n";
        }
    }
};

