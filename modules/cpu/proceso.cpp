#include "Proceso.h"

Proceso::Proceso(int id, int tiempo)
    : pid(id), tiempoEjecucion(tiempo), tiempoRestante(tiempo), estado("Listo") {}

int Proceso::getPID() const { return pid; }
int Proceso::getTiempoRestante() const { return tiempoRestante; }
string Proceso::getEstado() const { return estado; }

void Proceso::setEstado(string nuevoEstado) { estado = nuevoEstado; }

void Proceso::ejecutar(int quantum) {
    estado = "Ejecutando";
    if (tiempoRestante > quantum)
        tiempoRestante -= quantum;
    else
        tiempoRestante = 0;

    if (tiempoRestante == 0)
        estado = "Finalizado";
    else
        estado = "Listo";
}
