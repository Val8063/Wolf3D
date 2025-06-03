/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** manage_window.c
*/

#include "wolf.h"

void handling_menu_event(app_t *app)
{
    switch (app->evt.type) {
        case sfEvtClosed:
            sfRenderWindow_close(app->window);
            break;
        case sfEvtMouseButtonPressed:
            is_clicking_on_play(app);
            is_clicking_on_settings(app);
            is_clicking_on_exit(app);
            break;
        default:
            break;
    }
}

static void handle_close_event(app_t *app)
{
    sfRenderWindow_close(app->window);
}

static void handle_key_event(app_t *app)
{
    if (app->evt.key.code == sfKeyEscape)
        app->menu->show_menu = 1;
    if (app->evt.key.code == sfKeyZ)
        player_move_forward(app);
    if (app->evt.key.code == sfKeyS)
        player_move_backward(app);
    if (app->evt.key.code == sfKeyQ)
        player_move_leftward(app);
    if (app->evt.key.code == sfKeyD)
        player_move_rightward(app);
    if (app->evt.key.code == sfKeyW)
        app->g->p->w->cur_weapon = app->g->p->w->cur_weapon ? 0 : 1;
    if (app->evt.key.code == sfKeyF) {
        app->g->p->flashlight_on = !app->g->p->flashlight_on;
    }
}

static float get_dist(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrtf(dx * dx + dy * dy);
}

static void update_closest_enemy(enemy_t *enemy, enemy_t **target,
    float dist, float *closest_distance)
{
    if (dist < *closest_distance) {
        *closest_distance = dist;
        *target = enemy;
    }
}

static enemy_t *find_closest_enemy_in_crosshair(app_t *app)
{
    enemy_t *target = NULL;
    enemy_t *enemy = NULL;
    float closest_distance = FLT_MAX;
    float s_center = SCR_W / 2.0f;
    float hit_width = 0.0f;
    float dist = 0.0f;

    if (!process_enemy(app))
        return NULL;
    for (int i = 0; i < app->g->enemy_count; i++) {
        enemy = &app->g->enemies[i];
        if (!enemy->alive || !enemy->render)
            continue;
        hit_width = enemy->width * 0.225f;
        if (enemy->render && fabsf(enemy->screenX - s_center) < hit_width) {
            dist = get_dist(enemy->x, enemy->y, app->g->p->x, app->g->p->y);
            update_closest_enemy(enemy, &target, dist, &closest_distance);
        }
    }
    return target;
}

static void attack_enemy(app_t *app, enemy_t *target)
{
    float distance = 0.0f;

    if (app->g->p->w->cur_weapon == 0) {
        distance = get_dist(target->x, target->y,
        app->g->p->x, app->g->p->y);
        if (distance < 0.75f) {
            target->alive = 0;
            app->g->p->score += 5;
            update_score(app->g->hud, app->g->p->score);
            create_blood_particles(app, target->screenX, target->screenY);
        }
    } else {
        target->alive = 0;
        app->g->p->score += 1;
        if (app->g->hud)
            update_score(app->g->hud, app->g->p->score);
        create_blood_particles(app, target->screenX, target->screenY);
    }
}

void process_enemy_kill(app_t *app)
{
    enemy_t *target = NULL;
    int was_enemy_killed = 0;

    if (!app->g || !app->g->enemies || app->g->enemy_count <= 0)
        return;
    target = find_closest_enemy_in_crosshair(app);
    if (target) {
        was_enemy_killed = (target->alive == 1);
        attack_enemy(app, target);
        was_enemy_killed = was_enemy_killed && (target->alive == 0);
    }
    if (was_enemy_killed) {
        app->g->enemies_alive--;
        update_e_left(app->g->hud, app->g->enemies_alive);
    } else if (!target && app->g->p->life > 0) {
        app->g->p->life--;
        update_life(app->g->hud, app->g->p->life);
    }
}

static void handle_mouse_button_event(app_t *app)
{
    static sfClock *fire_cooldown_clock = NULL;
    float fire_cooldown = 0.625f;
    float elapsed_time = 0.0f;

    if (app->g && app->g->p && app->g->p->w && app->g->p->w->cur_weapon == 1)
        fire_cooldown = 0.4f;
    if (!fire_cooldown_clock)
        fire_cooldown_clock = sfClock_create();
    elapsed_time =
    sfTime_asSeconds(sfClock_getElapsedTime(fire_cooldown_clock));
    if (elapsed_time < fire_cooldown)
        return;
    sfClock_restart(fire_cooldown_clock);
    app->fire = 1;
    if (app->g && app->g->p && app->g->p->w) {
        app->g->p->w->firing = 1;
        play_weapon_sound(app->g->p->w);
    }
    process_enemy_kill(app);
}

void handling_event(app_t *app)
{
    switch (app->evt.type) {
        case sfEvtClosed:
            handle_close_event(app);
            break;
        case sfEvtKeyPressed:
            handle_key_event(app);
            break;
        case sfEvtMouseButtonPressed:
            handle_mouse_button_event(app);
            break;
        default:
            break;
    }
}
