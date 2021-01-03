#include <iostream>
#include "Gamal.h"
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*****************************************************************************************************/
string zztostring(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
}
/*****************************************************************************************************/
ZZ strtozz(string p){
            char oracion[1000];
            strcpy(oracion,p.c_str());
            return conv<ZZ>(oracion);
}
/*****************************************************************************************************/

int main()
{
    string a;
    Gamal e1(8);
    a= e1.cifrado("HOLACOMOESTASZ");


    string e_1 = "83";
    string e_2 = "157";
    string p = "167";
    string d = "138";


    Gamal e2(strtozz(e_1),strtozz(e_2),strtozz(p),strtozz(d));

    e2.decifrado("148089011116000097011081011027038003000038127");

    return 0;
}
