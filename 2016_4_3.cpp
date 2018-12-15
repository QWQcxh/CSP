#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;cin>>n;
    string cur_path;
    cin>>cur_path;
    cin.ignore();
    stringstream ss;
    vector<string> vec;
    while(n--){
        ss.clear();
        vec.clear();
        string newl,stmp;
        getline(cin,newl);
        if(newl[0]!='/') newl = cur_path+"/"+newl;
        ss<<newl;
        while(getline(ss,stmp,'/')){
            if(stmp=="") continue;
            else if(stmp==".."){
                if(!vec.empty()) vec.pop_back();
            }
            else if(stmp==".") ;
            else vec.push_back(stmp);
            stmp.clear();
        }
        if(vec.size()==0) cout<<'/';
        else{
            for(int i=0;i<vec.size();i++)
                cout<<'/'<<vec[i];
        }
        cout<<endl;
    }
    return 0;
}
