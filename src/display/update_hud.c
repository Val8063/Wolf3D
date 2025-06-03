/*
** EPITECH PROJECT, 2024
** Wolf3d
** File description:
** update_hud.c
*/

#include "wolf.h"

static void next_life(life_t *life_t, int life)
{
    if (life == 2) {
        sfSprite_setTexture(life_t->heart1, life_t->fill_heart, sfTrue);
        sfSprite_setTexture(life_t->heart2, life_t->fill_heart, sfTrue);
        sfSprite_setTexture(life_t->heart3, life_t->empty_heart, sfTrue);
        return;
    }
    if (life >= 3) {
        sfSprite_setTexture(life_t->heart1, life_t->fill_heart, sfTrue);
        sfSprite_setTexture(life_t->heart2, life_t->fill_heart, sfTrue);
        sfSprite_setTexture(life_t->heart3, life_t->fill_heart, sfTrue);
        return;
    }
}

// Update la vie sur l'HUD
void update_life(hud_t *hud, int life)
{
    life_t *l = hud->life;

    if (life == 0) {
        sfSprite_setTexture(l->heart1, l->empty_heart, sfTrue);
        sfSprite_setTexture(l->heart2, l->empty_heart, sfTrue);
        sfSprite_setTexture(l->heart3, l->empty_heart, sfTrue);
        return;
    }
    if (life == 1) {
        sfSprite_setTexture(l->heart1, l->fill_heart, sfTrue);
        sfSprite_setTexture(l->heart2, l->empty_heart, sfTrue);
        sfSprite_setTexture(l->heart3, l->empty_heart, sfTrue);
        return;
    }
    next_life(l, life);
}

// Update les munitions sur l'HUD
void update_ammo(hud_t *hud, int ammo)
{
    char str[12];

    sprintf(str, "%d", ammo);
    sfText_setString(hud->ammo, str);
}

// Update le score sur l'HUD
void update_score(hud_t *hud, int score)
{
    char str[12];
    sfText *sc = hud->score;

    sprintf(str, "%d", score);
    sfText_setString(sc, str);
    if (score >= 10)
        sfText_setPosition(sc, (sfVector2f){SCR_W / 1.84, SCR_H / 1.135});
    if (score >= 100)
        sfText_setPosition(sc, (sfVector2f){SCR_W / 1.86, SCR_H / 1.135});
}

// Update le nombre d'ennemis restant sur l'HUD
void update_e_left(hud_t *hud, int e_left)
{
    char str[12];

    sprintf(str, "%d", e_left);
    sfText_setString(hud->e_left, str);
}
