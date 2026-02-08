#include "../examples/door_controller.h"

int main(){
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
    fsm_state_t new_state;

    status = sensor_init(&door_sensor, DOOR_INIT_STATE);
    if (status != FSM_OK){
        printf("Sensor Initiation resulted in error:%d !\n",status);
        return -1;
    }
    status = fsm_init(&door_fsm, table, TABLE_SIZE, DOOR_INIT_STATE, &door_sensor);
    if (status != FSM_OK){
        printf("FSM Initiation resulted in error:%d !\n",status);
        return -1;
    }

    /* Test fsm_handle_event() */
    {
        /* Open the door */
        status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_OPEN_BUTTON, NULL);
        if (status != FSM_OK){
            printf("Error occured while changing state of the door: %d\n",status);
        }
        if (door_fsm.current != DOOR_OPEN){
            printf("Test for fsm_handle_event() failed!\n");
            return -1;
        }
    }
    /* Test invalid trasition */
    {
        status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_INVALID, NULL);
        if ((status == FSM_OK) || (door_fsm.current != DOOR_OPEN)){
            printf("Test for invalid transition failed!\n");
            return -1;
        }
    }
    /* Test invalid argument */
    {
        status = fsm_handle_event(NULL, (fsm_event_t)EVT_LOCK_BUTTON, NULL);
        if (status != FSM_ERROR_INVALID_ARG){
            printf("Test for invalid argument failed!\n");
            return -1;
        }
    }
    /* Test invalid action */
    {
        status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_LOCK_BUTTON, NULL);
        if ((status == FSM_OK) || (door_fsm.current != DOOR_OPEN)){
            printf("Test for invalid action failed!\n");
            return -1;
        }
    }
    /* Test out_new_state */
    {
        status = fsm_handle_event(&door_fsm, (fsm_event_t)EVT_CLOSE_BUTTON, &new_state);
        if ((status != FSM_OK) || (new_state != DOOR_CLOSED)){
            printf("Test for out_new_state failed!\n");
            return -1;
        }
    }
    /* Test fsm_reset() */
    {
        status = fsm_reset(&door_fsm, DOOR_CLOSED);
        if ((status != FSM_OK) || (door_fsm.current != DOOR_CLOSED)){
            printf("Test for fsm_reset() failed!\n");
            return -1;
        }
    }
    printf("ALL TEST PASSED\n");

    return 0;
}