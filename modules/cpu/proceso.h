#pragma once
#include <string>
using namespace std;

enum Estado { NUEVO, LISTO, EJECUTANDO, TERMINADO };

class Proceso {
private:
    int id;
    string nombre;
    int rafagasRestantes;
    Estado estado;

public:
    Proceso(int id_, string nombre_, int rafagas_)
        : id(id_), nombre(nombre_), rafagasRestantes(rafagas_), estado(NUEVO) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    int getRafagas() const { return rafagasRestantes; }
    Estado getEstado() const { return estado; }

    void setEstado(Estado e) { estado = e; }
    void ejecutarTick() { if (rafagasRestantes > 0) rafagasRestantes--; }
    bool terminado() const { return rafagasRestantes == 0; }
};

