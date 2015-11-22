#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 3
typedef struct node{
int source;
int dest;
struct node *left;
struct node *right;
}birth;
int main()
{
    FILE *p1,*x1;
    birth *root[MAX],*x,*p=NULL,*a1=NULL;
    
      char m[5][15]={"source","dest","birth"};
    char u[8][20]={"dehr","hw","rk","shrnpr","mzfngr","merrut","gzb","ndelhi"};
    char y11[2][10]={"bked","cncel"};
    char y23[2][10]={"cnfrm","wl"};
    int i,j,srce,dest,pass_st,bk_st,max,charge[8][8],pr_mod,pr_rail;
    p1=fopen("I_Test_A.csv","r");
    x1=fopen("O_Test_A","w");
    for(i=0;i<MAX;i++)
    root[i]=NULL;
    fprintf(x1,"%s\t%s\t%s\t\n",m[0],m[1],m[2]);
     while(fscanf(p1,"%d,%d,%d,%d",&srce,&dest,&pass_st,&bk_st)!=EOF)
     { x=(birth *)malloc(sizeof(birth));
    x->left=NULL;
    x->right=NULL;
    x->source=srce;
    x->dest=dest;
       for(i=0;i<MAX;i++) 
    {if(pass_st==1 && bk_st==0)
        break;
       if(root[i]==NULL)
    {  root[i]=x;
     fprintf(x1,"%s\t%s\t%d\n",u[srce],u[dest],i); 
    break;
}
else
{p=root[i];
while(p!=NULL)
{
    if((dest<=p->source) || (srce>=p->dest))
    {if(dest<=p->source)
    {a1=p;
    p=p->left;
}
else
{a1=p;
p=p->right;
}
}
else
break;
}
}
if(p==NULL)
{if(dest<=a1->source)
{
 a1->left=x;
 fprintf(x1,"%s\t%s\t%d\n",u[srce],u[dest],i); 
break;
}
else
{a1->right=x;
 fprintf(x1,"%s\t%s\t%d\n",u[srce],u[dest],i); 
break;
}
}
}
}
for(i=0;i<MAX;i++)
{free(root[i]);
}
fclose(x1);
fclose(p1);
getch();
return 0;
}


        
