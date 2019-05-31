#include <stdio.h>
#include<stdlib.h>

struct uzel {
	int value;
	struct uzel *next;
} uzel;

struct spis1{		
	struct uzel* head;	
} spis1;


int isEmpty(struct spis1* spisok)
{
	return spisok->head==0;
}

struct uzel* find(struct spis1* spisok,int value)
{
	struct uzel *tmp=spisok->head;
	while(tmp->value!=value){
		if(tmp->next!=0)
			tmp=tmp->next;
		else
			return 0;
	}
	return tmp;
}

void init(struct spis1* spisok,int value)
{
	struct uzel* tmp;
	tmp = (struct uzel*)malloc(sizeof(struct uzel));
	tmp->value=value;
	tmp->next=0;
	spisok->head = tmp;
}

int push_back(struct spis1* spisok, int x)
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct uzel* tmp = (struct uzel*)malloc(sizeof(struct uzel));
		tmp->value=x;
		tmp->next=0;
		struct uzel* temp = spisok->head;
		while(temp->next!=0)
			temp=temp->next;
		temp->next=tmp;
	}
	return 0;
}

int push_front(struct spis1* spisok,int x) 
{
	if(isEmpty(spisok)==1)
		init (spisok,x);
	else
	{
		struct uzel *tmp = (struct uzel*)malloc(sizeof(struct uzel));
		tmp->value=x;
		tmp->next=spisok->head;
		spisok->head=tmp;
	}
	return 0;
}

int clear(struct spis1* spisok)
{
	if(isEmpty(spisok)!=0)
	{
		struct uzel *tmp=spisok->head;
		struct uzel *temp=0;
		while(tmp!=0)
		{
			temp=tmp->next;
			free(tmp);
			tmp=temp;
		}
		spisok->head=0;
	}
}

void _remove(struct spis1* spisok, struct uzel *tmp){
	if(tmp!=0){
		if (tmp==spisok->head)
		{
			spisok->head=tmp->next;
		}
		else
		{
			struct uzel *temp = (struct uzel*)malloc(sizeof(struct uzel));
			temp=spisok->head;
			while(temp->next!=tmp)
				temp=temp->next;
			temp->next = tmp->next;
		}
		free(tmp);
	}
}

int removeFirst(struct spis1* spisok, int x)
{
	struct uzel* element = find(spisok,x);
	if (element!=0){
		_remove(spisok,element);
		return 0;
	}
	return -1;
}

int insertAfter	(struct spis1* spisok,int num, int value)
{
	struct uzel *temp = malloc(sizeof(uzel));
	temp->value=value;

	struct uzel* tmp = spisok->head;
	struct uzel* prev_tmp = spisok->head;
	
	for (int i = 1;i<num+1;i++)
	{
		prev_tmp=tmp;
		tmp=tmp->next;
		if(tmp==0) 
			return -1;
	}
	prev_tmp->next=temp;
	temp->next=tmp;
	return 0;   
}

void print(struct spis1* spisok)
{
	struct uzel* tmp=spisok->head;
	while(tmp->next!=0)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}

int main()
{
	int n,a;
	struct spis1* spisok=(struct spis1*)malloc(sizeof(struct spis1));	
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
		if(find(spisok,k[i])!=0)
			printf("1");
		else
			printf("0");
	}
	printf("\n");

	int m;
	scanf("%d",&m);
	push_back(spisok,m);
	print(spisok);

	int t;
	scanf("%d",&t);
	push_front(spisok,t);
	print(spisok);

	int j,x;
	scanf("%d%d",&j,&x);
	insertAfter(spisok,j,x);
	print(spisok);

	int z;
	scanf("%d",&z);
	removeFirst(spisok,z);
	print(spisok);

	clear(spisok);
	return 0;
}
