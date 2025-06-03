#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum color{BLACK,RED};
typedef struct Node{
    int val;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;
Node* root;
void init(){
    root=NULL;
}
Node* makeNode(int v,int color){
    Node* p = (Node*)malloc(sizeof(Node));
    p->val=v;
    p->color=color;
    p->parent=NULL;
    p->left=NULL;
    p->right=NULL;
    return p;
}
void leftRotation(Node* x){
    Node* y = x->right;
    x->right=y->left;
    if(y->left!=NULL)
        y->left->parent=x;
    Node* par = x->parent;
    y->parent=par;
    if(par==NULL)
        root=y;
    else if(par->left==x)
        par->left=y;
    else if(par->right==x)
        par->right=y;
    y->left=x;
    x->parent=y;
}
void rightRotation(Node* x){
    Node* y = x->left;
    x->left=y->right;
    if(y->right!=NULL)
        y->right->parent=x;
    Node* par = x->parent;
    y->parent=par;
    if(par==NULL)
        root=y;
    else if(par->left==x)
        par->left=y;
    else if(par->right==x)
        par->right=y;
    y->right=x;
    x->parent=y;
}
Node* RBFix(Node* x){
    while(1){
        //Case 1: If color of parent is Black -> Always True;
        if(x==NULL||x==root||x->parent->color==BLACK)
            break;
        Node* parent = x->parent;
        Node* grandpar = x->parent->parent;
        //Case 2: If color of uncle is Red -> set the color of uncle and parent to black and color of grandparent to red
        Node* uncle = (grandpar->left==parent)?grandpar->right:grandpar->left;
        if(uncle!=NULL&&uncle->color==RED){
            uncle->color=BLACK;
            parent->color=BLACK;
            grandpar->color=RED;
        }else{
        //Cases 3: If color of uncle is BLACK: We have 4 cases: 2 line forms and 2 triangle forms
        //Case 3.1 Uncle is in our left side
            if(grandpar->left==uncle){
                printf("Case 3.1 detected\n");
                if(parent->left==x){
                    rightRotation(parent);
                    x=parent;
                    parent=x->parent;
                }
                leftRotation(grandpar);
                grandpar->color=RED;
                parent->color=BLACK;
            }
            else if(grandpar->right==uncle){
                printf("Case 3.2 detected\n");
                if(parent->right==x){
                    leftRotation(parent);
                    x=parent;
                    parent=x->parent;
                };
                rightRotation(grandpar);
                grandpar->color=RED;
                parent->color=BLACK;
            }
        }
        x=x->parent->parent;
    }
    root->color=BLACK;
    return root;
}
Node* insert(int v){
    if(root==NULL)
        return makeNode(v,BLACK);
    Node* p = root;
    Node* prev;
    while(p!=NULL){
        prev=p;
        if(p->val>v)
            p=p->left;
        else if(p->val<v)
            p=p->right;
        else if(p->val==v)
            return root;
    }
    Node* target;
    if(prev->val>v)
        target=prev->left=makeNode(v,RED);
    if(prev->val<v)
        target=prev->right=makeNode(v,RED);
    target->parent=prev;
    return RBFix(target);
}
void preorder(Node* root){
    if(root==NULL)
        return;
    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node* root){
    if(root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->val);
}
void inorder(Node* root){
    if(root==NULL)
        return;
    inorder(root->left);
    printf("%d ",root->val);
    inorder(root->right);
}
int main(){
    init();
    char str[20];
    while(1){
        scanf("%s",str);
        if(!strcmp(str,"insert")){
            int v;
            scanf("%d",&v);
            root=insert(v);
        }else if(!strcmp(str,"remove")){

        }else if(!strcmp(str,"preorder")){
            preorder(root);
            printf("\n");
        }else if(!strcmp(str,"inorder")){
            inorder(root);
            printf("\n");
        }else if(!strcmp(str,"postorder")){
            postorder(root);
            printf("\n");
        }else if(!strcmp(str,"#")){
            break;
        }
    }
    return 0;
}
