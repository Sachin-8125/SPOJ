#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef unsigned __int128 u128;
vector<u64> pr;
u64 phi(u64 m){
    u64 r=m;
    for(u64 p:pr){
        if(p*p>m)break;
        if(m%p==0){
            while(m%p==0)
                m/=p;
                r-=r/p;
        }
    }
    if(m>1)r-=r/m;
    return r;
}

static inline u64 mulf(u64 a,u64 b,u64 m){
    u128 p=(u128)a*b;
    if(p>=m)return (u64)(p%m)+m;
    return (u64)p;
}
u64 powf_(u64 x,u64 e,u64 m){
    u64 r=1,b=x>=m?x%m+m:x;
    while(e){
        if(e&1)r=mulf(r,b,m);
        e>>=1;
        if(e)b=mulf(b,b,m);
    }
    return r;
}
u64 f(u64 x,u64 n,u64 m){
    if(n==0)return 1;
    if(m==1)return 1;
    if(x==1)return 1;
    u64 e=f(x,n-1,phi(m));
    return powf_(x,e,m);
}
int main(){
    for(int i=2;i<65536;i++){
        bool ok=true;
        for(int j=2;j*j<=i;j++)
            if(i%j==0){
                ok=false;
                break;
            }
        if(ok)pr.push_back(i);}
    int T;
    scanf("%d",&T);
    while(T--){
        u64 x,n,m;
        scanf("%llu %llu %llu",&x,&n,&m);
        u64 ans;
        if(n==0)ans=1%m;
        else if(x==0)ans=(n%2==0)?1%m:0;
        else ans=f(x,n,m)%m;
        printf("%llu\n",ans);
    }
}