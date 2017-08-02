#pragma GCC optimize ("O3")
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma GCC optimize ("O3")
int hd1[700005];
int val1[500005];
int hd2[700005];
int val2[500005];
int qu[200005];
int iq[200005];
const int MOD=200005;
int dis1[200005];
int dis2[200005];
int min(int a,int b){
    return a<b?a:b;
    }
void BFS(int s,int n,int *hd,int *val,int *dis){
    for(int i=0;i<n;i++)
        dis[i]=0x3fffffff,
        iq[i]=0;
    dis[s]=0;
    int qs=0,qe=0;
    qu[qe++]=s;
    while(qs!=qe){
        int now=qu[qs++];
        qs%=MOD;
        iq[now]=0;
        for(int i=hd[now];~i;i=hd[i]){
                int to=val[i-n];
            if(dis[now]+1<dis[to]){
                dis[to]=dis[now]+1;
                if(!iq[to]){
                    qu[qe++]=to;
                    qe%=MOD;
                    iq[to]=1;
                    }
                }
            }
        }
    }
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m,q;
        scanf("%d%d%d",&n,&m,&q);
        int tp=n;
        for(int i=0;i<n;i++)
            hd1[i]=-1,
            hd2[i]=-1;
        for(int i=0;i<m;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            a--;b--;
            hd1[tp]=hd1[a];
            val1[tp-n]=b;
            hd1[a]=tp;
            hd2[tp]=hd2[b];
            val2[tp-n]=a;
            hd2[b]=tp++;
            }
        BFS(0,n,hd1,val1,dis1);
        BFS(n-1,n,hd2,val2,dis2);
        int mi=dis1[n-1];
        for(int i=0;i<q;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            a--;b--;
            printf("%d\n",min(mi,dis1[a]+dis2[b]+1));
            }
        }
    return 0;
    }
