#include<iostream>
#include<stdlib.h>

using namespace std;

template<typename T>
class deque{
    private:
        int max_size;
        T *arr;
        int head,rear;
    public:
        deque(){
            max_size=1000;
            head=-1;
            rear=-1;
            arr=(T*)malloc(sizeof(T)*max_size);
        }
        deque(int n,T data){
            max_size=1000;
            head=0;
            rear=-1;
            if(n>max_size)
                max_size=2*n;
            arr=(T*)malloc(sizeof(T)*max_size);
            for(int i=0;i<n;i++){
                rear=(rear+1)%max_size;
                arr[rear]=data;
            }
        }

        void extend(int x){
            T *temp;
            temp=(T*)malloc(sizeof(T)*x*2);
            int cur_size=size();
            for(int i=0;i<cur_size;i++){
                temp[i]=arr[(head+i)%max_size];
            }
            head=0;
            rear=cur_size-1;
            max_size=2*x;
            T *t1=arr;
            arr=temp;
            free(t1);
        }

        void push_back(T data){
            if(size()==max_size) extend(max_size);
            if(head==-1){
                head=0;
                rear=0;
            }
            else{
                rear=(rear+1)%max_size;
            }
            arr[rear]=data;
        }

        void pop_back(){
            if(head==-1){
                cout<<"Empty Deque"<<endl;
                exit(0);
            }
            if(head==rear){
                head=-1;
                rear=-1;
            }
            rear=(rear-1+max_size)%max_size;
        }

        void push_front(T data){
            if(size()==max_size) extend(max_size);
            if(head==-1){
                head=0;
                rear=0;
            }
            else{
                head=(head-1+max_size)%max_size;
            }
            arr[head]=data;
        }

        void pop_front(){
            if(head==-1){
                cout<<"Empty Deque"<<endl;
                exit(0);
            }
            if(head==rear){
                head=-1;
                rear=-1;
            }
            head=(head+1)%max_size;
        }

        T front(){
            if(head==-1){
                cout<<"Empty Deque"<<endl;
                exit(0);
            }
            return arr[head];
        }

        T back(){
            if(head==-1){
                cout<<"Empty Deque"<<endl;
                exit(0);
            }
            return arr[rear];
        }

        bool empty(){
            if(head==-1)
                return true;
            return false;
        }

        int size(){
            if(head==-1) return 0;
            return ((rear-head+max_size)%max_size+1);
        }

        void resize(int x, T data){
            if(x>max_size){
                extend(x);
            }
            if(size()==x) return;
            int cur_size=size();
            if(x<cur_size){
                while(x++!=cur_size) pop_back();
            }
            else{
                while(x--!=cur_size) push_back(data);
            }
        }

        void clear(){
            head=-1;
            rear=-1;
        }

        T operator[](int n){
            if(head==-1){
                cout<<"Empty Deque"<<endl;
                exit(0);
            }
            int index=(head+n)%max_size;
            return arr[index];
        }

        void display(){
            int cur_size=size();
            for(int i=0;i<cur_size;i++){
                int index=(head+i)%max_size;
                cout<<arr[index]<<" ";
            }
            cout<<"\n";
            return;
        }
};

int main(){
    deque<int> *d=NULL;
    int q;
    cin>>q;
    d=new deque<int>();
    while(q--){
        int qtype;
        cin>>qtype;
        switch(qtype){
            case 1:{
                int s;
                cin>>s;
                d->push_front(s);
                d->display();
                break;
            }

            case 2:{
                d->pop_front();
                d->display();
                break;
            }

            case 3:{
                int s;
                cin>>s;
                d->push_back(s);
                d->display();
                break;
            }

            case 4:{
                d->pop_back();
                d->display();
                break;
            }

            case 5:{
                if(d!=NULL)
                    delete d;
                d=new deque<int>();
                break;
            }

            case 6:{
                int n;
                int x;
                cin>>n>>x;
                if(d!=NULL)
                    delete d;
                d=new deque<int>(n,x);
                d->display();
                break;
            }

            case 7:{
                cout<<d->front()<<endl;
                break;
            }

            case 8:{
                cout<<d->back()<<endl;
                break;
            }

            case 9:{
                if(d->empty()){
                    cout<<"True"<<endl;
                }
                else{
                    cout<<"False"<<endl;
                }
                break;
            }

            case 10:{
                cout<<d->size()<<endl;
                break;
            }

            case 11:{
                int x;
                int data;
                cin>>x;
                cin>>data;
                d->resize(x,data);
                d->display();
                break;
            }

            case 12:{
                d->clear();
                break;
            }

            case 13:{
                int n;
                cin>>n;
                cout<<(*d)[n]<<endl;
                break;
            }

            case 14:{
                d->display();
            }
        }
    }
    delete d;
}
