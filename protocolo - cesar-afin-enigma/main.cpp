#include <iostream>
#include "protocolo.h"
#include "chechi.h"
#include "enigma2.0.h"
#include "afin.h"
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main()

{
    enigma2puntocero a("123YQUGFHER");
    cout<<a.cifrar("RZGSPLQGKNWGC");
    return 0;
}
