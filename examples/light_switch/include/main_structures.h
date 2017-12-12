#ifndef MAIN_STRUCTURES_H__
#define MAIN_STRUCTURES_H__

#include <stdint.h>

/*message structure*/

typedef struct __attribute((packed))
{
    uint16_t destination_id;      /**< Destination ID. */
    uint8_t on_off;               /**< State to set. */
    uint8_t tid;                  /**< Transaction number. */
    
} message_main_t;

enum lock_state {OPEN, CLOSED};

#endif