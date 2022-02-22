#include<iostream>
#include<string>
using namespace std;
int main()
{
        string s;
        int a,i,count=0;
 
        cout<<"Enter The String: ";
        getline(cin,s);
 
        a=s.size();
 
        for(i=0;i<a;i++)
       {
                if(s[i]==' ')
                {
                  count++;
                }
       }
 
        cout<<" The Number Of Spaces In The String: "<<count;
 
        return 0;
}