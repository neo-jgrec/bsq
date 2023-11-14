/*
** EPITECH PROJECT, 2023
** bsqv2
** File description:
** bsq
*/

#ifndef BSQ_H_
    #define BSQ_H_

    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>

typedef struct {
    long int row;
    size_t col;
    size_t size;
} square_t;

square_t find_largest_square(char *map, size_t nb_lines, size_t nb_cols);

int bsq(int ac, char **av);

#endif /* !BSQ_H_ */
