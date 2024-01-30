
#include "crc_functions.h"

int crc_name_space::xor_function(int a, int b)                                      // 1-bitna XOR operacija
{
    if(a==b)
        return 0;
    else
        return 1;
}

int* crc_name_space::poly_division(const int dividend[], const int divisor[], int dividend_len, int divisor_len)
{
    int* rem;
    rem = new int[divisor_len];

    int* temp;                            //pomoći pokazivač koji pokazuje na tekući rezultat deljenja
    temp = new int[divisor_len];
    
    for(int i=0;i<divisor_len;i++)
        rem[i]=dividend[i];                    //ostatak pri deljenju se inicijalizuje na deljenik

    for(int j=divisor_len;j<=dividend_len;j++)
    {

        crc_name_space::shift_and_copy_array<int*>(rem, temp, 0, divisor_len);

        if(rem[0]==0)                // ako je naveći stepen tekućeg ostatka '0' preskače se jedan stepen deljenja 
        {
            crc_name_space::shift_and_copy_array<int*>(temp,rem, 1, divisor_len-1);

        
        }
        else                    // u suprotnom se vrši XOR operacija tekućeg ostatka i deljenika
        {    
            for(int i=0;i<divisor_len-1;i++)
                rem[i]=crc_name_space::xor_function(temp[i+1],divisor[i+1]);
            
        }
        if(j!=dividend_len)
            rem[divisor_len-1]=dividend[j];        //dodaje se sledeći bit deljenika
       else
            rem[divisor_len-1]=0;
    }

    delete[] temp;

return rem;
}

void crc_name_space::crc_encode(int data[], const int gen_poly[], int gen_poly_len, int data_len)
{
     
    for(int i=0;i<gen_poly_len-1;i++)                //informacioni frejm se dopunja nulama
        data[data_len+i]=0;
    
   
    int* rem;

   rem =  crc_name_space::poly_division(data, gen_poly, data_len+gen_poly_len-1,gen_poly_len);

    for(int i=0;i<gen_poly_len-1;i++)
        data[data_len+i]=rem[i];                // CRC dodatak se lepi na kraj frejma

    delete[] rem;

}

int crc_name_space::check_sum(int data[], const int gen_poly[], int gen_poly_len, int data_len)
{

   
    int flag = 0;

    int* rem;

    rem = crc_name_space::poly_division(data, gen_poly, data_len+gen_poly_len-1,gen_poly_len);

     for(int i=0;i<gen_poly_len-1;i++)
        data[data_len+i]=rem[i];  
    
    for (int i=0; i<gen_poly_len-1; i++)
    {
        if(rem[i]!=0) 
        {
            flag = 1;
            break;
        }
    }

    delete[] rem;

return flag;
}


template <class T>
void crc_name_space::shift_and_copy_array (const T orig_array, T new_array, int shift, int new_array_length)
{

    for(int i=0;i<new_array_length;i++)
                new_array[i]=orig_array[i+shift];
}

