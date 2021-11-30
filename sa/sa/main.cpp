#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;
#define dim 30
#define pi 3.141592653589793116
int stepcounter=0;
double par[dim],neiL[dim],neiR[dim], fitness,best = 100000,bestg=0, ogstep = 0.03, T=100000,step,upper,lower, bestpar[dim],avgbest, avgg,bestofall;
double avgfit=0, avgposi=0,avgmov=0;
void initras(){
    
    stepcounter=0;
    T=100000;
    upper = 5.12;
    lower = -5.12;
    step = (upper-lower)/10;
    bestg=0;
    for(int i=0; i<dim ; i++){
        par[i]= lower + (float)rand()/RAND_MAX*(upper-lower);
        bestpar[i] = 100;
    }
    best = 100000;
}
void initsph(){
    stepcounter=0;
    T=100000;
    upper = 100;
    lower = -100;
    step = (upper-lower)/10;
    bestg=0;
    for(int i=0; i<dim ; i++){
        par[i] = lower + (float)rand()/RAND_MAX*(upper-lower);
                bestpar[i] = 100;
    }
    best = 100000;
}
void schinit(){
    stepcounter=0;
    best = 100000;
    T=100000;
    upper = 500;
    lower = -500;
    step = (upper-lower)/10;
    bestg = 0;
    for(int i=0; i<dim ; i++){
        par[i] = lower + (float)rand()/RAND_MAX*(upper-lower);
        bestpar[i] = 1000;
    }
    best = 100000;
}

double sphere(double a[], int g)
{
    double fit = 0;
    
        for (int i = 0; i < dim; i++)
        {
            fit += pow(a[i], 2);
        }
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = a[i];
            }
        }
    return fit;
}
double rastrigin(double a[], int g)
{
    double fit = 0;
        for (int i = 0; i < dim; i++)
        {
            fit += a[i] * a[i] - 10 * cos(2 * pi * a[i]);
        }
        fit += 10 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = a[i];
            }
        }
        return fit;
}
double schwefel(double a[], int g)
{
    double fit = 0;
        for (int i = 0; i < dim; i++)
        {
            fit += a[i] * sin(pow(abs(a[i]), 0.5));
        }
        fit += 418.9829 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = a[i];
            }
        }
    return fit;
}

void moveras(int g){
    for(int i=0; i<dim; i++){
        neiL[i] = par[i];
        neiR[i] = par[i];
    }
    int ran = rand()%dim;
    neiR[ran] = par[ran]+step;
    neiL[ran] = par[ran] - step;
        if((rastrigin(par,g)>rastrigin(neiR,g))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }else if((rastrigin(par,g)>rastrigin(neiL,g))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(rastrigin(neiL,g)-rastrigin(par,g))/T))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(rastrigin(neiR,g)-rastrigin(par,g))/T))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }
        //step/=1.5;
   
     //cout<<"after moving position:  "<<posi<<endl;
}
void movesph(int g){
    for(int i=0; i<dim; i++){
        neiL[i] = par[i];
        neiR[i] = par[i];
    }
    int ran = rand()%dim;
    neiR[ran] = par[ran]+step;
    neiL[ran] = par[ran] - step;

        if((sphere(par,g)>sphere(neiR,g))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }else if((sphere(par,g)>sphere(neiL,g))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(sphere(neiL,g)-sphere(par,g))/T))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(sphere(neiR,g)-sphere(par,g))/T))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }
        //step/=1.5;
    
}
void movesch(int g){
    for(int i=0; i<dim; i++){
        neiL[i] = par[i];
        neiR[i] = par[i];
    }
    int ran = rand()%dim;
    neiR[ran] = par[ran]+step;
    neiL[ran] = par[ran] - step;
        if((schwefel(par,g)>schwefel(neiR,g))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }else if((schwefel(par,g)>schwefel(neiL,g))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(schwefel(neiL,g)-schwefel(par,g))/T))&&(neiL[ran]>=lower)){
            par[ran] = neiL[ran];
            //stepcounter++;
        }else if(((float)rand()/RAND_MAX < exp(-(schwefel(neiR,g)-schwefel(par,g))/T))&&(neiR[ran]<=upper)){
            par[ran] = neiR[ran];
            //stepcounter++;
        }
        //step/=1.5;
   
     //cout<<"after moving position:  "<<posi<<endl;
}

int main(){
    //ofstream file;
    //file.open("hw2.csv");
    double sd=0;
    avgbest=0;
    avgg=0;
    bestofall = 100000;
    for(int e=0; e<100; e++){
    initsph();
    for(int i=0 ;i<1000; i++){
        //cout<<i+1<<endl;
        movesph(i);
        stepcounter++;
        //cout<<"stepcounter: "<<stepcounter<<endl;
        //file<<i+1<<","<<setprecision(20)<<sphere(posi)<<endl;
        T-=50;
    }
        if(bestofall>best){
            bestofall = best;
        }
        avgbest+=best;
        avgg+=bestg;
        sd+=(pow((534.22-bestg),2));
    }
    sd/=100;
    sd=pow(sd, 0.5);
    cout<<"best fit: "<<avgbest/100<<"best g : "<<avgg/100<<" bestofall: "<<bestofall<<" Standard Deviation: "<<sd<<endl;
    //file<<"------------------rastrigin-------------------"<<endl;
    cout<<"------------------rastrigin-------------------"<<endl;
    sd=0;
    avgbest=0;
    avgg=0;
    bestofall = 100000;
    for(int e=0; e<100; e++){
    initras();
    for(int i=0 ;i<1000; i++){
        //cout<<i+1<<endl;
        moveras(i);
        stepcounter++;
        //cout<<"stepcounter: "<<stepcounter<<endl;
        //file<<i+1<<","<<setprecision(20)<<rastrigin(posi)<<endl;
        T-=50;
        if(bestofall>best){
            bestofall = best;
        }
        
    }
        avgbest+=best;
                avgg+=bestg;
        sd+=(pow((576.94-bestg),2));
    }
    sd/=100;
    sd=pow(sd, 0.5);
    cout<<"best fit: "<<avgbest/100<<"best g : "<<avgg/100<<" bestofall: "<<bestofall<<" Standard Deviation: "<<sd<<endl;
    
    cout<<"--------------------schwefel------------------"<<endl;
    sd=0;
    avgbest=0;
    avgg=0;
    bestofall = 100000;
    for(int e=0; e<100; e++){
    schinit();
    for(int i=0 ;i<1000; i++){
        //cout<<i+1<<endl;
        movesch(i);
        stepcounter++;
        //cout<<"stepcounter: "<<stepcounter<<endl;
        //file<<i+1<<","<<setprecision(20)<<rastrigin(posi)<<endl;
        T-=50;
        if(bestofall>best){
            bestofall = best;
        }
        
    
    }
        avgbest+=best;
                avgg+=bestg;
        sd+=(pow((486.88-bestg),2));
    }
    sd/=100;
    sd=pow(sd, 0.5);
    cout<<"best fit: "<<avgbest/100<<"best g : "<<avgg/100<<" bestofall: "<<bestofall<<" Standard Deviation: "<<sd<<endl;
    
    return 0;
}
