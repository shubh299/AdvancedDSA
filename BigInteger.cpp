#include<iostream>
#include<string>

using namespace std;

class Node{
    public:
        int value;
        Node *next;
        Node *prev;
        Node(int data){
            value=data;
            next=NULL;
            prev=NULL;
        }
};

class BigInt{
    public:
        Node* head;
        Node* tail;
        int sign;

        BigInt(){
            head=NULL;
            tail=head;
            sign=0;
        }
        BigInt(string s){
            int len=s.size();
            sign=0;
            if(s[0]=='-') sign=1;
            Node *temp=new Node(s[len-1]-'0');
            head=temp;
            tail=head;
            if(sign){
                for(int i=len-2;i>0;i--){
                    temp=new Node(s[i]-'0');
                    temp->prev=tail;
                    tail->next=temp;
                    tail=temp;
                }
            }
            else{
                for(int i=len-2;i>=0;i--){
                    temp=new Node(s[i]-'0');
                    temp->prev=tail;
                    tail->next=temp;
                    tail=temp;
                }
            }
        }

        void addAtEnd(int data){
            Node *temp=new Node(data);
            if(head==NULL){
                head=temp;
                tail=head;
            }
            else{
                tail->next=temp;
                temp->prev=tail;
                tail=temp;
            }
        }

        void addAtBeginning(int data){
            Node *temp=new Node(data);
            if(head==NULL){
                head=temp;
                tail=head;
            }
            else{
                head->prev=temp;
                temp->next=head;
                head=temp;
            }
        }

        void truncate0(){
            while(tail!=NULL){
                if(tail->value!=0) break;
                auto to_free=tail;
                tail=tail->prev;
                tail->next=NULL;
                free(to_free);
            }
            if(tail==NULL){
                head=NULL;
                tail=head;
            }
        }
        
        int isBiggerThan(BigInt a){ 
            //return 1 for caller bigger than a, 0 for equal, -1 for a bigger than caller
            auto head1=head;
            auto head2=a.head;
            int check=0;
            while(head1!=NULL || head2!=NULL){
                if(head1==NULL) return -1;
                if(head2==NULL) return 1;
                if(head1->value > head2->value)
                    check=1;
                if(head1->value < head2->value)
                    check=-1;
                head1=head1->next;
                head2=head2->next;
            }
            return check;
        }

        string print(){
            if(head==NULL) return "0";
            string res="";
            if(sign) res="-";
            Node *temp=tail;
            while(temp!=NULL){
                res+=(char)(temp->value+'0');
                temp=temp->prev;
            }
            return res;
        }

};

BigInt add(BigInt a, BigInt b){
    BigInt sum;
    auto head1=a.head,head2=b.head;
    int carry=0;
    while(head1!=NULL && head2!=NULL){
        int local_sum=head1->value+head2->value+carry;
        carry=local_sum/10;
        local_sum=local_sum%10;
        sum.addAtEnd(local_sum);
        head1=head1->next;
        head2=head2->next;
    }
    while(head1!=NULL){
        int local_sum=head1->value+carry;
        carry=local_sum/10;
        local_sum=local_sum%10;
        sum.addAtEnd(local_sum);
        head1=head1->next;
    }
    while(head2!=NULL){
        int local_sum=head2->value+carry;
        carry=local_sum/10;
        local_sum=local_sum%10;
        sum.addAtEnd(local_sum);
        head2=head2->next;
    }
    if(carry){
        sum.addAtEnd(carry);
    }
    return sum;
}

BigInt subtract(BigInt a, BigInt b){
    //while(head)
    if(a.isBiggerThan(b)==0) return BigInt();
    auto head1=a.head;
    auto head2=b.head;
    BigInt diff;
    int borrow=0;
    while(head1!=NULL && head2!=NULL){
        int local_diff=head1->value-head2->value-borrow;
        borrow=0;
        if(local_diff<0){
            borrow=1;
            local_diff=10+local_diff;
        }
        //cout<<"local_diff"<<local_diff<<endl;
        diff.addAtEnd(local_diff);
        head1=head1->next;
        head2=head2->next;
    }
    while(head1!=NULL){
        int local_diff=head1->value-borrow;
        borrow=0;
        if(local_diff<0){
            borrow=1;
            local_diff=10+local_diff;
        }
        diff.addAtEnd(local_diff);
        head1=head1->next;
    }
    diff.truncate0();
    return diff;
}

BigInt multiply(BigInt a, BigInt b){
    BigInt prod;
    //cout<<"inside multiply"<<endl;
    int iters=0;
    auto head1=a.head,head2=b.head;
    while(head2!=NULL){
        auto temp=head1;
        BigInt local;
        int carry=0;
        while(temp!=NULL){
            //cout<<temp->value;
            int local_prod=temp->value*head2->value+carry;
            carry=local_prod/10;
            local_prod=local_prod%10;
            local.addAtEnd(local_prod);
            temp=temp->next;
        }
        //cout<<"\n"<<head2->value<<"\n";
        if(carry)
            local.addAtEnd(carry);
        for(int i=0;i<iters;i++){
            local.addAtBeginning(0);
        }
        //cout<<prod.print()<<endl;
        prod=add(prod,local);
        //cout<<local.print()<<endl;
        //cout<<prod.print()<<endl;
        head2=head2->next;
        iters++;
    }
    return prod;
}

bool isZero(BigInt num){
    auto temp=num.head;
    while(temp!=NULL){
        if(temp->value!=0)
            return false;
        temp=temp->next;
    }
    return true;
}

BigInt exponent(BigInt base, int n){
    if(isZero(base)) return BigInt();
    
    if(n==1) return base;

    BigInt res=BigInt("1");
    if(n==0) return res;
    
    if(base.sign==1 && n%2==1)
        res.sign==1;
    
    while(n){
        if(n&1)
            res=multiply(base,res);
        base=multiply(base,base);
        /*cout<<"checkres"<<res.print()<<endl;
        cout<<"checkbase"<<base.print()<<endl;
        cout<<n<<endl;*/
        n=n>>1;
    }
    return res;
}

BigInt fact(int n){
    BigInt res=BigInt("1");
    for(int i=2;i<=n;i++){
        auto temp=BigInt(to_string(i));
        res=multiply(res,temp);
    }
    return res;
}

BigInt mod(BigInt a, BigInt b){
    //BigInt temp=BigInt("2");
    auto c=b;
    /*while(a.isBiggerThan(b)==1){
        c=b;
        b=multiply(b,b);
        //cout<<temp.print()<<" "<<c.print()<<endl;
        //temp=add(temp,BigInt("1"));
    }*/
    if(a.isBiggerThan(multiply(b,BigInt("2")))==-1){
        return subtract(a,b);
    }
    auto temp=b;
    for(int i=2;i<=20;i++){
        if(a.isBiggerThan(temp)==-1) break;
        c=temp;
        temp=exponent(b,i);
    }
    b=c;
    temp=BigInt("2");
    while(a.isBiggerThan(b)!=-1){
        c=b;
        b=multiply(b,temp);
        temp=add(temp,BigInt("1"));
        //temp=add(temp,temp);
    }
    //cout<<a.print()<<" "<<c.print()<<endl;
    //c=multiply(b,subtract(temp,BigInt("2")));
    return subtract(a,c);
}

BigInt gcd(BigInt a, BigInt b){
    //cout<<a.print()<<" "<<b.print()<<endl;
    if(isZero(a)) return b;
    if(isZero(b)) return a;

    if(a.isBiggerThan(BigInt("1"))==0)
        return a;
    if(b.isBiggerThan(BigInt("1"))==0)
        return b;
    
    //static int i=1;
    //if(i==50) exit(0);
    //cout<<i<<" ";
    //i++;

    if(a.isBiggerThan(b)==0){
        return a;
    }
    if(a.isBiggerThan(b)==1){
        return gcd(b,mod(a,b));
    }
    else{
        //cout<<"akbd"<<endl;
        return gcd(a,mod(b,a));
    }

}

int main(){
    //cout<<fact(5000).print()<<endl;
    int q;
    cin>>q;
    while(q--){
        int qtype;
        cin>>qtype;
        switch (qtype)
        {
            case 1:{
                string a;
                int b;
                cin>>a>>b;
                cout<<exponent(BigInt(a),b).print()<<endl;
                break;
            }
            
            case 2:{
                string a,b;
                cin>>a>>b;
                cout<<gcd(BigInt(a),BigInt(b)).print()<<endl;
                break;
            }

            case 3:{
                int n;
                cin>>n;
                cout<<fact(n).print()<<endl;
                break;
            }

            default:
                break;
        }
        //string s,c;
        //cin>>s;
        //cin>>c;
        //s="43466557686937456435688527675040625802564660517371780402481729089536555417949051890403879840079255169295922593080322634775209689623239873322471161642996440906533187938298969649928516003704476137795166849228875";
        //c="26863810024485359386146727202142923967616609318986952340123175997617981700247881689338369654483356564191827856161443356312976673642210350324634850410377680367334151172899169723197082763985615764450078474174626";
        //s="2738448472728378483738388838";
        //c="537382728";
        //BigInt a=BigInt(s);
        //BigInt b=BigInt("11");
        //BigInt t=BigInt(c);
        //cout<<gcd(t,a).print()<<endl;
    }
}
