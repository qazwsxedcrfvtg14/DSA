#pragma GCC optimize ("O3")
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma GCC optimize ("O3")
int bs[1000005];
int id[1000005];
const int type=4;
int bos(int k){
    int tmp=bs[k];
    if(k!=tmp){
        bs[k]=bos(bs[k]);
        id[k]=(id[k]+id[tmp])%type;
        }
    return bs[k];
    }
int chk(int a,int b){
    return bos(a)==bos(b);
    }
void add(int x,int y,int k){
    if(!chk(x,y)){
        int a=bos(x);
        int b=bos(y);
        bs[b]=a;
        id[b]=(id[x]-id[y]+k+type)%type;
        }
    }
int cnv(char c){
    if(c=='S')return 0;
    if(c=='W')return 1;
    if(c=='N')return 2;
    if(c=='L')return 3;
    return 87;
    }
char uncnv(int k){
    if(k==0)return 'S';
    if(k==1)return 'W';
    if(k==2)return 'N';
    if(k==3)return 'L';
    return 'A';
    }
char s[10];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,q;
        scanf("%d%d",&n,&q);
        for(int i=0;i<=n;i++)
            bs[i]=i,id[i]=0;
        while(q--){
            int x,y;
            scanf("%s%d%d",s,&x,&y);
            if(s[0]=='R'){
                scanf("%s",s);
                int k=cnv(s[0]);
                if(chk(x,y)&&(id[x]+k)%type!=id[y])puts("X");
                else{
                    add(x,y,k);
                    puts("O");
                    }
                }
            else{
                if(chk(x,y))
                    putchar(uncnv((id[y]-id[x]+type)%type)),puts("");
                else
                    puts("?");
                }
            }
        }
    return 0;
    }
