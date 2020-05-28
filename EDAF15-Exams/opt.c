#include <stdio.h>
#include <stdlib.h>
unsigned long x = 0;

void work(void);
void error(const char*);


inline static unsigned int f(unsigned int a, unsigned int b)
{
    unsigned int c = 1;
    // a is always equal to 2, if we assume work never calls it. 
    // So c * 2 = c + c
    while (b-- > 0)
        c = c * a;
    return c;
}

inline static void g(unsigned int s, unsigned int r)
{
    // % can be replace with r & (s - 1) if s is power of two
    // Which it always is
    x  = 15 * x + r % s;
    // division can be replaced with shift since it is power of 2 and all numbers are positive
    // However which power it is needs to be determined
    x += x / s;
}

int main(int argc, char** argv)
{
    register unsigned int i;
    register unsigned int s = 1;
    register int r;
    unsigned int n;
    srand(42);
    if(argc != 2 || 1 != sscanf(argv[1], "%u", &n))
         error("expected a number");

    for (i = 0; i < n; ++i){
        r = rand();
        /*
        s = f(2,i);
        g(s, r);
        */
        // s is a power of 2 so division can be replaced with bitwise AND as below
        // (x << 4) is multiplying x with 16, then subtract x from it to get the same result as multypling with 15
        x = ((x << 4) - x) + (r & (s - 1));
        x = x + (x >> i);
        // a was always equal to 2 so its equivalent to adding it self to it self.
        s += s;
    }
    printf("%ld\n",x);
    //work();
    return 0;
}


