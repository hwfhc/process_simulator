#include <string>
#include "./emitter.h"
#include "./define.h"

using namespace std;

class Process:public EventEmitter
{
    public:
        Process(int pid);
        string getStateStr();
        int getPid();
        //void Create();
        void Schedule();
        void Terminate();
        void Block();
        void Wakeup();
        void Suspend();
        void Active();

        void route(int event){
            cout << event << endl;
        }

    private:
        int state;
        int pid;

        void switchTo(int state);
};

Process::Process(int processID){
    state = ACTIVE_READY;
    pid = processID;
};
void Process::Schedule(){
    this->switchTo(RUNNING);
}
void Process::Terminate(){
    this->switchTo(TERMINATED);
}
void Process::Block(){
    this->switchTo(ACTIVE_BLOCKED);
}
void Process::Wakeup(){
    this->switchTo(ACTIVE_READY);
}
void Process::Suspend(){
    switch(this->state){
        case ACTIVE_READY:
            this->switchTo(STATIC_READY);
            break;
        case ACTIVE_BLOCKED:
            this->switchTo(STATIC_BLOCKED);
            break;
        default:
            this->switchTo(STATIC_BLOCKED);
    }
}
void Process::Active(){
    switch(this->state){
        case STATIC_READY:
            this->switchTo(ACTIVE_READY);
            break;
        case STATIC_BLOCKED:
            this->switchTo(ACTIVE_BLOCKED);
            break;
        default:
            this->switchTo(ACTIVE_BLOCKED);
    }
}

string Process::getStateStr()
{
    string str = "invalid state:" + to_string(this->state) + " in process: " + to_string(this->pid);

    if (this->state == CREATED)
        return "CREATED";
    else if (this->state == ACTIVE_READY)
        return "ACTIVE_READY";
    else if (this->state == STATIC_READY)
        return "STATIC_READY";
    else if(this->state == RUNNING)
        return "RUNNING";
    else if(this->state == ACTIVE_BLOCKED)
        return "ACTIVE_BLOCKED";
    else if(this->state == STATIC_BLOCKED)
        return "STATIC_BLOCKED";
    else if(this->state == TERMINATED)
        return "TERMINATED";
    else
        throw runtime_error(str);
};

int Process::getPid()
{
    return this->pid;
};

void Process::switchTo(int state)
{
    string str = "process " + to_string(this->getPid()) +
        " - invalid state change from " +
        to_string(this->state) + " to " + to_string(state);

    switch(this->state){
        case CREATED:
            // process is CREATED state
            if (state == ACTIVE_READY)
                this->state = state;
            else if (state == STATIC_READY)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case ACTIVE_READY:
            // process is active_ready state
            if (state == RUNNING)
                this->state = state;
            else if (state == STATIC_READY)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case STATIC_READY:
            // process is static_ready state
            if (state == ACTIVE_READY)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case RUNNING:
            // process is running state
            if (state == ACTIVE_READY)
                this->state = state;
            else if(state == STATIC_READY)
                this->state = state;
            else if(state == ACTIVE_BLOCKED)
                this->state = state;
            else if(state == TERMINATED)
                throw runtime_error(str);

            break;

        case ACTIVE_BLOCKED:

            // process is active_block state
            if (state == ACTIVE_READY)
                this->state = state;
            else if(state == STATIC_BLOCKED)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case STATIC_BLOCKED:
            // process is static_block state
            if (state == STATIC_READY)
                this->state = state;
            else if(state == ACTIVE_BLOCKED)
                this->state = state;
            else
                throw runtime_error(str);

            break;
        case TERMINATED:
            throw runtime_error(str);
    }
};
