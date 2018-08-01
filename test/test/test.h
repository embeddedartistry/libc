#include <stdint.h>
#include <stdlib.h>

void test_randseed(uint64_t s);
uint64_t test_randn(uint64_t n);
uint64_t test_randint(uint64_t a, uint64_t b);
void test_shuffle(uint64_t* p, size_t n);
void test_randrange(uint64_t* p, size_t n);
int t_choose(uint64_t n, size_t k, uint64_t* p);
