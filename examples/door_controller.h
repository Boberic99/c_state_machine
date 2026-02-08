#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include "../include/fsm.h"

#define TABLE_SIZE 8
#define DOOR_INIT_STATE 0

typedef enum {
    DOOR_CLOSED = 0,
    DOOR_OPEN = 1,
    DOOR_LOCKED = 2,
    DOOR_INVALID = 3
}door_state_t;

typedef enum{
    EVT_OPEN_BUTTON = 0,
    EVT_CLOSE_BUTTON,
    EVT_LOCK_BUTTON,
    EVT_UNLOCK_BUTTON,
    EVT_INVALID
}door_event_t;

typedef struct {
    door_state_t state;
}door_sensor_t;

fsm_status_t sensor_init(door_sensor_t* sensor, door_state_t initial_state){
    fsm_status_t status = FSM_OK;
    if (sensor == NULL){
        return FSM_ERROR_INVALID_ARG;
    } else {
        sensor->state = initial_state;
        return status;
    }
}

/* Simulation of reading a door sensor */
static door_state_t get_sensor_state(door_sensor_t *sensor){
    if (sensor == NULL){
        return DOOR_INVALID;
    } else{
        return sensor->state;
    }
}

/* Simulate giving command to close the door */
static fsm_status_t lock_the_door(door_sensor_t* door_sensor){

    if (door_sensor == NULL){
        return FSM_ERROR_INVALID_ARG;
    } else {
        door_sensor->state = DOOR_LOCKED;
        return FSM_OK;
    }
}

/* Simulate giving command to unlock the door */
static fsm_status_t unlock_the_door(door_sensor_t* door_sensor){

    if (door_sensor == NULL){
        return FSM_ERROR_INVALID_ARG;
    } else {
        door_sensor->state = DOOR_CLOSED;
        return FSM_OK;
    }
}

/* Simulate giving command to open the door */
fsm_status_t open_the_door(door_sensor_t* door_sensor){
    /* Simulate giving command to close the door */
    if (door_sensor == NULL){
        return FSM_ERROR_INVALID_ARG;
    } else {
        door_sensor->state = DOOR_OPEN;
        return FSM_OK;
    }
}

/* Simulate giving command to close the door */
static fsm_status_t close_the_door(door_sensor_t* door_sensor){
    /* Simulate giving command to close the door */
    if (door_sensor == NULL){
        return FSM_ERROR_INVALID_ARG;
    } else {
        door_sensor->state = DOOR_CLOSED;
        return FSM_OK;
    }
}

/* Callback function before door changes state */
fsm_status_t door_callback(void *user_ctx,
                        fsm_event_t event,
                        fsm_state_t from,
                        fsm_state_t to){

    fsm_status_t status = FSM_OK;
    if (user_ctx == NULL){
        return FSM_ERROR_INVALID_ARG;
    }

    if ((from < 0) || (from > 2)){
        printf("Door found in invalid state!\n");
        return FSM_ERROR_INVALID_ARG;
    } else if((to < 0) || (to > 2)){
        printf("Can't change door to invalid state!\n");
        return FSM_ERROR_INVALID_ARG;
    }
    switch(event){
        case EVT_OPEN_BUTTON: {
            if(get_sensor_state((door_sensor_t*)user_ctx) == DOOR_CLOSED){
                /* Open the door */
                status = open_the_door((door_sensor_t*)user_ctx);
                return status;
            }else {
                return FSM_ERROR_ACTION_FAILED;
                
            }
        }
        case EVT_CLOSE_BUTTON:{
            if(get_sensor_state((door_sensor_t*)user_ctx) == DOOR_OPEN){
                /* Close the door */
                status = close_the_door((door_sensor_t*)user_ctx);
                return status;
            }else {
                return FSM_ERROR_ACTION_FAILED;
                
            }
        }
        case EVT_LOCK_BUTTON:{
            if(get_sensor_state((door_sensor_t*)user_ctx) == DOOR_CLOSED){
                /* Lock the door */
                status = lock_the_door((door_sensor_t*)user_ctx);
                return status;
            }else {
                return FSM_ERROR_ACTION_FAILED;
                
            }
        }
        case EVT_UNLOCK_BUTTON:{
            if(get_sensor_state((door_sensor_t*)user_ctx) == DOOR_LOCKED){
                /* Unlock the door */
                status = unlock_the_door((door_sensor_t*)user_ctx);
                return status;
            }else {
                return FSM_ERROR_ACTION_FAILED;
            }
        }
        case EVT_INVALID:{
            return FSM_ERROR_INVALID_TRANSITION;
        }
        default:{
            return FSM_ERROR_ACTION_FAILED;
        }
            
    }

    return status;
}

#endif // DOOR_CONTROLLER_H