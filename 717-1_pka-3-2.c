#include <stdio.h>
#include<stdlib.h>

struct uzel {
	int value;
	struct uzel *next;
	struct uzel *prev;
} uzel;

struct spis2{		
	struct uzel* head;
	struct uzel* tail;	
} spis2;


int isEmpty(struct spis2* spisok)
{
	return spisok->head==NULL && spisok->tail==NULL;
}

struct uzel* find(struct spis2* spisok,int k)
{
	struct uzel *tmp=spisok->head;
	while(tmp->value!=k){
		if(tmp->next!=NULL){
			tmp=tmp->next;
		}else{
			return NULL;
		}
	}
	return tmp;
}

struct uzel* find_invers(struct spis2* spisok,int k)
{
	struct uzel *tmp=spisok->tail;
	while(tmp->value!=k){
		if(tmp->prev!=NULL){
			tmp=tmp->prev;
		}else{
			return NULL;
		}
	}
	return tmp;
}

void init(struct spis2* spisok,int value)
{
	struct uzel* tmp;
	tmp = (struct uzel*)malloc(sizeof(struct uzel));
	tmp->value=value;
	tmp->next=NULL;
	tmp->prev=NULL;
	spisok->head = tmp;
	spisok->tail = tmp;
}

int push_back(struct spis2* spisok, int x)
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct uzel *tmp = (struct uzel*)malloc(sizeof(struct uzel));
		tmp->value=x;
		tmp->prev=spisok->tail;
		tmp->next=NULL;
		spisok->tail=tmp;
		tmp->prev->next=tmp;
	}
	return 0;
}

int push_front(struct spis2* spisok,int x) 
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct uzel *tmp = (struct uzel*)malloc(sizeof(struct uzel));
		tmp->value=x;
		tmp->prev=NULL;
		tmp->next=spisok->head;
		spisok->head=tmp;
		tmp->next->prev=tmp;
	}
	return 0;
}

int clear(struct spis2* spisok)
{
	if(isEmpty(spisok)!=0)
	{
		struct uzel *tmp=spisok->head;
		struct uzel *temp=NULL;
		while(tmp!=NULL)
		{
			temp=tmp->next;
			free(tmp);
			tmp=temp;
		}
		spisok->head=NULL;
		spisok->tail=NULL;
	}
}

void _remove(struct spis2* spisok, struct uzel *tmp){
	if(tmp!=NULL){
		if (tmp==spisok->head && tmp==spisok->tail) {
			clear(spisok);
			return;
		}
		if (tmp==spisok->head)
		{
			spisok->head=tmp->next;
			tmp->next->prev=NULL;
		}
		else if(tmp==spisok->tail)
		{
			spisok->tail=tmp->prev;
			tmp->prev->next=NULL;
		}
		else if (tmp!=spisok->head && tmp!=spisok->tail)
		{
			tmp->next->prev=tmp->prev;
			tmp->prev->next=tmp->next;
		}
		free(tmp);
	}
}

int removeLast(struct spis2* spisok,int x)
{
	struct uzel* element = find_invers(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int removeFirst(struct spis2* spisok, int x)
{
	struct uzel* element = find(spisok,x);
	if (element!=NULL){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int insertAfter	(struct spis2* spisok,int num, int data)
{
	struct uzel* tmp = spisok->head;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct uzel *temp = malloc(sizeof(uzel));
	temp->value=data;
	temp->next=tmp->next;
	temp->prev=tmp;
	tmp->next->prev=temp;
	tmp->next=temp;  
	return 0;   
}

int insertBefore(struct spis2* spisok,int num, int data)
{
	struct uzel* tmp = spisok->head;
	for (int i = 1;i<num;i++)
	{
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	struct uzel *temp = malloc(sizeof(uzel));
	temp->value=data;
	temp->prev=tmp->prev;
	temp->next=tmp;
	tmp->prev=temp;
	temp->prev->next=temp;      
	return 0; 
}

void print(struct spis2* spisok)
{
	struct uzel* tmp=spisok->head;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

void print_invers(struct spis2* spisok)
{
	struct uzel* tmp=spisok->tail;
	while(tmp->prev!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->prev;
	}
	printf("%d\n", tmp->value);	
}



int main()
{
	int n,a;
	struct spis2* spisok=(struct spis2*)malloc(sizeof(struct spis2));	
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a);
		push_back(spisok,a);
	}
	print(spisok);
	
	int k[3];
	for(int i=0;i<3;i++){
		scanf("%d",&k[i]);
		if(find(spisok,k[i])!=NULL)
			printf("1");
		else
			printf("0");
	}
	printf("\n");

	int m;
	scanf("%d",&m);
	push_back(spisok,m);
	print_invers(spisok);

	int t;
	scanf("%d",&t);
	push_front(spisok,t);
	print(spisok);

	int j,x;
	scanf("%d%d",&j,&x);
	insertAfter(spisok,j,x);
	print_invers(spisok);

	int u,y;
	scanf("%d%d",&u,&y);
	insertBefore(spisok,u,y);
	print(spisok);

	int z;
	scanf("%d",&z);
	removeFirst(spisok,z);
	print_invers(spisok);

	int r;
	scanf("%d",&r);
	removeLast(spisok,r);
	print(spisok);

	clear(spisok);
	return 0;
}
