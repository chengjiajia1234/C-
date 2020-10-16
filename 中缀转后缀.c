#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACKSIZE 20
#define ITEMSIZE 20
#define EXPSIZE 200

typedef struct stack
{
	int top;
	int maxSize;
	int *element;
}
void Create(Stack *S,int mSize)
{
	S->maxSize=mSize;
	S->element=(ElemType*)malloc(sizeof(ElemType)*mSize);
	S->top=-1;
}
void Destroy(Stack *S)
{
	S->maxSize=0;
	free(S->element);
	S->top=-1;
}
BOOL IsEmpty(Stack *S)
{
	return S->top==-1;
}
BOOL IsFULL(Stack *S)
{
	return S->top==S->maxSize-1;
}
BOOL Top(Stack *S,int *x)
{
	if(IsEmpty(S))
		return FALSE;
	*x=S->element[S->top];
	return TRUE;
}
BOOL Push(Stack *S,int x)
{
	if(IsFULL(S))
		return FALSE;
	S->top++;
	S->element[S->top]=x;
	return TRUE;
}
BOOL Pop(Stack *S)
{
	if(IsEmpty(S))
		return FALSE;
	S->top--;
	return TRUE;
}
void Clear(Stack *S)
{
	S->top=-1;
}

BOOL IsLegal(char *postfix)
{
	int i;
	char c;
	for(i=0;i<strlen(postfix);i++)
	{
		c=postfix[i];
		if(!((c=='P')||(c=='Q')||(c=='R')))
			return FALSE;
	}
	return TRUE;
}
int GetItem(char *postfix,int *curPos,char *item)
{
	int i=0,k=*curPos,flag;
	if(postfix[k]=='.')
		flag=-1;
	else if(postfix[i]=='P'||postfix[i]=='Q'||postfix[i]=='R')
	{
		while(postfix[i]=='P'||postfix[i]=='Q'||postfix[i]=='R'||postfix[k]=='.')
			item[i++]=postfix[k++];
		item[i]='\0';
		flag=0;
	}
	else
	{
		item[0]=postfix[k++];
		item[1]='\0';
		flag=1;
	}
	while(postfix[k]==' ')
		k++;
	*curPos=k;
	return flag;
}
 int ICP(char c)
 {
	 if(c=='#')
		 return 0;
	 else if(c=='→')
		 return 1;
	 else if(c=='∨')
		 return 2;
	 else if(c=='∧')
		 return 3;
	 else
	 {
		 printf("后缀表达式不支持操作符%c!\n",c);
		 exit(0);
	 }
 }

 int ISP(char c)
 {
	  if(c=='#')
		 return 0;
	 else if(c=='→')
		 return 1;
	 else if(c=='∨')
		 return 2;
	 else if(c=='∧')
		 return 3;
	 else
	 {
		 printf("后缀表达式不支持操作符%c!\n",c);
		 exit(0);
	 }
 }

 void InfixToPostfix(char *infix,char *postfix)
 {
	 Stack S;
	 char item[ITEMSIZE];
	 int flag=-1;
	 int curPos=0;
	 int k=0,i;
	 char ch,curOP;
	 while(infix[curPos]==' ')
		 curPos++;
	 Create(&S,STACKSIZE);
	 Push(&S,'#');
	 while(curPos<strlen(infix))
	 {
		 flag=GetItem(infix,&curPos,item);
		 if(flag==-1)
		 {
			 printf("异常：中缀表达式元素不合法！\n");
			 exit(0);
		 }
		 else if(flag==1)
		 {
			 curOP=item[0];
			 if(curOP==')')
			 {
				 do
				 {
					 Top(&S,&ch);
					 Pop(&S);
					 if(ch=='#')
					 {
						 printf("异常：中缀表达式不合法！\n");
						 exit(0);
					 }
					 if(ch!='(')
					 {
						 postfix[k++]=ch;
						 postfix[k++]=' ';
					 }
				 }while(ch!='(');
			 }
			 else
			 {
				 Top(&S,&ch);
				 while(ICP(curOP)<=ISP(ch))
				 {
					 Pop(&S);
					 postfix[k++]=ch;
					 postfix[k++]=' ';
					 Top(&S,&ch);
				 }
				 Push(&S,curOP);
			 }
		 }
		 else
		 {
			 for(i=0;i<strlen(item);i++,k++)
				 postfix[k]=item[i];
			 postfix[k++]=' ';
		 }
	 }
	 while(!IsEmpty(&S))
	 {
		 Top(&S,&ch);
		 Pop(&S);
		 if(ch!='#');
		 {
			 postfix[k++]=ch;
			 postfix[k++]=' ';
		 }
	 }
	 postfix[--k]='\0';
 }
  
 void main()
 {
	 char infix[EXPSIZE];
	 char postfix[EXPSIZE];
	 printf("请输入中缀表达式：%s\n",infix);
	 gets(infix);
	 if(!IsLegal(infix))
	 {
		 printf("异常：中缀表达式中存在非法字符！\n");
		 return;
	 }
	 InfixToPostfix(infix,postfix);
	 printf("%s===>%s\n",infix,postfix);
 }

