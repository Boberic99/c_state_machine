#ifndef FSM_H
#define FSM_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t fsm_state_t;
typedef int32_t fsm_event_t;

/* Status/Error codes */
typedef enum {
    FSM_OK = 0,
    FSM_ERROR_INVALID_ARG = -1,
    FSM_ERROR_NOT_INITIALIZED = -2,
    FSM_ERROR_INVALID_TRANSITION = -3,
    FSM_ERROR_ACTION_FAILED = -4,
    FSM_OUT_OF_MEMORY = -5,
} fsm_status_t;

typedef fsm_status_t (*fsm_action_t)(void *user_ctx,
                                    fsm_event_t event,
                                    fsm_state_t from,
                                    fsm_state_t to);

typedef struct {
        fsm_state_t from;
        fsm_state_t to;
        fsm_event_t event;
        fsm_action_t action;
} fsm_transition_t;


/* FSM Instance */
typedef struct {
        fsm_state_t current;
        const fsm_transition_t *table;
        size_t table_size;
        void *user_ctx;
} fsm_t;

/* Public API */
fsm_status_t fsm_init(fsm_t *fsm,
                        const fsm_transition_t *table,
                        size_t table_size,
                        fsm_state_t initial_state,
                        void *user_ctx);

fsm_status_t fsm_handle_event(fsm_t* fsm,
                        fsm_event_t event,
                        fsm_state_t *out_new_state);

/* Querry current state */
fsm_status_t fsm_get_state(const fsm_t *fsm, fsm_state_t *out_state);

/* Reset to initial state */
fsm_status_t fsm_reset(fsm_t *fsm, fsm_state_t initial_state);

#ifdef __cplusplus
}
#endif

#endif //FSM_H