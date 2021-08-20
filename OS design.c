#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 99999//表示无穷

typedef struct{//进程结构体
    char PCBName;//进程名字
    int arriveTime;//进程到达时间
    int runTime;//进程运行时间
    char status;//进程状态
}PCB;

typedef struct QueueNode//定义一个结点   
{
    PCB data;
	struct QueueNode *next;
}QueueNode;

typedef struct{//链式队列
    QueueNode *front;//队头指针
    QueueNode *rear;//队尾指针
    int Q_size;//队列中元素的个数
}LinkQueue;

void init(PCB a[],int n){//初始化进程
    char name='A';
    for(int i=0;i<n;i++){
        a[i].PCBName=name;//进程名
        a[i].arriveTime=rand()%8;//进程到达时间初始化为0-7
        a[i].runTime=(rand()%4)+2;//进程运行时间初始化为2-5
        a[i].status='R';//进程状态初始化为就绪状态"Reader"
        name++;
    }
}

void sort(PCB c[],int n){//按照进程到达时间进行排序(冒泡排序)
    PCB temp;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(c[j].arriveTime>c[j+1].arriveTime){
                temp=c[j];
                c[j]=c[j+1];
                c[j+1]=temp;
            }
        }
    }
}

void show(PCB b[],int n){//输出进程信息
    printf("进程信息：\n");
    printf("进程名字\t进程到达时间\t进程运行时间\t进程状态\n");
    for(int i=0;i<n;i++){
        printf("  %c\t\t    %d\t\t   %d\t\t  %c",b[i].PCBName,b[i].arriveTime,b[i].runTime,b[i].status);
        printf("\n");
    }
    printf("************************开始执行*****************************\n");
}

void InitQueue(LinkQueue *Q){//构造一个空队列
    Q->front=Q->rear=NULL;
    Q->Q_size=0;
}

void EnQueue(LinkQueue*Q,PCB data){//入队
    QueueNode *newNode1=(QueueNode*)malloc(sizeof(QueueNode));//为入队元素分配结点空间
    newNode1->data=data;
    newNode1->next=NULL;
    if(Q->Q_size==0){//队列为空
        Q->front=newNode1;
        Q->rear=newNode1;
        Q->Q_size++;//队列元素+1
    }
    else{//队列不为空
        Q->rear->next=newNode1;
        Q->rear=newNode1;
        Q->Q_size++;//队列元素+1
    }
}

void DeQueue(LinkQueue*Q){//出队
    if(Q->Q_size==0){//队列为空
        exit(1);
    }
    else if(Q->Q_size==1){//队列只有一个元素
        Q->front=NULL;
        Q->rear=NULL;
        Q->Q_size--;//队列元素减1
    }
    else{
        QueueNode *q=(QueueNode*)malloc(sizeof(QueueNode));//申请内存
        q=Q->front;//q指向队头元素
        q->data=Q->front->data;//保存队头元素的值
        Q->front=q->next;//修改头指针
        Q->Q_size--;//队列元素-1
        free(q);//释放内存
    }
}

void DestroyQueue(LinkQueue *Q){//销毁队列
    if(Q->front!=NULL){
        Q->rear=Q->front;
        free(Q->front);
        Q->front=Q->rear;
    }
}

void remove_pcb(PCB e[],int n){//移除队列中运行时间为0的进程
    int i=0;
    int j=0;
    for(int k=0;k<n;k++){
        if(e[k].runTime!=0){
            e[i]=e[j];
            i++;
        }
        j++;
    }
}

void show_Q(LinkQueue *Q){//遍历就绪队列
    QueueNode *newNode2=(QueueNode*)malloc(sizeof(QueueNode));
    if(Q->front!=NULL){
        newNode2=Q->front;
        do{
            printf("进程名字:%c\t进程到达时间:%d\t进程剩余运行时间:%d\t进程状态:%c\n",newNode2->data.PCBName,\
            newNode2->data.arriveTime,newNode2->data.runTime,newNode2->data.status);
            newNode2=newNode2->next;
        }while(newNode2!=NULL);
    }
    else{
        printf("就绪队列中无进程！\n");
    }
}

void main(){
    srand((unsigned int)time(0));
    int n=0;//表示循环次数
    int PCBNum=(rand()%4)+3;//进程数初始化为3-6个
    int m=PCBNum;//用于判断何时退出时间循环
    PCB *pcb=(PCB*)malloc(PCBNum*sizeof(PCB));
    pcb[PCBNum];//创建进程结构体数组
    PCB pcb1;//用于保存出队元素
    pcb1.arriveTime=MAX;//将pcb1的到达时间初始化为无穷大，防止pcb1首次运行时就入队
    init(pcb,PCBNum);//初始化进程数据
    sort(pcb,PCBNum);//按照进程到达时间排序
    show(pcb,PCBNum);//输出进程信息
    LinkQueue *Q=(LinkQueue*)malloc(sizeof(LinkQueue));
    InitQueue(Q);//初始化队列
    for(int time=0;;time++){//表示时间增加
        n=m;//更新循环次数
        printf("\n时间%d:\n",time);
        for(int i=0;i<n;i++){
            if(time==pcb[i].arriveTime){//当前时间有进程到达
                EnQueue(Q,pcb[i]);//入队
                printf("进程%c到达\n",pcb[i].PCBName);//输出执行的进程名
            }  
        }
        if(pcb1.arriveTime!=MAX){
            EnQueue(Q,pcb1);//重新将头元素入队
        }
        printf("就绪队列中的进程状态：\n");
        show_Q(Q);//输出就绪队列进程信息
        if(Q->Q_size!=0){//就绪队列中不为空
            for(int i=0;i<PCBNum;i++){//更新pcb数组中的进程信息
                if(pcb[i].PCBName==Q->front->data.PCBName){
                    pcb[i].runTime--;//运行时间-1
                    if(pcb[i].runTime==0){
                        pcb[i].status='C';//进程状态更新为“C"
                        m--;//进程数减1
                    }
                    break;
                }
            }
            printf("进程%c正在执行\n",Q->front->data.PCBName);
            Q->front->data.runTime--;//正在执行的进程运行时间减1
            if(Q->front->data.runTime==0){//进程执行完毕
                Q->front->data.status='C';//进程状态更新为“C”
                printf("进程%c已执行完毕，退出就绪队列\n",Q->front->data.PCBName);
                DeQueue(Q);//出队
                pcb1.arriveTime=MAX;//更新pcb1中的值，防止再次入队
            }
            else{
                pcb1=Q->front->data;//保存就绪队列队头元素
                DeQueue(Q);//出队
            }
            remove_pcb(pcb,n);//移除进程队列中运行时间为0的进程
            if(m<=0){//进程全部执行完
                printf("\n进程已经全部执行完毕！\n");
                break;
            }
        }
        else{//无进程到达
            printf("无进程到达，无进程运行\n\n");
        }
    }
    free(pcb);
    DestroyQueue(Q);
    printf("队列已销毁!\n");
    system("pause");
}