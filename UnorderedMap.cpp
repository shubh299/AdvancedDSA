#include<iostream>
#include <type_traits>
#include<sstream>

using namespace std;

#define Ktype string
#define Vtype int

template<typename K,typename V>
class LinkedListNode{
    public:
        K key;
        V value;
        LinkedListNode *next;
        LinkedListNode(K k,V v){
            key=k;
            value=v;
            next=NULL;
        }
};

template<typename K,typename V>
class LinkedList{
    public:
    LinkedListNode<K,V> *head;
    LinkedList(){
        head=NULL;
    }
    
    void insertAtHead(K key,V value){
        if(find(key)) return;
        LinkedListNode<K,V> *newNode=new LinkedListNode<K,V>(key,value);
        newNode->next=head;
        head=newNode;
    }

    void print(){
        auto temp=head;
        while(temp!=NULL){
            cout<<"("<<temp->key<<","<<temp->value<<")"<<" ";
            temp=temp->next;
        }
    }

    void erase(K key){
        if(head==NULL) return;
        auto temp=head;
        if(head->next==NULL){
            if(head->key==key){
                head=NULL;
                free(temp);
            }
            return;
        }
        while(temp->next!=NULL){
            if(temp->next->key==key) break;
            temp=temp->next;
        }
        if(temp->next!=NULL){
            auto temp1=temp->next;
            temp->next=temp->next->next;
            free(temp1);
        }
    }

    bool find(K key){
        //if(head==NULL) return false;
        auto temp=head;
        while(temp!=NULL){
            if(temp->key==key)
                return true;
            temp=temp->next;
        }
        return false;
    }

    V search(K key){
        auto temp=head;
        while(temp!=NULL){
            if(temp->key==key) return temp->value;
            temp=temp->next;
        }
        return NULL;
    }
};

template<typename K,typename V>
class UnorderedMap{
    public:
    int mod;
    LinkedList<K,V> *map;
    UnorderedMap(){
        mod=10007;
        map=(LinkedList<K,V>*)malloc(mod*sizeof(LinkedList<K,V>));
    }

    int calculateHash(K key){
        /*if(is_same<K,int>::value){
            return ((3*key+465)%10007)%mod;
        }*/
        stringstream keyToString;
        keyToString<<key;
        string key1;
        keyToString>>key1;
        int hash=0;
        int alpha=1;
        int mul=13;
        for(int i=0;i<key1.length();i++){
            hash=(hash+(key1[i]*alpha)%mod)%mod;
            alpha=(alpha*mul)%mod;
        }
        return hash;
    }

    void insert(K key,V value){
        int hash=calculateHash(key);
        //cout<<hash<<endl;
        map[hash].insertAtHead(key,value);
    }

    void erase(K key){
        int hash=calculateHash(key);
        map[hash].erase(key);
    }

    bool find(K key){
        int hash=calculateHash(key);
        return map[hash].find(key);
    }

    V operator[](K key){
        int hash=calculateHash(key);
        return map[hash].search(key);
    }

    void printTable(){
        for(int i=0;i<mod;i++){
            if(map[i].head==NULL) continue;
            cout<<i<<" ";map[i].print();cout<<endl;
        }
    }

};

int main(){
    UnorderedMap<Ktype,Vtype> map;
    int menu;
    do{
        cin>>menu;
        switch(menu){
            case 1:{
                Ktype key;
                Vtype value;
                cin>>key>>value;
                map.insert(key,value);
                map.printTable();
                cout<<endl;
                break;
            }
            case 2:{
                Ktype data;
                cin>>data;
                map.erase(data);
                map.printTable();
                cout<<endl;
                break;
            }
            case 3:{
                Ktype data;
                cin>>data;
                cout<<map.find(data)<<endl;
                break;
            }
            case 4:{
                Ktype data;
                cin>>data;
                cout<<map[data]<<endl;
                break;
            }
            default: break;
        }
    }while(menu!=5);
}