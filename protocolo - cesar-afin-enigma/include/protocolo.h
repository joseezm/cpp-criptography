#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include "chechi.h"
#include "enigma2.0.h"
#include "afin.h"
#include<stdlib.h>
#include<time.h>
#include <string>
#include <fstream>

using namespace std;

class protocolo
{
    public:
        int cc;
        protocolo(){
            srand(time(NULL));
            cc=10+rand()%26;}

    string cifrartodo(){
        string text;
        ifstream arch;
        arch.open("cifrar.txt",ios::in);
            while(!arch.eof())
                getline(arch,text);
            arch.close();
        int t=text.length();
        string cif,text1,text2,text3,text4,text5,cif2,cif3;
        text1=text.substr(0,3);
        text2=text.substr(3,t-3);
        chechi c(cc);
        cif=c.cifrar(text2);
        text3=cif.substr(0,8);
        text4=text1+text3;
        cout << text4<<endl;
        text5=cif.substr(8,t-8);
        enigma2puntocero e(text4);
        cif2=e.cifrar(text5);
        afin a;
        cif3=a.cifrado(cif2);
        cout <<cc<<endl;
        return cif3;}
    string descifrar(){
        string tex;
        ifstream arc;
        arc.open("descifrar.txt",ios::in);
            while(!arc.eof())
                getline(arc,tex);
            arc.close();
        int t=tex.length();
        string caa,cab,cle,ces,eni;
        int ca,cb,ce;
        caa=tex.substr(0,2);
        cab=tex.substr(2,4);
        ca=atoi(caa.c_str());
        cb=atoi(cab.c_str());
        cle=tex.substr(4,15);
        ces=tex.substr(15,17);
        ce=atoi(ces.c_str());
        eni=tex.substr(17,t-17);
        string tex1,tex2,tex3;
        afin a(ca,cb);
        tex1=a.descifrado(eni);
        enigma2puntocero e(cle);
        tex2=e.cifrar(tex1);
        chechi c(ce);
        tex3=c.decifrar(tex2);
        return tex3;
        }
};

#endif // PROTOCOLO_H
