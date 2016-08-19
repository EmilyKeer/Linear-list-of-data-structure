# Linear-list-of-data-structure
## Data structure | Linear list
Language: C </br>
> The repository includes:
* 2 source files
* 2 input_txt (for testing the source code)
* 1 demmand for the code (in Chinese; complete requirement for the tasks)

There are 2 tasks concerning **linear list** :</br>
1. Write an `algorithm`: Insert the element X into the proper position in the **order list**
2. Write an `algorithm`: Reverse the **singly linked list** using the storage space of the origin list


### Preview:
* Insert the element X into the proper position in the order list
```c
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct Node 
{
	int data;
	struct Node *pNext;
}NODE, *PNODE;

void post_error(FILE *fp2);
PNODE create_list(FILE *fp,FILE *fp2, int n);
void insert_list(PNODE pHead,FILE *fp2, int num);
void print_list(FILE *fp2, PNODE pHead);
```


* Write an algorithm: Reverse the singly linked list using the storage space of the origin list

```c
#include<stdio.h>
#include<stdlib.h>  
#include<malloc.h>  
typedef struct Node  
{
	int data;
	struct Node *pNext;
}NODE, *PNODE;

void post_error(FILE *fp2);
PNODE create_list(FILE *fp,FILE *fp2, int n);  
void change_pos(PNODE pHead, FILE *fp2);  
void print_list(FILE *fp2, PNODE pHead); 
```

This project is my assignment for the course Data Structure when I was a first-year student at :blue_book: [the Department of Electrical Engineering at South China University of Technology](http://www.scut.edu.cn/ee/). </br>
I really appreciate the guidance and help from my teacher Dr. Qin, along with my classmates.:bowtie:
