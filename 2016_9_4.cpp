#include <bits/stdc++.h>
using namespace std;
#define MAXN 10005
#define MAXM 200005
#define INF 0x3f3f3f3f
int n,m;

int en=1;
int u[MAXM],v[MAXM],w[MAXM];
int first[MAXN],nxt[MAXM];
void adde(int uu,int vv,int ww){
    nxt[en]=first[uu];
    u[en]=uu;v[en]=vv;w[en]=ww;
    first[uu]=en++;
}

struct node{
    int to,w;
    bool operator<(const node& nd)const{
        return w>nd.w;
    }
};
int vis[MAXN],dist[MAXN],ine[MAXN];
void dijkstra(int s){
    node nd;
    memset(dist,INF,sizeof(dist));dist[s]=0;
    nd.to=s;nd.w=0;
    priority_queue<node> pq;
    pq.push(nd);
    while(!pq.empty()){
        nd=pq.top();
        pq.pop();
        int uu=nd.to;
        if(vis[uu]) continue;
        vis[uu]=1;
        for(int i=first[uu];i;i=nxt[i]){
            if(dist[uu]+w[i]<dist[v[i]]){
                dist[v[i]]=dist[uu]+w[i];
                nd.to=v[i];//update a node
                nd.w=dist[v[i]];
                ine[nd.to]=w[i];
                pq.push(nd);
            }
            else if(dist[uu]+w[i]==dist[v[i]]){
                ine[v[i]]=min(ine[v[i]],w[i]);
            }
        }
    }
}
int main()
{
//    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    cin>>n>>m;
    int i;
    for(i=0;i<m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        adde(x,y,z);
        adde(y,x,z);
    }
    dijkstra(1);
    //
//    for(i=2;i<=n;i++) cout<<dist[i]<<" ";
//    cout<<endl;
    //
    long long ans=0;
    for(i=2;i<=n;i++) ans+=ine[i];
    cout<<ans<<endl;
    return 0;
}
