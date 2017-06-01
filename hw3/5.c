#include<stdio.h>
#include<stdlib.h>
#include<string.h>
unsigned int mp[32][2000005],mtp[32];
int cmp(const void* a,const void* b){
    if ( *(unsigned int*)a <  *(unsigned int*)b ) return -1;
    if ( *(unsigned int*)a == *(unsigned int*)b ) return 0;
    if ( *(unsigned int*)a >  *(unsigned int*)b ) return 1;
    return 0;
    }
int main(){
    //for(int i=0;i<32;i++)
        //printf("%x\n",((-1)<<(31-i)));
    int t;
    scanf("%d",&t);
    while(t--){
        memset(mtp,0,sizeof(mtp));
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            unsigned int a,b,c,d,x,ip;
            scanf("%u.%u.%u.%u/%u",&a,&b,&c,&d,&x);x--;
            ip=((a<<24)|(b<<16)|(c<<8)|(d))&((-1)<<(31-x));
            mp[x][mtp[x]++]=ip;
            }
        for(int i=0;i<32;i++)
            qsort(mp[i],mtp[i],sizeof(unsigned int),cmp);
        while(m--){
            unsigned int a,b,c,d,ip,mip;
            scanf("%u.%u.%u.%u",&a,&b,&c,&d);
            ip=((a<<24)|(b<<16)|(c<<8)|(d));
            int ok=0;
            for(int i=0;i<32&&!ok;i++){
                mip=ip&((-1)<<(31-i));
                int l=0,r=mtp[i]-1;
                while(l<=r){
                    int mid=(l+r)/2;
                    if(mip<mp[i][mid])
                        r=mid-1;
                    else if(mip==mp[i][mid])
                        ok=1,r=mid-1;
                    else
                        l=mid+1;
                    }
                }
            puts(ok?"TRUE":"FALSE");
            }
        }
    return 0;
    }