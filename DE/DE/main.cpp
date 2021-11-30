//
//  main.cpp
//  CA
//
//  Created by 黃聆恩 on 2021/6/11.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#define pi 3.141592653589793116
#define dim 30

using namespace std;
double par[dim][10], mut[dim][10], cro[dim][10], best,bestpar[dim],cr = 1,f = 0.6, upper, lower,avgbest=0,avgg=0,bestofall=10000;
int rana = 0, ranb = 0, ranc = 0, rancro=0,besti=0, bestg=0;
double sphere(int sbee, int mode, int g)
{
    double fit = 0;
    if (mode == 0)
    {
        for (int i = 0; i < dim; i++)
        {
            fit += pow(par[i][sbee], 2);
        }
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = par[i][sbee];
            }
        }
    }
    else
    {
        for (int i = 0; i < dim; i++)
        {
            fit += pow(cro[i][sbee], 2);
        }
        if (fit < best)
        {
            bestg = g;
            best = fit;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = cro[i][sbee];
            }
        }
    }
    return fit;
}
double rastrigin(int sbee, int mode, int g)
{
    double fit = 0;
    if (mode == 0)
    {
        for (int i = 0; i < dim; i++)
        {
            fit += par[i][sbee] * par[i][sbee] - 10 * cos(2 * pi * par[i][sbee]);
        }
        fit += 10 * dim;
        if (fit < best)
        {
            best = fit;
            bestg=g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = par[i][sbee];
            }
        }
    }
    else
    {
        for (int i = 0; i < dim; i++)
        {
            fit += cro[i][sbee] * cro[i][sbee] - 10 * cos(2 * pi * cro[i][sbee]);
        }
        fit += 10 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = cro[i][sbee];
            }
        }
    }

    return fit;
}
double schwefel(int sp, int mode, int g)
{
    double fit = 0;
    if (mode == 0)
    {
        for (int i = 0; i < dim; i++)
        {
            fit += par[i][sp] * sin(pow(abs(par[i][sp]), 0.5));
        }
        fit += 418.9829 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
//            for (int i = 0; i < dim; i++)
//            {
//                bestpar[i] = par[i][sp];
//            }
        }
    }
    else
    {
        for (int i = 0; i < dim; i++)
        {
            fit += cro[i][sp] * sin(pow(abs(cro[i][sp]), 0.5));
        }
        fit += 418.9829 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = cro[i][sp];
            }
        }
    }

    return fit;
}

void sphinit(){
    cr = 0.5;
    f=0.8;
    upper = 100;
    lower = -100;
    for(int i=0; i<dim ; i++){
        for(int j=0; j<10; j++){
            par[i][j] = lower + (float)rand()/RAND_MAX*(upper-lower);
            mut[i][j] = 0;
            cro[i][j] = 0;
        }
        bestpar[i] = 100;
    }
    best = 100000;
    bestg=0;
}
void rasinit(){
    cr = 0.5;
    f=0.8;
    upper = 5.12;
    lower = -5.12;
    for(int i=0; i<dim ; i++){
        for(int j=0; j<10; j++){
            par[i][j] = lower + (float)rand()/RAND_MAX*(upper-lower);
            mut[i][j] = 0;
            cro[i][j] = 0;
        }
        bestpar[i] = 100;
    }
    best = 10000000;
    bestg=0;
}
void schinit(){
    cr = 0.5;
    f=0.8;
    upper = 500;
    lower = -500;
    for(int i=0; i<dim ; i++){
        for(int j=0; j<10; j++){
            par[i][j] = lower + (float)rand()/RAND_MAX*(upper-lower);
            mut[i][j] = 0;
            cro[i][j] = 0;
        }
        bestpar[i] = 1000;
    }
    best = 10000000;
    bestg=0;
}

void mutation(){
    
    //cout<<rana<<"  "<<ranb<<"  "<<ranc<<endl;
 
        for(int j=0; j<10; j++){
            rana = rand()%10;
            ranb = rand()%10;
            while (ranb==rana) {
                ranb = rand()%10;
            }
            ranc = rand()%10;
            while (ranc==rana || ranc==ranb) {
                ranc = rand()%10;
            }
            for(int i=0; i<dim; i++){
                mut[i][j] = par[i][rana] + f*(par[i][ranb]-par[i][ranc]);
                if(mut[i][j]<lower){
                    mut[i][j] = lower;
                }
                if(mut[i][j]>upper){
                    mut[i][j] = upper;
                }
            }
        }
//    for(int i=0; i<10 ; i++){
//        for(int j=0; j<2; j++){
//            cout<<par[j][i]<<" ";
//            //cout<<mut[j][i]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for(int i=0; i<10 ; i++){
//        for(int j=0; j<2; j++){
//            //cout<<par[j][i]<<" ";
//            cout<<mut[j][i]<<" ";
//        }
//        cout<<endl;
//    }
//
//
}
void crossover(){
    for(int i=0; i<10 ; i++){
        for(int j=0; j<dim; j++){
            if((float)rand()/RAND_MAX<=cr){
                cro[j][i] = mut[j][i];
            }else{
                cro[j][i] = par[j][i];
            }
        }
        rancro = rand()%dim;
        cro[rancro][i] = mut[rancro][i];
        
    }
}
void sphselection(int g){
    for(int i=0; i<10; i++){
        if(sphere(i, 0, g)>sphere(i, 1, g)){
            for(int j=0; j<dim; j++){
                par[j][i] = cro[j][i];
            }
        }
    }
    
}
void rasselection(int g){
    for(int i=0; i<10; i++){
        if(rastrigin(i, 0, g)>rastrigin(i, 1, g)){
            for(int j=0; j<dim; j++){
                par[j][i] = cro[j][i];
            }
        }
    }
}
void schselection(int g){
    for(int i=0; i<10; i++){
        if(schwefel(i, 0, g)>schwefel(i, 1, g)){
            for(int j=0; j<dim; j++){
                par[j][i] = cro[j][i];
            }
        }
    }
}

int main() {
    double sd=0;
    cout<<setprecision(20);
    //srand(50);
        for(int e=0; e<100; e++){
            sphinit();
            for(int i=0; i<1000; i++){
                mutation();
                crossover();
                sphselection(i);
                //cout<<best<<" "<<bestpar[0]<<","<<bestpar[1]<<endl;
                //cr-=0.0002;
            }
        
            avgbest+=best;
            avgg+=bestg;
            if(bestofall>best){
                bestofall = best;
            }
            sd+=(pow((989.88-bestg),2));
        }
        sd/=100;
        sd=pow(sd, 0.5);
        
    avgbest/=100;
    avgg/=100;
    cout<<"sphere"<<endl<<"n = "<<dim<<endl;
    cout<<"平均最佳解世代： "<<avgg<<endl;
    cout<<"最佳解平均： "<<avgbest<<endl;
    cout<<"最佳解: "<<bestofall<<endl;
    cout<<" Standard Deviation: "<<sd<<endl;
    
    
    
    
    sd=0;
    avgbest=0;
    avgg=0;
    bestofall=10000;
    for(int e=0; e<100; e++){
        rasinit();
        for(int i=0; i<1000; i++){
            mutation();
            crossover();
            rasselection(i);
            //cout<<best<<" "<<bestpar[0]<<","<<bestpar[1]<<endl;
            //cr-=0.0002;
        }
        avgbest+=best;
        avgg+=bestg;
        if(bestofall>best){
            bestofall = best;
        }
        sd+=(pow((857.55-bestg),2));
       // cout<<bestg<<endl;
    }
    sd/=100;
    sd=pow(sd, 0.5);
    
avgbest/=100;
avgg/=100;
cout<<"rastrigin"<<endl<<"n = "<<dim<<endl;
cout<<"平均最佳解世代： "<<avgg<<endl;
cout<<"最佳解平均： "<<avgbest<<endl;
cout<<"最佳解: "<<bestofall<<endl;
cout<<" Standard Deviation: "<<sd<<endl;

    sd=0;
    avgbest=0;
    avgg=0;
    bestofall=10000;
    for(int e=0; e<100; e++){
        schinit();
        for(int i=0; i<1000; i++){
            mutation();
            crossover();
            schselection(i);
            //cout<<best<<" "<<endl;
            //cr-=0.0001;
        }
        avgbest+=best;
        avgg+=bestg;
        if(bestofall>best){
            bestofall = best;
        }
        sd+=(pow((958.71-bestg),2));
    }
    sd/=100;
    sd=pow(sd, 0.5);
    
avgbest/=100;
avgg/=100;
cout<<"schwefel"<<endl<<"n = "<<dim<<endl;
cout<<"平均最佳解世代： "<<avgg<<endl;
cout<<"最佳解平均： "<<avgbest<<endl;
cout<<"最佳解: "<<bestofall<<endl;
cout<<" Standard Deviation: "<<sd<<endl;

        //cout<<"after"<<endl;
//    for(int i=0; i<10 ; i++){
//        for(int j=0; j<2; j++){
//            cout<<par[j][i]<<" ";
//            //cout<<mut[j][i]<<" ";
//        }
//        cout<<endl;
//    }
//
    return 0;
}
