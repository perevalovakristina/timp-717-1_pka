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
void init(tree* t);
int remove_(tree* t,int value);
int removeMin(node* n);
void printTree(tree* t);
void clear_branch(node* n);
void clear(tree* t);
void print_v_shirinu(node* n);
void straight_print (node* n);
void back_print(node* n);
void init_list(two_chained_list* l);
void clear_list(two_chained_list* l);
int isEmpty_list( two_chained_list* l);
int push_back_list( two_chained_list* l, node* val);
void print_list( two_chained_list* l);
int printable( two_chained_list* l);

int main(){
    tree* root = malloc(sizeof(tree));
    init(root);
    int t;
    for(int i=0;i<7;i++){
        scanf("%d",&t);
        insert(root,t);
    }
    printTree(root);

    return 0;
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

void print_v_shirinu(node* n)
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

void straight_print(node* n){

    node** nodes = malloc(sizeof(node)*128);
    int last_pos=127;
    printf("%d ", n->value);
    nodes[last_pos]=n->right;
    last_pos--;
    nodes[last_pos]=n->left;
    last_pos--;
    while(last_pos!=127){
        last_pos++;
        node* tmp=nodes[last_pos];
        printf("%d ", tmp->value);
        if(tmp->right!=NULL){
            nodes[last_pos]=tmp->right;
            last_pos--;
        }
        if(tmp->left!=NULL){
            nodes[last_pos]=tmp->left;
            last_pos--;
        }
    }
}

void back_print(node* n){
    if (n!=NULL) {
        int appended=0;
        if(n->left!=NULL && n->right!=NULL){}
        back_print(n->left);
        back_print(n->right);
        printf("%d ", n->value);
    }
}


void printTree(tree *t)
{
    // print_v_shirinu(t->root);
    straight_print(t->root);
    // back_print(t->root);
    printf("\n");
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
            printf("_ ");
        else
            printf("%d ", l->tail->address->value);
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
