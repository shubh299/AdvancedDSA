#include<iostream>

using namespace std;

template<typename T>
class DequeNode{
    public:
        T obj;
        DequeNode *next;
        DequeNode *prev;
        DequeNode(T o){
            this->obj=o;
            this->next=NULL;
            this->prev=NULL;
        }
};

template<typename T>
class deque{
    private:
        DequeNode<T> *head,*tail;
        unsigned long cur_size;
    public:
        deque(){
            this->head=NULL;
            this->tail=NULL;
            this->cur_size=0;
        }
        deque(unsigned long n,T obj){
            try{
                if(n<0)
                    throw n;
                else{
                    if(n==0){
                        this->head=NULL;
                        this->tail=NULL;
                    }
                    if(n>0){
                        this->head=new DequeNode<T>(obj);
                        this->tail=head;
                    }
                    this->cur_size=n;
                    while((--n)>0){
                        DequeNode<T> *temp=new DequeNode<T>(obj);
                        temp->prev=tail;
                        tail->next=temp;
                        tail=tail->next;
                    }
                }
            }
            catch(int n){
                cout<<"Invalid n";
            }
        }

        bool empty(){
            if(head==NULL)
                return true;
            return false;
        }

        void push_back(T obj){
            DequeNode<T> *temp=new DequeNode<T>(obj);
            if(empty()){
                head=temp;
                tail=head;
            }
            else{
                temp->prev=tail;
                tail->next=temp;
                tail=tail->next;
            }
            this->cur_size++;
        }

        void pop_back(){
            if(empty()) return;
            if(cur_size==1){
                auto temp=head;
                head=NULL;
                tail=NULL;
                free(temp);
            }
            else{
                auto temp=tail;
                tail=tail->prev;
                tail->next=NULL;
                free(temp);
            }
            this->cur_size--;
        }

        void push_front(T obj){
            DequeNode<T> *temp=new DequeNode<T>(obj);
            if(empty()){
                head=temp;
                tail=head;
            }
            else{
                head->prev=temp;
                temp->next=head;
                head=temp;
            }
            this->cur_size++;
        }

        void pop_front(){
            if(empty()) return;
            if(cur_size==1){
                auto temp=head;
                head=NULL;
                tail=NULL;
                free(temp);
            }
            else{
                auto temp=head;
                head=head->next;
                head->prev=NULL;
                free(temp);
            }
            this->cur_size--;
        }

        T front(){
            
            return head->obj;
        }

        T back(){
            return tail->obj;
        }

        int size(){
            return cur_size;
        }

        void clear(){
            auto temp=head;
            while(head!=tail){
                head=head->next;
                head->prev=NULL;
                free(temp);
            }
            temp=head;
            head=NULL;
            tail=NULL;
            free(temp);
        }

        T operator[](int n){
            if(n>=cur_size){
                cout<<"Index out of bound";
                return NULL;
            }
            auto temp=head;
            while(n--){
                temp=temp->next;
            }
            return temp->obj;
        }


};

int main(){
    deque<int> d1,d2;
    deque<int> d3(2,4);
    d1.push_front(1);
    d2.push_back(2);
    cout<<d1.back()<<endl;
    cout<<d2.front()<<endl;
    d1.clear();
    if(d1.front()==NULL) cout<<"Empty"<<endl;
    cout<<d3.front()<<" "<<d3.back()<<"\n";
    cout<<d3[2];
    return 0;
}