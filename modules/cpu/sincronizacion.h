#ifndef SINCRONIZACION_H
#define SINCRONIZACION_H

#include <mutex>
#include <condition_variable>

class Semaforo {
private:
    int contador; // cantidad de recursos disponibles
    std::mutex mtx;
    std::condition_variable cv;

public:
    Semaforo(int valorInicial = 1) : contador(valorInicial) {}

    // wait(): intenta entrar a la sección crítica
    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        while (contador == 0) {
            cv.wait(lock);
        }
        contador--;
    }

    // signal(): libera la sección crítica
    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        contador++;
        cv.notify_one();
    }
};

#endif
