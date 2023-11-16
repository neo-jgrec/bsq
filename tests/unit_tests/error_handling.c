#include <criterion/criterion.h>
#include <criterion/redirect.h>

int bsq(int ac, char **av);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(bsq_error_handling, no_args, .init = redirect_all_std) {
    char *av[] = {"./bsq"};
    int ac = 1;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 84);
}

Test(bsq_error_handling, no_line_nb, .init = redirect_all_std) {
    char *av[] = {"./bsq", "tests/unit_tests/no_line_nb"};
    int ac = 2;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 84);
}

Test(bsq_error_handling, unamatch_columns, .init = redirect_all_std) {
    char *av[] = {"./bsq", "tests/unit_tests/unamatch_columns"};
    int ac = 2;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 84);
}

Test(bsq_error_handling, wrong_file, .init = redirect_all_std) {
    char *av[] = {"./bsq", "/dev/random"};
    int ac = 2;
    int ret = bsq(ac, av);

    cr_assert_eq(ret, 84);
}

