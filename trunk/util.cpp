#include "util.h"

void print_short_array(short *a, size_t a_length) {
    for(unsigned int i = 0; i < a_length; i++)
        cout << a[i] << " " ;
    cout << endl;
}
