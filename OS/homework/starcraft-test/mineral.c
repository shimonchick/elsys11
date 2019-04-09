//
// Created by misho on 29/03/19.
//

#include "mineral.h"

int are_minerals_empty(int mineral_status[mineral_blocks_count]){
    for(int i = 0; i < mineral_blocks_count; i++){
        if(mineral_status[i] == 1){
            return 0;
        }
    }
    return 1;
}