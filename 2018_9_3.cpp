#include <bits/stdc++.h>
using namespace std;
struct node{
    int dots;
    string tag,id;
    int father;
    node(int dots=0,string tag="",string id="",int fa=0):dots(dots),tag(tag),id(id),father(fa){}
};
int getfa(vector<node>& vec,int dots){
    int i;
    for(i=vec.size()-1;i>=0&&vec[i].dots>=dots;i--)
        continue;
    return i;
}
void deal(string &line,vector<string>&rule){
    string stmp;
    for(int i=0;i<line.size();i++){
        if(line[i]==' '){
            rule.push_back(stmp);
            stmp.clear();
        }
        else stmp+=line[i];
    }
    rule.push_back(stmp);
}
bool ignore_equal(string s1,string s2){
    if(s1.size()!=s2.size()) return false;
    for(int i=0;i<s1.size();i++){
        if(tolower(s1[i])!=tolower(s2[i]))
            return false;
    }
    return true;
}
bool isok(vector<string>&rule,vector<node>&vec,int ind){
    int i=rule.size()-1;
    if(rule[i][0]=='#'&&rule[i]!=vec[ind].id) return false;
    else if(rule[i][0]!='#'&&!ignore_equal(rule[i],vec[ind].tag)) return false;
    else{
        int fa=vec[ind].father;
        i--;
        while(i>=0&&fa>=0){
            if(rule[i][0]=='#'&&vec[fa].id==rule[i]) {i--;fa=vec[fa].father;}
            else if(rule[i][0]!='#'&&ignore_equal(vec[fa].tag,rule[i])) {i--;fa=vec[fa].father;}
            else fa=vec[fa].father;
        }
        return i==-1;
    }
}
int main()
{
    int n,m;
    cin>>n>>m;getchar();
    vector<node> vec;
    string line;
    for(int i=0;i<n;i++){
        getline(cin,line);
        node now;
        while(line[now.dots]=='.') now.dots++;
        stringstream ss(line.substr(now.dots));
        ss>>now.tag>>now.id;
        now.father=getfa(vec,now.dots);
        vec.push_back(now);
    } //initial finished
    while(m--){
        getline(cin,line);
        vector<string> rule;
        deal(line,rule);
        int sum=0;
        vector<int> res;
        for(int i=0;i<vec.size();i++){
            if(isok(rule,vec,i)){
                sum++;res.push_back(i+1);
            }
        }
        cout<<sum<<" ";
        if(sum) for(int i=0;i<res.size();i++) cout<<res[i]<<" ";
        cout<<endl;
    }
    return 0;
}

