//
//  main.cpp
//  montecarlo
//
//  Created by 黃聆恩 on 2021/3/16.
//
#include <iomanip>
#include <iostream>
#include <cstdlib>
using namespace std;
int main(int argc, const char * argv[]) {
    int in=0, out=0;
    double ran1, ran2,dis=0, pi=0,total=0;
    for(int i=0; i<1000000; i++){
        ran1 = (double)rand()/RAND_MAX;
        ran2 = (double)rand()/RAND_MAX;
        //cout<<ran1<<endl;
        dis = pow((pow(ran1, 2)+pow(ran2, 2)), 0.5);
        //cout<<dis<<endl;
        if(dis<=1){
            in++;
        }else{
            out++;
        }
    }
    total = in + out;
    pi = in/total*4;
    cout<<"pi: "<<pi<<endl;
    return 0;
}
