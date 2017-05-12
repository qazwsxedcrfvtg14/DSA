#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[100005];
int st[100005];
int jmp[100005];
const int MOD=(1e9+7);
int digit(char c){
    if(c>='0'&&c<='9')return c-'0';
    return -1;
    }
int mod(long long int x){
    return (x%MOD+MOD)%MOD;
    }
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int i;
        scanf("%s",s+1);
        s[0]='(';
        int n=strlen(s);
        s[n++]=')';
        s[n]=0;
        int sp=0,dig=0,zero=0;
        st[0]=0;
        //puts(s);
        for(i=0;i<n;i++){
            if(~digit(s[i])){
                if(zero)goto invalid;
                if(!dig&&!digit(s[i]))zero=1;
                st[sp]=mod(1ll*st[sp]*10+digit(s[i]));
                dig=1;
                }
            else if(s[i]=='+'||s[i]=='-'){
                if(!dig)goto invalid;
                int now=1;
                while(st[sp]>=0){
                    now=mod(1ll*now*st[sp--]);
                    if(st[sp]==-'*')sp--;
                    }
                st[++sp]=now;
                st[++sp]=-s[i];
                st[++sp]=0;
                dig=0;zero=0;
                }
            else if(s[i]=='*'){
                if(!dig)goto invalid;
                st[++sp]=-s[i];
                st[++sp]=0;
                dig=0;zero=0;
                }
            else if(s[i]=='('){
                if(dig)goto invalid;
                st[sp++]=-s[i];
                st[sp]=0;
                dig=0;zero=0;
                }
            else if(s[i]==')'){
                if(!dig)goto invalid;
                int now=1;
                while(st[sp]>=0){
                    now=mod(1ll*now*st[sp--]);
                    if(st[sp]==-'*')sp--;
                    }
                st[++sp]=now;
                now=0;
                while(sp>=0&&st[sp]!=-'('){
                    int x=st[sp--];
                    if(st[sp]==-'-')x*=-1,sp--;
                    else if(st[sp]==-'+')sp--;
                    now=mod(now+x);
                    }
                if(st[sp]!=-'(')goto invalid;
                st[sp]=now;
                dig=1;zero=1;
                }
            else goto invalid;
            }
        if(sp)goto invalid;
        printf("%d\n",st[0]);
        goto end;
        invalid:;
        puts("invalid");
        goto end;
        end:;
        }
    }