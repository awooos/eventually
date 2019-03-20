#include <eventually.h>
#include <stdint.h>
#include <stdio.h>
#include <stdnoreturn.h>
#include <string.h>
#include <tinker.h>

void add_eventually_tests(void);

noreturn void _panic(const char *message, const char *function,
        const char *filename, size_t line)
{
    // loosely copy Rust's panic message format.
    fprintf(stderr, "function '%s' panicked at '%s', %s:%zu\n", function, message, filename, line);
    exit(1);
}

int main(void)
{
    add_eventually_tests();

    //eventually_init(&_panic);

    bool success = tinker_run_tests(&putchar);

    return (success ? 0 : 1);
}
