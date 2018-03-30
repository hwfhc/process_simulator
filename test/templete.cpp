#include <iostream>

template <typename Func,typename... Args>
void invoke(Func routine,Args... args){
    routine(args...);
}

void print(int c,double d){
    std::cout << c << d << std::endl;
}

int main(int argc,char** argv){
    invoke(print,3,3.14);
    return 0;
}
