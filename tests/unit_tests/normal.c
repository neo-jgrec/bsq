#include <criterion/criterion.h>
#include <criterion/redirect.h>

int bsq(int ac, char **av);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(bsq, normal, .init = redirect_all_std) {
    char *av[] = {"./bsq", "tests/unit_tests/maps/normal_map"};
    int ac = 2;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 0);
}

Test(bsq, help, .init = redirect_all_std) {
    char *av[] = {"./bsq", "-h"};
    int ac = 2;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 0);
}
