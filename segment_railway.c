#include<stdio.h>
#include<stdlib.h>
#define Max 3
#define last 3
#define maxwl 1

typedef struct node{
int b;    //Source
int e;    //Dest
int k;
int k1;
struct node *l;
struct node *r;
}node;

typedef struct store{
int cnfrm;
int wl;
}store;

typedef struct waiting{
	int be;
	int en;
	struct waiting *next;
}waiting;

void buildtree(node *h,int b,int e);
void insert(node *h,int b,int e);
int okToInsert(node *h, int b,int e,int n);
void insertInterval(node *h,int b,int e);
void deleteInterval(node *h,int b,int e);
int max(int,int);
void compute(int b,int e,int res,int status);
void wlinsert(int,int);
void wldelete(int,int);

int z;
int z1;
store st[last+1][last+1];
waiting *head1=NULL;
waiting *tail=NULL;
node *head=NULL;
int temp1;

int main()
{

head=(node *)malloc(sizeof(node));
head->b=0;
head->e=3;
head->k=head->k1=0;
head->l=head->r=NULL;

buildtree(head,0,last);
//printf("%d",((head->r)->r)->l);

insert(head,1,3);
insert(head,2,3);
insert(head,0,1);
insert(head,1,3);
insert(head,0,2);
insert(head,1,3);
insert(head,1,2);
//insert(head,0,3);
//insert(head,0,3);
insert(head,0,1);
//insert(head,0,1);

//Assuming Confirm Ticket is cancelled
deleteInterval(head,1,3);
printf("start =%d , end = %d Cancelled\n\n",1,3);
wldelete(1,3);
deleteInterval(head,0,2);
printf("start =%d , end = %d Cancelled\n\n",0,2);
wldelete(0,2);


//compute(1,3,1,0);
//deleteInterval(head,0,3);

insert(head,1,2);
insert(head,1,3);
insert(head,2,3);
insert(head,0,1);
return 0;
}

void buildtree(node *h,int b,int e)
{
int mid=((b+e)/2);

if(mid>b&&mid<e)
{ // if(mid+1>b&&mid+1<e)mid++;
node *t;
node *t1;

t=(node *)malloc(sizeof(node));
t1=(node *)malloc(sizeof(node));

t->b=b;
t->e=mid;
t->k=t->k1=0;
t->l=t->r=NULL;
t1->b=mid;
t1->e=e;
t1->k=t1->k1=0;
t1->l=t1->r=NULL;
h->l=t;
h->r=t1;

buildtree(t,b,mid);
buildtree(t1,mid,e);
}
}

void insert(node *h,int b,int e)
{
	if(okToInsert(h,b,e,Max))
	{
		printf("Cnfrm\n");
insertInterval(h,b,e);
z=0;
compute(b,e,0,0);
}
else 
{
	printf("WL\n");
//insertInterval(h,b,e);
	z=1;
	compute(b,e,0,1);
	wlinsert(b,e);
}
}

int okToInsert(node *h, int b,int e,int n)
{
	int c1=0;
	if(((h->l==NULL&&h->r==NULL)&&(!((h->b>=e&&h->e>e)||(h->e<=b&&h->b<b))))|| (h->b>=b&&h->e<=e)) {
		//printf("k1=%d",h->k);
	//if(n<((h->k) + 1))temp1=((h->k) + 1)-n;
return (n >=((h->k) + 1));
}
else if((h->l==NULL&&h->r==NULL))return 1;
else{
c1=n-(h->k1); //# Calculate the number of colors left
//printf("c1=%d",h->k1);
return ((okToInsert(h->l,b,e,c1 )) && (okToInsert(h->r,b,e,c1 )));
}
}

void insertInterval(node *h,int b,int e){
	if(h!=NULL){
	if ((h->b>=b&&h->e<=e)) {//if(h->k-Max<=maxwl)h->k=h->k+1;
	//	if(h->k1-Max<=maxwl)h->k1=h->k1+1;
h->k1=h->k1+1;
h->k=h->k+1;
}
else{
	if(h->l!=NULL&&h->r!=NULL){
if(((!(h->l->b>e||h->l->e<b))))
insertInterval(h->l,b,e);
if(((!(h->r->b>e||h->r->e<b))))
insertInterval(h->r,b,e);
}
if(h->l==NULL&&h->r==NULL)
h->k=h->k1;
else
{//if(h->b==0&&h->e==4)printf("shan++\n");
//	if(((max(h->l->k,h->r->k))+(h->k1)-Max)<=maxwl)
	h->k=(max(h->l->k,h->r->k))+(h->k1);
	}
}
}
}

void deleteInterval(node *h,int b,int e){
	if(h!=NULL){
	if ((h->b>=b&&h->e<=e)) {
h->k1=h->k1-1;
h->k=h->k-1;
}
else{
	if(h->l!=NULL&&h->r!=NULL){
if(((!(h->l->b>e||h->l->e<b))))
deleteInterval(h->l,b,e);
if(((!(h->r->b>e||h->r->e<b))))
deleteInterval(h->r,b,e);
}
if(h->l==NULL&&h->r==NULL)
h->k=h->k1;
else
{//if(h->b==0&&h->e==4)printf("shan++\n");
	h->k=(max(h->l->k,h->r->k))+(h->k1);
	}
}
}
}

int max(int a,int b){
if(a>b)return a;
else return b;
}

void compute(int b,int e,int res,int status)
{
	if(res==0)
	{
if(z==0)
st[b][e].cnfrm++;
else
{
	if(st[b][e].wl<maxwl)
	st[b][e].wl++;
	else printf("Max Wl reached\n");
}
}

else
{
  if(status==0)
  {if(st[b][e].wl>0)st[b][e].wl--;
   else st[b][e].cnfrm--;
}

else st[b][e].wl--;
}
//printf("start =%d , end = %d , Cnfrm= %d , Wl= %d\n\n",b,e,st[b][e].cnfrm,st[b][e].wl);
printf("start =%d , end = %d \n\n",b,e);


}

void wlinsert(int st,int end)
{
	waiting *temp=(waiting *)malloc(sizeof(waiting));
	temp->be=st;
	temp->en=end;
	temp->next=NULL;
	if(head1==NULL)head1=tail=temp;
	else{
		tail->next=temp;
		tail=temp;
	}
}

void wldelete(int st1,int end)
{ 
	waiting *temp,*temp1;
	
	while(head1!=NULL){
	     if(okToInsert(head,head1->be,head1->en,Max)){
			 printf("Previous");
			 insert(head,head1->be,head1->en);
			 temp=head1;
			 if(temp==tail)tail=NULL;
			 head1=head1->next;
			 st[temp->be][temp->en].wl--;
			 free(temp);
	}
	else break;
}
	if(head1!=NULL){
	temp=head1;
	temp1=head1->next;
	
	while(temp1!=NULL)
	{ 
		if(okToInsert(head,temp1->be,temp1->en,Max)){
			waiting *xx;
			printf("Previous");
			 insert(head,temp1->be,temp1->en);
			 temp->next=temp1->next;
			
			 if(temp1==tail)tail=temp;
			 xx=temp1;
			  temp1=temp1->next;
			  st[xx->be][xx->en].wl--;
			 free(xx);
	}
	else{
		temp=temp1;
	temp1=temp1->next;
}
		
	}
	st[st1][end].cnfrm--;
}
	
	
	
}




	
