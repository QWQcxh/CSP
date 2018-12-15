#include <bits/stdc++.h>
using namespace std;
struct node{
    int lever;
    string key;
    string val;
    bool subobj;
    node():lever(0),subobj(false){}
};
string input;
vector<node> vec;
vector<string> rule;
int findchr(int head,char c){
    int res=head;
    while(input[res]!=c){
        if(input[res]=='\\') res+=2;
        else res++;
    }
    return res;
}
void getstr(int head,int tail,string &s){
    while(head<tail){
        if(input[head]=='\\'){s+=input[head+1];head++;}
        else s+=input[head];
        head++;
    }
}
void split(string &stmp,vector<string> &rule){
    string part;
    for(int i=0;i<stmp.size();i++){
        if(stmp[i]=='.') {rule.push_back(part);part.clear();}
        else part+=stmp[i];
    }
    rule.push_back(part);
}
int match(int vec_id,int r_id){
    if(r_id==rule.size()) return vec_id-1;
    if(vec_id==vec.size()) return -1;
    for(int i=vec_id;i<vec.size();i++){
        int res;
        if(vec[i].key==rule[r_id]&&vec[i].lever==r_id+1)
            if((res=match(i+1,r_id+1))!=-1) return res;
    }
    return -1;
}
int main()
{
    string stmp;
    int n,m;cin>>n>>m;getchar();
    while(n--){
        getline(cin,stmp);
        for(int i=0;i<stmp.size();i++)
            if(!isspace(stmp[i])) input+=stmp[i];
        stmp.clear();
    }//input
    int head=0,tail=0,lever=0;
    while(head<input.size()){
        if(input[head]=='}') {head++;lever--;}
        else if(input[head]=='{'){
            head++;lever++;
            if(input[head+1]!='}') vec.push_back(node());
        }
        else if(input[head]==','){
            head++;vec.push_back(node());
        }
        else{ //" "
            vec.back().lever=lever;
            int pos=findchr(++head,'\"');
            getstr(head,pos,vec.back().key);
            if(input[pos+2]=='{') {
                head=pos+2;vec.back().subobj=true;
            }
            else{
                head=pos+3;pos=findchr(head,'\"');
                getstr(head,pos,vec.back().val);
                head=pos+1;
            }
        }
    }
    while(m--){
        stmp.clear();
        rule.clear();
        cin>>stmp;
        split(stmp,rule);
        int res;
        res = match(0,0);
        if(res== -1)
            cout<<"NOTEXIST"<<endl;
        else {
            if(vec[res].subobj) cout<<"OBJECT"<<endl;
            else cout<<"STRING "<<vec[res].val<<endl;
        }
    }
    return 0;
}
