#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <semaphore>
#include <barrier>
using namespace std;

void PrintForRace(char asciiSym)
{
    this_thread::sleep_for(chrono::milliseconds(500));
    for (int i = 0; i < 5; i++)
    {
        cout << asciiSym;
    }
    
}


void RaceState()
{
    auto start = std::chrono::high_resolution_clock::now();
    
    thread th1(PrintForRace, 'a');
    thread th2(PrintForRace, 'b');
    thread th3(PrintForRace, 'c');
    thread th4(PrintForRace, 'd');

    th1.detach();
    th2.detach();
    th3.detach();
    th4.join();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << endl << "Elapsed time in race function: " << elapsed.count() << " seconds\n";
}

mutex mtx;



void PrintForMutexes(char asciiSym)
{
    lock_guard<mutex> mutexCheck(mtx);
    //this_thread::sleep_for(chrono::milliseconds(500));
    for (int i = 0; i < 5; i++)
    {
        cout << asciiSym;
    }
    
}

void MutexesState()
{
    auto start = std::chrono::high_resolution_clock::now();
    thread th1(PrintForMutexes, 'a');
    th1.detach();
    thread th2(PrintForMutexes, 'b');
    th2.detach();
    thread th3(PrintForMutexes, 'c');
    th3.detach();
    thread th4(PrintForMutexes, 'd');
    
    th4.join();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << endl << "Elapsed time in mutex lock function: " << elapsed.count() << " seconds\n";

}

counting_semaphore<4> sem(2);

void PrintForSemaphore(char asciiSym)
{
    sem.acquire();
    //this_thread::sleep_for(chrono::milliseconds(500));
    for (int i = 0; i < 5; i++)
    {
        cout << asciiSym;
    }
    sem.release();
    
}

void SemaphoreState()
{
    auto start = std::chrono::high_resolution_clock::now();
    thread th1(PrintForSemaphore, 'a');
    th1.detach();
    thread th2(PrintForSemaphore, 'b');
    th2.detach();
    thread th3(PrintForSemaphore, 'c');
    th3.detach();
    thread th4(PrintForSemaphore, 'd');
    
    
    
    th4.join();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << endl << "Elapsed time in semaphore lock function: " << elapsed.count() << " seconds\n";
}

barrier myBarrier{4};

void PrintForBarrier(char sym)
{
    myBarrier.arrive_and_wait();
    cout << sym;
}

void BarrierState()
{
    auto start = std::chrono::high_resolution_clock::now();
    thread th1(PrintForBarrier, 'a');
    th1.detach();
    thread th2(PrintForBarrier, 'b');
    th2.detach();
    thread th3(PrintForBarrier, 'c');
    th3.detach();
    thread th4(PrintForBarrier, 'd');
    
    //th1.join();
    //th2.join();
    //th3.join();
    th4.join();

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << endl << "Elapsed time in barrier lock function: " << elapsed.count() << " seconds\n";
}


int main()
{
    //RaceState();
    chrono::milliseconds(500);
    //MutexesState();
    chrono::milliseconds(500);
    //SemaphoreState();
    chrono::milliseconds(500);
    BarrierState();
    return 0;
}