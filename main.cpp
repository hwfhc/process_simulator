#include <iostream>
#include <string>
#include <list>
#include "./process.h"

using namespace std;

const list<Process> ReadyIndexTable;
const list<Process> BlockIndexTable;

int main()
{
    Process p1(1);
    Process p2(2);
    Process p3(3);
    cout << p.size();

    cout << "Pid is: " + to_string(p1.getPid()) << endl
        << "State is: " + p1.getStateStr() << endl
        << endl;

    // this operation is ok
    p1.switchTo(ACTIVE_READY);

    cout << "Pid is: " + to_string(p1.getPid()) << endl
        << "State is: " + p1.getStateStr() << endl
        << endl;


    // this operation will throw a error
    p1.switchTo(TERMINATED);

    return 0;
};
