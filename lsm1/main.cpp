#include <stdio.h>
#include<stdlib.h>
typedef struct NODE
{ int data;
  struct NODE *next;
}SLNode;//定义一个结构体类型
//SLNode *p;
int InitList1(SLNode **head);
int CreatL1(SLNode **h,int a[],int n);
void print(SLNode *p);
int main(void)
{
//int x,key;
SLNode **h;
int b[10],i,m;
int n=6;
printf("请输入数据:\n");
for (i=0;i<n;i++)
  scanf("%d",&b[i]);
printf("Output data:\n");
m=CreatL1(h,b,6);
if (m==1)
printf("lll\n");
print(*h);
//printf("请输入要插入的数据和关键字值:/n");
//scanf("%d%d",&x,&key);
//p->data=x;
//data=key;
//L=insertL(SLNode *head,DataType x,DataType key)
}


//int insertL(SLNode *head,DataType x,DataType key)
//{SLNode*p,*q,*s;
//q=head;
//p=head->next;
//while((p!=NULL)&&(p->data!=key))
//{q=p;
//p=p->next;}
//p=p>next;}
//if(p->data==key)
//{if((s=(SLNode*)malloc(sizeof(SLNode)))==NULL)
//return0;
//s->data=x;
//s->next=p;
//q->next=s;
//return1;}
//else return0;}

int InitList1(SLNode **head)
{*head=(SLNode*)malloc(sizeof(SLNode));
if((*head)==NULL)
return 0;
 (*head)->next=NULL;
return 1;
}

int CreatL1(SLNode **h,int a[],int n)
{ SLNode *p,*s;    /*p尾指针，s申请结点*/
  int i,j;
  i=InitList1(h);/*初始化单链表*/
  if(i==0)
  return 0;
  p=*h;/*初始化尾指针*/
  for(j=0;j<=n-1;j++)
  {
	  if ((s=(SLNode*)malloc(sizeof(SLNode)))==NULL)   /*申请新结点*/
   return 0;
	s->data=a[j];
     s->next=NULL;
     p->next=s;/*尾结点指向新结点*/
     p=s;}   /*尾指针后移*/
  return 1;
}

void print(SLNode *p)
{
	while (p!=NULL)
	{
		printf("%2c",p->data);
		p=p->next;
	}
	printf("\n");
}
