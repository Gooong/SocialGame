//
// Created by gongxr on 18-11-22.
//

#ifndef SOCIALGAME_PHILOSOPHER_H
#define SOCIALGAME_PHILOSOPHER_H


#include <time.h>
#include <stdlib.h>
#include "../decision.h"

enum Decision philosopher(int len, char* my_decisions, char* the_decisions){
    srand((unsigned)time(NULL) + len);
    int r = rand();
    if (r % 2 == 0){
        return COOPERATION;
    }
    else{
        return BETRAYAL;
    }
}

#endif //SOCIALGAME_PHILOSOPHER_H
