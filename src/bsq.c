/*
** EPITECH PROJECT, 2023
** bsqv2
** File description:
** bsq
*/

#include <bsq.h>

void mark_largest_square(char *map, size_t nb_cols, square_t largest_square)
{
    for (size_t i = largest_square.row; i < largest_square.row + largest_square.size; ++i)
        for (size_t j = largest_square.col; j < largest_square.col + largest_square.size; ++j)
            map[i * nb_cols + j] = 'x';
}

void print_map(char *map, long int nb_lines, size_t nb_cols)
{
    for (long int i = 0; i < nb_lines; ++i) {
        for (size_t j = 0; j < nb_cols; ++j)
            putchar(map[i * nb_cols + j]);
        putchar('\n');
    }
}

char *bufferize_map(FILE *fd, long int nb_lines, size_t nb_cols, size_t size)
{
    char *map = malloc(nb_lines * nb_cols + 1);
    char *buffer = NULL;

    if (map == NULL) {
        fclose(fd);
        dprintf(2, "Failed to allocate memory\n");
        return NULL;
    }

    map[nb_lines * nb_cols] = '\0';

    fseek(fd, 0, SEEK_SET);
    getline(&buffer, &size, fd);

    for (long int i = 0; i < nb_lines; ++i) {
        getline(&buffer, &size, fd);

        if (strlen(buffer) - 1 != nb_cols) {
            fclose(fd);
            free(buffer);
            free(map);
            dprintf(2, "Invalid number of columns\n");
            return NULL;
        }

        memcpy(map + i * nb_cols, buffer, nb_cols);
    }

    free(buffer);
    return map;
}

int bsq_solver(char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    char *buffer = NULL;
    size_t size = 0;

    if (fd == NULL) {
        perror("BSQ");
        return 84;
    }

    getline(&buffer, &size, fd);
    long int nb_lines = atoi(buffer);
    getline(&buffer, &size, fd);
    size_t nb_cols = nb_cols = strlen(buffer) - 1;

    if (nb_lines <= 0 || nb_cols <= 0) {
        fclose(fd);
        dprintf(2, "Invalid number of lines or columns\n");
        return 84;
    }

    char *map = bufferize_map(fd, nb_lines, nb_cols, size);

    if (map == NULL)
        return 84;

    fclose(fd);
    free(buffer);

    square_t result = find_largest_square(map, nb_lines, nb_cols);

    if (result.size > 0)
        mark_largest_square(map, nb_cols, result);
    print_map(map, nb_lines, nb_cols);
    free(map);

    return 0;
}

int bsq(int ac, char **av)
{
    if (ac != 2)
        return (84);
    else if (access(av[1], F_OK | R_OK) == -1) {
        perror("BSQ");
        return (84);
    } else
        return (bsq_solver(av[1]));
    return (0);
}
