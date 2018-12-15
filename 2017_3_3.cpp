#include <bits/stdc++.h>
using namespace std;
vector<string> vec;
int p,ul;
void deal_line(string &line,string &work)
{
    int i=0,em=0;
    while(i<line.size()){
        if(line[i]=='_'){
            if(em==1){em=0;work+="</em>";}
            else {em=1;work+="<em>";}
        }
        else if(line[i]=='['){
            string text,link;
            int in_em=0;
            ++i;
            while(line[i]!=']'){
                if(line[i]=='_'){
                    if(in_em==1){in_em=0;text+="</em>";}
                    else {in_em=1;text+="<em>";}
                }
                else text+=line[i];
                ++i;
            }
            i+=2;
            while(line[i]!=')'){
                if(line[i]=='_'){
                    if(in_em==1){in_em=0;link+="</em>";}
                    else {in_em=1;link+="<em>";}
                }
                else link+=line[i];
                ++i;
            }
            work+="<a href=\""+link+"\">"+text+"</a>";
        }
        else work+=line[i];
        ++i;
    }
}
int main()
{
    string line,tail,work;
    while(getline(cin,line)){
        if(line==""){
            if(p==1){p=0;vec.back()+="</p>";}
            else if(ul==1){ul=0;vec.push_back("</ul>");}
        }
        else{
            work.clear();tail.clear();
            if(line[0]=='#'){ //heading
                int lever=0;
                char buf[10];
                while(line[lever]=='#') lever++;
                sprintf(buf,"%d",lever);
                work=work+"<h"+buf+">";
                tail=tail+"</h"+buf+">";
                while(line[lever]==' ') lever++;
                line=line.substr(lever);
                deal_line(line,work);
                work+=tail;
                vec.push_back(work);
            }
            else if(line[0]=='*'){ //ul
                if(ul==0) {ul=1;vec.push_back("<ul>");}
                work+="<li>";tail="</li>";
                int ind=0;
                while(line[ind]=='*'||line[ind]==' ') ind++;
                line=line.substr(ind);
                deal_line(line,work);
                work+=tail;
                vec.push_back(work);
            }
            else{ //paragraph
                if(p==0){p=1;work+="<p>";}
                deal_line(line,work);
                vec.push_back(work);
            }
        }
    }
    if(p==1){p=0;vec.back()+="</p>";}
    else if(ul==1){ul=0;vec.push_back("</ul>");}
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<endl;
    }
    return 0;
}
