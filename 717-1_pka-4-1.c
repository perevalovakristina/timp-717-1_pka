#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
        int size;
        struct node* root;
} tree;

typedef struct node{
        struct node *left,*right,*parent;
        int value;
} node;

typedef struct list
{
    struct node* address;
    struct list *next;
} list;

typedef struct two_chained_list
{
    struct list *head,*tail;
} two_chained_list;

void insert(tree* t,int value);
int find(tree* t,int value,node* n);
void init(tree* t);
int remove_(tree* t,int value);
int removeMin(node* n);
int rotateLeft(node* n);
int root_rotateLeft(tree* t);
int rotateRight(node* n);
int root_rotateRight(tree* t);
void printTree(tree* t);
void clear_branch(node* n);
void clear(tree* t);
void print(node* n);

void init_list(two_chained_list* l);
void clear_list(two_chained_list* l);
int isEmpty_list( two_chained_list* l);
int push_back_list( two_chained_list* l, node* val);
void print_list( two_chained_list* l);
int printable( two_chained_list* l);

void print_founded(node* n){
    if(n->parent!=NULL)
        printf("%d ", n->parent->value);
    else
        printf("_ ");
    if(n->left!=NULL)
        printf("%d ", n->left->value);
    else
        printf("_ ");
    if(n->right!=NULL)
        printf("%d\n", n->right->value);
    else
        printf("_\n");
}

int main(){
    tree* root = malloc(sizeof(tree));
    init(root);
    int t;
    for(int i=0;i<4;i++){
        scanf("%d",&t);
        insert(root,t);
    }
    printTree(root);
    for(int i=0;i<3;i++){
        scanf("%d",&t);
        insert(root,t);
    }
    printTree(root);

    int m;
    scanf("%d",&m);
    node* n = malloc(sizeof(node));
    if(find(root,m,n)==0)
        print_founded(n); 
    else
        printf("-\n");

    scanf("%d",&m);
    if(find(root,m,n)==0)
        print_founded(n); 
    else
        printf("-\n");

    scanf("%d",&m);
    remove_(root,m);
    printTree(root);
    while(root_rotateLeft(root)!=1);
    printTree(root);
    while(root_rotateRight(root)!=1);
    printTree(root);
    printf("%d\n", root->size);
    clear(root);
    printTree(root);
    return 0;
}


int rotateRight( node* n) {
    if (n->left == NULL)
        return 1;
    node* tmp = n->left;
    if (n->parent != NULL) {
        if (n->parent->left == n)
            n->parent->left = tmp;
        else
            n->parent->right = tmp;
    }
    tmp->parent = n->parent;
    n->parent = tmp;
    node* t1 = tmp->right;
    tmp->right = n;
    n->left = t1;
    n = tmp;
    return 0;
}

int rotateLeft( node* n) {
        if (n->right == NULL)
                return 1;
        node* tmp = n->right;
        if (n->parent != NULL){
                if (n->parent->right == n) 
                        n->parent->right = tmp;
                else
                        n->parent->left = tmp;
        }
        tmp->parent = n->parent;
        n->parent = tmp;
        node* t1 = tmp->left;
        tmp->left = n;
        n->right = t1;
        n = tmp;
        return 0;
}


int root_rotateLeft(tree* t){
        node* n = t->root;
        if(rotateLeft(n)==0){
                t->root=n->parent;
                return 0;
        }
        else
                return 1;
}

int root_rotateRight(tree* t){
        node* n = t->root;
        if(rotateRight(n)==0){
                t->root=n->parent;
                return 0;
        }
        else
                return 1;
}


void insert(tree* t,int value){
        if(t->root==NULL){
                t->root=malloc(sizeof(node));
                t->root->value=value;
                t->root->left=t->root->right=t->root->parent=NULL;
                t->size=1;
                return;
        }
        node* tmp=t->root;
        while(1){
                if(tmp->value==value){
                        return;
                }
                if(value > tmp->value){
                        if(tmp->right==NULL){
                                tmp->right=malloc(sizeof(node));
                                tmp->right->value=value;
                                tmp->right->right=tmp->right->left=NULL;
                                tmp->right->parent=tmp;
                                t->size++;
                                return;
                        }
                        else
                                tmp=tmp->right;
                }
                else if(value < tmp->value){
                        if(tmp->left==NULL){
                                tmp->left=malloc(sizeof(node));
                                tmp->left->value=value;
                                tmp->left->left=tmp->left->left=NULL;
                                tmp->left->parent=tmp;
                                t->size++;
                                return;
                        }else
                                tmp=tmp->left;
                }
        }
}

int find(tree* t,int value,node* n){
        if(t->root==NULL){
                return 1;
        }
        node* tmp=t->root;
        while(1){
                if(tmp==NULL)
                        return 1;
                if(tmp->value==value){
                        n->value=tmp->value;
                        n->left=tmp->left;
                        n->right=tmp->right;
                        n->parent=tmp->parent;
                        return 0;
                }
                if(value > tmp->value)
                        tmp=tmp->right;
                else if(value < tmp->value)
                        tmp=tmp->left;
        }
}

void init(tree* t){
        t->root=NULL;
        t->size=0;
}

int remove_(tree* t,int value){
        if(t->root==NULL)
                return 1;
        node* tmp=t->root;
        while(1){
                if(tmp==NULL)
                        return 1;

                if(value > tmp->value)
                        tmp=tmp->right;
                else if(value < tmp->value)
                        tmp=tmp->left;
                else{
                        if(tmp->left==NULL && tmp->right==NULL){
                                if(tmp->parent->left==tmp)
                                        tmp->parent->left=NULL;
                                else if(tmp->parent->right==tmp)
                                        tmp->parent->right=NULL;
                                free(tmp);
                        }
                        else if(tmp->left!=NULL && tmp->right==NULL){
                                if(tmp->parent->left==tmp)
                                        tmp->parent->left=tmp->left;
                                else if(tmp->parent->right==tmp)
                                        tmp->parent->right=tmp->left;
                                free(tmp);
                        }
                        else if(tmp->left==NULL && tmp->right!=NULL){
                                if(tmp->parent->left==tmp)
                                        tmp->parent->left=tmp->right;
                                else if(tmp->parent->right==tmp)
                                        tmp->parent->right=tmp->right;
                                free(tmp);
                        }
                        else
                                tmp->value=removeMin(tmp->right);
                    t->size--;
                    return 0;
                }
        }
}

int removeMin(node* n){
        if(n!=NULL){
                if(n->left!=NULL)
                        return removeMin(n->left);
                else{
                        if(n->right!=NULL){
                                n->parent->right=n->right;
                                n->right=n->parent;
                        }else
                                n->parent->left=NULL;
                        int res=n->value;
                        free(n);
                        n=NULL;
                        return res;
                }
        }       
}

void print(node* n)
{
    if (n==NULL)
    {
        printf("-\n");
        return;
    }
    two_chained_list tmp1, tmp2;
    list *nd;
    init_list(&tmp1);
    init_list(&tmp2);
    push_back_list(&tmp1, n);
    while(printable(&tmp1)|| printable(&tmp2))
    {
        if (isEmpty_list(&tmp2)==0)
        {
            print_list(&tmp1);
            nd=tmp1.head;
            while(nd!=NULL)
            {
                if (nd->address==NULL)
                {
                    push_back_list(&tmp2, NULL);
                    push_back_list(&tmp2, NULL);
                }
                else
                {
                    push_back_list(&tmp2, nd->address->left);
                    push_back_list(&tmp2, nd->address->right);
                }
                nd=nd->next;
            }
            clear_list(&tmp1);
        }
        else
        {
            print_list(&tmp2);
            nd=tmp2.head;
            while(nd!=NULL)
            {
                if (nd->address==NULL)
                {
                    push_back_list(&tmp1, NULL);
                    push_back_list(&tmp1, NULL);
                }
                else
                {
                push_back_list(&tmp1, nd->address->left);
                push_back_list(&tmp1, nd->address->right);
                }
                nd=nd->next;
            }
            clear_list(&tmp2);
        }
    }
}

 void printTree(tree *t)
 {
     print(t->root);
 }

void clear(tree *t)
{
    two_chained_list tmp1, tmp2;
    list *nd;
    init_list(&tmp1);
    init_list(&tmp2);
    push_back_list(&tmp1, t->root);
    while(printable(&tmp1)|| printable(&tmp2))
    {
        if (isEmpty_list(&tmp2)==0)
        {
            nd=tmp1.head;
            while(nd!=NULL)
            {
                if (nd->address==NULL)
                {
                    push_back_list(&tmp2, NULL);
                    push_back_list(&tmp2, NULL);
                }
                else
                {
                    push_back_list(&tmp2, nd->address->left);
                    push_back_list(&tmp2, nd->address->right);
                }
                free(nd->address);
                nd=nd->next;
            }
            clear_list(&tmp1);
        }
        else
        {
            nd=tmp2.head;
            while(nd!=NULL)
            {
                if (nd->address==NULL)
                {
                    push_back_list(&tmp1, NULL);
                    push_back_list(&tmp1, NULL);
                }
                else
                {
                push_back_list(&tmp1, nd->address->left);
                push_back_list(&tmp1, nd->address->right);
                }
                free(nd->address);
                nd=nd->next;
            }
            clear_list(&tmp2);
        }
    }
    init(t);
}


void init_list(two_chained_list* l)
{
    l->head=l->tail=NULL;
}

void clear_list(two_chained_list* l)
{
    list *tmp1,*tmp2;
    tmp1=l->head;
    while (tmp1->next!=NULL)
    {
        tmp2=tmp1;
        tmp1=tmp1->next;
        free(tmp2);
    }
    free(tmp1);
    init_list(l);
}

int isEmpty_list( two_chained_list* l)
{
    if (l->head==NULL) 
        return 0;
    else return 1;
}

int push_back_list( two_chained_list* l, node* val)
{
    list* new_node;
    new_node=malloc(sizeof( list));
    new_node->address = val;
    new_node->next = NULL;
    if (l->head==NULL) 
        l->head=new_node;
    else if (l->head->next==NULL) 
        l->head->next = new_node;
    else 
        l->tail->next = new_node;
    l->tail=new_node;
    return 0;
}

void print_list( two_chained_list* l)
{
    if (isEmpty_list(l)==1)
    {
        list* tmp;
        tmp=l->head;
        while (tmp->next!=NULL)
        {
            if (tmp->address == NULL) 
                printf("_ ");
            else
                printf("%d ", tmp->address->value);
            tmp = tmp->next;
        }
        if (tmp->address == NULL) 
            printf("_\n");
        else
            printf("%d\n", l->tail->address->value);
        }
}

int printable( two_chained_list* l)
{
    int r=0;
    if (isEmpty_list(l)==0)
        return 0;
    list* n;
    n=l->head;
    while (n!=NULL)
    {
        if (n->address!=NULL) 
            r=1;
        n=n->next;
    }
    return r;
}
