/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** free_game.c
*/

#include "wolf.h"

/**
 * @brief Libère les ressources allouées pour les ennemis
 * @param app Structure contenant les données de l'application
 */
static void free_enemies(app_t *app)
{
    if (!app || !app->g)
        return;
    if (!app->g->enemies) {
        app->g->enemy_count = 0;
        return;
    }
    for (int i = 0; i < app->g->enemy_count; i++) {
        if (app->g->enemies[i].sprite) {
            sfSprite_destroy(app->g->enemies[i].sprite);
            app->g->enemies[i].sprite = NULL;
        }
    }
    if (app->g->enemy_count > 0 && app->g->enemies[0].texture) {
        sfTexture_destroy(app->g->enemies[0].texture);
        for (int i = 0; i < app->g->enemy_count; i++)
            app->g->enemies[i].texture = NULL;
    }
    free(app->g->enemies);
    app->g->enemies = NULL;
    app->g->enemy_count = 0;
}

static void free_weapon_audio(weapon_t *weapon)
{
    if (weapon->pistol_snd.s) {
        sfSound_stop(weapon->pistol_snd.s);
        sfSound_destroy(weapon->pistol_snd.s);
        weapon->pistol_snd.s = NULL;
    }
    if (weapon->pistol_snd.buf) {
        sfSoundBuffer_destroy(weapon->pistol_snd.buf);
        weapon->pistol_snd.buf = NULL;
    }
    if (weapon->knife_snd.s) {
        sfSound_stop(weapon->knife_snd.s);
        sfSound_destroy(weapon->knife_snd.s);
        weapon->knife_snd.s = NULL;
    }
    if (weapon->knife_snd.buf) {
        sfSoundBuffer_destroy(weapon->knife_snd.buf);
        weapon->knife_snd.buf = NULL;
    }
}

static void free_weapon(weapon_t *weapon)
{
    if (!weapon)
        return;
    if (weapon->tex) {
        sfTexture_destroy(weapon->tex);
        weapon->tex = NULL;
    }
    if (weapon->spr) {
        sfSprite_destroy(weapon->spr);
        weapon->spr = NULL;
    }
    free_weapon_audio(weapon);
    if (weapon->anim_clk) {
        sfClock_destroy(weapon->anim_clk);
        weapon->anim_clk = NULL;
    }
    free(weapon);
}

static void free_player(app_t *app)
{
    if (app->g->p) {
        if (app->g->p->w) {
            free_weapon(app->g->p->w);
            app->g->p->w = NULL;
        }
        free(app->g->p);
        app->g->p = NULL;
    }
}

void free_game(app_t *app)
{
    if (!app)
        return;
    if (app->g) {
        free_player(app);
        free_enemies(app);
        if (app->g->map) {
            free_map(app->g->map);
            app->g->map = NULL;
        }
        free(app->g);
        app->g = NULL;
    }
    if (app->window) {
        if (sfRenderWindow_isOpen(app->window))
            sfRenderWindow_close(app->window);
        sfRenderWindow_destroy(app->window);
        app->window = NULL;
    }
}
