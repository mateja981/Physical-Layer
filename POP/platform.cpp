#include "platform.h"


void generate_inform_stream(int inform_stream[], int padding) // binarni izvor s memorijom prvog reda
{
    float random_number;
    int source_state = 0;
    srand(time(nullptr));                // podesiti seed slučajnog generatora na osnovu trenutnog vremena; srand(const) omogućava ponovljivost niza slučajnog brojeva 

    for (int i=0;i<SOURCE_LENGTH+padding;i++)
    {
        random_number = float(rand())/RAND_MAX;

        switch (source_state)
        {
        case 0:
            source_state = 1-int(random_number>PROB_0_TO_1);
            inform_stream[i]=source_state;
            break;
  
        default: 
            source_state = 1-int(random_number<PROB_1_TO_0);
            inform_stream[i]=source_state;
        }
    }

}

void generate_frames(const int inform_stream[], int frames[], int num_frames)
{
    int* temp_frame;
    temp_frame = new int[PAYLOAD_SIZE+crc_length];
    

   for(int i=0;i<num_frames;i++)
   {

     for(int j=0;j<PAYLOAD_SIZE;j++)
     {
        temp_frame[j]=inform_stream[i*PAYLOAD_SIZE+j];
     }

    crc_name_space::crc_encode(temp_frame,crc_gen_poly,crc_length,PAYLOAD_SIZE);                    // kodovanje CRC kodom

    for(int j=0;j<PAYLOAD_SIZE+crc_length;j++)
     {
        frames[i*(PAYLOAD_SIZE+crc_length)+j]=temp_frame[j];    // kopiranje privremenog frejma u izlazni niz frejmova
     }

   }
   delete[] temp_frame;
}

void bsc_channel(int frames[], float channel_rate, int total_frames_length)
{
    float random_number;

    srand(time(nullptr));                // podesiti seed slučajnog generatora na osnovu trenutnog vremena; srand(const) omogućava ponovljivost niza slučajnog brojeva 

    for (int i=0;i<total_frames_length;i++)
    {
        random_number = float(rand())/RAND_MAX;
        
        if(random_number<channel_rate)
            frames[i] = crc_name_space::xor_function(frames[i],1); 
    }  
}

int decode_frames(int frames[], int num_frames)
{    
    int num_failures = 0;               // broj frejmova za koje se zahteva retransmisija
    int flag;
    int* temp_frame;

    temp_frame = new int[PAYLOAD_SIZE+crc_length];

    for (int i=0;i<num_frames;i++)
    {
        for (int j=0;j<PAYLOAD_SIZE+crc_length;j++)
        {
            temp_frame[j] = frames[i*(PAYLOAD_SIZE+crc_length)+j];
        }
        
        flag = crc_name_space::check_sum(temp_frame, crc_gen_poly,crc_length,PAYLOAD_SIZE);
        num_failures = num_failures + flag;

        if(flag==1)   // brisanje pogrešno primljenih frejmova
        {
            for (int j=0;j<PAYLOAD_SIZE+crc_length;j++) 
                frames[i*(PAYLOAD_SIZE+crc_length)+j]=2;
        }  

    }
    
    delete[] temp_frame;

    return num_failures;
}

void print_transmission_statistic(const int sent_frames[], const int received_frames[], float channel_rate, int num_frames)
{
    int undetecded_failures = 0;
    int detecded_failures = 0;


    for (int i=0;i<num_frames;i++)
    {
        if(received_frames[i*(PAYLOAD_SIZE+crc_length)]!=2)
        {

            for (int j=0;j<PAYLOAD_SIZE;j++) 
            {
                if(received_frames[i*(PAYLOAD_SIZE+crc_length)+j]!=sent_frames[i*(PAYLOAD_SIZE+crc_length)+j])
                { 
                    undetecded_failures ++;
                    break;
                }
            }
  
        }
        else 
            detecded_failures ++;
    }

    cout<< "----------------------------------"<< endl;
    cout<< "Verovatnoca greske u kanalu: "<< channel_rate << endl;
    cout<< "----------------------------------"<< endl;
    cout<< "Broj poslatih paketa: "<< num_frames << endl;
    cout<< "Broj paketa sa detektovanom greskom: "<< detecded_failures << endl;
    cout<< "Broj paketa sa nedetektovanom greskom: "<< undetecded_failures << endl;

}

void print_transmission_statistic( float channel_rate, int num_frames)
{
    cout<< "----------------------------------"<< endl;
    cout<< "Verovatnoca greske u kanalu: "<< channel_rate << endl;
    cout<< "----------------------------------"<< endl;
    cout<< "Broj poslatih paketa: "<< num_frames << endl;
    cout<< "Broj paketa sa detektovanom greskom: "<< num_frames << endl;
}
