/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** init_player.c
*/

#include "wolf.h"

/**
 * @brief Initialise un joueur à 0
 * @return Renvoie la structure du joueur initialisée à 0
 */
player_t *init_player(void)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return NULL;
    player->x = 1.5;
    player->y = 1.5;
    player->dx = -1.0;
    player->dy = 0.0;
    player->planeX = 0.0;
    player->planeY = 0.66;
    player->speed = 0.025;
    player->life = 3;
    player->w = init_weapon();
    if (!player->w)
        return free(player), NULL;
    player->score = 0;
    player->light_intensity = 1.0f;
    player->flashlight_on = 0;
    return player;
}
