//  Two Circles
#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    double x1,y1,r1,x2,y2,r2;
    while(t>0)
    {
        cin>>x1>>y1>>r1>>x2>>y2>>r2;
        int sqdist=(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
        if(sqdist==(r2-r1)*(r2-r1))
            cout<<"E";
        else if(sqdist<(r2-r1)*(r2-r1))
            cout<<"I";
        else
            cout<<"O";
        if(t!=1)
            cout<<endl;
        t-=1;
    }
}
