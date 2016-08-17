//��˳���va�е�����Ԫ�ص���������дһ�㷨����x���뵽˳�����ʵ�λ���ϣ�
//�Ա��ָñ�������ԡ�
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct Node  //�ṹ��Ҫ�ȶ���
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
	FILE *fp2;     //������
	char ch;
	int n, insert_num;
	PNODE pHead = NULL;     //PNODE����Ҫ������ǰ��
if ((fp=fopen("input.txt","r"))==NULL)
{
	exit(0);
}
if ((fp2=fopen("output.txt","w"))==NULL)
{
	exit(0);
}
ch=fgetc(fp); //��ָ��ָ��1Lλ��

//fscanf(fp, "%d", &n);//ע�⵽Ӧ����ch��ܻ�������
//fseek(fp, 2L, 1); //��ʵ����Ҫ��仰 ��Ϊ�Ͼ��ѵ���β��windows��'\n'ռ2L��
while(ch!=EOF) //�жϣ������־����Ǽ���Ȼ���������з��ͼ�����һ��
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
//i = ftell(fp);//��ָ��λ���жϣ����ԣ�
//printf("%ld",i);
ch = fgetc(fp); //ԭ����ָ����'\n'λ�á��ڶ���L������ôһ��͵���һ��
if ((ch>='0' && ch <='9') ||(ch == '-'))
	{
		ungetc(ch, fp);  //λ�û���
		fscanf(fp, "%d", &insert_num); //�������֣����������ĸ��������
	}
	else 
	{
		post_error(fp2);  //��������ᷨ������
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
		ch=fgetc(fp);//��©
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
	while(p!=NULL)//whileѭ��������ȱ��
	{
	if(p->pNext->data < num) //ע�⣺��Ҫд��p->data < num ����ʵ�� 1 2 4 ����3
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
		break; //������
	}
	}
}

void print_list(FILE *fp2, PNODE pHead)
{
	PNODE q = pHead->pNext;
	while(q!=NULL)
	{
		fprintf(fp2, "%d ", q->data);   //ע��' '
		q = q->pNext;  //���� q = pHead->pNext
	}
}