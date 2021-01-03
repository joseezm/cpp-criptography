#include <iostream>
#include <string>
#include "afin.h"

using namespace std;

int main()
{
    Afin a1;
    cout << "cifrado: " <<  a1.cifrado("holaperra") << endl;


    Afin a2(19,27);
    cout << "decifrado: " << a2.descifrado("ehcb") << endl;

    return 0;
}
