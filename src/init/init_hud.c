/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** init_hud.c
*/

#include "wolf.h"
#include <stdlib.h>
#include <stdio.h>

static life_t *init_life(void)
{
    life_t *str = malloc(sizeof(life_t));
    sfIntRect fheart_area = {0, 0, 90, 90};
    sfIntRect eheart_area = {90, 0, 90, 90};

    if (str == NULL)
        return NULL;
    str->fill_heart = sfTexture_createFromFile(HEART_ASSET, &fheart_area);
    str->empty_heart = sfTexture_createFromFile(HEART_ASSET, &eheart_area);
    str->heart1 = sfSprite_create();
    str->heart2 = sfSprite_create();
    str->heart3 = sfSprite_create();
    sfSprite_setPosition(str->heart1, (sfVector2f){SCR_W / 8.3, SCR_H / 1.13});
    sfSprite_setPosition(str->heart2, (sfVector2f){SCR_W / 5.9, SCR_H / 1.13});
    sfSprite_setPosition(str->heart3, (sfVector2f){SCR_W / 4.6, SCR_H / 1.13});
    sfSprite_setTexture(str->heart1, str->fill_heart, sfTrue);
    sfSprite_setTexture(str->heart2, str->fill_heart, sfTrue);
    sfSprite_setTexture(str->heart3, str->fill_heart, sfTrue);
    return str;
}

static void init_score_text(hud_t *hud)
{
    hud->score = sfText_create();
    sfText_setScale(hud->score, (sfVector2f){2.5, 2.5});
    sfText_setString(hud->score, "0");
    sfText_setPosition(hud->score, (sfVector2f){SCR_W / 1.8, SCR_H / 1.135});
    sfText_setFont(hud->score, hud->font);
}

static void init_ammo_text(hud_t *hud)
{
    char ammo[12];

    hud->ammo = sfText_create();
    sprintf(ammo, "%d", INITIAL_AMMO);
    sfText_setScale(hud->ammo, (sfVector2f){2.5, 2.5});
    sfText_setString(hud->ammo, ammo);
    sfText_setPosition(hud->ammo, (sfVector2f){SCR_W / 3.105, SCR_H / 1.135});
    sfText_setFont(hud->ammo, hud->font);
}

static void init_e_left_text(hud_t *hud)
{
    char e_left[12];

    hud->e_left = sfText_create();
    sprintf(e_left, "%d", INITIAL_ENNEMIES);
    sfText_setScale(hud->e_left, (sfVector2f){2.5, 2.5});
    sfText_setString(hud->e_left, e_left);
    sfText_setPosition(hud->e_left, (sfVector2f){SCR_W / 1.45, SCR_H / 1.135});
    sfText_setFont(hud->e_left, hud->font);
}

static void init_flashlight_indicator(hud_t *hud)
{
    hud->flashlight_icon = sfRectangleShape_create();
    sfRectangleShape_setSize(hud->flashlight_icon, (sfVector2f){30, 30});
    sfRectangleShape_setPosition(hud->flashlight_icon,
        (sfVector2f){SCR_W / 1.2, SCR_H / 1.135});
    sfRectangleShape_setFillColor(hud->flashlight_icon, sfYellow);
    sfRectangleShape_setOutlineThickness(hud->flashlight_icon, 2);
    sfRectangleShape_setOutlineColor(hud->flashlight_icon, sfBlack);
    hud->flashlight_text = sfText_create();
    sfText_setScale(hud->flashlight_text, (sfVector2f){1.5, 1.5});
    sfText_setString(hud->flashlight_text, "F: OFF");
    sfText_setPosition(hud->flashlight_text,
        (sfVector2f){SCR_W / 1.175, SCR_H / 1.135});
    sfText_setFont(hud->flashlight_text, hud->font);
    sfText_setColor(hud->flashlight_text, sfWhite);
}

static void init_text(hud_t *hud)
{
    init_score_text(hud);
    init_ammo_text(hud);
    init_e_left_text(hud);
    init_flashlight_indicator(hud);
}

hud_t *init_hud(app_t *app)
{
    hud_t *hud = malloc(sizeof(hud_t));
    sfFloatRect bounds;

    if (hud == NULL)
        return NULL;
    hud->tex = sfTexture_createFromFile(HUD_ASSET, NULL);
    hud->sp = sfSprite_create();
    sfSprite_setTexture(hud->sp, hud->tex, sfTrue);
    bounds = sfSprite_getLocalBounds(hud->sp);
    sfSprite_setOrigin(hud->sp, (sfVector2f){bounds.width / 2, bounds.height});
    sfSprite_setPosition(hud->sp, (sfVector2f){SCR_W / 2, SCR_H});
    hud->life = init_life();
    hud->font = app->font;
    init_text(hud);
    return hud;
}
