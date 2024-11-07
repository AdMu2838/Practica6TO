#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <mutex>

std::mutex mtx; // Mutex para sincronizar el acceso a primVect

void FindPrimes(unsigned int start, unsigned int end, std::vector<unsigned int> &vect)
{
    for (unsigned int x = start; x <= end; x += 2)
    {
        for (unsigned int y = 2; y < x; y++)
        {
            if ((x % y) == 0)
            {
                break;
            }
            else if ((y + 1) == x)
            {
                std::lock_guard<std::mutex> lock(mtx); // Bloqueo para evitar condiciones de carrera
                vect.push_back(x);
            }
        }
    }
}

void FindPrimesWithThreads(unsigned int start, unsigned int end, unsigned int numThreads, std::vector<unsigned int> &primVect)
{
    std::vector<std::thread> threadVect;
    unsigned int threadSpread = (end - start + 1) / numThreads;
    unsigned int newEnd = start + threadSpread - 1;

    for (unsigned int x = 0; x < numThreads; x++)
    {
        threadVect.emplace_back(FindPrimes, start, newEnd, std::ref(primVect));
        start += threadSpread;
        newEnd += threadSpread;
    }

    for (auto &t : threadVect)
    {
        t.join();
    }
}

int main()
{
    std::vector<unsigned int> primVect;
    auto startTime = std::chrono::high_resolution_clock::now();
    FindPrimes(1, 100000, primVect);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
    std::cout << "Execution Time (sin hilos): " << duration << " segundos" << std::endl;

    primVect.clear();
    startTime = std::chrono::high_resolution_clock::now();
    FindPrimesWithThreads(1, 100000, 8, primVect);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
    std::cout << "Execution Time (con hilos): " << duration << " segundos" << std::endl;

    return 0;
}
