#include "memoria.h"
#include <iostream>
using namespace std;

Memoria::Memoria(int tam) : capacidad(tam), accesos(0), fallos(0) {}

void Memoria::accederPagina(int pagina) {
    accesos++;
    cout << "Accediendo a página " << pagina << "...\n";

    if (conjuntoPaginas.find(pagina) != conjuntoPaginas.end()) {
        cout << "✔ Página " << pagina << " ya está en memoria (HIT)\n";
        return;
    }

    fallos++;
    cout << "❌ Fallo de página con " << pagina << "\n";

    if (paginasEnMemoria.size() == capacidad) {
        int paginaReemplazada = paginasEnMemoria.front();
        paginasEnMemoria.pop();
        conjuntoPaginas.erase(paginaReemplazada);
        cout << "Reemplazando página " << paginaReemplazada << " por " << pagina << "\n";
    }

    paginasEnMemoria.push(pagina);
    conjuntoPaginas.insert(pagina);
}

void Memoria::mostrarEstadisticas() const {
    cout << "\n📊 Estadísticas de reemplazo de páginas (FIFO):\n";
    cout << "Accesos totales: " << accesos << "\n";
    cout << "Fallos de página: " << fallos << "\n";
    cout << "Tasa de fallos: " << ((float)fallos / accesos) * 100 << "%\n";
}
