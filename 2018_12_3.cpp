#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;
struct IP{
    unsigned ip;
    unsigned len;
    IP(unsigned x=0,int y=0):ip(x),len(y){}
    bool operator<(const IP&y)const{
        return ip<y.ip||(ip==y.ip&&len<y.len);
    }
};
list<IP> lst;
typedef list<IP>::iterator it;
void show(unsigned x){
    int i;
    for(i=3;i>=0;i--){
        int v=(x>>(i*8) )& 0xff;
        printf("%d",v);
        if(i) printf(".");
    }
}
void getip(string &s){
    int sz=(int)s.length();
    IP x;
    string str;
    unsigned cnt=0,val=0,len_flag=0;
    for(int i=0;i<sz;i++){
        if(s[i]=='.'||s[i]=='/'){
            val=atoi(str.c_str());
            x.ip=(x.ip<<8)+val;
            x.len+=8;
            cnt++;
            if(s[i]=='/') len_flag=1;
            str.clear();
        }
        else str+=s[i];
    }
    val=atoi(str.c_str());
    if(len_flag) x.len=(int)val;
    else x.ip=(x.ip<<8)+val,cnt++,x.len+=8;
    x.ip=x.ip<<(4-cnt)*8;
    lst.push_back(x);
}
bool issubset(IP x,IP y){ // x is subset of y
    unsigned maskx=!x.len?0:~((1<<(32-x.len))-1);
    unsigned masky=!x.len?0:~((1<<(32-y.len))-1);
    unsigned xl=x.ip&maskx;
    unsigned xr=xl | (~maskx);
    unsigned yl=y.ip&masky;
    unsigned yr=yl | (~masky);
    return yl<=xl&&xr<=yr;
}
bool canmerge(IP x,IP y){
    unsigned maskv=1<<(32-x.len);
    if(x.len&&!(x.ip&maskv)){
        IP xx(x.ip,x.len-1);
        unsigned maskx=!x.len?0:~((1<<(32-x.len))-1);
        unsigned masky=!y.len?0:~((1<<(32-y.len))-1);
        unsigned maskxx=!xx.len?0:~((1<<(32-xx.len))-1);
        unsigned xl=x.ip&maskx;
        unsigned xr=xl | (~maskx);
        unsigned yl=y.ip&masky;
        unsigned yr=yl | (~masky);
        unsigned xxl=xx.ip&maskxx;
        unsigned xxr=xx.ip|(~maskxx);
        bool contain = (xl>=yl&&xl<=yr)||(xr>=yl&&xr<=yr)||(yl<=xr&&yl>=xl)||(yr<=xr&&yr>=xl);
        bool neighbor = (xr+1)==yl||(yr+1)==xl;
        unsigned mergel=min(xl,yl),merger=max(xr,yr);
        return (contain||neighbor)&&mergel==xxl&&merger==xxr;
    }
    return false;
}
void showlst(){
    for(it p=lst.begin();p!=lst.end();p++){
        show(p->ip); cout<<'/'<<p->len<<endl;
    }
}
int main()
{
    //debug
//    freopen("C:\\Users\\Administrator\\Desktop\\input.txt","r",stdin);
    int n;cin>>n;getchar();
    int i;
    string s;
    for(i=0;i<n;i++){
        getline(cin,s);
        getip(s);
    }
    lst.sort();
    it ps=lst.begin(),pe=++ps;
    --ps;
    for(;pe!=lst.end();){
        if(issubset(*pe,*ps)){
            lst.erase(pe);
            pe=++ps;
            --ps;
        }
        else {++ps;++pe;}
    }
    ps=lst.begin();pe=++ps;--ps;
    while(pe!=lst.end()){
        if(canmerge(*ps,*pe)){
            lst.erase(pe);
            ps->len--;
            if(ps!=lst.begin()){
                pe=ps;
                --ps;
            }
            else{
                pe=++ps;
                --ps;
            }
        }
        else{
            ++ps;++pe;
        }
    }
    for(it p=lst.begin();p!=lst.end();p++){
        show(p->ip);cout<<'/'<<p->len<<endl;
    }
    return 0;
}
