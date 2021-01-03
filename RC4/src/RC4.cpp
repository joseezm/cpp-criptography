#include "RC4.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace NTL;

RC4::RC4(int n){
    nbits=n;
}

int RC4::modulo(int x, int y){
    x=x-(x/y)*y;
    if(x<0)
        return x+y;
    return x;
}


string RC4::Delete_Zero(string n){
    while (n[0]=='0'){
        n.erase(0,1);
    }
    return n;
}

string RC4::Generar(){
    srand(time(NULL));
    for (int i=0; i<256; i++){
        s[i]=i;
    }

    k[0]=rand()%256;
    k[1]=rand()%256;
    k[2]=rand()%256;

    f=0;

    int temp;
    for (int i=0; i<255; i++){
        f=modulo((f+ s[i] + k[modulo(i,3)]),256);
        temp=s[i];
        s[i]=s[f];
        s[f]=temp;
    }


    int i = 0;
    f=0;
    string res;

    for (i=0; res.size()<nbits ; i++ ){
        i= modulo((i+1),256);
        f=modulo(f+s[i],256);
        temp=s[i];
        s[i]=s[f];
        s[f]=temp;
        t=modulo(s[i]+s[f],256);
        num=t;
        res+=num.to_string();
    }

    int dif = res.size()-nbits;
    if(dif!=0)  res.erase(0,dif);

    return res;
}

