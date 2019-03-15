#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005
long long g[MAXN][MAXN];
int n,m,k,d;
struct pos{
    int x,y;
    pos(int x=0,int y=0):x(x),y(y){}
};
const pos dir[4]={pos(-1,0),pos(1,0),pos(0,-1),pos(0,1)};

int vis[MAXN][MAXN],dis[MAXN][MAXN];
bool isok(int x,int y){
    if(x<1||x>n||y<1||y>n||g[x][y]<0||vis[x][y])
        return false;
    else return true;
}
vector<pos> vec;
void bfs(){
    int x,y,z,i;
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
    queue<pos> q;
    for(i=0;i<m;i++){scanf("%d%d",&x,&y);q.push(pos(x,y));vis[x][y]=1;}
    for(i=0;i<k;i++){scanf("%d%d%d",&x,&y,&z);g[x][y]+=z;vec.push_back(pos(x,y));}
    for(i=0;i<d;i++){scanf("%d%d",&x,&y);g[x][y]=-1;}
    //debug
//    for(int a=n;a>=1;a--){
//        for(int b=1;b<=n;b++)
//            cout<<g[b][a]<<" ";
//        cout<<endl;
//    }
    while(!q.empty()){
        pos p=q.front();
        q.pop();
        for(i=0;i<4;i++){
            int xx=p.x+dir[i].x;
            int yy=p.y+dir[i].y;
             if(isok(xx,yy)){
                dis[xx][yy]=dis[p.x][p.y]+1;
                q.push(pos(xx,yy));
                vis[xx][yy]=1;
                //debug
//                cout<<"xx: "<<xx<<" yy: "<<yy<<endl;
            }
        }
    }
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    memset(g,0,sizeof(g));
    cin>>n>>m>>k>>d;
    int i;
    bfs();
    long long ans=0;
    for(i=0;i<(int)vec.size();i++)
        ans+=g[vec[i].x][vec[i].y] * dis[vec[i].x][vec[i].y];
    cout<<ans<<endl;
}
