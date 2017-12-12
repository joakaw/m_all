
#include "main_functions.h"
#include "main_structures.h"
#include "locks_controller.h"

#include "nrf_sdm.h"
#include "boards.h"

#include "log.h"

#include "simple_on_off_client.h"


#define CLIENT_COUNT        (SERVER_COUNT + 1)
#define GROUP_CLIENT_INDEX  (SERVER_COUNT)


static simple_on_off_client_t m_clients[CLIENT_COUNT];

/** Keeps a single global TID for all transfers. */
static uint8_t m_tid;


uint8_t repeats = 2;



static void message_handler(uint32_t button_number){



    uint32_t status = NRF_SUCCESS;
    switch (button_number)
    {
        case 0: 
          set_client_state(OPEN);
          status = send_open(&m_clients[GROUP_CLIENT_INDEX], 1);
          __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "send open to 1 server.\n");
          break;
        case 1:
          set_client_state(CLOSED);
          status = send_close(&m_clients[GROUP_CLIENT_INDEX], 1);
          __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "send close to 1 server.\n");
          break;
        case 2:
          set_client_state(OPEN);
          status = send_open(&m_clients[GROUP_CLIENT_INDEX], 2);
          __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "send open to 2 server.\n");
            break;
        case 3:
          set_client_state(CLOSED);
          status = send_close(&m_clients[GROUP_CLIENT_INDEX], 2);
          __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "send close to 2 server.\n");
            break;
        default:
            break;

    }

    if (status == NRF_ERROR_INVALID_STATE ||
        status == NRF_ERROR_NO_MEM ||
        status == NRF_ERROR_BUSY)
    {
        __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "Cannot send. Device is busy.\n");
        hal_led_blink_ms(LEDS_MASK, 50, 4);
    }
    else
    {
        ERROR_CHECK(status);
    }

 }


 uint32_t send_open(simple_on_off_client_t * p_client, uint16_t destination_id)
{
    message_main_t message_set_state;
    message_set_state.on_off = true;
    message_set_state.tid = m_tid++;
    message_set_state.destination_id = destination_id;

    access_message_tx_t message;
    message.opcode.opcode = SIMPLE_ON_OFF_OPCODE_SET_UNRELIABLE;
    message.opcode.company_id = ACCESS_COMPANY_ID_NORDIC;
    message.p_buffer = (const uint8_t*) &message_set_state;
    message.length = sizeof(message_set_state);

    uint32_t status = NRF_SUCCESS;
    for (uint8_t i = 0; i < repeats; ++i)
    {
        status = access_model_publish(p_client->model_handle, &message);
        if (status != NRF_SUCCESS)
        {
            break;
        }
    }
    return status;
}

uint32_t send_close(simple_on_off_client_t * p_client, uint16_t destination_id)
{
    message_main_t message_set_state;
    message_set_state.on_off = false;
    message_set_state.tid = m_tid++;
    message_set_state.destination_id = destination_id;

    access_message_tx_t message;
    message.opcode.opcode = SIMPLE_ON_OFF_OPCODE_SET_UNRELIABLE;
    message.opcode.company_id = ACCESS_COMPANY_ID_NORDIC;
    message.p_buffer = (const uint8_t*) &message_set_state;
    message.length = sizeof(message_set_state);

    uint32_t status = NRF_SUCCESS;
    
    for (uint8_t i = 0; i < repeats; ++i)
    {
        status = access_model_publish(p_client->model_handle, &message);
        if (status != NRF_SUCCESS)
        {
            break;
        }
    }
    return status;
}

static void set_client_state(enum lock_state state){

  set_lock_state(state);

}
