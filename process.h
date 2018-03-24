#include <string>

using namespace std;

const int CREATED = 0;
const int ACTIVE_READY = 1;
const int STATIC_READY = 2;
const int RUNNING = 3;
const int ACTIVE_BLOCKED = 4;
const int STATIC_BLOCKED = 5;
const int TERMINATED = 6;

class Process
{
    public:
        Process(int processID);
        string getStateStr();
        int getPid();
        void switchTo(int state);
        void Terminate();

    private:
        int state;
        int pid;
};

Process::Process(int processID){
    state = CREATED;
    pid = processID;
};

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
