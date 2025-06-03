/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** rotate_raycast.c
*/

#include "wolf.h"

void rotate_left(player_t *player, float rotSpeed)
{
    float oldDx = player->dx;
    float oldPx = player->planeX;

    player->dx = player->dx * cos(rotSpeed) - player->dy * sin(rotSpeed);
    player->dy = oldDx * sin(rotSpeed) + player->dy * cos(rotSpeed);
    player->planeX =
    player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
    player->planeY = oldPx * sin(rotSpeed) + player->planeY * cos(rotSpeed);
}

void rotate_right(player_t *player, float rotSpeed)
{
    float oldDx = player->dx;
    float oldPx = player->planeX;

    player->dx = player->dx * cos(-rotSpeed) - player->dy * sin(-rotSpeed);
    player->dy = oldDx * sin(-rotSpeed) + player->dy * cos(-rotSpeed);
    player->planeX =
    player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
    player->planeY = oldPx * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
}

static void update_rotation(app_t *app, float rotation)
{
    float oldDx = 0.0f;
    float oldPx = 0.0f;

    oldDx = app->g->p->dx;
    oldPx = app->g->p->planeX;
    app->g->p->dx =
    app->g->p->dx * cos(-rotation) - app->g->p->dy * sin(-rotation);
    app->g->p->dy = oldDx * sin(-rotation) + app->g->p->dy * cos(-rotation);
    app->g->p->planeX =
    app->g->p->planeX * cos(-rotation) - app->g->p->planeY * sin(-rotation);
    app->g->p->planeY =
    oldPx * sin(-rotation) + app->g->p->planeY * cos(-rotation);
}

void update_player_rotation(app_t *app)
{
    sfVector2i mousePos;
    sfVector2i center;
    float rotSpeed = 0.0015f;
    int deltaX = 0;
    float rotation = 0.0f;

    mousePos = sfMouse_getPositionRenderWindow(app->window);
    center.x = SCR_W / 2;
    center.y = SCR_H / 2;
    deltaX = mousePos.x - center.x;
    if (deltaX != 0) {
        rotation = deltaX * rotSpeed;
        update_rotation(app, rotation);
    }
    if (!app->menu || !app->menu->show_menu)
        sfMouse_setPositionRenderWindow(center, app->window);
}
