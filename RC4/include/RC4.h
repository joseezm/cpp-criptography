#ifndef RC4_H
#define RC4_H
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;
using namespace NTL;

class RC4
{
    public:
        int nbits;
        int s[256];
        int k[3];
        int t;
        int f;
        bitset<9> num;

        RC4(int n);
        string Delete_Zero(string num);
        string Generar();
        int modulo(int a, int b);

};

#endif // RANDOM_H
