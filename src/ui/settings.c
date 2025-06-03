/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** settings.c - Gestion des paramètres
*/

#include "wolf.h"

void create_button(sfRectangleShape **button, sfVector2f pos,
    const sfColor color, sfVector2f size)
{
    *button = sfRectangleShape_create();
    sfRectangleShape_setSize(*button, size);
    sfRectangleShape_setPosition(*button, pos);
    sfRectangleShape_setFillColor(*button, color);
}

sfVector2f get_normalized_mouse_pos(app_t *app)
{
    sfVector2i mouse_pos_window = sfMouse_getPositionRenderWindow(app->window);
    sfVector2u window_size = sfRenderWindow_getSize(app->window);
    sfVector2f mouse_pos_normalized;

    mouse_pos_normalized.x =
    (float)mouse_pos_window.x / window_size.x * SCR_W;
    mouse_pos_normalized.y =
    (float)mouse_pos_window.y / window_size.y * SCR_H;
    return mouse_pos_normalized;
}

static int is_mouse_over_button(sfVector2f mouse, sfRectangleShape *button)
{
    sfVector2f pos = sfRectangleShape_getPosition(button);
    sfVector2f size = sfRectangleShape_getSize(button);

    if (mouse.x < pos.x || mouse.x > pos.x + size.x)
        return 0;
    if (mouse.y < pos.y || mouse.y > pos.y + size.y)
        return 0;
    return 1;
}

static void toggle_fullscreen(app_t *app)
{
    sfVideoMode mode;

    if (app->fullscreen) {
        mode.width = SCR_W;
        mode.height = SCR_H;
        mode.bitsPerPixel = 32;
        app->fullscreen = 0;
        app->win_w = SCR_W;
        app->win_h = SCR_H;
        app->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
        return;
    }
    mode = sfVideoMode_getDesktopMode();
    app->fullscreen = 1;
    app->win_w = mode.width;
    app->win_h = mode.height;
    app->window = sfRenderWindow_create(mode, TITLE, sfFullscreen, NULL);
}

static void apply_post_window_settings(app_t *app)
{
    int show_cursor = app->menu->show_menu || app->menu->show_settings;

    sfRenderWindow_setMouseCursorVisible(app->window, show_cursor);
    sfRenderWindow_setVerticalSyncEnabled(app->window, sfTrue);
    sfRenderWindow_setFramerateLimit(app->window, 60);
    app->menu->show_settings = 0;
}

void handle_settings_click(app_t *app)
{
    sfVector2f mouse_pos = get_normalized_mouse_pos(app);

    if (is_mouse_over_button(mouse_pos, app->menu->settings_btn[0])) {
        app->menu->show_settings = 0;
        app->menu->show_menu = 1;
        return;
    }
    if (is_mouse_over_button(mouse_pos, app->menu->settings_btn[1])) {
        sfRenderWindow_destroy(app->window);
        toggle_fullscreen(app);
        apply_post_window_settings(app);
        return;
    }
    if (is_mouse_over_button(mouse_pos, app->menu->settings_btn[2]))
        return update_sound_volume(app, 10.0f);
    if (is_mouse_over_button(mouse_pos, app->menu->settings_btn[3]))
        return update_sound_volume(app, -10.0f);
}
