#ifndef AFIN_H
#define AFIN_H
#include<stdlib.h>
#include<time.h>
#include <string>
#include <iostream>
using namespace std;

class afin
{

    int modulo(int a,int n){
        int q=a/n;
        int r=a-n*q;
        if(r<0)
            r+=n;
        return r;}
    int euexten(int a,int b){
        int resp0,resp1,resp2;
        int x,y,d;
        if(b==0){
            resp0=a;resp1=1;resp2=0;}
        else{
            int x2=1,x1=0,y2=0,y1=1;
            int q=0,r=0;
            while(b>0){
                q=(a/b);
                r=a-q*b;
                x=x2-q*x1;
                y=y2-q*y1;
                a=b;
                b=r;
                x2=x1;
                x1=x;
                y2=y1;
                y1=y;}
            resp0=a;
            resp1=x2;
            resp2=y1;}
        return resp1;}
    int mcd(int x , int y){
        int t;
        x = (x < 0) ? -x:x;
        y = (y < 0) ? -y:y;
        t = (x < y) ? x : y;
        while ( (x % t) || (y % t))
            --t;
        return t;}

    public:
        string let="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int a,b;
        int n=let.length();
        afin(){
            do{
            srand(time(NULL));
            a = 10+rand()%n;
            }while(mcd(a,b)==1);
            b = 10+rand()%n;
            cout << a<<" "<<b<<endl;}
        afin(int x, int y){
            a=x;
            b=y;}

    string cifrado(string p){
        int t;
        for(int i=0;i<p.length();i++){
            t=let.find(p[i]);
            p[i]=let[modulo((t*a+b),n)];}
        return p;}

    string descifrado(string p){
        int t;
        int ai=euexten(a,n);
        for(int i=0;i<p.length();i++){
            t=let.find(p[i])-b;
            if(t<0)t=t+n;
            p[i]=let[modulo((ai*t),n)];}
        return p;}

};

#endif // AFIN_H
