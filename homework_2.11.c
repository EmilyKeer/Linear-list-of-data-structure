//设顺序表va中的数据元素递增有序。试写一算法，将x插入到顺序表的适当位置上，
//以保持该表的有序性。
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct Node  //结构体要先定义
{
	int data;
	struct Node *pNext;
}NODE, *PNODE;

void post_error(FILE *fp2);
PNODE create_list(FILE *fp,FILE *fp2, int n);
void insert_list(PNODE pHead,FILE *fp2, int num);
void print_list(FILE *fp2, PNODE pHead);
//int i;///////////////////////////////////for test

int main()
{
	FILE *fp;
	FILE *fp2;     //设两个
	char ch;
	int n, insert_num;
	PNODE pHead = NULL;     //PNODE定义要放在最前面
if ((fp=fopen("input.txt","r"))==NULL)
{
	exit(0);
}
if ((fp2=fopen("output.txt","w"))==NULL)
{
	exit(0);
}
ch=fgetc(fp); //流指针指着1L位置

//fscanf(fp, "%d", &n);//注意到应该用ch规避换行问题
//fseek(fp, 2L, 1); //其实不需要这句话 因为上句已到行尾【windows下'\n'占2L】
while(ch!=EOF) //判断：这数字究竟是几，然后，遇到换行符就继续下一步
{
	if (ch>='0' && ch <='9')
	{
		ungetc(ch, fp);
		fscanf(fp, "%d", &n);
	}
	else if (ch == '\n')
	{
		//fseek(fp, 1L, 1);
		break;
	}
	ch=fgetc(fp);
}
pHead = create_list(fp,fp2,n);
//i = ftell(fp);//流指针位置判断（调试）
//printf("%ld",i);
ch = fgetc(fp); //原来流指针在'\n'位置【第二个L】，这么一变就到下一行
if ((ch>='0' && ch <='9') ||(ch == '-'))
	{
		ungetc(ch, fp);  //位置回退
		fscanf(fp, "%d", &insert_num); //不是数字（比如出现字母）不可以
	}
	else 
	{
		post_error(fp2);  //出问题的提法三部曲
		fcloseall();
		exit(0);
	}

insert_list(pHead,fp2, insert_num);
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
		if((ch>='0' && ch<='9') || (ch == '-'))
		{
			ungetc(ch, fp);
			fscanf(fp, "%d", &val);
			if (val<-999 || val >999)
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
if (count!=n)
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

void insert_list(PNODE pHead,FILE *fp2, int num)
{
	PNODE p=pHead;
	PNODE q;
	PNODE pNew;
	while(p!=NULL)//while循环不可以缺少
	{
	if(p->pNext->data < num) //注意：不要写成p->data < num 考虑实例 1 2 4 插入3
	{
		p=p->pNext;
		//printf("\n!!!!!!!!!%d\n", p->data);
	}
	else
	{
		pNew = (PNODE)malloc(sizeof(NODE));
		if (pNew == NULL)
		{
			post_error(fp2);
			fcloseall();
			exit(0);
		}
		pNew->data = num;
		q = p->pNext;
		p->pNext = pNew;
		pNew->pNext = q;
		break; //必须有
	}
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