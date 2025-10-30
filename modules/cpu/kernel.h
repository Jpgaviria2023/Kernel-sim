#pragma once
#include <vector>
#include "Planificador.h"

class Kernel {
private:
    vector<Proceso*> procesos;
    Planificador planificador;

public:
    Kernel(int quantum);
    void crearProceso(int tiempoEjecucion);
    void iniciarSimulacion();
};
