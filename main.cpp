#include <iostream>
using namespace std;

///MyList as an abstract class(interface)
template <typename T>
class MyList{
protected:
    T* arr;
    int itsSize;

public:

    MyList(int itsSize){
        this->itsSize = itsSize;
        this->arr = new T[itsSize];
    }

    virtual ~MyList(){
        delete this->arr;
    }

    int getSize(){
        return this->itsSize;
    }
    ///virtual functions
    virtual void addElem(T element) = 0;
    virtual T getElem() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void clearItems() = 0;
};

template <typename T>
class MyStack:public MyList<T>{
private:
    ///to keep track of where the pushed element will be put
    int nextFreeIdx;
public:

    MyStack(int itsSize):MyList<T>(itsSize){
        this->nextFreeIdx = 0;
    }

    ///make sure first the stack is not full then push if there's still enough space
    void addElem(T element){
        if(!this->isFull()){
            this->arr[this->nextFreeIdx] = element;
            this->nextFreeIdx++;
        }
    }

    ///return the top of the stack and delete it
    T getElem(){
        T top = this->arr[this->nextFreeIdx-1];
        nextFreeIdx--;
        return top;
    }

    ///if next free index to put data is 0 then it must be empty
    bool isEmpty(){
        if(this->nextFreeIdx == 0){
            return true;
        }
        return false;
    }

    ///to check if the stack if full by comparing next free index with the total size
    bool isFull(){
        if(this->nextFreeIdx < this->itsSize){
            return false;
        }
        return true;
    }

    ///delete all the current data and point to new empty data
    ///once this function is called the stack will be empty
    void clearItems(){
        delete this->arr;
        this->nextFreeIdx = 0;
        this->arr = new T[this->itsSize];
    }

};

template <typename T>
class MyQueue:public MyList<T>{
private:
    ///to keep track of the first element and the current pushed element
    int nextFreeIdx, firstTillNow;
public:
    MyQueue(int itsSize):MyList<T>(itsSize){
        this->nextFreeIdx = 0;
        this->firstTillNow = 0;
    }

    ///make sure the queue is not full before pushing items to it
    void addElem(T element){
        if(!this->isFull()){
            this->arr[this->nextFreeIdx] = element;
            this->nextFreeIdx++;
        }
    }

    ///return top of the queue and delete it
    T getElem(){
        T first = this->arr[this->firstTillNow];
        firstTillNow++;
        return first;
    }

    ///to check is the queue is empty
    bool isEmpty(){
        if(this->nextFreeIdx == 0 || this->firstTillNow == nextFreeIdx){
            return true;
        }
        return false;
    }

    bool isFull(){
        if(this->nextFreeIdx < this->itsSize){
            return false;
        }
        return true;
    }

    void clearItems(){
        delete this->arr;
        this->nextFreeIdx = 0;
        this->firstTillNow = 0;
        this->arr = new T[this->itsSize];
    }

};

class Rectangle{
    int length;
    int width;
public:
     class NegativeValue{};
     Rectangle(){
         this->length = 10;
         this->width = 10;
     }

     Rectangle(int l,int w){
         this->length = l;
         this->width = w;
     }

     int getLength(){
         return this->length;
     }

     void setLength(int l){
         if(l < 0){
            throw NegativeValue();
         }
         this->length = l;
     }

     int getWidth(){
         return this->width;
     }

     void setWidth(int w){
         if(w < 0){
            throw NegativeValue();
         }
         this->width = w;
     }

     int getArea(){
         return this->width*this->length;
     }

     friend ostream& operator<<(ostream& out,const Rectangle& r){
         out<<"\nLength = "<<r.length<<"Width = "<<r.width<<'\n';
         out<<"Area = "<<r.length*r.width<<'\n';
         return out;
     }

};


int main(){

    bool running = 1;
    while(running){
        cout<<"Would you like to use a stack or a queue (S/Q)?\n>>";
        char data;cin>>data;
        cout<<"How many items to store?\n>>";
        int capacity;cin>>capacity;
        cout<<"Would you like to store integers, strings, or rectangles (1, 2, or 3)?\n>>";
        int type;cin>>type;
        bool badChoice = 0;
        if(data == 's' || data == 'S'){
            ///stack
            switch(type){

                case 1:
                {
                    MyStack<int> myData(capacity);
                    while(capacity--){
                        cout<<"Enter num:";
                        string buffer;
                        cin>>buffer;
                        int num = 0;
                        int sign = 1;
                        if(buffer[0] == '-'){
                            sign = -1;
                        }
                        int bufferSize = buffer.size();
                        for(int i=0;i<bufferSize;i++){
                            if(i==0 && buffer[0] == '-' ){
                                continue;
                            }
                            if(buffer[i] < '0' || buffer[i] > '9'){
                                num = 0;
                                cout<<"Wrong String Input-->will enter 0\n";
                                break;
                            }else{
                                num*=10;
                                num+=buffer[i]-'0';
                            }
                        }
                        myData.addElem(sign*num);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        cout<<"Element-->"<<myData.getElem()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                case 2:
                {
                    MyStack<char*> myData(capacity);
                    while(capacity--){
                        cout<<"Enter string:";
                        char* str = new char[100];cin>>str;
                        myData.addElem(str);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        cout<<"Element-->"<<myData.getElem()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                case 3:
                {
                    MyStack<Rectangle> myData(capacity);
                    while(capacity--){
                        cout<<"Enter length and width space separated:";
                        int l,w;cin>>l>>w;
                        Rectangle temp;
                        try{
                            temp.setLength(l);
                            temp.setWidth(w);
                        }catch(Rectangle::NegativeValue){
                            cout<<"Wrong length or width entering 0 and 0\n";
                            temp.setLength(0);
                            temp.setWidth(0);
                        }
                        myData.addElem(temp);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        Rectangle curr = myData.getElem();
                        cout<<"Element-->Length="<<curr.getLength()<<", Width="<<curr.getWidth()<<", Area="<<curr.getArea()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                default:
                {
                    badChoice = 1;
                    break;
                }
            }

        }else{
            ///queue
            switch(type){

                case 1:
                {
                    MyQueue<int> myData(capacity);
                    while(capacity--){
                        cout<<"Enter num:";
                        string buffer;
                        cin>>buffer;
                        int num = 0;
                        int sign = 1;
                        if(buffer[0] == '-'){
                            sign = -1;
                        }
                        int bufferSize= buffer.size();
                        for(int i=0;i<bufferSize;i++){
                            if(i==0 && buffer[0] == '-' ){
                                continue;
                            }
                            if(buffer[i] < '0' || buffer[i] > '9'){
                                num = 0;
                                cout<<"Wrong String Input-->will enter 0\n";
                                break;
                            }else{
                                num*=10;
                                num+=buffer[i]-'0';
                            }
                        }
                        myData.addElem(sign*num);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        cout<<"Element-->"<<myData.getElem()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                case 2:
                {
                    MyQueue<char*> myData(capacity);
                    while(capacity--){
                        cout<<"Enter string:";
                        char* str = new char[100];cin>>str;
                        myData.addElem(str);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        cout<<"Element-->"<<myData.getElem()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                case 3:
                {
                    MyQueue<Rectangle> myData(capacity);
                    while(capacity--){
                        cout<<"Enter length and width space separated:";
                        int l,w;cin>>l>>w;
                        Rectangle temp;
                        try{
                            temp.setLength(l);
                            temp.setWidth(w);
                        }catch(Rectangle::NegativeValue){
                            cout<<"Wrong length or width entering 0 and 0\n";
                            temp.setLength(0);
                            temp.setWidth(0);
                        }
                        myData.addElem(temp);
                    }
                    cout<<endl;
                    cout<<"All Elements\n";
                    while(!myData.isEmpty()){
                        Rectangle curr = myData.getElem();
                        cout<<"Element-->Length="<<curr.getLength()<<", Width="<<curr.getWidth()<<", Area="<<curr.getArea()<<endl;
                    }
                    cout<<endl;
                    break;
                }

                default:
                {
                    badChoice = 1;
                    break;
                }
            }
        }
        if(badChoice){
            cout<<"Invalid Choice\n";
            continue;
        }
        cout<<"Do you want to run again (y/n)\n>>";
        char quitChoice;cin>>quitChoice;
        if(quitChoice == 'n' || quitChoice == 'N'){
            running = 0;
        }
    }

    return 0;
}
