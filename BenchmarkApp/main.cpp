#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class RaceState 
{
private:
    static void safePrint(const string& word, mutex& printMutex) 
    {
        lock_guard<mutex> lock(printMutex); // Локальный мьютекс для cout
        cout << word;
    }

    static void wordAdd(const char& sym, mutex& printMutex) 
    {
        this_thread::sleep_for(chrono::milliseconds(300)); // Имитация задержки
        ostringstream buffer;
        for (int i = 0; i < 3; i++) 
        {
            buffer << sym;
        }
        safePrint(buffer.str(), printMutex); // Использование локального мьютекса
    }

public:
    void checkTime() 
    {
        auto start = chrono::high_resolution_clock::now();

        mutex printMutex; // Локальный мьютекс для всей функции

        jthread th1(&RaceState::wordAdd, 'a', ref(printMutex));
        jthread th2(&RaceState::wordAdd, 'b', ref(printMutex));
        jthread th3(&RaceState::wordAdd, 'c', ref(printMutex));
        jthread th4(&RaceState::wordAdd, 'd', ref(printMutex));

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        {
            lock_guard<mutex> lock(printMutex);
            cout << "\nElapsed time in race function: " + to_string(elapsed.count()) + " seconds\n";
        }
    }
};

class MutexState 
{
private:

    static void safePrint(const string& word, mutex& printMutex) 
    {
        lock_guard<mutex> lock(printMutex); // Локальный мьютекс для cout
        cout << word;
    }

    static void wordAdd(const char& sym, mutex& printMutex, mutex& funcMutex) 
    {
        lock_guard<mutex> lock(funcMutex); // Локальный мьютекс для функции
        this_thread::sleep_for(chrono::milliseconds(300)); // Имитация задержки
        ostringstream buffer;
        for (int i = 0; i < 3; i++) 
        {
            buffer << sym;
        }
        safePrint(buffer.str(), printMutex); // Использование мьютекса для cout
    }

public:

    void checkTime() 
    {
        auto start = chrono::high_resolution_clock::now();

        mutex printMutex; // Локальный мьютекс для cout
        mutex funcMutex;  // Локальный мьютекс для синхронизации функции

        jthread th1(&MutexState::wordAdd, 'a', ref(printMutex), ref(funcMutex));
        jthread th2(&MutexState::wordAdd, 'b', ref(printMutex), ref(funcMutex));
        jthread th3(&MutexState::wordAdd, 'c', ref(printMutex), ref(funcMutex));
        jthread th4(&MutexState::wordAdd, 'd', ref(printMutex), ref(funcMutex));

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        {
            lock_guard<mutex> lock(printMutex);
            cout << "\nElapsed time for mutex: " + to_string(elapsed.count()) + " seconds\n";
        }
    }

};

class SemaphoreState
{
private:

    static void safePrint(const string& word, counting_semaphore<1>& printMutex) 
    {
        printMutex.acquire(); // Локальный мьютекс для cout
        cout << word;
        printMutex.release();
    }

    static void wordAdd(const char& sym, counting_semaphore<1>& printMutex, counting_semaphore<1>& funcMutex) 
    {
        funcMutex.acquire(); // Локальный мьютекс для функции
        this_thread::sleep_for(chrono::milliseconds(300)); // Имитация задержки
        ostringstream buffer;
        for (int i = 0; i < 3; i++) 
        {
            buffer << sym;
        }
        safePrint(buffer.str(), printMutex); // Использование мьютекса для cout
        funcMutex.release();
    }

public:

    void checkTime() 
    {
        auto start = chrono::high_resolution_clock::now();

        counting_semaphore<1> printMutex(1); // Локальный мьютекс для cout
        counting_semaphore<1> funcMutex(1); // Локальный мьютекс для синхронизации функции

        jthread th1(&SemaphoreState::wordAdd, 'a', ref(printMutex), ref(funcMutex));
        jthread th2(&SemaphoreState::wordAdd, 'b', ref(printMutex), ref(funcMutex));
        jthread th3(&SemaphoreState::wordAdd, 'c', ref(printMutex), ref(funcMutex));
        jthread th4(&SemaphoreState::wordAdd, 'd', ref(printMutex), ref(funcMutex));

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        {
            printMutex.acquire();
            cout << "\nElapsed time for semaphores: " + to_string(elapsed.count()) + " seconds\n";
            printMutex.release();
        }
    }

};


int main() {
    RaceState race;
    race.checkTime();

    this_thread::sleep_for(chrono::milliseconds(500)); // Небольшая пауза

    MutexState mutexes;
    mutexes.checkTime();

    this_thread::sleep_for(chrono::milliseconds(500)); // Небольшая пауза

    SemaphoreState semaphores;
    semaphores.checkTime();

    return 0;
}
