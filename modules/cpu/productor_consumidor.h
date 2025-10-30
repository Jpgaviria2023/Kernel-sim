#ifndef PRODUCTOR_CONSUMIDOR_H
#define PRODUCTOR_CONSUMIDOR_H

#include <queue>
#include <thread>
#include <chrono>
#include <iostream>
#include "sincronizacion.h"
using namespace std;

class ProductorConsumidor {
private:
    queue<int> buffer;
    int capacidad;
    Semaforo mutex;
    Semaforo empty;
    Semaforo full;
    int itemID = 0;

public:
    ProductorConsumidor(int capacidadBuffer)
        : capacidad(capacidadBuffer), mutex(1), empty(capacidadBuffer), full(0) {}

    // Función para producir un ítem
    void producir() {
        while (true) {
            this_thread::sleep_for(chrono::milliseconds(800)); // simula tiempo de producción
            empty.wait();
            mutex.wait();

            itemID++;
            buffer.push(itemID);
            cout << "🧱 Productor creó ítem " << itemID
                 << " | Buffer: " << buffer.size() << "/" << capacidad << endl;

            mutex.signal();
            full.signal();
        }
    }

    // Función para consumir un ítem
    void consumir() {
        while (true) {
            this_thread::sleep_for(chrono::milliseconds(1200)); // simula tiempo de consumo
            full.wait();
            mutex.wait();

            int item = buffer.front();
            buffer.pop();
            cout << "🧺 Consumidor tomó ítem " << item
                 << " | Buffer: " << buffer.size() << "/" << capacidad << endl;

            mutex.signal();
            empty.signal();
        }
    }
};

#endif
