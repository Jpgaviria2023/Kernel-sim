#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PCB {
private:
    int pid;                     // Identificador del proceso
    string estado;               // Estado actual del proceso
    vector<int> rafagas;         // Ráfagas de CPU
    int indiceRafagaActual;      // Qué ráfaga está ejecutando
    int tiempoRestante;          // Tiempo total restante del proceso

public:
    PCB(int id, vector<int> rafagasCPU)
        : pid(id), estado("Listo"), rafagas(rafagasCPU),
          indiceRafagaActual(0), tiempoRestante(0) 
    {
        for (int r : rafagas)
            tiempoRestante += r;
    }

    // Getters
    int getPID() const { return pid; }
    string getEstado() const { return estado; }
    int getTiempoRestante() const { return tiempoRestante; }

    // Cambia el estado del proceso
    void setEstado(string nuevoEstado) { estado = nuevoEstado; }

    // Ejecuta una ráfaga parcial (Round Robin)
    void ejecutar(int quantum) {
        estado = "Ejecutando";

        if (indiceRafagaActual < rafagas.size()) {
            if (rafagas[indiceRafagaActual] > quantum) {
                rafagas[indiceRafagaActual] -= quantum;
                tiempoRestante -= quantum;
            } else {
                tiempoRestante -= rafagas[indiceRafagaActual];
                rafagas[indiceRafagaActual] = 0;
                indiceRafagaActual++;
            }

            if (tiempoRestante <= 0)
                estado = "Finalizado";
            else
                estado = "Listo";
        }
    }

    void mostrarInfo() const {
        cout << "P" << pid << " | Estado: " << estado
             << " | Tiempo restante: " << tiempoRestante << endl;
    }
};

#endif
