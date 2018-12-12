#include <bits/stdc++.h>
using namespace std;
struct role{
    int attack;
    int health;
    int id;
    role(){}
    role(int atk,int heal,int pos):attack(atk),health(heal),id(pos){}
};
typedef list<role> rls;
list<role>::iterator role_find(rls &p,int pos){
    list<role>::iterator it;
    for(it=p.begin();it!=p.end()&&it->id<pos;it++)
        continue;
    return it;
}
void clean(list<role>::iterator it,rls &ls){
    list<role>::iterator nextit=it;
    nextit++;
    if(it->id==0) return ;
    ls.erase(it);
    while(nextit!=ls.end()){
        nextit->id--;
        nextit++;
    }
}
void show(rls &ls){
    cout<<ls.front().health<<endl
    <<ls.size()-1<<" ";
    list<role>::iterator it=ls.begin();
    it++;
    while(it!=ls.end()){
        cout<<it->health<<" ";
        it++;
    }
    cout<<endl;
}
int main()
{
//    /*debug*/
//    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
//    /*debug*/
    int n;cin>>n;getchar();
    string cmd;
    int arg1,arg2,arg3;
    rls play[2];
    play[0].push_back(role(0,30,0));
    play[1].push_back(role(0,30,0));
    int now=0;
    while(n--){
        cin>>cmd;
        if(cmd[0]=='s'){//ÕÙ»½
            cin>>arg1>>arg2>>arg3; //pos,attack,health
            role ptmp(arg2,arg3,arg1);
            list<role>::iterator it=role_find(play[now],arg1);
            play[now].insert(it,ptmp);
            while(it!=play[now].end()){
                it->id++;
                it++;
            }
        }
        else if(cmd[0]=='a'){//¹¥»÷
            cin>>arg1>>arg2;
            list<role>::iterator it1,it2;
//            /*debug*/
//            show(play[0]);
//            show(play[1]);
//            /*debug*/
            it1=role_find(play[now],arg1);
            it2=role_find(play[1-now],arg2);
            it1->health-=it2->attack;
            it2->health-=it1->attack;
            if(it1->health<=0) clean(it1,play[now]);
            if(it2->health<=0) clean(it2,play[1-now]);
        }
        else{ //½áÊø
            now=1-now;
        }
    }
    if(play[0].front().health>0&&play[1].front().health>0)  cout<<0<<endl;
    else if(play[0].front().health>0) cout<<1<<endl;
    else cout<<-1<<endl;
    show(play[0]);
    show(play[1]);
    return 0;
}
