#include <bits/stdc++.h>
using namespace std;
#define MAXN  20010
int u[MAXN],v[MAXN],mx[MAXN][2];
int first[MAXN],nxt[MAXN];
int cnt=1;
void adde(int uu,int vv){
    nxt[cnt]=first[uu];
    u[cnt]=uu;v[cnt]=vv;
    first[uu]=cnt++;
}
int ans=0;
void dfs(int s){
    if(first[s]==0) return;
    for(int i=first[s];i;i=nxt[i]){
        dfs(v[i]);
        int mn=mx[s][0]<mx[s][1]?0:1;
        if(max(mx[v[i]][0],mx[v[i]][1])+1>mx[s][mn])
            mx[s][mn]=max(mx[v[i]][0],mx[v[i]][1])+1;
        ans=max(ans,mx[s][0]+mx[s][1]);
    }
}
int main()
{
//    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    int n,m;cin>>n>>m;
    int i,j;
    for(i=2;i<=n;i++){
        scanf("%d",&j);
        adde(j,i);
    }
    int k;
    for(j=1;j<=m;j++){
        scanf("%d",&k);
        adde(k,j+i);
    }
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
