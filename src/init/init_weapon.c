/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** init_weapon.c
*/

#include "wolf.h"

/*
** @brief   Initialise les armes du joueur
** @return  Renvoie la structure d'arme initialisée
*/

static int init_weapon_graphics(weapon_t *weapon)
{
    weapon->tex = sfTexture_createFromFile(WEAPON_ASSET, NULL);
    if (!weapon->tex) {
        printf("Erreur: Impossible de charger la sprite sheet des armes.\n");
        return -1;
    }
    weapon->spr = sfSprite_create();
    sfSprite_setTexture(weapon->spr, weapon->tex, sfTrue);
    return 0;
}

static void init_weapon_pistol_sound(weapon_t *weapon)
{
    weapon->pistol_snd.buf = sfSoundBuffer_createFromFile(PISTOL_SOUND);
    if (!weapon->pistol_snd.buf)
        printf("Erreur: Impossible de charger le son de tir.\n");
    weapon->pistol_snd.s = sfSound_create();
    sfSound_setBuffer(weapon->pistol_snd.s, weapon->pistol_snd.buf);
    sfSound_setVolume(weapon->pistol_snd.s, 50.0f);
}

static void init_weapon_knife_sound(weapon_t *weapon)
{
    weapon->knife_snd.buf = sfSoundBuffer_createFromFile(KNIFE_SOUND);
    if (!weapon->knife_snd.buf)
        printf("Erreur: Impossible de charger le son du couteau.\n");
    weapon->knife_snd.s = sfSound_create();
    sfSound_setBuffer(weapon->knife_snd.s, weapon->knife_snd.buf);
    sfSound_setVolume(weapon->knife_snd.s, 50.0f);
}

weapon_t *init_weapon(void)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));

    if (weapon == NULL)
        return NULL;
    weapon->cur_weapon = 1;
    weapon->anim_frame = 0;
    weapon->firing = 0;
    weapon->fire_frame = 0;
    weapon->anim_clk = sfClock_create();
    if (init_weapon_graphics(weapon) == -1)
        return free(weapon), NULL;
    init_weapon_pistol_sound(weapon);
    init_weapon_knife_sound(weapon);
    return weapon;
}
