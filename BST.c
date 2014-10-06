#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct tnode *treeAdd(struct tnode* root,struct tnode *helper);
struct tnode* treeDelete(struct tnode *root,struct tnode *x);
struct tnode* treeFind(struct tnode* p,int val);
struct tnode *treeLL(struct tnode *p,struct tnode *root);
struct tnode *treeLR(struct tnode *p,struct tnode *root);
struct tnode *treeRL(struct tnode *p,struct tnode *root);
struct tnode *treeRR(struct tnode *p,struct tnode *root);
struct tnode *treeMax(struct tnode* p);
struct tnode *treeMin(struct tnode* p);
struct tnode *treePredecessor(struct tnode *p);
struct tnode *treeSuccessor(struct tnode *p);
void treePrint(struct tnode *p);

struct tnode{
    int value;
    int height;
    struct tnode *left;
    struct tnode *right;
    struct tnode *parrent;
};

int main(){
struct tnode *root,*helper,*finder;
register unsigned int i=0;
signed int in=0;
unsigned int n=0;
static char buffer[10];
root=NULL;

scanf("%d",&n);
i=n;
while(i)
{
    scanf("%s %d", buffer,&in);

    if((strcmp("insert",buffer) == 0))
    {
            helper=malloc(sizeof(struct tnode));
            helper->value=in;
            helper->height=0;
            helper->left=helper->right=helper->parrent=NULL;

            if(!root)
                root=helper;

            else
            {
                root=treeAdd(root,helper);
            }
    }
    else if((strcmp("delete",buffer)==0))
    {
        finder=treeFind(root,in);
        if(finder)
        {
            if(!(root->left||root->right)&&(root->value==in))
                root=NULL;
            else
                treeDelete(root,finder);
        }
    }
    else if((strcmp("find",buffer)==0))
    {
        if((treeFind(root,in)))
            printf("1\n");
        else
            printf("0\n");
    }
    else if((root)&&(strcmp("inorder",buffer)==0))
    {
        treePrint(root);
        printf("\n");
    }
    else if((root)&&(strcmp("min",buffer)==0))
        printf("%d\n",treeMin(root)->value);

    else if((root)&&(strcmp("max",buffer)==0))
        printf("%d\n",treeMax(root)->value);

    else
        printf("\n");
    i--;
}
}

struct tnode *treeAdd(struct tnode *root,struct tnode *helper)
{
    struct tnode *tmp=root,*currentParrent;
/**
*Wstawiamy do bst
*/
    while(tmp)
    {
        if(helper->value==tmp->value)
            return root;
        currentParrent=tmp;
        if(helper->value>tmp->value)
            tmp=tmp->right;
        else
            tmp=tmp->left;
    }

    helper->parrent=currentParrent;

    if(helper->value < currentParrent->value)
        currentParrent->left = helper;
    else
        currentParrent->right = helper;
/**
*Balansuje drzewo
*/
    if(!currentParrent)
        return root;

    if(currentParrent->height)
    {
        currentParrent->height=0;
        return root;
    }
    if(currentParrent->left==helper)
        currentParrent->height=1;
    else
        currentParrent->height=-1;

    struct tnode *parrentOfCurrentParrent=currentParrent->parrent;

    while(parrentOfCurrentParrent)
    {
        if(parrentOfCurrentParrent->height)
            break;

        if(parrentOfCurrentParrent->left==currentParrent)
        {
            parrentOfCurrentParrent->height=1;
        }
        else
        {
            parrentOfCurrentParrent->height=-1;
        }
        currentParrent=parrentOfCurrentParrent;
        parrentOfCurrentParrent=parrentOfCurrentParrent->parrent;
    }
    if(!parrentOfCurrentParrent)
        return root;

    if(parrentOfCurrentParrent->height==1)
    {
        if(parrentOfCurrentParrent->right==currentParrent)
        {
            parrentOfCurrentParrent->height=0;
            return root;
        }
        if(currentParrent->height==-1)
        {
            root=treeLR(parrentOfCurrentParrent,root);
        }
        else
        {
            root=treeLL(parrentOfCurrentParrent,root);
        }
        return root;
    }
    else{
        if(parrentOfCurrentParrent->left==currentParrent)
        {
            parrentOfCurrentParrent->height=0;
            return root;
        }
        if(currentParrent->height==1)
        {
            root=treeRL(parrentOfCurrentParrent,root);
        }
        else
        {
            root=treeRR(parrentOfCurrentParrent,root);
        }
    }
    return root;

}
struct tnode *treeRR(struct tnode *p,struct tnode *root)
{
    struct tnode *SubTree=p->right,*currentParrent=p->parrent;

    p->right=SubTree->left;

    if(p->right)
        p->right->parrent=p;

    SubTree->left=p;
    SubTree->parrent=currentParrent;
    p->parrent=SubTree;

    if(currentParrent)
    {
        if(currentParrent->left==p)
            currentParrent->left=SubTree;

        else
            currentParrent->right=SubTree;
    }
    else
    {
        root=SubTree;
    }

    if(SubTree->height==-1)
    {
        p->height=SubTree->height=0;
    }
    else
    {
        p->height=-1;
        SubTree->height=1;
    }
   return root;
}
struct tnode *treeRL(struct tnode *p,struct tnode *root)
{
    struct tnode * bSubTree = p->right, * cSubTree = bSubTree->left, * currentParrent = p->parrent;

    bSubTree->left = cSubTree->right;

    if(bSubTree->left)
        bSubTree->left->parrent = bSubTree;

    p->right = cSubTree->left;

    if(p->right)
        p->right->parrent = p;

    cSubTree->left = p;
    cSubTree->right = bSubTree;
    p->parrent = bSubTree->parrent = cSubTree;
    cSubTree->parrent = currentParrent;

    if(currentParrent)
    {
        if(currentParrent->left == p)
            currentParrent->left = cSubTree;
        else
            currentParrent->right = cSubTree;
    }
    else
     root = cSubTree;

  p->height = (cSubTree->height == -1) ?  1 : 0;
  bSubTree->height = (cSubTree->height ==  1) ? -1 : 0;
  cSubTree->height = 0;

  return root;
}
struct tnode *treeLR(struct tnode *p,struct tnode *root)
{

    struct tnode * bSubTree = p->left, * cSubTree = bSubTree->right, * currentParrent = p->parrent;

    bSubTree->right = cSubTree->left;
    if(bSubTree->right)
        bSubTree->right->parrent = bSubTree;

    p->left = cSubTree->right;

    if(p->left)
     p->left->parrent = p;

    cSubTree->right = p;
    cSubTree->left = bSubTree;
    p->parrent = bSubTree->parrent = cSubTree;
    cSubTree->parrent = currentParrent;

    if(currentParrent)
    {
        if(currentParrent->left == p)
            currentParrent->left = cSubTree;
        else
            currentParrent->right = cSubTree;
    }
    else
        root = cSubTree;

  p->height = (cSubTree->height ==  1) ? -1 : 0;
  bSubTree->height = (cSubTree->height == -1) ?  1 : 0;
  cSubTree->height = 0;

  return root;

}
struct tnode *treeLL(struct tnode *p,struct tnode *root)
{
    struct tnode *SubTree=p->left,*currentParrent=p->parrent;

    p->left=SubTree->right;

    if(p->left)
        p->left->parrent=p;

    SubTree->right=p;
    SubTree->parrent=currentParrent;
    p->parrent=SubTree;

    if(currentParrent)
    {
        if(currentParrent->left==p)
            currentParrent->left=SubTree;
        else
            currentParrent->right=SubTree;
    }
    else
    {
        root=SubTree;
    }

    if(SubTree->height==1)
    {
        p->height=SubTree->height=0;
    }
    else{
        p->height=1;
        SubTree->height=-1;
    }

    return root;
}
struct tnode *treeSuccessor(struct tnode *p)
{
    if(p->right)
        return treeMin(p->right);

    struct tnode *tmp=p->parrent;

    while((tmp)&&(tmp->left!=p))
    {
        p=tmp;
        tmp=p->parrent;
    }

    return tmp;
}
struct tnode *treePredecessor(struct tnode *p)
{
    if(p->left)
        return treeMax(p->left);

    struct tnode *tmp=p->parrent;

    while((tmp)&&(tmp->right!=p))
    {
        p=tmp;
        tmp=p->parrent;
    }

    return tmp;
}
void treePrint(struct tnode *p)
{
    if(p)
    {
        treePrint(p->left);
        printf("%d ",p->value);
        treePrint(p->right);

    }
}
struct tnode* treeFind(struct tnode *p,int val)
{
    if(!p)
        return NULL;

    while((p)&&(val!=p->value))
    {
        if(p->value>val)
        {
            p=p->left;
        }
        else
        {
            p=p->right;
        }
    }

    return p;
}
struct tnode* treeMin(struct tnode* p)
{
    while(p->left)
        p=p->left;

    return p;
}
struct tnode* treeMax(struct tnode* p)
{

    while(p->right)
        p=p->right;

    return p;
}
struct tnode* treeDelete(struct tnode *root,struct tnode *x)
{
    struct tnode * t, * y, * z;
    bool nest;

    if(!root)
        return x;

    if((x->left) && (x->right))
    {
        y = treeDelete(root,treePredecessor(x));
        nest = false;
    }
    else
    {
        if(x->left)
        {
            y = x->left; x->left = NULL;
        }
        else
        {
         y = x->right; x->right = NULL;
        }

        x->height = 0;
        nest = true;
    }

    if(y)
    {
        y->parrent = x->parrent;
        if(y->left  = x->left)  y->left->parrent  = y;
        if(y->right = x->right) y->right->parrent = y;
        y->height = x->height;
    }

    if(x->parrent)
    {
        if(x->parrent->left == x)
            x->parrent->left = y;
        else
            x->parrent->right = y;
    }
    else
    {
        *root = *y;
    }
    if(nest)
    {
        z = y;
        y = x->parrent;
        while(y)
        {
            if(!(y->height))
            {
                y->height = (y->left == z) ? -1 : 1;
                return x;
            }
            else
            {
                if(((y->height ==  1) && (y->left  == z)) || ((y->height == -1) && (y->right == z)))
                {
                    y->height = 0;
                    z = y; y = y->parrent;
                }
                else
                {
                    t = (y->left == z) ? y->right : y->left;
                    if(!(t->height))
                    {
                        if(y->height == 1) treeLL(y,root); else treeRR(y,root);
                        return x;
                    }
                    else if(y->height == t->height)
                    {
                        if(y->height == 1) treeLL(y,root); else treeRR(y,root);
                        z = t; y = t->parrent;

                    }
                    else
                    {
                        if(y->height == 1) treeLR(y,root); else treeRL(y,root);
                        z = y->parrent; y = z->parrent;
                    }
                }
            }
        }
    }
  return x;
}
