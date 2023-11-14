/*
** EPITECH PROJECT, 2023
** bsqv2
** File description:
** map_info
*/

#ifndef MAP_INFO_H_
    #define MAP_INFO_H_

    #include <sys/types.h>

typedef struct {
    char *map;
    size_t nb_lines;
    size_t nb_cols;
} map_info_t;

#endif /* !MAP_INFO_H_ */
