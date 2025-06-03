/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** functions_sound.c
*/

#include "wolf.h"

void update_sound_volume(app_t *app, float delta)
{
    float new_volume = app->g->snd_efct_vol + delta;

    if (new_volume < 0.0f)
        new_volume = 0.0f;
    if (new_volume > 100.0f)
        new_volume = 100.0f;
    app->g->snd_efct_vol = new_volume;
    if (app->g->p && app->g->p->w) {
        if (app->g->p->w->pistol_snd.s)
            sfSound_setVolume(app->g->p->w->pistol_snd.s, new_volume);
        if (app->g->p->w->knife_snd.s)
            sfSound_setVolume(app->g->p->w->knife_snd.s, new_volume);
    }
}
