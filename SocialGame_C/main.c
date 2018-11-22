#include <stdio.h>
#include <assert.h>
#include "decision.h"
#include "players/naive.h"
#include "players/tricker.h"
#include "players/philosopher.h"

const int N = 20;

int main() {
    char choice_a[N], choice_b[N], a, b;
    enum Decision (*f[3])(int, char *, char *);
    f[0] = &naive;
    f[1] = &tricker;
    f[2] = &philosopher;

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int sa = 0, sb = 0;
            for (int k = 0; k < N; k++) {
                a = f[i](k, choice_a, choice_b);
                b = f[j](k, choice_b, choice_a);
                assert(a == COOPERATION || a == BETRAYAL);
                assert(b == COOPERATION || b == BETRAYAL);
                choice_a[k] = a;
                choice_b[k] = b;

                if (a == COOPERATION && b == COOPERATION) {
                    sa += 3;
                    sb += 3;
                } else if (a == COOPERATION && b == BETRAYAL) {
                    sa += 0;
                    sb += 5;
                } else if (a == BETRAYAL && b == COOPERATION) {
                    sa += 5;
                    sb += 0;
                } else {
                    sa += 1;
                    sb += 1;
                }
            }
            printf("%s:%s\n", choice_a, choice_b);
            printf("%d:%d\n", sa, sb);
        }
    }


    return 0;
}