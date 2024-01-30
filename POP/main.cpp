
#include "platform.h"


int main(int argc, char *argv[])
{

int* inform_stream;
int* frames;
int* sent_frames;
int num_failures;
int num_frames; 
int total_frames_length;

int padding;

padding = (PAYLOAD_SIZE - (SOURCE_LENGTH % PAYLOAD_SIZE)) % PAYLOAD_SIZE; 

num_frames = ceil(SOURCE_LENGTH/PAYLOAD_SIZE);

total_frames_length = num_frames*crc_length+SOURCE_LENGTH+padding;

// alokacija memorije za nizove frejmova
inform_stream = new int[SOURCE_LENGTH+padding];

frames = new int[total_frames_length];
sent_frames = new int[total_frames_length];


// simulacija prenosa za sve kanale
for(int i=0;i<num_Of_channels;i++)
{
  generate_inform_stream(inform_stream, padding); 


  generate_frames(inform_stream, frames,num_frames);

  crc_name_space::shift_and_copy_array<int*>(frames, sent_frames, 0, total_frames_length);

  bsc_channel(frames, bsc_error_prob_array[i],total_frames_length);

  num_failures = decode_frames(frames,num_frames);

  if(num_failures<num_frames)
    print_transmission_statistic(sent_frames, frames, bsc_error_prob_array[i],num_frames);
  else
  {
    print_transmission_statistic(bsc_error_prob_array[i],num_frames);  // preklapanje imena funkcije

  }

}
 
    return 0;
}