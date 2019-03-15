#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
int a[MAXN];

int Abs(int x,int y){
    int z=x-y;
    return z>0?z:-z;
}
int main()
{
    int n;cin>>n;
    int i;
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int ans=Abs(a[1],a[0]);
    for(i=1;i<n;i++)
        ans=max(ans,Abs(a[i],a[i-1]));
    printf("%d\n",ans);
    return 0;
}
