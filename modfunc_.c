#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int strlen(char *a)
{
    
    int c=0;
    for (;*a!='\0'&&*a!='\n';c++,a++);
    return c;
        
}
void *sub(char *a,char *b,char c[]) // c=a-b ; c should be >=0
{
    char ints[]="0123456789";
    int b_size=strlen(b);
    int a_size=strlen(a);
    int max_size=b_size>a_size?b_size:a_size; // max_size of c 
    for (;*a;a++);
    for (;*b;b++);
    a--;// last digit of a
    b--; // last digit of b
    int c1=0;
    int carryon=0; // carry-on
    for (;c1<b_size&&c1<a_size;c1++,a--,b--)
        {
            c[max_size-c1-1]=
            ints[((int)((*a-'0')-(*b-'0')-carryon>=0?(*a-'0')-(*b-'0')-carryon:((*a-'0')-(*b-'0')-carryon+10)))%10];
            if (*a-'0'-carryon>=*b-'0')carryon=0;
                else carryon=1;
        }
 
    for (;c1<a_size;c1++,a--)
        {
            c[max_size-c1-1]=ints[((*a-'0')-carryon>=0?(*a-'0')-carryon:(*a-'0')-carryon+10)%10];
            if (*a-'0'>=carryon)carryon=0;
                else carryon=1;
                
            
        }
        c1=0;

        for (;c[c1]=='0'&&c1<strlen(c);c1++);
        int c2=0;
        for (;c1<strlen(c);c2++,c1++)
            c[c2]=c[c1];
        c[c2]='\0';
        
}
void *add(char *a,char *b,char c[]) // c=a+b : c can have leading 0
{
    
    char ints[]="0123456789";
    int b_size=strlen(b);
    int a_size=strlen(a);
    int max_size=b_size>a_size?1+b_size:1+a_size; // max_size of c with carry
    for (;*a;a++);
    for (;*b;b++);
    a--;// last digit of a
    b--; // last digit of b
    int c1=0;
    int carryon=0; // carry-on
    for (;c1<b_size&&c1<a_size;c1++,a--,b--)
        {
            c[max_size-c1-1]=ints[(carryon+*a-'0'+*b-'0')%10];
            carryon=(*a-'0'+*b-'0'+carryon)/10;
            
            
        }
    for (;c1<b_size;c1++,b--)
        {
            c[max_size-c1-1]=ints[(carryon+*b-'0')%10];
            carryon=(carryon+*b-'0')/10;
        }
    for (;c1<a_size;c1++,a--)
        {
            c[max_size-c1-1]=ints[(carryon+*a-'0')%10];
            carryon=(carryon+*a-'0')/10;
        }
        c[0]=ints[carryon];
        c[max_size]='\0';
        if (c[0]=='0')
        {
            for (int c1=0;c1<max_size;c1++)
                c[c1]=c[c1+1];
        }
        
        
}
bool comp(char *a,char *b) // returns a>=b 
{
    for (;*a!='\0'&&*a=='0';a++); // omitting leading zeros
    for (;*b!='\0'&&*b=='0';b++); // omitting leading zeros
    if (strlen(a)!=strlen(b))return strlen(a)>strlen(b);
    for (;*a!='\0'&&*b!='\0'&&*a==*b;a++,b++);
   
    return *a-'0'>=*b-'0';

}

bool is_mod(char *dividend,char *divisior) // dividend%divisior
{
    char sum[1002];  
    int size=strlen(dividend);
    sum[0]='\0';
    for (int c=0;c<size;c++,dividend++)
    {
        int sum_counter=0;
        for (;sum[sum_counter];sum_counter++);
        sum[sum_counter]=*dividend; 
        sum[sum_counter+1]='\0';
        if (comp(sum,divisior)) // sum>=divisor
            {
                
                
                while(comp(sum,divisior))
                {
                        char c[1002];
                        sub(sum,divisior,c); // c=sum-divisor
                        int c1=0;
                        sum_counter=0;
                        for (;c1<strlen(c);c1++)
                        {
                            sum[c1]=c[c1];
                        }
                        sum[c1]='\0';
                        
                }

                
            }
        
    }
    
    for (int c=0;c<strlen(sum);c++)
        {
            
            if (sum[c]!='0')
                return 0;
            
        }
    return 1;
}
void strcpy(char *a,char *b) // copies b to a
{

    for (;*b;b++,a++)
        *a=*b;
    *a='\0';
    return ;
}
void printf_factors(char p[1000])
{
    char a[1000];
    a[0]='0';
    int total_factors=0;
    for (;comp(p,a);)
        {
        char c[strlen(a)+2];
        add(a,"1",c);
        
        strcpy(a,c); // copies c to a
        
        if (is_mod(p,a)>0)
            {
                total_factors++;
                printf("%s, ",a);
                fflush(stdout);
            }
        }
        printf("%d\n",total_factors);
return ;
}
int main()
{
    char a[1000];
     scanf("%s",a);
     a[strlen(a)]='\0';
   printf_factors(a);
   printf("%d\n",is_mod("100000","60"));
}
