#include <bits/stdc++.h>
using namespace std;
map<string,int> alp_map;
string m[12]={"jan","feb","mar","apr","may","jun","jul","aug","sep",
"oct","nov","dec"};
string w[7]={"sun","mon","tue","wed","thu","fri","sat"};
struct mytime{
    int year,month,day,hour,minute;
    int week;
    bool isgap(int y);//是闰年
    int daynum(int mth);//一个月的天数
public:
    mytime(const string &line);
    void operator++();
    bool operator!=(mytime &t);
    void show();
};
struct conf{
    int minuts[60];
    int hours[24];
    int day[32];
    int month[13];
    int week[7];
    string cmd;
    conf();
};
conf::conf(){
    memset(minuts,0,sizeof(minuts));
    memset(hours,0,sizeof(hours));
    memset(day,0,sizeof(day));
    memset(month,0,sizeof(month));
    memset(week,0,sizeof(week));   
}
bool mytime::isgap(int y){return (y%400==0)||(y%4==0&&y%100);}
int mytime::daynum(int mth){
    if(mth==2){
        if(isgap(year)) return 29;
        else return 28;
    }
    else if(mth==4||mth==6||mth==9||mth==11)
        return 30;
    else return 31;
}
mytime::mytime(const string &line){
    year=(line[0]-'0')*1000+(line[1]-'0')*100+(line[2]-'0')*10+(line[3]-'0');
    month=(line[4]-'0')*10+(line[5]-'0');
    day=(line[6]-'0')*10+(line[7]-'0');
    hour=(line[8]-'0')*10+(line[9]-'0');
    minute=(line[10]-'0')*10+(line[11]-'0');
    int day_count=0;
    for(int i=1970;i<year;i++){
        if(isgap(i)) day_count+=366;
        else day_count+=365;
    }
    for(int j=1;j<month;j++)
        day_count+=daynum(j);
    day_count+=day-1;
    week= (4+day_count)%7;
}
void mytime::operator++()
{
    if(minute==59){
        minute=0;
        if(hour==23){
            hour=0;
            week=(week+1)%7;
            if(day==daynum(month)){
                day=1;
                if(month==12){
                    month=1;
                    year++;
                }
                else month++;
            }
            else day++;
        }
        else hour++;
    }
    else minute++;
}
bool mytime::operator!=(mytime &t){
    return !(year==t.year&&month==t.month&&
    day==t.day&&hour==t.hour&&minute==t.minute);
}
void mytime::show(){
    printf("%04d%02d%02d%02d%02d",year,month,day,hour,minute);
    // cout<<week<<endl;
}
void fill_array(int array[],string &str){
    int digit=0,lb=-1,en=0;
    string alpha;
    for(int i=0;i<str.size();i++){
        if(str[i]==',') {
            if(lb!=-1){
                for(int j=lb;j<=digit;j++) 
                    array[j]=1;
                lb=-1;
            }
            else array[digit]=1;
            digit=0;en=0;
        }
        else if(str[i]=='-'){
            lb=digit;
            digit=0;en=0;
        }
        else if(isdigit(str[i])) {digit=digit*10+str[i]-'0';en=1;}
        else if(isalpha(str[i])){
            alpha.clear();
            while(i!=str.size()&&isalpha(str[i]))
                alpha+=tolower(str[i++]);
            i--;
            digit= alp_map[alpha];en=1;
        }
    }
    if(lb!=-1) 
        for(int j=lb;j<=digit;j++) 
            array[j]=1;
    else if(en)array[digit]=1;
    return ;
}
void handle(vector<conf>& vec,string &line){
    conf cf;
    stringstream ss(line);
    string stmp;
    int field=1;
    while(getline(ss,stmp,' ')){
        if(stmp=="") continue;
        switch(field){
            case 1:{
                field++;
                if(stmp[0]=='*')
                    for(int i=0;i<60;i++) cf.minuts[i]=1;
                else fill_array(cf.minuts,stmp);
                break;
            }
            case 2:{
                field++;
                if(stmp[0]=='*')
                    for(int i=0;i<24;i++) cf.hours[i]=1;
                else fill_array(cf.hours,stmp);
                break;
            }
            case 3:{
                field++;
                if(stmp[0]=='*')
                    for(int i=0;i<32;i++) cf.day[i]=1;
                else fill_array(cf.day,stmp);
                break;
            }
            case 4:{
                field++;
                if(stmp[0]=='*')
                    for(int i=0;i<13;i++) cf.month[i]=1;
                else fill_array(cf.month,stmp);
                break;
            }
            case 5:{
                field++;
                if(stmp[0]=='*')
                    for(int i=0;i<7;i++) cf.week[i]=1;
                else fill_array(cf.week,stmp);
                break;
            }
            case 6:{
                cf.cmd=stmp;
                break;
            }
        }
    }
    vec.push_back(cf);
}
void init(map<string,int> &alp_map){
    for(int i=0;i<12;i++){
        alp_map[m[i]]=i+1;
    }
    for(int i=0;i<7;i++){
        alp_map[w[i]]=i;
    }
}
int match(vector<conf>&vec,mytime& t){
    int i=0;
    for(;i<vec.size();i++){
        if(vec[i].minuts[t.minute]&&vec[i].hours[t.hour]&&
        vec[i].day[t.day]&&vec[i].month[t.month]&&vec[i].week[t.week])
            break;
    }
    if(i==vec.size()) return -1;
    else return i;
}
int main()
{
    // freopen("cin_file","r",stdin);
    init(alp_map);
    int n,index;string s,t;
    vector<conf> vec;
    cin>>n>>s>>t;
    cin.ignore();
    mytime t1(s),t2(t);
    while(n--){
        string line;
        getline(cin,line);
        handle(vec,line);
    }
    while(t1!=t2){
        index=match(vec,t1);
        if(index!=-1){
            t1.show();
            putchar(' ');
            // cout<<"week is "<<t1.week<<" ";
            cout<<vec[index].cmd<<endl;
        }
        ++t1;
    }
    return 0;
}
