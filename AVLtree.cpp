#include<iostream>

using namespace std;

#define dtype int

template<typename T>
class AVLNode{
    public:
        T data;
        AVLNode *right;
        AVLNode *left;
        int height;
        int count;
        AVLNode(T d){
            data=d;
            right=NULL;
            left=NULL;
            height=0;
            count=1;
        }
};

template<typename T>
class AVLTree{
    public:
        AVLNode<T> *root;

        AVLTree(){
            root=NULL;
        }
        int getHeight(AVLNode<T>* root){
            if(root==NULL) return -1;
            return root->height;
        }

        int getBalance(AVLNode<T>* root){
            if(root==NULL) return 0;
            return (getHeight(root->left)-getHeight(root->right));
        }

        AVLNode<T> *rightRotate(AVLNode<T> *root){
            auto temp=root;
            auto temp2=root->left->right;
            root=root->left;
            temp->left=temp2;
            root->right=temp;
            root->right->height=max(getHeight(root->right->left),getHeight(root->right->right))+1;
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            return root;
        }

        AVLNode<T> *leftRotate(AVLNode<T> *root){
            auto temp=root;
            auto temp2=root->right->left;
            root=root->right;
            temp->right=temp2;
            root->left=temp;
            root->left->height=max(getHeight(root->left->left),getHeight(root->left->right))+1;
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            return root;
        }

        AVLNode<T> *balanceRoot(AVLNode<T>* root, int balance){
            
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

        AVLNode<T> *insertHelp(AVLNode<T> *root, T x){
            if(root==NULL)
                return new AVLNode<T>(x);
            if(root->data==x){
                root->count++;
            }
            if(root->data>x)
                root->left=insertHelp(root->left,x);
            if(root->data<x)
                root->right=insertHelp(root->right,x);
            
            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            int balance=getBalance(root);
            root=balanceRoot(root,balance);
            return root;
        }

        void insert(T x){
            root=insertHelp(root,x);
        }

        T findMax(AVLNode<T> *root){
            if(root->right!=NULL)
                return findMax(root->right);
            return root->data;
        }

        T findMin(AVLNode<T> *root){
            if(root->left!=NULL)
                return findMin(root->left);
            return root->data;
        }

        AVLNode<T> *deleteDataHelp(AVLNode<T> *root,T x){
            if(root==NULL) return root;
            if(root->data==x){
                if(root->count==1){
                    if(root->left==NULL && root->right==NULL){
                        //cout<<"ahbdkas"<<endl;
                        //cout<<root->data<<endl;
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
                        T data=findMax(root->left);
                        //cout<<data<<endl;
                        root->data=data;
                        root->left=deleteDataHelp(root->left,data);
                    }
                }
                else{
                    root->count--;
                }
            }
            if(root->data>x){
                root->left=deleteDataHelp(root->left,x);
            }
            if(root->data<x){
                root->right=deleteDataHelp(root->right,x);
            }

            root->height=max(getHeight(root->left),getHeight(root->right))+1;
            int balance=getBalance(root);
            root=balanceRoot(root,balance);
            return root;
        }

        void deleteData(T x){
            root=deleteDataHelp(root,x);
        }

        bool search_help(AVLNode<T> *root, T x){
            if(root==NULL) return false;
            if(root->data==x) return true;
            if(root->data>x) return search_help(root->left,x);
            if(root->data<x) return search_help(root->right,x);
        }

        bool search(T x){
            return search_help(root,x);
        }

        int countOccurrencesHelp(AVLNode<T> *root, T x){
            if(root==NULL) return 0;
            if(root->data==x) return root->count;
            if(root->data>x) return countOccurrencesHelp(root->left,x);
            if(root->data<x) return countOccurrencesHelp(root->right,x);
        }

        int countOccurrences(T x){
            return countOccurrencesHelp(root,x);
        }

        AVLNode<T>* lower_bound_helper(AVLNode<T> *root, T x,AVLNode<T>* min){
            if(root==NULL) return root;
            //cout<<"y "<<root->data<<endl;
            if(root->data==x) return root;
            if(root->data>x){
                if(min->data>root->data)
                    min=root;
                AVLNode<T>* temp=lower_bound_helper(root->left,x,min);
                if (temp!=NULL && temp->data<min->data){
                    return temp;
                }
                return min;
            }
            else{
                return lower_bound_helper(root->right,x,min);
            }
        }

        AVLNode<T>* lower_bound(AVLNode<T> *root, T x){
            AVLNode<T>* min;
            //cout<<"x "<<root->data<<endl;
            if(root==NULL) return root;
            if(root->data==x) return root;
            if(root->data>x){
                min=root;
                AVLNode<T>* temp=lower_bound_helper(root->left,x,min);
                if(temp!=NULL && temp->data<min->data){
                    return temp;
                }
                else{
                    return min;
                }
            }
            else{
                return lower_bound(root->right,x);
            }
        }

        AVLNode<T>* lowerBound(T x){
            return lower_bound(root,x);
        }

        AVLNode<T>* upper_bound_helper(AVLNode<T> *root, T x,AVLNode<T>* min){
            if(root==NULL) return root;
            //cout<<"y "<<root->data<<endl;
            if(root->data>x){
                if(min->data>root->data)
                    min=root;
                AVLNode<T>* temp=upper_bound_helper(root->left,x,min);
                if (temp!=NULL && temp->data<min->data){
                    return temp;
                }
                return min;
            }
            else{
                return upper_bound_helper(root->right,x,min);
            }
        }

        AVLNode<T>* upper_bound(AVLNode<T>* root,T x){
            AVLNode<T>* min;
            if(root==NULL) return root;
            if(root->data>x){
                min=root;
                AVLNode<T>* temp=upper_bound_helper(root->left,x,min);
                if(temp!=NULL && temp->data<min->data){
                    return temp;
                }
                else{
                    return min;
                }
            }
            else{
                return upper_bound(root->right,x);
            }
        }

        AVLNode<T>* upperBound(T x){
            return upper_bound(root,x);
        }

        AVLNode<T>* get_max_smaller_helper(AVLNode<T> *root, T x,AVLNode<T>* max){
            if(root==NULL) return root;
            //cout<<"y "<<root->data<<endl;
            if(root->data<x){
                if(max->data<root->data)
                    max=root;
                AVLNode<T>* temp=upper_bound_helper(root->right,x,max);
                if (temp!=NULL && temp->data>max->data){
                    return temp;
                }
                return max;
            }
            else{
                return upper_bound_helper(root->left,x,max);
            }
        }

        AVLNode<T>* get_max_smaller(AVLNode<T>* root,T x){
            if(root==NULL) return root;
            AVLNode<T>* max;
            if(root->data<x){
                max=root;
                AVLNode<T>* temp=get_max_smaller_helper(root->right,x,max);
                if(temp!=NULL && temp->data>max->data){
                    return temp;
                }
                else{
                    return max;
                }
            }
            else{
                return get_max_smaller(root->left,x);
            }
        }

        T closest_element(AVLNode<T>* root,T x){
            if(root==NULL) return NULL;
            auto big=lower_bound(root,x);
            if(big==NULL){
                return findMax(root);
            }
            if(big->data==x){
                return big->data;
            }
            auto small=get_max_smaller(root,x);
            if(small==NULL) return big->data;
            //cout<<small->data<<endl;
            if((big->data-x)>(x-small->data)){
                return small->data;
            }
            return big->data;
        }

        T closest(T x){
            return closest_element(root,x);
        }

        /*string closest_element(AVLNode<string>* root,string x){
            if(root==NULL) return NULL;
            auto big=lower_bound(root,x);
            if(big==NULL){
                return findMax(root);
            }
            if(big->data==x){
                return big->data;
            }
            auto small=get_max_smaller(root,x);
            if(small==NULL) return big->data;
            //cout<<small->data<<endl;
            return small->data;
        }*/

        void kth_largest_helper(AVLNode<T>* root,int *k,T* result){
            if(root==NULL) return;
            kth_largest_helper(root->right,k,result);
            *k=*k-root->count;
            if((*k)<=0 && (*k + root->count>0)){
                *result=root->data;
                //cout<<root->data<<endl;
                return;
            }
            kth_largest_helper(root->left,k,result);
        }

        T kth_largest(AVLNode<T>* root,int k){
            if(root==NULL) return NULL;//root;
            T res; 
            kth_largest_helper(root,&k,&res);
            return res;
        }

        T kthLargest(int k){
            return kth_largest(root,k);
        }

        int count_in_range(AVLNode<T>* root,T a,T b){
            if(root==NULL) return 0;
            if(root->data>=a && root->data<=b){
                return(count_in_range(root->left,a,b)+count_in_range(root->right,a,b)+root->count);
            }
            if(root->data<a){
                return (count_in_range(root->right,a,b));
            }
            if(root->data>b){
                return (count_in_range(root->left,a,b));
            }
        }

        int rangeCount(T a, T b){
            return count_in_range(root,a,b);
        }

};

template<typename T>
void inorder(AVLNode<T> *root){
    if(root==NULL) return;
    inorder(root->left);
    for(int i=0;i<root->count;i++)
        cout<<root->data<<" ";//<<root->height<<endl;
    inorder(root->right);
}

template<typename T>
void preorder(AVLNode<T> *root){
    if(root==NULL) return;
    for(int i=0;i<root->count;i++)
        cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

template<typename T>
void postorder(AVLNode<T> *root){
    if(root==NULL) return;
        postorder(root->left);
        postorder(root->right);
    for(int i=0;i<root->count;i++)
        cout<<root->data<<" ";
}


int main(){
    AVLTree<dtype> tree;
    int menu;
    do{
        cin>>menu;
        switch(menu){
            case 1:{
                dtype data;
                cin>>data;
                tree.insert(data);
                inorder(tree.root);
                cout<<endl;
                break;
            }
            case 2:{
                dtype data;
                cin>>data;
                tree.deleteData(data);
                inorder(tree.root);
                cout<<endl;
                break;
            }
            case 3:{
                dtype data;
                cin>>data;
                cout<<tree.search(data)<<endl;
                break;
            }
            case 4:{
                dtype data;
                cin>>data;
                cout<<tree.countOccurrences(data)<<endl;
                break;
            }
            case 5:{
                dtype data;
                cin>>data;
                auto temp=tree.lowerBound(data);
                if(temp!=NULL){
                    cout<<temp->data<<endl;
                }
                else{
                    cout<<"No lower bound"<<endl;
                }
                break;
            }
            case 6:{
                dtype data;
                cin>>data;
                auto temp=tree.upperBound(data);
                if(temp!=NULL){
                    cout<<temp->data<<endl;
                }
                else{
                    cout<<"No upper bound"<<endl;
                }
                break;
            }
            case 7:{
                dtype data;
                cin>>data;
                cout<<tree.closest(data)<<endl;
                break;
            }
            case 8:{
                int k;
                cin>>k;
                cout<<tree.kthLargest(k)<<endl;
                break;
            }
            case 9:{
                dtype a,b;
                cin>>a>>b;
                cout<<tree.rangeCount(a,b)<<endl;
                break;
            }
            defualt: break;
        }
    }while(menu!=10);
    return 0;
}