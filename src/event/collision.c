/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** collision.c
*/

#include "wolf.h"

int for_loop(app_t *app, float newX, float newY, int offsetY)
{
    int baseX = (int)newX;
    int baseY = (int)newY;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    int mapX = 0;
    int mapY = 0;

    for (int offsetX = -1; offsetX <= 1; offsetX++) {
        mapX = baseX + offsetX;
        mapY = baseY + offsetY;
        if (mapX < 0 || mapY < 0 || mapX >= MAP_WIDTH || mapY >= MAP_HEIGHT)
            continue;
        deltaX = fabsf(newX - mapX - 0.5f);
        deltaY = fabsf(newY - mapY - 0.5f);
        if (app->g->map[mapY][mapX] > 0 &&
            deltaX < 0.5f + WALL_DISTANCE &&
            deltaY < 0.5f + WALL_DISTANCE)
            return 1;
    }
    return 0;
}

int player_will_collide(app_t *app, float newX, float newY)
{
    float deltaX = 0.0f;
    float deltaY = 0.0f;

    for (int offsetY = -1; offsetY <= 1; offsetY++) {
        if (for_loop(app, newX, newY, offsetY))
            return 1;
    }
    for (int i = 0; i < app->g->enemy_count; i++) {
        if (!app->g->enemies[i].alive)
            continue;
        deltaX = fabsf(newX - app->g->enemies[i].x);
        deltaY = fabsf(newY - app->g->enemies[i].y);
        if (deltaX < 0.5f && deltaY < 0.5f)
            return 1;
    }
    return 0;
}
