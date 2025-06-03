/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** weapon.c
*/

#include "wolf.h"

static void end_animation(app_t *app, sfIntRect *rect)
{
    if (app->g->p->w->fire_frame >= FRAME_COUNT) {
        app->g->p->w->firing = 0;
        (*rect).left = app->g->p->w->cur_weapon ? 23 : 30;
    }
}

void play_weapon_sound(weapon_t *w)
{
    if (w->cur_weapon && w->pistol_snd.s && w->pistol_snd.buf) {
        sfSound_stop(w->pistol_snd.s);
        sfSound_play(w->pistol_snd.s);
    }
    if (!w->cur_weapon && w->knife_snd.s && w->knife_snd.buf) {
        sfSound_stop(w->knife_snd.s);
        sfSound_play(w->knife_snd.s);
    }
}

static void animate_weapon_frame(sfClock *clk, app_t *app,
    sfIntRect *rect, int frames[2][4])
{
    float sec = 0.0f;

    if (app->g->p->w->firing && clk) {
        sec = sfTime_asSeconds(sfClock_getElapsedTime(clk));
        if (sec >= FRAME_TIME) {
            app->g->p->w->fire_frame++;
            sfClock_restart(clk);
            end_animation(app, rect);
        }
        if (app->g->p->w->firing && app->g->p->w->fire_frame >= 0 &&
        app->g->p->w->fire_frame < FRAME_COUNT && app->g->p->w->cur_weapon >= 0
        && app->g->p->w->cur_weapon < 2)
            rect->left = frames[app->g->p->w->cur_weapon]
            [app->g->p->w->fire_frame];
    }
}

static void animate_weapon(app_t *app, sfIntRect *rect)
{
    weapon_t *w = app->g->p->w;
    sfClock *clk = w->anim_clk;
    int frames[2][4] = {{91, 153, 216, 282}, {88, 153, 218, 282}};

    if (app->fire) {
        app->fire = 0;
        w->firing = 1;
        w->fire_frame = 0;
        if (clk)
            sfClock_restart(clk);
        play_weapon_sound(w);
    }
    animate_weapon_frame(clk, app, rect, frames);
    if (w->spr)
        sfSprite_setTextureRect(w->spr, *rect);
}

/**
 * @brief Affiche l'arme en cours sur l'écran
 * @param app Structure contenant les données de l'application
 */
void draw_weapon(app_t *app)
{
    int weapon_width = 22;
    int weapon_height = 31;
    sfVector2f scale = {15, 15};
    sfIntRect rect = {0, 0, weapon_width, weapon_height};
    sfVector2f position = {(SCR_W - weapon_width) / 2, 570 - H_HUD};

    if (!app || !app->g || !app->g->p || !app->g->p->w || !app->g->p->w->spr)
        return;
    if (app->g->p->w->cur_weapon) {
        rect.left = 23;
        rect.top = 90;
    } else {
        rect.left = 30;
        rect.top = 19;
    }
    sfSprite_setScale(app->g->p->w->spr, scale);
    sfSprite_setPosition(app->g->p->w->spr, position);
    animate_weapon(app, &rect);
    sfRenderWindow_drawSprite(app->window, app->g->p->w->spr, NULL);
}
