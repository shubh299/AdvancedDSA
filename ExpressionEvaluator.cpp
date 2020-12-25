#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>

using namespace std;

template<typename T>
class StackNode{
    public:
        T data;
        StackNode *next;
        StackNode(T d){
            data=d;
            next=NULL;
        }
};

template<typename T>
class Stack{
    private:
        StackNode<T> *top;
    public:  
        Stack(){
            top=NULL;
        }
        
        void push(T new_data){
            StackNode<T> *temp = new StackNode<T>(new_data);
            temp->next = top;
            top=temp;
        }

        void pop(){
            if(top==NULL)
                return;
            StackNode<T> *temp=top;
            top=top->next;
            free(temp);
        }

        StackNode<T> *getTop(){
            return top;
        }
};

bool isOperator(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='%')
        return true;
    return false;
}

int precedence(char c){
    if(c=='+' || c=='-')
        return 1;
    if(c=='*' || c=='/' || c=='%')
        return 2;
    return 0;
}

double strToDouble(string str){
    double a=stod(str);
    //if(sign==1) a=-a;
    return a;
}

double performOperation(double a, double b, char c){
    double res;
    switch (c)
    {
    case '+':
        res=b+a;
        break;
    
    case '-':
        res=b-a;
        break;
    
    case '*':
        res=b*a;
        break;
    
    case '/':
        res=b/a;
        break;
    
    case '%':
        res=fmod(b,a);
        break;
    
    default:
        break;
    }
    return res;
}

void evaluate(string input,Stack<char> &operators,Stack<double> &operands){
    
    int len=input.size();
    //int sign=0;
    int startIndex=-1,endIndex=-1;
    for(int i=0;i<len;i++){
        if(input[i]=='('){
            operators.push(input[i]);
            continue;
        }

        if(input[i]==')'){
            while(operators.getTop()->data!='('){
                double a=operands.getTop()->data;
                operands.pop();
                double b=operands.getTop()->data;
                operands.pop();
                double res=performOperation(a,b,operators.getTop()->data);
                operands.push(res);
                operators.pop();
            }
            operators.pop();
            continue;
        }

        if(isOperator(input[i])){
            /*if((input[i]=='-' && i==0) || 
                (input[i]=='-' && (isOperator(input[i-1]) || input[i-1]=='('))){
                sign=1;
                continue;
            }*/
            if(operators.getTop()==NULL)
                operators.push(input[i]);
            else{
                while(precedence(operators.getTop()->data)>=precedence(input[i])){
                    double a=operands.getTop()->data;
                    operands.pop();
                    double b=operands.getTop()->data;
                    operands.pop();
                    double res=performOperation(a,b,operators.getTop()->data);
                    operands.push(res);
                    operators.pop();
                    if(operators.getTop()==NULL)
                        break;
                }
                operators.push(input[i]);
            }
        }
        else{
            if(i==0){
                startIndex=0;
            }
            else{
                if(isOperator(input[i-1]) || input[i-1]=='(')
                    startIndex=i;
            }
            if(i==len-1){
                endIndex=len-1;
            }
            else{
                if(isOperator(input[i+1]) || input[i+1]==')'){
                    endIndex=i;
                }
            }
            if(endIndex!=-1){
                //cout<<startIndex<<" "<<endIndex<<endl;
                double val=strToDouble(input.substr(startIndex,endIndex-startIndex+1));
                //cout<<val<<endl;
                operands.push(val);
                //sign=0;
                startIndex=-1;
                endIndex=-1;
            }
        }
    }
    while(operators.getTop()!=NULL){
        double a=operands.getTop()->data;
        operands.pop();
        double b=operands.getTop()->data;
        operands.pop();
        double res=performOperation(a,b,operators.getTop()->data);
        operators.pop();
        operands.push(res);
    }
}

template<typename T>
void printStack(Stack<T> s){
    StackNode<T> *top=s.getTop();
    while(top!=NULL){
        cout<<top->data<<" ";
        top=top->next;
    }
    cout<<"\n";
}

int main(){
    Stack<char> operators;//=new Stack();
    Stack<double> operands;//=new Stack();
    string input;
    cin>>input;
    evaluate(input,operators,operands);
    cout<<fixed;
    cout<<setprecision(5);
    cout<<operands.getTop()->data<<endl;
    return 0;
}