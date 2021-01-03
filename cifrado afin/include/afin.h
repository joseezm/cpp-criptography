#ifndef AFIN_H_INCLUDED
#define AFIN_H_INCLUDED
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class Afin{
public:
    int a;
    int b;
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";

    Afin(){
    do{
        srand(time(NULL));
        a = rand() % alfabeto.length();
    }while(!euclides(a));

    b = 10+ rand() % alfabeto.length();

    cout<< endl << "Clave publica A : "<<a<<endl;
    cout<<"Clave publica B : "<<b<<endl;
    }

    Afin(int _a,int _b){
        a=_a;
        b=_b;
    }
        bool euclides(int b){
        int q;
        int a = alfabeto.length();
        while(b>0){
            q = a/b;
            int r = a - (q*b);
            a = b;
            b = r;
        }
        if(a == 1){
            return true;
        }
        else{
            return false;
        }
    }

    int euclidesExt(int b){
        int a = alfabeto.length();
        int q;
        int s;
        int r;
        int s1 = 0;
        int s2 = 1;
        while(b>0){
            q = a/b;
            r = a - q*b;
            a = b;
            b = r;
            s = s1 - (q*s2);
            s1 = s2;
            s2 = s;
        }
        if(s1<0){
            s1 = alfabeto.length() + s1;
            return s1;
        }
        else{
            return s1;
        }
    }

    int modulo(int a, int n){
        a=a-(a/n)*n;
        if(a<0) return a+n;
        return a;
    }

    string cifrado(string mensaje){
        string cifrado;
        int pos;
        for(int i=0;i<mensaje.length();i++){
            pos = alfabeto.find(mensaje[i]);
            pos = pos * a;
            pos = pos + b;
            pos = modulo(pos,alfabeto.length());
            cifrado+=alfabeto[pos];

        }
        return cifrado;
    }


    string descifrado(string cifrado){
        string mensaje;
        int inv = euclidesExt(a);
        int pos;
        for(int i=0;i<cifrado.length();i++){
            pos = alfabeto.find(cifrado[i]);
            pos = pos - b;
            if(pos<0){
                pos = alfabeto.length()+pos;
            }
            pos = pos*inv;
            pos = modulo(pos,alfabeto.length());
            mensaje+=alfabeto[pos];
        }
        return mensaje;

    }

};



#endif // AFIN_H_INCLUDED
