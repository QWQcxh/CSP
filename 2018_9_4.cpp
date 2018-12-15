#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> low;
vector<int> high;
vector<int> res;
vector<int> avg(n);
vector<set<pair<int,int> > >table;
bool isok(int ind){
    if(ind==n-1) return (res[ind]+res[ind-1])/2==avg[n-1];
    for(int sum=low[ind];sum<=high[ind];sum++){
        res[ind+1]=ind?sum-res[ind]-res[ind-1]:sum-res[ind];
        if(res[ind+1]<1) continue;
        if(table[ind].count(pair<int,int>(res[ind],res[ind+1]))) continue;
        if(isok(ind+1)) return true;
        table[ind].insert(pair<int,int>(res[ind],res[ind+1]));
    }
    return false;
}
int main()
{
    int i;
    cin>>n;
    avg.resize(n);low.resize(n);high.resize(n);res.resize(n);
    table.resize(n);
    for(i=0;i<n;i++) cin>>avg[i];
    for(i=0;i<n;i++){
        if(i==0||i==n-1) {low[i]=2*avg[i];high[i]=2*(avg[i]+1)-1;}
        else{low[i]=3*avg[i];high[i]=3*(avg[i]+1)-1;}
    }
    for(res[0]=1;!isok(0);res[0]++)
        ;
    for(i=0;i<n;i++) cout<<res[i]<<" ";
    cout<<endl;
    return 0;
}
