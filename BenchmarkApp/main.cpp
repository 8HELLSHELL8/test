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

        jthread th1(wordAdd, 'a');
        jthread th2(wordAdd, 'b');
        jthread th3(wordAdd, 'c');
        jthread th4(wordAdd, 'd');


        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        safePrint("\nElapsed time in race function: " + to_string(elapsed.count()) + " seconds\n");
    }
};


class MutexState
{
private:


    static void safePrint(const string& word)
    {
        
        cout << word;
    }

    static void wordAdd(const char& sym) 
    {
        lock_guard<mutex> mutexForFunc(mutex);
        this_thread::sleep_for(chrono::milliseconds(300));
        lock_guard<mutex> mtx(mutex);
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

        jthread th1(wordAdd, 'a');
        jthread th2(wordAdd, 'b');
        jthread th3(wordAdd, 'c');
        jthread th4(wordAdd, 'd');


        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        safePrint("\nElapsed time for mutex: " + to_string(elapsed.count()) + " seconds\n");
    }

};


int main()
{

    RaceState race;
    race.checkTime();

    this_thread::sleep_for(chrono::milliseconds(200));

    MutexState mutexes;
    mutexes.checkTime();

    return 0;
}