#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;


class RaceState
{
private:

    static void safePrint(const string& word)
    {
        lock_guard<mutex> mtx(mutex);
        cout << word;
    }

    static void wordAdd(const char& sym) 
    {
        this_thread::sleep_for(chrono::milliseconds(300));
        ostringstream buffer;
        for (int i = 0; i < 3; i++)
        {
            buffer << sym;
        }
        safePrint(buffer.str());
    }

public:

    void checkTime() 
    {
        auto start = chrono::high_resolution_clock::now();

        jthread th1(&RaceState::wordAdd, 'a');
        jthread th2(&RaceState::wordAdd, 'b');
        jthread th3(&RaceState::wordAdd, 'c');
        jthread th4(&RaceState::wordAdd, 'd');


        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "\nElapsed time in race function: " + to_string(elapsed.count()) + " seconds\n";
    }
};

class MutexState 
{
private:
    static void safePrint(const string& word) 
    {
        
        mutex printMutex;
        lock_guard<mutex> lock(printMutex);
        cout << word;
    }

    static void wordAdd(const char& sym) 
    {
        
        mutex funcMutex;
        lock_guard<mutex> lock(funcMutex);
        ostringstream buffer;
        for (int i = 0; i < 3; i++) {
            buffer << sym;
        }

        safePrint(buffer.str());
    }

public:
    void checkTime() {
        auto start = chrono::high_resolution_clock::now();

        // Запускаем потоки, которые используют локальный мьютекс внутри wordAdd
        jthread th1(&MutexState::wordAdd, 'a');
        jthread th2(&MutexState::wordAdd, 'b');
        jthread th3(&MutexState::wordAdd, 'c');
        jthread th4(&MutexState::wordAdd, 'd');

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "\nElapsed time for mutex: " + to_string(elapsed.count()) + " seconds\n";
        
    }
};


int main()
{

    RaceState race;
    race.checkTime();

    this_thread::sleep_for(chrono::milliseconds(500));

    MutexState mutexes;
    mutexes.checkTime();

    return 0;
}