#include <iostream>
#include "DH.h"
using namespace std;

int main()
{
    //DH c1(16);
    //c1.obtenerClave(conv<ZZ>(9946));

    DH c2(conv<ZZ>(37547),conv<ZZ>(18774),conv<ZZ>(572));
    c2.obtenerClave(conv<ZZ>(33427));


    DH c3(conv<ZZ>(37547),conv<ZZ>(18774),conv<ZZ>(1242));
    c3.obtenerClave(conv<ZZ>(33301));
    return 0;
}
