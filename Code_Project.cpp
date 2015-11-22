#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 780
 int alloc_mat[8][8];
int main()
{
    FILE *p1,*x1;
      char m[5][15]={"source","dest","sttus","psst","bcst"};
    char u[8][20]={"dehr","hw","rk","shrnpr","mzfngr","merrut","gzb","ndelhi"};
    char y11[2][10]={"bked","cncel"};
    char y23[2][10]={"cnfrm","wl"};
    int i,j,srce,dest,pass_st,bk_st,max,charge[8][8],pr_mod,pr_rail;
         for(i=0;i<7;i++)
         {charge[i][i+1]=300;
         for(j=i+2;j<8;j++)
              charge[i][j]=charge[i][j-1]+40;
              }
    p1=fopen("I_Project.csv","r");
    x1=fopen("O_Project","w");
    fprintf(x1,"%s\t\t%s\t\t%s\t\t%s\t%s\n",m[0],m[1],m[2],m[3],m[4]);
     while(fscanf(p1,"%d,%d,%d,%d",&srce,&dest,&pass_st,&bk_st)!=EOF)
    { for(i=srce;i<dest;i++)
       { for(j=srce+1;j<=dest;j++)
          alloc_mat[i][j]+=1;
          }
          
          max=alloc_mat[srce][srce+1];
          for(i=srce;i<dest;i++)
           { for(j=srce+1;j<=dest;j++)
             {if(max<alloc_mat[i][j])
                  max=alloc_mat[i][j];
                  }
          }
          if((pass_st==1 && max<=MAX && bk_st==0)|| (pass_st==1 && max>MAX && bk_st==1))
          {for(i=srce;i<dest;i++)
       { for(j=srce+1;j<=dest;j++)
          alloc_mat[i][j]-=1;
          }
          }
          if(max<=MAX)
          {
              fprintf(x1,"%s\t\t%s\t\t%s\t\t%s\t%s\t%d\n",u[srce],u[dest],y23[0],y11[pass_st],y23[bk_st],max);  
              }
              else
               {   
                  fprintf(x1,"%s\t\t%s\t\t%s\t\t%s\t%s\t%d\n",u[srce],u[dest],y23[1],y11[pass_st],y23[bk_st],max);  
              } 
              printf("%d",max);
          if(max<=MAX && pass_st==0 && bk_st==0)
          {pr_mod+=charge[srce][dest];
          pr_rail+=charge[srce][dest];
          }
          else if(max<=MAX && pass_st==1 && bk_st==0)
                { pr_mod+=40;
                pr_rail+=40;
                }
                 
            else if(max<=MAX && pass_st==0 && bk_st==1)   
           { pr_mod+=charge[srce][dest];
          pr_rail+=charge[srce][dest];
          }
           else if(max<=MAX && pass_st==1 && bk_st==1)
          {pr_mod+=charge[srce][dest];
          pr_rail+=40;
          }
          else if(max>MAX && pass_st==0 && bk_st==0)
          pr_rail+=charge[srce][dest];
          else if(max>MAX && pass_st==0 && bk_st==1)
          pr_rail+=40;
          else if(max>MAX && pass_st==1 && bk_st==1)
          {pr_mod+=40;
          pr_rail+=40;        
          }
         // fprintf(x1,"\nOptimized profit=%d\n",pr_mod);
          //fprintf(x1,"Railway profit=%d\n",pr_rail);
           //fprintf(x1,"Total Profit=%d\n\n",pr_mod-pr_rail);
        //   printf("\n");
           
           
           }
           for(i=0;i<dest;i++)
           { for(j=srce+1;j<=dest;j++)
             {if(max<alloc_mat[i][j])
                  max=alloc_mat[i][j];
                  }
                  }
             //     fprintf(x1,"Max seats=%d\n",max);
           getch();
           }
          
