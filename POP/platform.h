#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "crc_functions.h"

//////* Specificiranje parametara simulacije *////////

// izvor informacija
#define PROB_0_TO_1 0.2 // verovatnoće promene stanja izvora
#define PROB_1_TO_0 0.5
#define SOURCE_LENGTH 100000

// parametri protokola
#define PAYLOAD_SIZE 10  // veličina informacionog dela frejma

const int crc_gen_poly[] = {1,0,0,1,1}; // prvi element predstavlja koeficijent uz najveći stepen generišućeg polinoma CRC koda
const int crc_length = sizeof(crc_gen_poly)/sizeof(int);

// komunikacioni kanal
const float bsc_error_prob_array[] = {0,0.01,0.05,0.075, 0.1}; 
const int num_Of_channels = sizeof(bsc_error_prob_array)/sizeof(float);


// funkcije koje se obavljaju u platformi za simulaciju

void generate_inform_stream(int*, int); // binarni izvor s memorijom prvog reda

void generate_frames(const int*, int*, int);  // generisanje niza frejmova

void bsc_channel(int*, float, int);    // prolazak frejmova kroz kanal

int decode_frames(int*, int);   // funkcija vraća indekse frejmova koji su prošli CRC proveru

void print_transmission_statistic(const int*, const int*, float, int); // ispisivanje statistike na standardni izlaz (slučaj 1)

void print_transmission_statistic(float, int); // ispisivanje statistike na standardni izlaz (slučaj 2)





