/*
** EPITECH PROJECT, 2023
** bsqv2
** File description:
** find_largest_square
*/

#include <bsq.h>
#include <map_info.h>

static int count_obstacles(map_info_t mapInfo, square_t square)
{
    if (square.row + square.size > mapInfo.nb_lines
        || square.col + square.size > mapInfo.nb_cols)
        return 1;

    for (size_t i = square.row; i < square.row + square.size; ++i)
        for (size_t j = square.col; j < square.col + square.size; ++j)
            if (mapInfo.map[i * mapInfo.nb_cols + j] == 'o')
                return 1;

    return 0;
}

static size_t find_square_size(map_info_t mapInfo, size_t i, size_t j)
{
    size_t size = 0;
    int total_obstacles = 0;
    size_t max_size = (mapInfo.nb_lines - i < mapInfo.nb_cols - j)
        ? mapInfo.nb_lines - i
        : mapInfo.nb_cols - j;

    while (size + 1 <= max_size) {
        ++size;
        total_obstacles = count_obstacles(mapInfo, (square_t){i, j, size});
        if (total_obstacles != 0) {
            --size;
            break;
        }
    }

    return size;
}

square_t find_largest_square(char *map, size_t nb_lines, size_t nb_cols)
{
    map_info_t mapInfo = {map, nb_lines, nb_cols};
    square_t largest_square = {0, 0, 0};
    size_t size = 0;

    for (size_t i = 0; i < mapInfo.nb_lines; ++i) {
        for (size_t j = 0; j < mapInfo.nb_cols; ++j) {
            size = find_square_size(mapInfo, i, j);
            largest_square = (size > largest_square.size) ? (square_t){i, j, size} : largest_square;
        }
    }

    return largest_square;
}
