#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 99999//��ʾ����

typedef struct{//���̽ṹ��
    char PCBName;//��������
    int arriveTime;//���̵���ʱ��
    int runTime;//��������ʱ��
    char status;//����״̬
}PCB;

typedef struct QueueNode//����һ�����   
{
    PCB data;
	struct QueueNode *next;
}QueueNode;

typedef struct{//��ʽ����
    QueueNode *front;//��ͷָ��
    QueueNode *rear;//��βָ��
    int Q_size;//������Ԫ�صĸ���
}LinkQueue;

void init(PCB a[],int n){//��ʼ������
    char name='A';
    for(int i=0;i<n;i++){
        a[i].PCBName=name;//������
        a[i].arriveTime=rand()%8;//���̵���ʱ���ʼ��Ϊ0-7
        a[i].runTime=(rand()%4)+2;//��������ʱ���ʼ��Ϊ2-5
        a[i].status='R';//����״̬��ʼ��Ϊ����״̬"Reader"
        name++;
    }
}

void sort(PCB c[],int n){//���ս��̵���ʱ���������(ð������)
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

void show(PCB b[],int n){//���������Ϣ
    printf("������Ϣ��\n");
    printf("��������\t���̵���ʱ��\t��������ʱ��\t����״̬\n");
    for(int i=0;i<n;i++){
        printf("  %c\t\t    %d\t\t   %d\t\t  %c",b[i].PCBName,b[i].arriveTime,b[i].runTime,b[i].status);
        printf("\n");
    }
    printf("************************��ʼִ��*****************************\n");
}

void InitQueue(LinkQueue *Q){//����һ���ն���
    Q->front=Q->rear=NULL;
    Q->Q_size=0;
}

void EnQueue(LinkQueue*Q,PCB data){//���
    QueueNode *newNode1=(QueueNode*)malloc(sizeof(QueueNode));//Ϊ���Ԫ�ط�����ռ�
    newNode1->data=data;
    newNode1->next=NULL;
    if(Q->Q_size==0){//����Ϊ��
        Q->front=newNode1;
        Q->rear=newNode1;
        Q->Q_size++;//����Ԫ��+1
    }
    else{//���в�Ϊ��
        Q->rear->next=newNode1;
        Q->rear=newNode1;
        Q->Q_size++;//����Ԫ��+1
    }
}

void DeQueue(LinkQueue*Q){//����
    if(Q->Q_size==0){//����Ϊ��
        exit(1);
    }
    else if(Q->Q_size==1){//����ֻ��һ��Ԫ��
        Q->front=NULL;
        Q->rear=NULL;
        Q->Q_size--;//����Ԫ�ؼ�1
    }
    else{
        QueueNode *q=(QueueNode*)malloc(sizeof(QueueNode));//�����ڴ�
        q=Q->front;//qָ���ͷԪ��
        q->data=Q->front->data;//�����ͷԪ�ص�ֵ
        Q->front=q->next;//�޸�ͷָ��
        Q->Q_size--;//����Ԫ��-1
        free(q);//�ͷ��ڴ�
    }
}

void DestroyQueue(LinkQueue *Q){//���ٶ���
    if(Q->front!=NULL){
        Q->rear=Q->front;
        free(Q->front);
        Q->front=Q->rear;
    }
}

void remove_pcb(PCB e[],int n){//�Ƴ�����������ʱ��Ϊ0�Ľ���
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

void show_Q(LinkQueue *Q){//������������
    QueueNode *newNode2=(QueueNode*)malloc(sizeof(QueueNode));
    if(Q->front!=NULL){
        newNode2=Q->front;
        do{
            printf("��������:%c\t���̵���ʱ��:%d\t����ʣ������ʱ��:%d\t����״̬:%c\n",newNode2->data.PCBName,\
            newNode2->data.arriveTime,newNode2->data.runTime,newNode2->data.status);
            newNode2=newNode2->next;
        }while(newNode2!=NULL);
    }
    else{
        printf("�����������޽��̣�\n");
    }
}

void main(){
    srand((unsigned int)time(0));
    int n=0;//��ʾѭ������
    int PCBNum=(rand()%4)+3;//��������ʼ��Ϊ3-6��
    int m=PCBNum;//�����жϺ�ʱ�˳�ʱ��ѭ��
    PCB *pcb=(PCB*)malloc(PCBNum*sizeof(PCB));
    pcb[PCBNum];//�������̽ṹ������
    PCB pcb1;//���ڱ������Ԫ��
    pcb1.arriveTime=MAX;//��pcb1�ĵ���ʱ���ʼ��Ϊ����󣬷�ֹpcb1�״�����ʱ�����
    init(pcb,PCBNum);//��ʼ����������
    sort(pcb,PCBNum);//���ս��̵���ʱ������
    show(pcb,PCBNum);//���������Ϣ
    LinkQueue *Q=(LinkQueue*)malloc(sizeof(LinkQueue));
    InitQueue(Q);//��ʼ������
    for(int time=0;;time++){//��ʾʱ������
        n=m;//����ѭ������
        printf("\nʱ��%d:\n",time);
        for(int i=0;i<n;i++){
            if(time==pcb[i].arriveTime){//��ǰʱ���н��̵���
                EnQueue(Q,pcb[i]);//���
                printf("����%c����\n",pcb[i].PCBName);//���ִ�еĽ�����
            }  
        }
        if(pcb1.arriveTime!=MAX){
            EnQueue(Q,pcb1);//���½�ͷԪ�����
        }
        printf("���������еĽ���״̬��\n");
        show_Q(Q);//����������н�����Ϣ
        if(Q->Q_size!=0){//���������в�Ϊ��
            for(int i=0;i<PCBNum;i++){//����pcb�����еĽ�����Ϣ
                if(pcb[i].PCBName==Q->front->data.PCBName){
                    pcb[i].runTime--;//����ʱ��-1
                    if(pcb[i].runTime==0){
                        pcb[i].status='C';//����״̬����Ϊ��C"
                        m--;//��������1
                    }
                    break;
                }
            }
            printf("����%c����ִ��\n",Q->front->data.PCBName);
            Q->front->data.runTime--;//����ִ�еĽ�������ʱ���1
            if(Q->front->data.runTime==0){//����ִ�����
                Q->front->data.status='C';//����״̬����Ϊ��C��
                printf("����%c��ִ����ϣ��˳���������\n",Q->front->data.PCBName);
                DeQueue(Q);//����
                pcb1.arriveTime=MAX;//����pcb1�е�ֵ����ֹ�ٴ����
            }
            else{
                pcb1=Q->front->data;//����������ж�ͷԪ��
                DeQueue(Q);//����
            }
            remove_pcb(pcb,n);//�Ƴ����̶���������ʱ��Ϊ0�Ľ���
            if(m<=0){//����ȫ��ִ����
                printf("\n�����Ѿ�ȫ��ִ����ϣ�\n");
                break;
            }
        }
        else{//�޽��̵���
            printf("�޽��̵���޽�������\n\n");
        }
    }
    free(pcb);
    DestroyQueue(Q);
    printf("����������!\n");
    system("pause");
}