/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** enemy_visibility.c
*/

#include "wolf.h"

int set_pos_if_valid(int x, int y, int enemy_index, app_t *app)
{
    float dist = 0.0f;

    if (app->g->map[y][x] == 0) {
        dist = sqrtf(powf(x - app->g->p->x, 2) + powf(y - app->g->p->y, 2));
        if (dist > 3.0f) {
            app->g->enemies[enemy_index].x = (float)x + 0.5f;
            app->g->enemies[enemy_index].y = (float)y + 0.5f;
            return 1;
        }
    }
    return 0;
}

static int is_behind_wall(app_t *app, float dirX, float dirY, float distance)
{
    float currentDist = 0.0f;
    float stepSize = 0.02f;
    float rayX = app->g->p->x;
    float rayY = app->g->p->y;
    int mapX = 0;
    int mapY = 0;

    while (currentDist < distance) {
        rayX += dirX * stepSize;
        rayY += dirY * stepSize;
        currentDist += stepSize;
        mapX = (int)rayX;
        mapY = (int)rayY;
        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
            return 0;
        if (app->g->map[mapY][mapX] > 0)
            return 0;
    }
    return 1;
}

int is_enemy_visible(app_t *app, enemy_t *enemy)
{
    float dirX = enemy->x - app->g->p->x;
    float dirY = enemy->y - app->g->p->y;
    float distance = sqrtf(dirX * dirX + dirY * dirY);

    if (distance > 0.0001f) {
        dirX /= distance;
        dirY /= distance;
    } else {
        return 1;
    }
    if (!is_behind_wall(app, dirX, dirY, distance))
        return 0;
    return 1;
}
