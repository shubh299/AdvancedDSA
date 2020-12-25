#include<iostream>

using namespace std;

#define Ktype string
#define Vtype string

template<typename K, typename V>
class AVLNode{
    public:
        K key;
        V value;
        AVLNode *right;
        AVLNode *left;
        int height;
        AVLNode(K k,V v){
            key=k;
            value=v;
            right=NULL;
            left=NULL;
            height=0;
        }

};

template<typename K, typename V>
class OrderedMap{
    public:
        AVLNode<K,V> *root;
        int mapSize;
        
        OrderedMap(){
            root=NULL;
            mapSize=0;
        }
        
        int getHeight(AVLNode<K,V>* root){
            if(root==NULL) return -1;
            return root->height;
        }

        int getBalance(AVLNode<K,V>* root){
            if(root==NULL) return 0;
            return (getHeight(root->left)-getHeight(root->right));
        }

        AVLNode<K,V>* rightRotate(AVLNode<K,V>* root){
            auto temp=root;
            auto temp2=root->left->right;
            root=root->left;
            temp->left=temp2;
            root->right=temp;
            root->right->height=max(getHeight(root->right->left),getHeight(root->right->right))+1;
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            return root;
        }

        AVLNode<K,V>* leftRotate(AVLNode<K,V>* root){
            auto temp=root;
            auto temp2=root->right->left;
            root=root->right;
            temp->right=temp2;
            root->left=temp;
            root->left->height=max(getHeight(root->left->left),getHeight(root->left->right))+1;
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            return root;
        }

        AVLNode<K,V>* balanceRoot(AVLNode<K,V>* root, int balance){
            
            if(balance>1){
                if(getBalance(root->left)>0){
                    root=rightRotate(root);
                }
                else{
                    root->left=leftRotate(root->left);
                    root=rightRotate(root);
                }
            }
            if(balance<-1){
                if(getBalance(root->right)<0){
                    root=leftRotate(root);
                }
                else{
                    root->right=rightRotate(root->right);
                    root=leftRotate(root);
                }
            }
            return root;
        }

        AVLNode<K,V>* insertInTree(AVLNode<K,V>* root, K key, V value){
            if(root==NULL){
                //root=AVLNode<K,V>(key,value);
                //return root;
                mapSize++;
                return new AVLNode<K,V>(key,value);
            }
            if(root->key==key){
                root->value=value;
            }
            if(root->key>key)
                root->left=insertInTree(root->left,key,value);
            if(root->key<key)
                root->right=insertInTree(root->right,key,value);
            
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            int balance=getBalance(root);
            root=balanceRoot(root,balance);
            return root;
        }

        void insert(K key, V value){
            root=insertInTree(root,key,value);
        }

        AVLNode<K,V>* findMax(AVLNode<K,V> *root){
            if(root->right!=NULL)
                return findMax(root->right);
            return root;
        }

        AVLNode<K,V> *deleteData(AVLNode<K,V> *root,K x){
            if(root==NULL) return root;
            if(root->key==x){
                mapSize--;
                if(root->left==NULL && root->right==NULL){
                    auto temp=root;
                    root=NULL;
                    free(temp);
                    return root;
                }
                if(root->left==NULL && root->right!=NULL){
                    auto temp=root;
                    root=root->right;
                    free(temp);
                    return root;
                }
                if(root->left!=NULL && root->right==NULL){
                    auto temp=root;
                    root=root->left;
                    free(temp);
                    return root;
                }
                if(root->left!=NULL && root->right!=NULL){
                    auto temp=findMax(root->left);
                    root->key=temp->key;
                    root->value=temp->value;
                    root->left=deleteData(root->left,temp->key);
                }
            }
            
            if(root->key>x){
                root->left=deleteData(root->left,x);
            }
            if(root->key<x){
                root->right=deleteData(root->right,x);
            }

            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            int balance=getBalance(root);
            root=balanceRoot(root,balance);
            return root;
        }

        void erase(K key){
            root=deleteData(root,key);            
        }

        bool searchHelp(AVLNode<K,V> *root, K x){
            if(root==NULL) return false;
            if(root->key==x) return true;
            if(root->key>x) return searchHelp(root->left,x);
            if(root->key<x) return searchHelp(root->right,x);
        }

        bool find(K x){
            if(root==NULL) return false;
            if(root->key==x) return true;
            return searchHelp(root,x);
        }

        AVLNode<K,V>* getNode(AVLNode<K,V>* root,K key){
            if(root==NULL) return root;
            if(root->key==key) return root;
            if(root->key>key) return getNode(root->left,key);
            if(root->key<key) return getNode(root->right,key);
        }

        V& operator[](K key){
            //clog<<key;
            //cout<<"test1"<<endl;
            if(!(find(key))){
                V default_value;
                root=insertInTree(root,key,default_value);
            }
            AVLNode<K,V>* temp=getNode(root,key);
            //cout<<temp->key<<endl;
            //cout<<temp->value<<endl;
            return temp->value;
        }

        int size(){
            return mapSize;
        }

        AVLNode<K,V>* clearHelp(AVLNode<K,V>* root){
            if(root==NULL) return root;
            root->left=clearHelp(root->left);
            root->right=clearHelp(root->right);
            auto temp=root;
            free(temp);
            root=NULL;
            return root;
        }

        void clear(){
            if(root==NULL) return;
            root=clearHelp(root);
            mapSize=0;
            //root=NULL;
        }

        void inorder(AVLNode<K,V>* root){
            if(root==NULL) return;
            inorder(root->left);
            cout<<root->key<<" "<<root->value<<endl;
            inorder(root->right);
        }

        void print(){
            inorder(root);
        }
};

int main(){
    OrderedMap<Ktype,Vtype> map;
    map["1"]="12";
    map.print();
    map.insert("2","31");
    map.insert("2","33");
    map.print();
    cout<<map.find("2")<<endl;
    cout<<map.find("3")<<endl;
    map.erase("1");
    map.print();
}