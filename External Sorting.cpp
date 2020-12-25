#include<iostream>
#include<cmath>
#include<limits.h>

using namespace std;

#define dtype long

class PriorityQueueNode{
    public:
        dtype data;
        int partition;
        PriorityQueueNode(dtype d,int part){
            data=d;
            partition=part;
        }
        bool operator<(PriorityQueueNode p){
            return data<p.data;
        }
        bool operator>(PriorityQueueNode p){
            return data>p.data;
        }
};

class PriorityQueue{
    public:
        PriorityQueueNode *heap;
        int size;
        PriorityQueue(int n){
            heap=(PriorityQueueNode*)malloc(n*sizeof(PriorityQueueNode));
            size=0;
        }

        void heapify(int i){
            int smallest=i;
            int child1=2*i+1;
            int child2=2*i+2;
            if(child1<size){
                if(heap[child1]<heap[smallest])
                    smallest=child1;
            }
            if(child2<size){
                if(heap[child2]<heap[smallest])
                    smallest=child2;
            }
            if(smallest!=i){
                auto temp=heap[i];
                heap[i]=heap[smallest];
                heap[smallest]=temp;
                heapify(smallest);
            }
        }

        PriorityQueueNode getMin(){
            size--;
            auto temp=heap[0];
            heap[0]=heap[size];
            heap[size]=PriorityQueueNode(LLONG_MAX,0);
            heapify(0);
            return temp;
        }

        void insert(dtype data,int partition){
            heap[size]=PriorityQueueNode(data,partition);
            size++;
            int current=size-1;
            int parent=(current-1)/2;
            while(heap[parent]>heap[current]){
                auto temp=heap[parent];
                heap[parent]=heap[current];
                heap[current]=temp;
                current=parent;
                parent=(current-1)/2;
            }
            return;
        }

        void print(){
            for(int i=0;i<size;i++)
                cout<<heap[i].data<<" ";
            cout<<endl;
        }
};

void merge(dtype suffixes[],int left,int mid,int right){
    int temp1Size=mid-left+1;
    int temp2Size=right-mid;

    dtype temp1[temp1Size],temp2[temp2Size];

    for(int i=0;i<temp1Size;i++){
        temp1[i]=suffixes[i+left];
    }
    for(int i=0;i<temp2Size;i++){
        temp2[i]=suffixes[i+mid+1];
    }

    int t1=0,t2=0,t3=left;
    while(t1<temp1Size && t2<temp2Size){
        if(temp1[t1]<temp2[t2]){
            suffixes[t3]=temp1[t1];
            t1++;
            t3++;
        }
        else{
            suffixes[t3]=temp2[t2];
            t2++;
            t3++;
        }
    }
    while(t1<temp1Size){
        suffixes[t3]=temp1[t1];
        t1++;
        t3++;
    }
    while(t2<temp2Size){
        suffixes[t3]=temp2[t2];
        t2++;
        t3++;
    }
}

void mergeSort(dtype suffixes[],int left,int right){
    if(left<right){
        int mid=(right+left)/2;
        mergeSort(suffixes,left,mid);
        mergeSort(suffixes,mid+1,right);
        merge(suffixes,left,mid,right);
    }

}

void mergePartitions(FILE *outFp,int numPartitions,int numElements){
    FILE *parts[numPartitions];
    string part="part";
    PriorityQueue priorityQueue(numPartitions);
    for(int i=0;i<numPartitions;i++){
        string temp=part+to_string(i);
        //cout<<temp<<endl;
        parts[i]=fopen(temp.c_str(),"r");
        //cout<<i<<" "<<parts[i]<<endl;
    }
    for(int i=0;i<numPartitions;i++){
        dtype data;
        fscanf(parts[i],"%ld,",&data);
        priorityQueue.insert(data,i);
    }
    //cout<<priorityQueue.size<<endl;
    int count=0;
    int c1=0;
    int finished[numPartitions]={0};
    while(count<numPartitions){
        PriorityQueueNode temp=priorityQueue.getMin();
        c1++;
        if(c1==numElements){
            fprintf(outFp,"%ld",temp.data);    
        }
        else{
            fprintf(outFp,"%ld,",temp.data);
        }
        int partition=temp.partition;
        dtype data;
        if(fscanf(parts[partition],"%ld,",&data)!=-1){
            //c1++;
            priorityQueue.insert(data,partition);
        }
        else{
            count++;
            //cout<<count<<" "<<partition<<endl;
            priorityQueue.insert(LLONG_MAX,partition);
        }
    }
    for(int i=0;i<numPartitions;i++){
        fclose(parts[i]);
        remove((part+to_string(i)).c_str());
    }
}

void createPartitions(FILE *input,int numPartitions,int partSize){
    int partNum=0;
    string part="part";
    
    for(int i=0;i<numPartitions && !feof(input);i++){
        string temp=part+to_string(i);
        //cout<<i;
        FILE *fp=fopen(temp.c_str(),"w");
        int arrIndex=0;
        dtype *tempArr=(dtype*)malloc(partSize*sizeof(dtype));
        for(int j=0;j<partSize && !feof(input);j++,arrIndex++){
            fscanf(input,"%ld,",&tempArr[arrIndex]);
            //printf("%d %d %ld ",i,j,tempArr[arrIndex]);
        }
        mergeSort(tempArr,0,arrIndex-1);
        for(int j=0;j<arrIndex;j++){
            fprintf(fp,"%ld,",tempArr[j]);
        }
        fclose(fp);
        free(tempArr);
    }
}

int main(int argc, char *argv[]){
    if(argc!=3){
        return 0;
    }
    int partSize=1000000;
    int numElements=0;
    FILE *fp=fopen(argv[1],"r");
    while(!feof(fp)){
        dtype data;
        fscanf(fp,"%ld,",&data);
        numElements++;
    }
    fclose(fp);
    //cout<<numElements<<endl;
    int numPartitions=ceil((double)numElements/partSize);
    //cout<<numPartitions<<endl;
    fp=fopen(argv[1],"r");
    //cout<<numElements/partSize<<endl;
    createPartitions(fp,numPartitions,partSize);
    fclose(fp);
    FILE *outFp=fopen(argv[2],"w");
    mergePartitions(outFp,numPartitions,numElements);
    fclose(outFp);
    
    return 0;
}