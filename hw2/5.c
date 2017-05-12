#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define N 100010
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define swap(x,y) swp=x,x=y,y=swp
int swp;
char s[1000005];
typedef struct par{
    int id,v;
}par;
par p[26];
int cmp(const void* x,const void* y){
    const par *a=x,*b=y;
    if(a->v==b->v)return a->id-b->id;
    return b->v-a->v;
    }
int ar[26];
int br[26];
int main(){
    int t;
    //scanf("%d\n",&t);
    gets(s);
    t=atoi(s);
    while(t--){
        gets(s);
        int n=strlen(s);
        for(int i=0;i<26;i++)
            p[i].id=i,p[i].v=0;
        for(int i=0;i<n;i++)
            if(s[i]>='a'&&s[i]<='z')
                p[s[i]-'a'].v++;
        qsort(p,26,sizeof(par),cmp);
        int l=0;
        for(;l<26;l++){
            if(!p[l].v)break;
            ar[l]=p[l].id;
            }
        for(int i=0;i<l;i++){
            //putchar('a'+ar[i]);
            br[ar[i]]=ar[l-i-1];
            }
        //puts("");
        for(int i=0;i<n;i++)
            if(s[i]>='a'&&s[i]<='z')
                s[i]=br[s[i]-'a']+'a';
        puts(s);
        }
    return 0;
    }