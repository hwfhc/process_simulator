#include <iostream>
#include <string>

using namespace std;

const int INIT = 0;
const int ACTIVE_READY = 1;
const int STATIC_READY = 2;
const int EXECUTE = 3;
const int ACTIVE_BLOCK = 4;
const int STATIC_BLOCK = 5;
const int OVER = 6;

class Process
{
    public:
        Process(int processID);
        string getStateStr();
        int getPid();
        void switchTo(int state);

    private:
        int state;
        int pid;
};

Process::Process(int processID){
    state = INIT;
    pid = processID;
};

string Process::getStateStr()
{
    string str = "invalid state:" + to_string(this->state) + " in process: " + to_string(this->pid);

    if (this->state == INIT)
        return "INIT";
    else if (this->state == ACTIVE_READY)
        return "ACTIVE_READY";
    else if (this->state == STATIC_READY)
        return "STATIC_READY";
    else if(this->state == EXECUTE)
        return "EXECUTE";
    else if(this->state == ACTIVE_BLOCK)
        return "ACTIVE_BLOCK";
    else if(this->state == STATIC_BLOCK)
        return "STATIC_BLOCK";
    else if(this->state == OVER)
        return "OVER";
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
        case INIT:
            // process is init state
            if (state == ACTIVE_READY)
                this->state = state;
            else if (state == STATIC_READY)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case ACTIVE_READY:
            // process is active_ready state
            if (state == EXECUTE)
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

        case EXECUTE:
            if (state == ACTIVE_READY)
                this->state = state;
            else if(state == STATIC_READY)
                this->state = state;
            else if(state == ACTIVE_BLOCK)
                this->state = state;
            else if(state == OVER)
                throw runtime_error(str);

            break;

        case ACTIVE_BLOCK:

            // process is active_block state
            if (state == ACTIVE_READY)
                this->state = state;
            else if(state == STATIC_BLOCK)
                this->state = state;
            else
                throw runtime_error(str);

            break;

        case STATIC_BLOCK:
            // process is static_block state
            if (state == STATIC_READY)
                this->state = state;
            else if(state == ACTIVE_BLOCK)
                this->state = state;
            else
                throw runtime_error(str);

            break;
        case OVER:
            throw runtime_error(str);
    }
};



int main()
{
    Process test(2);
    cout << "Pid is: " + to_string(test.getPid()) << endl
        << "State is: " + test.getStateStr() << endl
        << endl;

    // this operation is ok
    test.switchTo(ACTIVE_READY);

    cout << "Pid is: " + to_string(test.getPid()) << endl
        << "State is: " + test.getStateStr() << endl
        << endl;


    // this operation will throw a error
    test.switchTo(OVER);

    return 0;
};
