#ifndef ENIGMA2_0_H
#define ENIGMA2_0_H
#include <string>
using namespace std;

class enigma2puntocero
{
    public:
        string im="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string r8="FKQHTLXOCBJSPDZRAMEWNIUYGV";
        string r7="NZJHGRCXMYSWBOUFAIVLPEKQDT";
        string r6="JPGVOUMFYQBENHZRDKASXLICTW";
        string r5="VZBRGITYUPSDNHLXAWMJQOFECK";
        string r4="ESOVPZJAYQUIRHXLNFTGKDXMWB";
        string r3="BDFHJLCPRTXVZNYEIWGAKMUSQO";
        string r2="AJDKSIRUXBLHWTMCQGZNPYFVOE";
        string r1="EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        string re="YRUHQSLDPXNGOKMIEBFZCWVJAT";
        int x,y,z,p3,p2,p1,s1,s2;
        int q=im.length();
        enigma2puntocero(string e){
            for(int i=0;i<3;i++){
                if(e[i]==1){
                    if(i==0)r1=r1;
                    if(i==1)r2=r1;
                    if(i==2)r3=r1;}
                else if (e[i]==2){
                    if(i==0)r1=r2;
                    if(i==1)r2=r2;
                    if(i==2)r3=r2;}
                else if (e[i]==3){
                    if(i==0)r1=r3;
                    if(i==1)r2=r3;
                    if(i==2)r3=r3;}
                else if (e[i]==4){
                    if(i==0)r1=r4;
                    if(i==1)r2=r4;
                    if(i==2)r3=r4;}
                else if (e[i]==5){
                    if(i==0)r1=r5;
                    if(i==1)r2=r5;
                    if(i==2)r3=r5;}
                else if (e[i]==6){
                    if(i==0)r1=r6;
                    if(i==1)r2=r6;
                    if(i==2)r3=r6;}
                else if (e[i]==7){
                    if(i==0)r1=r7;
                    if(i==1)r2=r7;
                    if(i==2)r3=r7;}
                else if (e[i]==8){
                    if(i==0)r1=r8;
                    if(i==1)r2=r8;
                    if(i==2)r3=r8;}}
            x=im.find(e[3]);
            y=im.find(e[4]);
            z=im.find(e[5]);
            p3=modulo((x-im.find(e[6])),q);
            p2=modulo((y-im.find(e[7])),q);
            p1=modulo((z-im.find(e[8])),q);
            s1=im.find(e[9]);
            s2=im.find(e[10]);
            }

    int modulo(int a,int n){
        int q=a/n;
        int r=a-n*q;
        if(r<0)
            r+=n;
        return r;}

    string cifrar(string p){
        int c=1;
        int t;
        for(int i=0;i<p.length();i++){
            if(p[i]==im[s1])p[i]=im[s2];
            else if(p[i]==im[s2])p[i]=im[s1];
            t=im.find(p[i])+x+c;
            if(t>=q)t=modulo(t,q);
            p[i]=r3[t];
            t=im.find(p[i])-c-x+y;
            if(t<0 || t>=q)t=modulo(t,q);
            p[i]=r2[t];
            t=im.find(p[i])-y+z;
            if(t<0 || t>=q)t=modulo(t,q);
            p[i]=r1[t];
            t=im.find(p[i])-z;
            if(t<0)t=modulo(t,q);
            p[i]=re[t];
            t=im.find(p[i])+z;
            if(t>=q)t=modulo(t,q);
            p[i]=im[t];
            t=r1.find(p[i])-z+y;
            if(t<0 || t>=q)t=modulo(t,q);
            p[i]=im[t];
            t=r2.find(p[i])-y+x+c;
            if(t<0 || t>=q)t=modulo(t,q);
            p[i]=im[t];
            t=r3.find(p[i])-x-c;
            if(t<0)t=modulo(t,q);
            p[i]=im[t];
            if(p[i]==im[s1])p[i]=im[s2];
            else if(p[i]==im[s2])p[i]=im[s1];
            c++;
            p3++;
            if(p3==25){
                y++;
                p2++;
                p3=0;}
            if(p2==26){
                z++;
                p2=0;}}
        return p;}
};

#endif // ENIGMA2_0_H
