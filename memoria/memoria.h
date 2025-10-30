#ifndef MEMORIA_H
#define MEMORIA_H

#include <queue>
#include <unordered_set>

class Memoria {
private:
    int capacidad;                     
    std::queue<int> paginasEnMemoria;  
    std::unordered_set<int> conjuntoPaginas;

    int accesos;
    int fallos;

public:
    Memoria(int tam);
    void accederPagina(int pagina);
    void mostrarEstadisticas() const;
};

#endif
