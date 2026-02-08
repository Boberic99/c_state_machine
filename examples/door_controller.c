#include "door_controller.h"


int main() {
    fsm_status_t status = FSM_OK;

    const fsm_transition_t table[8] = {
        {
            .event = EVT_OPEN_BUTTON,
            .action = door_callback,
            .from = DOOR_CLOSED,
            .to = DOOR_OPEN
        },
        {
            .event = EVT_CLOSE_BUTTON,
            .action = door_callback,
            .from = DOOR_OPEN,
            .to = DOOR_CLOSED
        },
        {
            .event = EVT_LOCK_BUTTON,
            .action = door_callback,
            .from = DOOR_CLOSED,
            .to = DOOR_LOCKED
        },
        {
            .event = EVT_UNLOCK_BUTTON,
            .action = door_callback,
            .from = DOOR_LOCKED,
            .to = DOOR_CLOSED
        },
    };

    fsm_t door_fsm;
    door_sensor_t door_sensor;
    /* Initialize door sensor */
    status = sensor_init(&door_sensor, DOOR_INIT_STATE);
    if (status != FSM_OK){
        printf("Sensor Initiation resulted in error:%d !\n",status);
        return -1;
    }

    /* Initialize door fsm */
    status = fsm_init(&door_fsm, table, TABLE_SIZE, DOOR_INIT_STATE, &door_sensor);
    if (status != FSM_OK){
        printf("FSM Initiation resulted in error:%d !\n",status);
        return -1;
    }

    /* Lock the door */
    status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_LOCK_BUTTON, NULL);
    if (status != FSM_OK){
        printf("Error occured while changing state of the door: %d\n",status);
    }
    printf("Door changed to state: %d\n", door_fsm.current);

    /* Unlock the door */
    status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_UNLOCK_BUTTON, NULL);
    if (status != FSM_OK){
        printf("Error occured while changing state of the door: %d\n",status);
    }
    printf("Door changed to state: %d\n", door_fsm.current);

    /* Open the door */
    status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_OPEN_BUTTON, NULL);
    if (status != FSM_OK){
        printf("Error occured while changing state of the door: %d\n",status);
    }
    printf("Door changed to state: %d\n", door_fsm.current);

    /* Close the door */
    status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_CLOSE_BUTTON, NULL);
    if (status != FSM_OK){
        printf("Error occured while changing state of the door: %d\n",status);
    }
    printf("Door changed to state: %d\n", door_fsm.current);

    return 0;
}