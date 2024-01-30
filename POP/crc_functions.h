#include<iostream>
#include <math.h>
#include <cstring>
#include <new>

using namespace std;

namespace crc_name_space
{

int xor_function(int a, int b);                                      // 1-bitna XOR operacija

int* poly_division(const int*, const int*, int, int);

void crc_encode(int*, const int*, int, int);

int check_sum(int*, const int*, int, int);


template <class T>
void shift_and_copy_array (const T, T, int, int);        // obrazac funkcije koja radi pomeranje i kopiranje jednog niza u drugi, pri čemu nizovi mogu biti proizvoljnog tipa 

}