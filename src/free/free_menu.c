/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** free_menu.c
*/

#include "wolf.h"

static void free_menu_tex(menu_t *menu)
{
    if (menu->menu_spr) {
        sfSprite_destroy(menu->menu_spr);
        menu->menu_spr = NULL;
    }
    if (menu->menu_tex) {
        sfTexture_destroy(menu->menu_tex);
        menu->menu_tex = NULL;
    }
    if (menu->settings_bg) {
        sfRectangleShape_destroy(menu->settings_bg);
        menu->settings_bg = NULL;
    }
}

void free_menu_struct(menu_t *menu)
{
    if (!menu)
        return;
    free_menu_tex(menu);
    for (int i = 0; i < 4; i++) {
        if (menu->settings_btn[i]) {
            sfRectangleShape_destroy(menu->settings_btn[i]);
            menu->settings_btn[i] = NULL;
        }
        if (menu->settings_txt[i]) {
            sfText_destroy(menu->settings_txt[i]);
            menu->settings_txt[i] = NULL;
        }
    }
    free(menu);
}

/**
 * @brief Libère les ressources allouées pour le menu
 * @param app Structure contenant les données de l'application
 */
void free_menu(app_t *app)
{
    if (!app || !app->menu)
        return;
    if (app->menu->menu_spr) {
        sfSprite_destroy(app->menu->menu_spr);
        app->menu->menu_spr = NULL;
    }
    if (app->menu->menu_tex) {
        sfTexture_destroy(app->menu->menu_tex);
        app->menu->menu_tex = NULL;
    }
}

/**
 * @brief Libère les ressources allouées pour l'écran des paramètres
 * @param app Structure contenant les données de l'application
 */
void free_settings(app_t *app)
{
    if (!app || !app->menu)
        return;
    if (app->menu->settings_bg) {
        sfRectangleShape_destroy(app->menu->settings_bg);
        app->menu->settings_bg = NULL;
    }
    for (int i = 0; i < 4; i++) {
        if (app->menu->settings_btn[i]) {
            sfRectangleShape_destroy(app->menu->settings_btn[i]);
            app->menu->settings_btn[i] = NULL;
        }
        if (app->menu->settings_txt[i]) {
            sfText_destroy(app->menu->settings_txt[i]);
            app->menu->settings_txt[i] = NULL;
        }
    }
    if (app->font) {
        sfFont_destroy(app->font);
        app->font = NULL;
    }
}
