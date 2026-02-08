#include "../include/fsm.h"


fsm_status_t fsm_init(fsm_t *fsm,
                        const fsm_transition_t *table,
                        size_t table_size,
                        fsm_state_t initial_state,
                        void *user_ctx){

    /* Table is read-only and owned by caller */
    if ((table == NULL) || (table_size <= 0) || (fsm == NULL)){
        return FSM_ERROR_INVALID_ARG;
    } else{
        fsm->current = initial_state;
        fsm->table = table;
        fsm->table_size = table_size;
        fsm->user_ctx = user_ctx;
    }
    
    return FSM_OK;
}

fsm_status_t fsm_handle_event(fsm_t* fsm,
                        fsm_event_t event,
                        fsm_state_t *out_new_state){
    fsm_status_t status = FSM_OK;

    if ((fsm == NULL) || (fsm->table == NULL) || (fsm->table_size <= 0)) {
        return FSM_ERROR_INVALID_ARG;
    }
    for(size_t i = 0; i < fsm->table_size; i++){
        if (fsm->table[i].from == fsm->current &&
            fsm->table[i].event == event){
                /* Matching transition found */
                if (fsm->table[i].action != NULL){
                    status = fsm->table[i].action(fsm->user_ctx, event, 
                        fsm->table[i].from, fsm->table[i].to);
                        if (status == FSM_OK) {
                            fsm->current = fsm->table[i].to;
                            if (out_new_state != NULL){
                                *out_new_state = fsm->table[i].to;
                            }
                            return status;
                        } else{
                            /* Error occured during transition */
                            return status;
                        }
                }

        }
    }
    /* No matching transition found */   
    return FSM_ERROR_INVALID_TRANSITION;
}

fsm_state_t fsm_get_state(const fsm_t *fsm){
    return fsm == NULL ? FSM_ERROR_INVALID_ARG : fsm->current; 
}

fsm_status_t fsm_reset(fsm_t *fsm, fsm_state_t initial_state){
    if (fsm == NULL) {
        return FSM_ERROR_INVALID_ARG;
    } else{
        fsm->current = initial_state;
        return FSM_OK;
    }
}