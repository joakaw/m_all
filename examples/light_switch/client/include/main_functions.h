
#ifndef MAIN_FUNCTIONS_H__
#define MAIN_FUNCTIONS_H__

#include <stdint.h>
#include "simple_on_off_client.h"
#include "locks_controller.h"


<<<<<<< HEAD
static void message_handler(uint8_t action, uint8_t door_number);
=======
static void message_handler(uint32_t button_number);
>>>>>>> 62b668b5be013284a380a9de3fe4b637b3aca6ee
static void set_client_state(enum lock_state state);

uint32_t send_open(simple_on_off_client_t * p_client, uint16_t destination_id);
uint32_t send_close(simple_on_off_client_t * p_client, uint16_t destination_id);


#endif
