//
//  main.cpp
//  ABC
//
//  Created by 黃聆恩 on 2021/5/12.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;
#define pi 3.141592653589793116
#define cn 10
#define gen 1000
#define dim 30

double par[dim][cn], tri[dim][cn], best, bestofall=0, bestall[dim], bestpar[dim], parfit[cn], tcounter[cn], avgbest[gen] = {0}, upper, lower, avggen = 0,sd=0;
int randim = 0, limit, bestg = 0;
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
            fit += pow(tri[i][sbee], 2);
        }
        if (fit < best)
        {
            bestg = g;
            best = fit;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = tri[i][sbee];
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
            fit += tri[i][sbee] * tri[i][sbee] - 10 * cos(2 * pi * tri[i][sbee]);
        }
        fit += 10 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = tri[i][sbee];
            }
        }
    }

    return fit;
}
double schwefel(int sbee, int mode, int g)
{
    double fit = 0;
    if (mode == 0)
    {
        for (int i = 0; i < dim; i++)
        {
            fit += par[i][sbee] * sin(pow(abs(par[i][sbee]), 0.5));
        }
        fit += 418.9829 * dim;
        if (fit < best)
        {
            best = fit;
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
            fit += tri[i][sbee] * sin(pow(abs(tri[i][sbee]), 0.5));
        }
        fit += 418.9829 * dim;
        if (fit < best)
        {
            best = fit;
            bestg = g;
            for (int i = 0; i < dim; i++)
            {
                bestpar[i] = tri[i][sbee];
            }
        }
    }

    return fit;
}
void init()
{

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < cn; j++)
        {
            par[i][j] = lower + (float)rand() / RAND_MAX * (upper - lower);
            tri[i][j] = par[i][j];
            tcounter[j] = 0;
        }
        bestpar[i] = 100;
    }
    best = RAND_MAX;
    bestg = 0;
}

void sphmove(int sbee, int g)
{
    int sdim, rbee;
    sdim = rand() % dim;
    rbee = rand() % cn;
    while (rbee == sbee)
    {
        rbee = rand() % cn;
    }
    float ran = -1 + (float)rand() / RAND_MAX * 2;
    tri[sdim][sbee] = par[sdim][sbee] + ran * (par[sdim][sbee] - par[sdim][rbee]);
    if (tri[sdim][sbee] > upper)
        tri[sdim][sbee] = upper;
    if (tri[sdim][sbee] < lower)
        tri[sdim][sbee] = lower;
    if (sphere(sbee, 0, g) > sphere(sbee, 1, g))
    {
        par[sdim][sbee] = tri[sdim][sbee];
        tcounter[sbee] = 0;
    }
    else
    {
        tcounter[sbee]++;
    }
    parfit[sbee] = sphere(sbee, 0, g);
}
void sphemploy(int g)
{

    for (int i = 0; i < cn; i++)
    {
        sphmove(i, g);
    }
}
void sphonlook(int g)
{
    double prob[cn], sum = 0;
    float ran;
    int onlookc[cn] = {0};
    for (int i = 0; i < cn; i++)
    {
        if (parfit[i] >= 0)
        {
            prob[i] = 1.0 / (parfit[i] + 1);
        }
        else
        {
            prob[i] = 1.0 + abs(parfit[i]);
        }
        sum += prob[i];
    }
    //cout<<sum<<endl;
    for (int i = 0; i < cn; i++)
    {
        prob[i] = prob[i] / sum;
    }

    for (int i = 1; i < cn; i++)
    {
        prob[i] += prob[i - 1];
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << prob[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        ran = (float)rand() / RAND_MAX;
        //cout << ran << endl;
        if (ran >= 0 && ran < prob[0])
        {
            onlookc[0]++;
        }
        else
        {
            for (int j = 0; j < cn - 1; j++)
            {
                if (ran >= prob[j] && ran < prob[j + 1])
                {
                    onlookc[j + 1]++;
                }
            }
        }
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << onlookc[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        while (onlookc[i] != 0)
        {
            sphmove(i, g);
            onlookc[i]--;
        }
    }
}

void rasmove(int sbee, int g)
{
    int sdim, rbee;
    sdim = rand() % dim;
    rbee = rand() % cn;
    while (rbee == sbee)
    {
        rbee = rand() % cn;
    }
    float ran = -1 + (float)rand() / RAND_MAX * 2;
    tri[sdim][sbee] = par[sdim][sbee] + ran * (par[sdim][sbee] - par[sdim][rbee]);
    if (tri[sdim][sbee] > upper)
        tri[sdim][sbee] = upper;
    if (tri[sdim][sbee] < lower)
        tri[sdim][sbee] = lower;
    if (rastrigin(sbee, 0, g) >= rastrigin(sbee, 1, g))
    {
        par[sdim][sbee] = tri[sdim][sbee];
        tcounter[sbee] = 0;
    }
    else
    {
        tcounter[sbee]++;
    }
    parfit[sbee] = rastrigin(sbee, 0, g);
}
void rasemploy(int g)
{

    for (int i = 0; i < cn; i++)
    {
        rasmove(i, g);
    }
}
void rasonlook(int g)
{
    double prob[cn], sum = 0;
    float ran;
    int onlookc[cn] = {0};
    for (int i = 0; i < cn; i++)
    {
        if (parfit[i] >= 0)
        {
            prob[i] = 1.0 / (parfit[i] + 1);
        }
        else
        {
            prob[i] = 1.0 + abs(parfit[i]);
        }
        sum += prob[i];
    }
    //cout<<sum<<endl;
    for (int i = 0; i < cn; i++)
    {
        prob[i] = prob[i] / sum;
    }

    for (int i = 1; i < cn; i++)
    {
        prob[i] += prob[i - 1];
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << prob[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        ran = (float)rand() / RAND_MAX;
        //cout << ran << endl;
        if (ran >= 0 && ran < prob[0])
        {
            onlookc[0]++;
        }
        else
        {
            for (int j = 0; j < cn - 1; j++)
            {
                if (ran >= prob[j] && ran < prob[j + 1])
                {
                    onlookc[j + 1]++;
                }
            }
        }
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << onlookc[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        while (onlookc[i] != 0)
        {
            rasmove(i, g);
            onlookc[i]--;
        }
    }
}

void schmove(int sbee, int g)
{
    int sdim, rbee;
    sdim = rand() % dim;
    rbee = rand() % cn;
    while (rbee == sbee)
    {
        rbee = rand() % cn;
    }
    float ran = -1 + (float)rand() / RAND_MAX * 2;
    tri[sdim][sbee] = par[sdim][sbee] + ran * (par[sdim][sbee] - par[sdim][rbee]);
    if (tri[sdim][sbee] > upper)
        tri[sdim][sbee] = upper;
    if (tri[sdim][sbee] < lower)
        tri[sdim][sbee] = lower;
    if (schwefel(sbee, 0, g) >= schwefel(sbee, 1, g))
    {
        par[sdim][sbee] = tri[sdim][sbee];
        tcounter[sbee] = 0;
    }
    else
    {
        tcounter[sbee]++;
    }
    parfit[sbee] = schwefel(sbee, 0, g);
}
void schemploy(int g)
{

    for (int i = 0; i < cn; i++)
    {
        schmove(i, g);
    }
}
void schonlook(int g)
{
    double prob[cn], sum = 0;
    float ran;
    int onlookc[cn] = {0};
    for (int i = 0; i < cn; i++)
    {
        if (parfit[i] >= 0)
        {
            prob[i] = 1.0 / (parfit[i] + 1);
        }
        else
        {
            prob[i] = 1.0 + abs(parfit[i]);
        }
        sum += prob[i];
    }
    //cout<<sum<<endl;
    for (int i = 0; i < cn; i++)
    {
        prob[i] = prob[i] / sum;
    }

    for (int i = 1; i < cn; i++)
    {
        prob[i] += prob[i - 1];
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << prob[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        ran = (float)rand() / RAND_MAX;
        //cout << ran << endl;
        if (ran >= 0 && ran < prob[0])
        {
            onlookc[0]++;
        }
        else
        {
            for (int j = 0; j < cn - 1; j++)
            {
                if (ran >= prob[j] && ran < prob[j + 1])
                {
                    onlookc[j + 1]++;
                }
            }
        }
    }
    // for (int i = 0; i < cn; i++)
    // {
    //     cout << onlookc[i] << ", ";
    // }
    // cout << endl;
    for (int i = 0; i < cn; i++)
    {
        while (onlookc[i] != 0)
        {
            schmove(i, g);
            onlookc[i]--;
        }
    }
}

void scout()
{
    int max = 0, index=0;
    for (int i = 0; i < cn; i++)
    {
        if (tcounter[i] > max)
        {
            max = tcounter[i];
            index = i;
        }
    }
    if (max > limit)
    {
        for (int i = 0; i < dim; i++)
        {
            par[i][index] = lower + (float)rand() / RAND_MAX * (upper - lower);
        }
        tcounter[index] = 0;
    }
}
int main()
{
    ofstream output;
    output.open("hw.csv");
    output << fixed << setprecision(100);
    sd=0;
    limit = 100;
    lower = -100; //sphere boundary
    upper = 100;
    bestofall = 1000000;
    avggen = 0;
    for (int e = 0; e < 100; e++)
    {
        init();

        for (int g = 0; g < gen; g++)
        {

            //cout << "G: " << g + 1 << endl;
            sphemploy(g);

            sphonlook(g);

            scout();

            avgbest[g] += best;
        }
        if (bestofall > best)
        {
            bestofall = best;
            for (int i = 0; i < dim; i++)
            {
                bestall[i] = bestpar[i];
            }
        }
        avggen += bestg;
        sd+=(pow((551.89-bestg), 2));
        
    }
    sd/=100;
    sd=pow(sd, 0.5);
    avggen /= 100;
    for (int i = 0; i < gen; i++)
    {
        avgbest[i] /= 100;
        output << avgbest[i] << ", ";
    }
    output << endl
           << bestofall << " ,";
    cout << "Sphere: " << endl;
    cout << "n= " << dim << endl;
    cout << "average best : " << avgbest[gen - 1] << endl;
    cout << "average generation: " << avggen << endl;
    cout << "bestofall: "<<bestofall<<endl;
    cout << "standard deviation: "<<sd<<endl;
    for (int i = 0; i < dim; i++)
    {
        output << bestall[i] << ",";
        //cout << bestall[i] << ", ";
    }
    output << endl;
    cout << endl;
    //rastrigin
    //rastrigin
    //rastrigin
    //rastrigin
    //rastrigin

    for (int i = 0; i < gen; i++)
    {
        avgbest[i] = 0;
    }
    sd=0;
    limit = 30;
    lower = -5.12;
    upper = 5.12;
    bestofall = 1000000;
    avggen = 0;
    for (int e = 0; e < 100; e++)
    {
        init();

        for (int g = 0; g < gen; g++)
        {

            //cout << "G: " << g + 1 << endl;
            rasemploy(g);

            rasonlook(g);

            scout();

            avgbest[g] += best;
        }
        if (bestofall > best)
        {
            bestofall = best;
            for (int i = 0; i < dim; i++)
            {
                bestall[i] = bestpar[i];
            }
        }
        avggen += bestg;
        sd+=(pow((420.03-bestg), 2));
        
    }
    sd/=100;
    sd=pow(sd, 0.5);
    avggen /= 100;
    for (int i = 0; i < gen; i++)
    {
        avgbest[i] /= 100;
        output << avgbest[i] << ", ";
    }
    output << endl
           << bestofall << " ,";
    cout << "Rastrigin: " << endl;
    cout << "n= " << dim << endl;
    cout << "average best : " << avgbest[gen - 1] << endl;
    cout << "average generation: " << avggen << endl;
    cout << "bestofall: "<<bestofall<<endl;
    cout << "standard deviation: "<<sd<<endl;
    
    for (int i = 0; i < dim; i++)
    {
        output << bestall[i] << ",";
    }
    output << endl;
    //Schwefel
    //Schwefel
    //Schwefel
    //Schwefel
    for (int i = 0; i < gen; i++)
    {
        avgbest[i] = 0;
    }
    limit = 70;
    lower = -500;
    upper = 500;
    bestofall = 10000;
    avggen = 0;
    for (int e = 0; e <100; e++)
    {
        init();

        for (int g = 0; g < gen; g++)
        {

            //cout << "G: " << g + 1 << endl;
            schemploy(g);

            schonlook(g);

            scout();

            avgbest[g] += best;
        }
        if (bestofall > best)
        {
            bestofall = best;
            for (int i = 0; i < dim; i++)
            {
                bestall[i] = bestpar[i];
            }
        }
        avggen += bestg;
        sd+=(pow((491.23-bestg), 2));
        
    }
    sd/=100;
    sd=pow(sd, 0.5);
    avggen /= 100;
    for (int i = 0; i < gen; i++)
    {
        avgbest[i] /= 100;
        output << avgbest[i] << ", ";
    }
    output << endl
           << bestofall << " ,";
    cout << "Schwefel: " << endl;
    cout << "n= " << dim << endl;
    cout << "average best : " << avgbest[gen - 1] << endl;
    cout << "average generation: " << avggen << endl;
    cout << "bestofall: "<<bestofall<<endl;
    cout << "standard deviation: "<<sd<<endl;
    
    for (int i = 0; i < dim; i++)
    {
        output << bestall[i] << ",";
    }

    return 0;
}
