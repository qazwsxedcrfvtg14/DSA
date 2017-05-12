#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define N 100010
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define swap(x,y) swp=x,x=y,y=swp
int swp;
int wa[N*2],wb[N*2],wv[N*2],ws[N*2];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
    }
void mak_SA(char *r,int *sa,int n,int m){
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) ws[i]=0;
    for(i=0;i<n;i++) ws[x[i]=r[i]]++;
    for(i=1;i<m;i++) ws[i]+=ws[i-1];
    for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) ws[i]=0;
        for(i=0;i<n;i++) ws[wv[i]]++;
        for(i=1;i<m;i++) ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
        x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
    return;
    }
void mak_H(char *s,int *SA,int n,int *rnk,int *H){
    for(int i=0;i<n;i++)
        rnk[SA[i]]=i;
    for(int i=0,lcp=0;i<n;i++)
        if(rnk[i]==0)
            H[0]=0;
        else{
            int j=SA[rnk[i]-1];
            if(lcp>0)lcp--;
            while(s[i+lcp]==s[j+lcp])lcp++;
            H[rnk[i]]=lcp;
            }
    }
void mak_spt(int v[20][N*2],int *ar,int n){
    for(int i=0;i<n;i++)
        v[0][i]=ar[i];
    for(int i=1;(1<<i)<=n;i++)
        for(int j=0;j+(1<<i)<=n;j++)
            v[i][j]=min(v[i-1][j],v[i-1][j+(1<<(i-1))]);
    return;
    }
int qry_spt(int v[20][N*2],int a,int b){
    if(a>b)swap(a,b);
    int p = 31 - __builtin_clz(b-a+1);
    return min(v[p][a],v[p][b-(1<<p)+1]);
    }
typedef struct vec{
    int *ar;
    int sz;
    int msz;
    }vec;
int mempool[20*N];
int* upper_bound(int *ar,size_t n,int k){
    int l=0,r=n-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(k<ar[mid])r=mid-1;
        else l=mid+1;
        }
    return ar+l;
    }
void preadd_bit(vec* ve,int n,int x){
    x++;
    while(x<=n+1){
        ve[x].msz++;
        x+=x&-x;
        }
    }
void add_bit(vec* ve,int n,int x,int y){
    x++;
    while(x<=n+1){
        ve[x].ar[ve[x].sz++]=y;
        x+=x&-x;
        }
    }
void clear_bit(vec* ve,int n){
    for(int i=1;i<=n+1;i++)
        ve[i].msz=ve[i].sz=0;
    }
void resize_bit(vec* ve,int n){
    int *now=mempool;
    for(int i=1;i<=n+1;i++){
        ve[i].ar=now;
        now+=ve[i].msz;
        }
    }
int qry_bit(vec* ve,int x,int y){
    x++;
    int ans=0;
    while(x){
        ans+=upper_bound(ve[x].ar,ve[x].sz,y)-ve[x].ar;
        x-=x&-x;
        }
    return ans;
    }
char s[N*2];
int SA[N*2];
int rnk[N*2];
int H[N*2];
int spt[20][N*2];
vec ve[N*2];
int Sn,Tn;
// <- 0
// -> 1
int search(int spt[20][N*2],int x,int l,int r,int k,int dir){
    while(l<=r){
        int mid=(l+r)/2;
        if((qry_spt(spt,x,mid)<k)^dir)
            l=mid+1;
        else
            r=mid-1;
        }
    return dir?r:l;
    }
int qry_square(int x1,int x2,int y1,int y2){
    return qry_bit(ve,x2,y2)-qry_bit(ve,x2,y1-1)-qry_bit(ve,x1-1,y2)+qry_bit(ve,x1-1,y1-1);
    }
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        Sn=strlen(s);
        scanf("%s",s+Sn);
        Tn=strlen(s+Sn)+1;
        int n=Sn+Tn;
        mak_SA(s,SA,n,128);
        mak_H(s,SA,n,rnk,H);
        mak_spt(spt,H,n);
        clear_bit(ve,n);
        for(int i=0;i<n-1;i++)
            preadd_bit(ve,n,rnk[i]);
        resize_bit(ve,n);
        for(int i=0;i<n-1;i++)
            add_bit(ve,n,rnk[i],i);
        int q;
        scanf("%d",&q);
        while(q--){
            int x1,y1,x2,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            x2+=Sn;
            y2+=Sn;
            if(y2-x2>y1-x1)
                swap(x1,x2),swap(y1,y2);
            int l=search(spt,rnk[x2],1,rnk[x2],y2-x2+1,0);
            int r=search(spt,rnk[x2]+1,rnk[x2]+1,n-1,y2-x2+1,1);
            if(l>r){
                puts("0");
                continue;
                }
            int ans=qry_square(l-1,r,x1,y1-y2+x2);
            printf("%d\n",ans);
            }
        }
    return 0;
    }