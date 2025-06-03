/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** event.c
*/

#include "wolf.h"

static void process_menu_event(app_t *app)
{
    handling_menu_event(app);
}

static void process_settings_mouse(app_t *app)
{
    handle_settings_click(app);
}

static void process_settings_key(app_t *app)
{
    if (app->evt.key.code == sfKeyEscape)
        app->menu->show_settings = 0;
}

static void process_settings_event(app_t *app)
{
    if (app->evt.type == sfEvtMouseButtonPressed) {
        process_settings_mouse(app);
        return;
    }
    if (app->evt.type == sfEvtKeyPressed) {
        process_settings_key(app);
    }
}

void process_event(app_t *app)
{
    if (app->menu && app->menu->show_menu) {
        process_menu_event(app);
        return;
    }
    if (app->menu && app->menu->show_settings) {
        process_settings_event(app);
        return;
    }
    if (app->victory && app->victory->show_victory) {
        if (app->evt.type == sfEvtKeyPressed &&
        app->evt.key.code == sfKeyEscape) {
            app->victory->show_victory = 0;
            app->menu->show_menu = 1;
        }
    }
    handling_event(app);
    if ((!app->menu || !app->menu->show_menu) &&
    (!app->menu || !app->menu->show_settings) &&
    (!app->victory || !app->victory->show_victory))
        update_player_movement(app);
}
