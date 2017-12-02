
#ifndef MAIN_FUNCTIONS_H__
#define MAIN_FUNCTIONS_H__

#include <stdint.h>
#include "simple_on_off_client.h"


static void button_handler(uint32_t button_number);

uint32_t send_open(simple_on_off_client_t * p_client, uint16_t destination_id);
uint32_t send_close(simple_on_off_client_t * p_client, uint16_t destination_id);


#endif
