/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** free_map.c
*/

#include "wolf.h"

/**
 * @brief Libère les lignes allouées de la map en cas d'erreur
 * @param map Pointeur vers la map
 * @param nb_lines Nombre de lignes à libérer
 */
void free_map_lines(int **map, int nb_lines)
{
    for (int j = 0; j < nb_lines; j++)
        free(map[j]);
    free(map);
}

/**
 * @brief Libère la map entière
 * @param map Pointeur vers la map
 */
void free_map(int **map)
{
    if (!map)
        return;
    for (int i = 0; i < MAP_HEIGHT; i++)
        free(map[i]);
    free(map);
}
