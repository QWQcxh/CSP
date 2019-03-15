#include <bits/stdc++.h>
using namespace std;
#define MAXN 200010
int n,m;

struct edge{
    int u,v;
    bool operator<(const edge& eg)const{
        return v>eg.v;
    }
}e[MAXN];

int en=1;
int first[MAXN],nxt[MAXN];
int u[MAXN],v[MAXN];
void adde(int uu,int vv){
    nxt[en]=first[uu];
    u[en]=uu;v[en]=vv;
    first[uu]=en++;
}
int path[MAXN];int ind;
char mark[10002][10002];
bool isok(int s,int idx){
    path[idx]=s;ind=idx;
    if(idx==m) return true;
    int i,t=0;
    for(i=first[s];i;i=nxt[i]){
        t=v[i];
        if(mark[s][t]) continue;
        mark[s][t]=mark[t][s]=1;
        if(isok(t,idx+1)) return true;
        ind=idx;mark[s][t]=mark[t][s]=0;
    }
    return false;
}
int main()
{
    //debug
//    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    scanf("%d%d",&n,&m);
    int i,cnt=0,j;
    for(i=0;i<m;i++,cnt+=2) {
        scanf("%d%d",&e[i].u,&e[i].v);
        e[m+i].u=e[i].v;
        e[m+i].v=e[i].u;
    }
    sort(&e[0],&e[cnt]);
    for(i=0;i<cnt;i++) adde(e[i].u,e[i].v);
    for(i=1;i<=n;i++){
        ind=0;
        if(isok(i,0)){
            for(j=0;j<=ind;j++){
                if(j) putchar(' ');
                printf("%d",path[j]);
            }
            putchar('\n');
            return 0;
        }
    }
    printf("%d\n",-1);
    return 0;
}
