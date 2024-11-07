#include <thread>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;
void ExecuteThread(int id) {
    auto nowTime = chrono::system_clock::now();
    time_t sleepTime = chrono::system_clock::to_time_t(nowTime);
    
    // Calculate the local timezone
    tm myLocalTime = *localtime(&sleepTime);

    cout << "Thread: " << id << " sleep time: " << ctime(&sleepTime) << "\n";
    cout << "Month: " << (myLocalTime.tm_mon + 1) << "\n";
    cout << "Day: " << myLocalTime.tm_mday << "\n";
    cout << "Year: " << (myLocalTime.tm_year + 1900) << "\n";
    cout << "Hours: " << myLocalTime.tm_hour << "\n";
    cout << "Minutes: " << myLocalTime.tm_min << "\n";
    cout << "Seconds: " << myLocalTime.tm_sec << "\n\n";

    // 3 seconds of sleep
    this_thread::sleep_for(chrono::seconds(3));

    nowTime = chrono::system_clock::now();
    sleepTime = chrono::system_clock::to_time_t(nowTime);
    
    cout << "Thread: " << id << " Awake Time: " << ctime(&sleepTime) << "\n";
}

int main() {
    thread th1(ExecuteThread, 1);
    th1.join();

    thread th2(ExecuteThread, 2);
    th2.join();

    return 0;
}
