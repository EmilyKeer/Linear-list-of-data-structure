#include<stdio.h>
#include<stdlib.h>  //exit(0)
#include<malloc.h>  //malloc
typedef struct Node   //结构体写在前面
{
	int data;
	struct Node *pNext;
}NODE, *PNODE;

void post_error(FILE *fp2);//如果出错，就fp2输出ERROR
PNODE create_list(FILE *fp,FILE *fp2, int n);  //创建链表
void change_pos(PNODE pHead, FILE *fp2);  //逆序
void print_list(FILE *fp2, PNODE pHead); //把链表输入到fp2指向文件

int main()
{
	FILE *fp;
	FILE *fp2;
	char ch;
	int n;
	PNODE pHead = NULL;
if ((fp=fopen("input.txt","r"))==NULL)
{
	exit(0);
}
if ((fp2=fopen("output.txt","w"))==NULL)
{
	exit(0);
}
ch=fgetc(fp);//此时，ftell(fp)==1

//fscanf(fp, "%d", &n);//有问题，注意到应该用ch规避换行问题
//fseek(fp, 2L, 1);
while(ch!=EOF)
{
	if (ch>='0' && ch <='9')
	{
		ungetc(ch, fp);
		fscanf(fp, "%d", &n);
		if(n<1 || n>19)//n不符合要求
		{
		post_error(fp2);
		fcloseall();
		exit(0);
		}
		
	}
	else if (ch == '\n')
	{
		//fseek(fp, 1L, 1);
		break;
	}
	ch=fgetc(fp);  //循环的保证
}
pHead = create_list(fp,fp2,n);
//i = ftell(fp);//流指针位置判断（调试）
//printf("%ld",i);
change_pos(pHead,fp2);
print_list(fp2, pHead);
fcloseall();
while(1);
return 0;
}

PNODE create_list(FILE *fp,FILE *fp2, int n)
{
	int count=0, val;
	char ch=fgetc(fp);
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	PNODE pTail = pHead;
	PNODE pNew;
	if (pHead == NULL)
	{
		post_error(fp2);
		fcloseall();
		exit(0);
	}
	pTail->pNext = NULL;
	while(ch!=EOF)
	{
		//=ftell(fp);
	//printf("%d\n",i);
		if((ch>='0' && ch<='9') || (ch == '-')) //输入-999~999整数
		{
			ungetc(ch, fp);
			fscanf(fp, "%d", &val);
			if (val<-999 || val>999)  //输入-999~999整数
			{
				post_error(fp2);
				fcloseall();
		        exit(0);
			}
			count++;
			pNew = (PNODE)malloc(sizeof(NODE));
			if (pNew == NULL)
			{
				post_error(fp2);
				fcloseall();
		        exit(0);
			}
			pNew->data = val;
			pNew->pNext = NULL;
			pTail->pNext = pNew;
			pTail = pNew;
		}
		else if(ch == '\n')
		{
		break;
		}
		ch=fgetc(fp);//勿漏
	}
if (count!=n)//如果数字数不匹配
{
	        post_error(fp2);
			fcloseall();
			exit(0);
}
return pHead;
}

void post_error(FILE *fp2)
{
	fprintf(fp2, "%s", "ERROR");
}

void change_pos(PNODE pHead, FILE *fp2)
{
	PNODE p, r;//r:temp
	p = pHead->pNext;
	if (p!=NULL)
	{
		r= p->pNext;
		p->pNext = NULL;
		p = r;
		while(p!=NULL)
		{
			r = p->pNext;
			p->pNext = pHead->pNext;
			pHead->pNext = p;
			p =r;
		}
	}
	else //考虑判空
	{
		post_error(fp2);
		fcloseall();
		exit(0);
	}
}

void print_list(FILE *fp2, PNODE pHead)
{
	PNODE q = pHead->pNext;
	while(q!=NULL)
	{
		fprintf(fp2, "%d ", q->data);   //注意' '
		q = q->pNext;  //不是 q = pHead->pNext
	}
}