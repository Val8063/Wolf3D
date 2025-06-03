/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** display_hud.c
*/

#include "wolf.h"

static void render_life(sfRenderWindow *win, life_t *life)
{
    sfRenderWindow_drawSprite(win, life->heart1, NULL);
    sfRenderWindow_drawSprite(win, life->heart2, NULL);
    sfRenderWindow_drawSprite(win, life->heart3, NULL);
}

static void render_text(sfRenderWindow *win, hud_t *hud)
{
    sfRenderWindow_drawText(win, hud->ammo, NULL);
    sfRenderWindow_drawText(win, hud->e_left, NULL);
    sfRenderWindow_drawText(win, hud->score, NULL);
}

static void render_flashlight_indicator(sfRenderWindow *win, hud_t *hud,
    int flashlight_on)
{
    if (flashlight_on) {
        sfRectangleShape_setFillColor(hud->flashlight_icon, sfYellow);
        sfText_setString(hud->flashlight_text, "F: ON");
    } else {
        sfRectangleShape_setFillColor(hud->flashlight_icon,
        sfColor_fromRGB(80, 80, 80));
        sfText_setString(hud->flashlight_text, "F: OFF");
    }
    sfRenderWindow_drawRectangleShape(win, hud->flashlight_icon, NULL);
    sfRenderWindow_drawText(win, hud->flashlight_text, NULL);
}

void render_hud(app_t *app)
{
    sfRenderWindow_drawSprite(app->window, app->g->hud->sp, NULL);
    render_life(app->window, app->g->hud->life);
    render_text(app->window, app->g->hud);
    render_flashlight_indicator(app->window, app->g->hud,
    app->g->p->flashlight_on);
}
