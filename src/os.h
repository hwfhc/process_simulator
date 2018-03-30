#include "./emitter.h"
#include "./process.h"

class OS:public EventEmitter{
    public:
        void readFile(){
            Process p = new Process(1);
        }
}
