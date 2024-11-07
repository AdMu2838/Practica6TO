#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::list<int> linkedList;
std::mutex mtx;

void insertar() {
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 100;
        std::lock_guard<std::mutex> guard(mtx);
        linkedList.push_back(num);
        std::cout << "Insertando: " << num << std::endl;
    }
}

void eliminar() {
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 100;
        std::lock_guard<std::mutex> guard(mtx);
        auto it = std::find(linkedList.begin(), linkedList.end(), num);
        if (it != linkedList.end()) {
            linkedList.erase(it);
            std::cout << "Eliminando: " << num << std::endl;
        } else {
            std::cout << "No se eliminó: " << num << std::endl;
        }
    }
}

void buscar() {
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 100;
        std::lock_guard<std::mutex> guard(mtx);
        auto it = std::find(linkedList.begin(), linkedList.end(), num);
        if (it != linkedList.end()) {
            std::cout << "Buscado: " << num << std::endl;
        } else {
            std::cout << "No encontrado: " << num << std::endl;
        }
    }
}

void modificar() {
    for (int i = 0; i < 10; ++i) {
        int num = rand() % 100;
        std::lock_guard<std::mutex> guard(mtx);
        auto it = std::find(linkedList.begin(), linkedList.end(), num);
        if (it != linkedList.end()) {
            int newVal = *it + 1;
            *it = newVal;
            std::cout << "Modificando " << num << " a " << newVal << std::endl;
        } else {
            std::cout << "No se encontró: " << num << std::endl;
        }
    }
}

int main() {
    srand(time(0));

    std::thread t1(insertar);
    std::thread t2(eliminar);
    std::thread t3(buscar);
    std::thread t4(modificar);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
