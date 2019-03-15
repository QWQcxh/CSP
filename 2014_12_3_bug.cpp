#include <bits/stdc++.h>
using namespace std;
#define MAXN 5005
struct rec{
    long long type;//1->bug=y,0->sell
    float p;
    long long s;
    bool operator<(const rec& r) const{
        return p<r.p;
    }
};

rec raw[MAXN],a[MAXN];
long long inv[MAXN],buy[MAXN],sell[MAXN];
int main()
{
    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
//    freopen("C:\\Users\\marlin\\Desktop\\output.txt","w",stdout);
    memset(inv,0,sizeof(inv));
    char str[100];
    long long i=0,n;
    while(scanf("%s",str)==1){
        if(str[0]=='c'){//cancle
            scanf("%d",&n);
            inv[n-1]=inv[i]=1;
        }
        else{
            if(str[0]=='b') raw[i].type=1;
            else raw[i].type=0;
            scanf("%f%lld",&raw[i].p,&raw[i].s);
        }
        i++;
    }
    long long j,k;
    for(k=0,j=0;k<i;k++)
        if(!inv[k]) a[j++]=raw[k];
    sort(&a[0],&a[j]);
    raw[0]=a[0];
    for(i=0,k=1;k<j;k++){
        if(raw[i].p==a[k].p&&raw[i].type==a[k].type)
            raw[i].s+=a[k].s;
        else raw[++i]=a[k];
    }
    i++;
    //debug
//    for(long long x=0;x<i;x++)
//        cout<<raw[x].p<<" sell "<<raw[x].s<<endl;
    long long sum;
    for(k=0,sum=0;k<i;k++){
        if(raw[k].type==0) sum+=raw[k].s;
        sell[k]=sum;
    }
    for(k=i-1,sum=0;k>=0;k--){
        if(raw[k].type==1) sum+=raw[k].s;
        buy[k]=sum;
    }
    float price=a[0].p;long long ans=0;
    for(k=0;k<i;k++){
        if(min(buy[k],sell[k])>=ans)
            price=raw[k].p,ans=min(buy[k],sell[k]);
    }
    printf("%.2f %lld",price,ans);
    return 0;
}
