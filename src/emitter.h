#include <iostream>
#include <string>
#include <list>

using namespace std;

virtual class EventEmitter{
    protected:
        string m_status;

    private:
        list<EventEmitter* > m_observers; //观察者链表

    public:
        EventEmitter(){}
        ~EventEmitter(){}
        void on(EventEmitter *observer) { m_observers.push_back(observer); }     //添加观察者
        void remove(EventEmitter *observer) { m_observers.remove(observer); }        //移除观察者

        void emit(int eventID) //通知观察者
        {
            list<EventEmitter*>::iterator iter = m_observers.begin();
            for(; iter != m_observers.end(); iter++)
                (*iter)->route(eventID);
        }
        virtual void route(int event){return;}
};
