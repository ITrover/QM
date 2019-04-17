#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define true 1
#define error 0
#define false 0
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10
#define MAXBIT 9
typedef int SElemtype;
typedef int Status;
typedef struct{
	//用于进制转化
     SElemtype *base;
     SElemtype *top;
     int stacksize;
}SqStack;
typedef struct lnode {
	//用于存放二进制
	int notResult;//用于判断
	int* node;//用于存放二进制
	int *Ten;//用于存放二进制的十进制
	int numofTen;
	struct lnode *next;
}Lnode;
typedef struct{
	//为了方便管理
	int*  trueDate;
	Lnode *trueNode;//真值
	Lnode *boundTerm;//约束项
	Lnode *outcome;
	int numOfTrue;//真值的个数
	int numOfboundTerm;
}result;

SqStack* InitStack(SqStack *s){
     //初始化栈
     s=(SqStack*)malloc(sizeof(SqStack));
    s->top=s->base=(SElemtype*)malloc(sizeof(SElemtype)*STACK_INIT_SIZE);
    s->stacksize=STACK_INIT_SIZE;
    if(!s->base)exit(false);
    return s;
}
Status DestroyStack(SqStack *s){
    //摧毁栈
    free(s->base);
    return OK;
}
Status ClearStack(SqStack *s){
     //清空栈
     s->top=s->base;
     return OK;
}
int StackLength(SqStack *s){
     //返回栈的个数
      return s->top-s->base;
}
Status Push(SqStack *s,SElemtype e){
      //入栈
      if(s->stacksize==StackLength(s)){
          s->base=(SElemtype*)realloc(s->base,(s->stacksize+STACKINCREMENT)*sizeof(SElemtype));
          s->top=s->base+s->stacksize;
          s->stacksize=s->stacksize+STACKINCREMENT;
      }
      *(s->top)++=e;
      return OK;
}
Status Pop(SqStack *s,SElemtype *e){
     //出栈
     if(s->base==s->top)return error;
     *e=*--(s->top);
     return OK;
}
Lnode* InitLnode(Lnode* head){
	//初始化链表
	head=(Lnode*)malloc(sizeof(Lnode));
	head->Ten=NULL;
	head->node=NULL;
	head->next=NULL;
	return head;
}
int LnodeLength(Lnode* head) {
	//计算链表的实际长度
	Lnode*p = head; int length = 0;
	while (p->next != NULL) {
		length++;
		p = p->next;
	}
	return length;
}
int square(int a, int n) {
	//a的n次方
	if (n == 0)return 1;
	if (n == 1)return a;
	else
		return a*square(a, n - 1);
}
int transformToBinary(int decimalNum,SqStack *s){
       //将十进制转为二进制
       //返回的是二进制的位数
       int reminder=0,Divisor=decimalNum;int numOfBinary=0;
       while(Divisor!=0){
             reminder=Divisor%2;
             Push(s,reminder);
             numOfBinary++;
             Divisor/=2;
       }
       return numOfBinary;
}
int transformToTen(int *s,int n){
      //将二进制转化为十进制
	int Ten=0;
      for(int i=0;i<n;i++){
		  if (s[i] != 0) {
			  Ten += square(2, n - i - 1);
		 }
		  i++;
      }
      return Ten;
}
int printResult(int a[],int size,int n){
       //n为二进制的长度
       for(int i=n-size;i<n;i++){
       printf("%d",a[i]);
                   if(a[i]==1)
		      printf("%c",i-n+size+64);
				   else if (a[i] == 0) {
                   printf("%c",i-n+size+64);
				   printf("\'");
				   }
}
			      return OK;
}
int findMax(int a[],int n){
     int max=a[0];
     for(int i=0;i<n;i++){
     if(a[i]>max)max=a[i];
     }
     return max;
}
int* inputAndTrans(Lnode* head,int n,int maxBit,int *maxSize){
    //返回输入的真值
       int temp=0;
	  int* trueDate = (int*)malloc(sizeof(int)*n);//n为输入的数量
	 SqStack*tempStack=NULL;//临时栈
	 tempStack=InitStack(tempStack); int i = 0;
		 while (i<n) {
			 scanf("%d", &temp);
			 getchar();
			 trueDate[i] = temp;
	       //这是含有头结点的链表
	   Lnode*Node=(Lnode*)malloc(sizeof(Lnode));
	   Node->node=(int*)malloc(sizeof(int)*maxBit);
	   Node->Ten = (int*)malloc(sizeof(int));
	   *(Node->Ten) = temp;
	   Node->numofTen = 1;
	   Node->next=NULL;
           int size=transformToBinary(temp,tempStack);
           if(*maxSize<size)*maxSize=size;
           int j=0;
           for(;j<maxBit-size;j++){
         Node->node[j]=0;
	//不足的应当以0填充
           }
           for(;j<maxBit;j++){
               Pop(tempStack,&(Node->node[j]));
}
     head->next=Node;
	 head=head->next;
	 i++;
       }
       DestroyStack(tempStack);//记得把地址还回去
       return trueDate;
}
int freeLnode(Lnode *head){
	//释放整个链表包括头结点
	if(head==NULL)return 0;
	Lnode *p=head;
        while(head->next!=NULL){
		head=head->next;
		if(p->Ten!=NULL)free(p->Ten);
		if (p->node!= NULL)free(p->node);
		free(p);
		p=head;
	}
	if(head->Ten!=NULL)free(head->Ten);
	if(head->node!=NULL)free(head->node);
	free(head);
	return OK;
}
Lnode* append(Lnode* head,Lnode* Node){
	//添加节点
	if(Node==NULL)return head;
	if(head==NULL){
		head=(Lnode*)malloc(sizeof(Lnode));
		head->Ten=NULL;
		head->node=NULL;
		head->next=NULL;
	}
	Lnode* p=head;
	while(p->next!=NULL){
        p=p->next;
	}
    p->next=Node;p->next->next=NULL;
	return head;
}
Lnode* freeNode(Lnode* head,Lnode* Node){
	//释放单个节点
	Lnode*p=head;int flag=0;
	if(head->next==NULL)exit(1);
	while(p->next!=Node){
	   p=p->next;
	   if(p->next==NULL){
		   flag=1;
		   break;
	   }
	}
	if(flag==0){
		Lnode*q=p->next;
		p->next=p->next->next;
		free(q->Ten);
		free(q->node);
		free(q);
	}
	return head;
}
Lnode* clearLnode(Lnode* head){
//将链表变为只有头结点的空链表
     if(head==NULL)return NULL;
     Lnode*p=head;
     while(p->next!=NULL){
        Lnode* q=p->next;
        p=p->next;
        free(q->node);
        free(q->Ten);
        free(q);
     }
     free(p->node);
     free(p->Ten);
     free(p);
     head->next=NULL;
     return head;
}
Lnode* mergeLnode(Lnode *s1,Lnode*s2){
    Lnode*p1=s1;
    if(p1==NULL)return NULL;
    if(s2==NULL)return NULL;
	//合并两个链表
	while(p1->next!=NULL){
		p1=p1->next;
	}
	p1->next=s2->next;
	return s1;
}
//目前无用
Lnode* deleteNode(Lnode* s1,Lnode*s2,int maxBit){
	//删除一些重复的
	while(s1->next!=NULL){
		while(s2->next!=NULL){
			int flag=0;
			for(int i=0;i<maxBit;i++){
				if((s1->next)->node[i]!=(s2->next)->node[i]){
					flag=1;
					break;
					}
			}
			if(!flag){
				 Lnode*q=s1->next;
                 s1->next=(s1->next)->next;
				 free(q->node);
				 free(q);
		}
		s2=s2->next;
			}
        s1=s1->next;
	}
	return s1;
}
int Display(Lnode*head){
    //把链表展示出来 展示存的十进制和十进制的个数
    if(head==NULL||head->next==NULL){
    printf("这是个空链表\n");
    return 0;
    }
    Lnode*p=head;
    while(p->next!=NULL){
       printf("%d  ",p->next->numofTen);
      for(int i=0;i<p->next->numofTen;i++)
        printf("%d",p->next->Ten[i]);
       printf("\n");
       for(int i=0;i<MAXBIT;i++)
	       printf("%d",p->next->node[i]);
	       printf("\n");
       p=p->next;
    }
    return 1;
}
Lnode* CopyNode(Lnode* newNode,Lnode* Node,int maxBit){
	//复制一个节点
    if(newNode==NULL){
        newNode=(Lnode*)malloc(sizeof(Lnode));
     }
    if(Node==NULL)return NULL;
    newNode->next=NULL;
    newNode->node=NULL;
    newNode->node=(int*)malloc(sizeof(int)*maxBit);
    for(int i=0;i<maxBit;i++){
    newNode->node[i]=Node->node[i];
    printf("%d",newNode->node[i]);
    }
    newNode->notResult=Node->notResult;
    newNode->numofTen=Node->numofTen;
    newNode->Ten=(int*)malloc(sizeof(int)*Node->numofTen);
    for(int i=0;i<Node->numofTen;i++){
    newNode->Ten[i]=Node->Ten[i];
    }
    return newNode;
}
int combine(Lnode *head,Lnode* outcome,int maxBi){
	//用于合成
        Lnode*newHead=NULL;//生成一个新的链表
	newHead=InitLnode(newHead);//初始化
    if(head->next==NULL)return 0;
    if(head->next->next==NULL){outcome=append(outcome,head->next);head->next==NULL;return 0;  }
    int returnSign=0;
    Lnode*p1=head;
    while(p1->next!=NULL&&p1->next->next!=NULL){
	    //外循环 每一个都与其他的几个比较
         int flag1=1;//用于判断一个二进制与其他二进制都不相同 都不相同则为1
        Lnode* p2=p1->next;
          while(p2->next!=NULL){
                int flag2=0;
               for(int i=0;i<maxBi;i++){
                 if(p1->next->node[i]!=p2->next->node[i]){
                   flag2++;
                 }
                 if(flag2>=2){break;}
               }
               if(flag2==0){
		       //两个二进制相同删除
               deleteNode(head,p2->next,maxBi);
               }
               else if(flag2==1){
		       //仅有一个不相同
                   flag1=0;
                   returnSign=1;
                   Lnode*newNode=(Lnode*)malloc(sizeof(Lnode));
                   newNode=CopyNode(newNode,p1->next,maxBi);//建立新的节点 复制p1->next
                   p2->next->notResult=1;//p2->next 有与之相同的项了
		   int position=newNode->numofTen;
		   newNode->notResult=0;
                   newNode->numofTen*=2;
                   newNode->Ten=realloc(newNode,newNode->numofTen*2);//加长 用于存放最小项
                   for(int i=0;i<position;i++){
                   newNode->Ten[i+position]=p2->next->Ten[i];
                   }
                   if(newNode==NULL)printf("有问题");
		   if(newNode->node==NULL){printf("有问题");getchar();}
                   for(int i=0;i<maxBi;i++){
                    if(newNode->node[i]!=p2->next->node[i])newNode->node[i]=2;
                   }
		           newNode->next=NULL;
                   newHead=append(newHead,newNode);
                   newNode=NULL;
               }
               p2=p2->next;
          }
          if(flag1&&!p1->next->notResult){
               Lnode*newNode=(Lnode*)malloc(sizeof(Lnode));
               newNode=CopyNode(newNode,p1->next,maxBi);
               outcome=append(outcome,newNode);
               Display(outcome);
               newNode=NULL;
          }
          p1=p1->next;
          if(p1->next==NULL)break;
    }

       clearLnode(head);
       if(returnSign==0)return returnSign;
       if(newHead==NULL||newHead->next==NULL){printf("有问题了");return returnSign;}
       head->next=newHead->next;
       return returnSign;
}
Lnode* LnodeElem(Lnode*head, int *location) {
	//返回i位置处的节点
	int i = 0;
	Lnode*p = head->next;
	while (p->next != NULL) {
		if (*location == i) {
			return p;
		}
		p = p->next;
		i++;
	}
	return NULL;
}
int HowManyTwo(int* binary,int maxBit) {
	//计算有多少是2
	int num = 0;
	for (int i= 0; i < maxBit; i++) {
		if (binary[i] == 2)
			num++;
	   }
	return num;
}
Lnode* simplify(Lnode *head,int* Date,int n,int maxBit) {
	//寻找本质源
	Lnode* newHead = NULL;
	newHead=(Lnode*)malloc(sizeof(Lnode));
	newHead=InitLnode(newHead);
	for (int i = 0; i < n; i++) {
		Lnode* p = head; int flag = 0;
		while (p->next != NULL) {
			Lnode* temp = p->next;
			for (int j = 0; j < temp->numofTen; j++) {
				if (temp->Ten[j] == Date[j]) {
					flag++;//在temp中存在数Date[i]
					break;
				}
			}
			if (flag == 2)
				break;
		  //     有多个蕴含项有这个数
			p = p->next;
		}
		if (flag == 1) {
			//小心了
                Lnode*newNode=NULL;
		newNode=(Lnode*)malloc(sizeof(Lnode));
		newNode=CopyNode(newNode,p->next,maxBit);
		newNode->next=NULL;
		newHead=append(newHead, newNode);
		}
	}
	//判断是否全部包含
	//还差几行
	return newHead;
}
void freeResult(result *Result) {
    if(Result==NULL)return ;
    if(Result->trueNode!=NULL)freeLnode(Result->trueNode);
	if(Result->boundTerm!=NULL)freeLnode(Result->boundTerm);
	if(Result->outcome!=NULL)freeLnode (Result->outcome);
	if(Result->trueDate!=NULL)free(Result->trueDate);
	free(Result);
}
void absorb(){
while(getchar()!='\n');
}
int main()
{
	   //输入的为真值的十进制，都再转化为maxBit位二进制，将化简的变量和约束项用2来表示。
       printf("请输入查找次数:");
       int n;
       scanf("%d",&n);absorb();
       int maxSize=0;
	   //生成多个查找项
       int i=0;
       while(i<n){
		   //输入并合成为最简的
		   result *Result=(result*)malloc(sizeof(Result));
		   int maxSize1=0,maxSize2=0;
		   printf("请输入最小项和无关项的数目:\n");
		   scanf("%d%d", &Result->numOfTrue, &Result->numOfboundTerm);absorb();
           printf("请输入最小项\n");
		   Result->trueNode=InitLnode(Result->trueNode);
		   Result->trueDate=inputAndTrans(Result->trueNode,Result->numOfTrue, MAXBIT,&maxSize1);//返回最小项
		   printf("请输入无关项\n");
		   Result->boundTerm=InitLnode(Result->boundTerm);
		   inputAndTrans(Result->boundTerm,Result->numOfboundTerm, MAXBIT,&maxSize2);
		   Display(Result->boundTerm);
		   Result->trueNode = mergeLnode(Result->trueNode, Result->boundTerm);//合成 将约束项全部看成1
		   Result->outcome=InitLnode(Result->outcome);
		   Display(Result->trueNode);
           while(combine(Result->trueNode,Result->outcome,MAXBIT)==1);
           if(Result->outcome==NULL||Result->outcome->next==NULL)printf("有问题");
           Display(Result->outcome);
           Result->outcome=simplify(Result->outcome,Result->trueDate,Result->numOfTrue,MAXBIT);
           maxSize=maxSize1>maxSize2?maxSize1:maxSize2;
           Lnode*p=Result->outcome;
           while(p->next!=NULL){
           printResult(p->next->node,maxSize,MAXBIT);
           p=p->next;
           printf("+");
    }
           printResult(p->node,maxSize,MAXBIT);
           freeResult(Result);
           getchar();
           i++;

}
    return 0;
}
