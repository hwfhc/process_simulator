#include <iostream>
#include <string>
#include <map>
#include "./process.h"

using namespace std;

Process* RunningProcess;
map<int,Process> ReadyIndexTable;
map<int,Process> BlockIndexTable;

int i = 0;

Process create(){
    Process p(i);

    ReadyIndexTable.insert(pair<int, Process>(i, p));

    i++;
    return p;
}

void Schedule(Process* p){
    RunningProcess = p;
    p->Schedule();

    ReadyIndexTable.erase(p->getPid());
    BlockIndexTable.erase(p->getPid());
}
void Terminate(Process* p){
    p->Terminate();

    ReadyIndexTable.erase(p->getPid());
    BlockIndexTable.erase(p->getPid());
}
void Block(Process* p){
    p->Block();
    ReadyIndexTable.erase(p->getPid());
    BlockIndexTable.insert(pair<int, Process>(p->getPid(), *p));
}
void Wakeup(Process* p){
    p->Wakeup();
    ReadyIndexTable.insert(pair<int, Process>(p->getPid(), *p));
    BlockIndexTable.erase(p->getPid());
}
void Suspend(Process* p){
    p->Suspend();
}
void Active(Process* p){
    p->Active();
}


Process p1 = create();
Process p2 = create();
Process p3 = create();

void print(){
    cout << "state of p1 is: " << p1.getStateStr() << endl;
    cout << "state of p2 is: " << p2.getStateStr() << endl;
    cout << "state of p3 is: " << p3.getStateStr() << endl;
    cout << "size of ReadyTable is: " << ReadyIndexTable.size() << endl;
    cout << "size of BlockTable is: " << BlockIndexTable.size() << endl;
    cout << "Running Process is: " << RunningProcess->getPid() << endl << endl;
}

int main()
{
    cout << "Schedule p1 " << endl
        << "Suspend p2" << endl << endl;
    Schedule(&p1);
    Suspend(&p2);
    print();

    cout << "Block p1 " << endl
        << "Active p2" << endl
        << "Schedule p3" << endl << endl;
    Block(&p1);
    Active(&p2);
    Schedule(&p3);
    print();

    return 0;
};

