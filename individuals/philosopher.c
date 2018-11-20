#include <time.h>
#include <stdlib.h>

enum Decision{
    COOPERATION = 'c',
    BETRAYAL = 'b',
};

enum Decision decide(int len, char* my_decisions, char* the_decisions){
    srand((unsigned)time(NULL) + len);
    int r = rand();
    if (r % 2 == 0){
        return COOPERATION;
    }
    else{
        return BETRAYAL;
    }
}