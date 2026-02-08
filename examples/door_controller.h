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

/* Initialize door sensor */
fsm_status_t sensor_init(door_sensor_t* sensor, door_state_t initial_state);

/* Simulate giving command to open the door */
fsm_status_t open_the_door(door_sensor_t* door_sensor);

/* Callback function before door changes state */
fsm_status_t door_callback(void *user_ctx,
                        fsm_event_t event,
                        fsm_state_t from,
                        fsm_state_t to);

#endif // DOOR_CONTROLLER_H