#include "locks_controller.h"
#include "main_structures.h"
#include "nrf_gpio.h"

#define LED_EXTERNAL 29

void set_lock_state(enum lock_state state){

  if(state == OPEN){
    nrf_gpio_pin_set(LED_EXTERNAL);
  }
  else if(state == CLOSED){
    nrf_gpio_pin_clear(LED_EXTERNAL);
  }

}


