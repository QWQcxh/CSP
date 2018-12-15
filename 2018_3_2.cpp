#include <bits/stdc++.h>
using namespace std;
const int myleft=-1;
const int myright=1;
struct ball{
    int direction,pos;
};

int main()
{
    //freopen("cin_file","r",stdin);
    int n,l,t;
    cin>>n>>l>>t;
    vector<ball> vec(n);
    vector<int> line(l+1,0);
    for(int i=0;i<n;i++){
        cin>>vec[i].pos;
        if(vec[i].pos==l) vec[i].direction=myleft;
        else vec[i].direction=myright;
        line[vec[i].pos]=1;
    }
    for(int i=0;i<t;i++){
        for(int j=0;j<n;j++){
            line[vec[j].pos]--;
            if(vec[j].direction==myright)
                vec[j].pos++;
            else vec[j].pos--;
            line[vec[j].pos]++;
        }
        for(int j=0;j<n;j++){
            if(line[vec[j].pos]==2) 
                vec[j].direction=-vec[j].direction;
            else if(vec[j].pos==0)
                vec[j].direction=myright;
            else if(vec[j].pos==l)
                vec[j].direction=myleft;
        }
    }
    for(int i=0;i<n;i++)
        cout<<vec[i].pos<<" ";
    cout<<endl;
    return 0;
}
