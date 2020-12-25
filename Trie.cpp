#include<iostream>

#define ll long long

using namespace std;

class TrieNode{
    public:
        struct TrieNode* next[2];
        //bool isLeaf;
        TrieNode(){
            next[0]=NULL;
            next[1]=NULL;
        }
};

class Trie{
    public:
        TrieNode *trieRoot;
        Trie(){
            trieRoot=new TrieNode;
        }
        void insert(ll a){
            auto temp=trieRoot;
            ll check1=(ll)1<<39;
            for(int i=39;i>=0;i--){
                ll oneFlag=(check1&a);
                //cout<<oneFlag<<" ";
                if(check1&a){
                    //cout<<1<<" ";
                    if(temp->next[1]==NULL)
                        temp->next[1]=new TrieNode;
                    temp=temp->next[1];
                }
                else{
                    //cout<<0<<" ";
                    if(temp->next[0]==NULL)
                        temp->next[0]=new TrieNode;
                    temp=temp->next[0];
                }
                check1=check1>>1;
            }
            //cout<<endl;
        }

        ll maxXOR(ll value){
            ll ans=0;
            ll check1=(ll)1<<39;
            auto temp=trieRoot;
            for(int i=39;i>=0;i--){
                if(!(check1&value)){
                    if(temp->next[1]!=NULL){
                        ans=ans+((ll)1<<i);
                        //cout<<i<<" "<<ans<<" "<<((ll)1<<i)<<"\n";
                        temp=temp->next[1];
                    }
                    else{
                        temp=temp->next[0];
                    }
                }
                else{
                    if(temp->next[0]!=NULL){
                        ans=ans+((ll)1<<i);
                        //cout<<i<<" "<<ans<<" "<<((ll)1<<i)<<"\n";
                        temp=temp->next[0];
                    }
                    else{
                        temp=temp->next[1];
                    }
                }
                check1=check1>>1;
                //cout<<i<<" "<<ans<<"as";
            }
            //cout<<endl;
            return ans;
        }
};

int main(){
    Trie trie;
    int n,q;
    cin>>n>>q;
    for(int i=0;i<n;i++){
        ll ai;
        cin>>ai;
        trie.insert(ai);
    }
    while(q--){
        ll qi;
        cin>>qi;
        cout<<trie.maxXOR(qi)<<endl;
    }
}