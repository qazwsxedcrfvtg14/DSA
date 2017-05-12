#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[1000005];
int cnt[26];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int i;
        scanf("%s",s);
        memset(cnt,0,sizeof(cnt));
        int bit=0,msk=(1<<26)-1;
        int n=strlen(s);
        for(i=0;i<n;i++)
            cnt[s[i]-'a']++,bit|=1<<(s[i]-'a');
        long long int ans=0;
        int r=n;
        for(i=0;i<n;i++){
            while(bit==msk){
                r--;
                cnt[s[r]-'a']--;
                if(!cnt[s[r]-'a']){
                    cnt[s[r]-'a']++;
                    r++;break;
                    }
                }
            while(bit!=msk&&r<n){
                if(!cnt[s[r]-'a'])
                    bit^=1<<(s[r]-'a');
                cnt[s[r]-'a']++;
                r++;
                }
            ans+=n-r+(bit==msk);
            //printf("%d %d\n",n-r,bit==msk);
            cnt[s[i]-'a']--;
            if(!cnt[s[i]-'a'])
                bit^=1<<(s[i]-'a');
            }
        printf("%lld\n",ans);
        }
    }