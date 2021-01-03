#include <iostream>
#include "RC4.h"
#include "LFRS.h"
#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <sstream>

using namespace std;
using namespace NTL;
using namespace std;

int main()
{
    int bits = 32;

    LFRS r1(bits,bits/5,1);
    cout << r1.Generar();

    return 0;
}
