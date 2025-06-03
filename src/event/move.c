/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** move.c
*/

#include "wolf.h"

void player_move_forward(app_t *app)
{
    float newX = app->g->p->x + app->g->p->dx * app->g->p->speed;
    float newY = app->g->p->y + app->g->p->dy * app->g->p->speed;

    if ((newX >= 0 && newX < MAP_WIDTH) && (newY >= 0 && newY < MAP_HEIGHT) &&
        (player_will_collide(app, newX, newY) != 1)) {
        app->g->p->x = newX;
        app->g->p->y = newY;
    }
}

void player_move_backward(app_t *app)
{
    float newX = app->g->p->x - app->g->p->dx * app->g->p->speed;
    float newY = app->g->p->y - app->g->p->dy * app->g->p->speed;

    if ((newX >= 0 && newX < MAP_WIDTH) && (newY >= 0 && newY < MAP_HEIGHT) &&
        (player_will_collide(app, newX, newY) != 1)) {
        app->g->p->x = newX;
        app->g->p->y = newY;
    }
}

void player_move_leftward(app_t *app)
{
    float newX = app->g->p->x - app->g->p->dy * app->g->p->speed;
    float newY = app->g->p->y + app->g->p->dx * app->g->p->speed;

    if ((newX >= 0 && newX < MAP_WIDTH) && (newY >= 0 && newY < MAP_HEIGHT) &&
        (player_will_collide(app, newX, newY) != 1)) {
        app->g->p->x = newX;
        app->g->p->y = newY;
    }
}

void player_move_rightward(app_t *app)
{
    float newX = app->g->p->x + app->g->p->dy * app->g->p->speed;
    float newY = app->g->p->y - app->g->p->dx * app->g->p->speed;

    if ((newX >= 0 && newX < MAP_WIDTH) && (newY >= 0 && newY < MAP_HEIGHT) &&
        (player_will_collide(app, newX, newY) != 1)) {
        app->g->p->x = newX;
        app->g->p->y = newY;
    }
}

static void process_move_dir(app_t *app)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        player_move_forward(app);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        player_move_backward(app);
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        player_move_leftward(app);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        player_move_rightward(app);
}

void update_player_movement(app_t *app)
{
    sfTime time = sfClock_getElapsedTime(app->move_clk);
    float elapsed = sfTime_asSeconds(time);
    float speed_factor = 0.0f;
    float saved_speed = 0.0f;

    if (elapsed < 0.016f)
        return;
    speed_factor = elapsed / 0.016f;
    saved_speed = app->g->p->speed;
    if (speed_factor > 2.0f)
        speed_factor = 2.0f;
    app->g->p->speed *= speed_factor;
    process_move_dir(app);
    app->g->p->speed = saved_speed;
    sfClock_restart(app->move_clk);
}
