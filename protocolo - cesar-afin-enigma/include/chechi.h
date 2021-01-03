#ifndef CHECHI_H
#define CHECHI_H
#include <string>
using namespace std;

class chechi
{
    public:
        string a="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int y=a.length();
        int c;
        chechi(int clave){
            c=clave;}

    int modulo(int a,int n){
        int q=a/n;
        int r=a-n*q;
        if(r<0)
            r+=n;
        return r;}

    string cifrar(string p){
        int t;
        for(int i=0;i<p.length();i++){
            t=a.find(p[i])+c;
            if (t>=y){
                t=modulo(t,y);
                p[i]=a[t];}
            else
                p[i]=a[t];}
        return p;}
    string decifrar(string p){
        int t;
        for(int i=0;i<p.length();i++){
            t=a.find(p[i])-c;
            if (t<0){
                t=modulo(t,y);
                p[i]=a[t];}
            else
                p[i]=a[t];}
        return p;}
};

#endif // CHECHI_H

