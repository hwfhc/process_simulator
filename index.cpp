#include <iostream>

using namespace std;

const int INIT = 0;
const int READY = 1;
const int EXECUTE = 2;
const int BLOCK = 3;
const int OVER = 4;

class process
{
  public:
    int getState()
    {
        return this.state;
    }

    int getPid()
    {
        return this.pid;
    }

    void switchTo(int state)
    {
        // process is ready state
        if (this.state == READY)
        {
            if (state == EXECUTE)
                process.state = state;
            else
                throw exception("process " + this.getPid() +
                                " - invalid state change from " +
                                this.state + " to " + state);
        }

        // process is block state
        if (this.state == BLOCK)
        {
            if (state == READY)
                process.state = state;
            else
                throw exception("process " + this.getPid() +
                                " - invalid state change from " +
                                this.state + " to " + state);
        }

        // process is execute state
        if (this.state == EXECUTE)
        {
            if (state == READY)
                process.state = state;
            else if (state == BLOCK)
                process.state = state;
            else
                throw exception("process " + this.getPid() +
                                " - invalid state change from " +
                                this.state + " to " + state);
        }
    }

  private:
    int state = READY;
    int pid = 1;
};

int main()
{
    count << process.getState();
    return 0;
}
