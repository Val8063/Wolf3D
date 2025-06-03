/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** menu.c
*/

#include "wolf.h"

void scale_menu_sprite(app_t *app)
{
    sfVector2f scale;
    sfVector2u tex_size;

    if (!app || !app->menu || !app->menu->menu_tex || !app->menu->menu_spr)
        return;
    tex_size = sfTexture_getSize(app->menu->menu_tex);
    scale.x = (float)SCR_W / tex_size.x;
    scale.y = (float)SCR_H / tex_size.y;
    sfSprite_setScale(app->menu->menu_spr, scale);
}

void is_clicking_on_play(app_t *app)
{
    sfVector2i mouse_pos_window;
    sfVector2f mouse_pos_normalized;
    sfVector2u window_size;

    if (!app || !app->menu || !app->window)
        return;
    mouse_pos_window = sfMouse_getPositionRenderWindow(app->window);
    window_size = sfRenderWindow_getSize(app->window);
    mouse_pos_normalized.x =
    (float)mouse_pos_window.x / window_size.x * SCR_W;
    mouse_pos_normalized.y =
    (float)mouse_pos_window.y / window_size.y * SCR_H;
    if ((mouse_pos_normalized.x >= 542 && mouse_pos_normalized.x <= 927) &&
        (mouse_pos_normalized.y >= 424 && mouse_pos_normalized.y <= 578)) {
        app->menu->show_menu = 0;
    }
}

static int is_mouse_on_settings_button(sfVector2f mouse_pos)
{
    if (mouse_pos.x < 982 || mouse_pos.x > 1135)
        return 0;
    if (mouse_pos.y < 414 || mouse_pos.y > 584)
        return 0;
    return 1;
}

void create_settings_bg(app_t *app)
{
    if (!app || !app->menu)
        return;
    app->menu->settings_bg = sfRectangleShape_create();
    sfRectangleShape_setSize(app->menu->settings_bg,
    (sfVector2f){SCR_W, SCR_H});
    sfRectangleShape_setFillColor(app->menu->settings_bg,
    sfColor_fromRGBA(0, 0, 0, 200));
}

void create_text(sfText **text, sfFont *font,
    const char *str, sfVector2f pos)
{
    *text = sfText_create();
    sfText_setFont(*text, font);
    sfText_setString(*text, str);
    sfText_setCharacterSize(*text, 24);
    sfText_setPosition(*text, pos);
    sfText_setColor(*text, sfWhite);
}

static void create_settings_buttons(app_t *app)
{
    sfVector2f pos1 = {SCR_W / 2 - 220, SCR_H / 2 - 100};
    sfVector2f pos2 = {SCR_W / 2 + 20, SCR_H / 2 - 100};
    sfVector2f pos3 = {SCR_W / 2 - 220, SCR_H / 2 + 20};
    sfVector2f pos4 = {SCR_W / 2 + 20, SCR_H / 2 + 20};
    sfVector2f size = {200, 80};
    sfVector2f text_pos1 = {SCR_W / 2 - 175, SCR_H / 2 - 75};
    sfVector2f text_pos2 = {SCR_W / 2 + 50, SCR_H / 2 - 75};
    sfVector2f text_pos3 = {SCR_W / 2 - 175, SCR_H / 2 + 45};
    sfVector2f text_pos4 = {SCR_W / 2 + 50, SCR_H / 2 + 45};
    sfColor color = sfColor_fromRGB(100, 100, 100);

    create_button(&app->menu->settings_btn[0], pos1, color, size);
    create_text(&app->menu->settings_txt[0], app->font, "MENU", text_pos1);
    create_button(&app->menu->settings_btn[1], pos2, color, size);
    create_text(&app->menu->settings_txt[1],
    app->font, "FULLSCREEN", text_pos2);
    create_button(&app->menu->settings_btn[2], pos3, color, size);
    create_text(&app->menu->settings_txt[2], app->font, "VOLUME +", text_pos3);
    create_button(&app->menu->settings_btn[3], pos4, color, size);
    create_text(&app->menu->settings_txt[3], app->font, "VOLUME -", text_pos4);
}

void is_clicking_on_settings(app_t *app)
{
    sfVector2f mouse_pos = get_normalized_mouse_pos(app);

    if (!is_mouse_on_settings_button(mouse_pos))
        return;
    app->menu->show_settings = 1;
    app->menu->show_menu = 0;
    if (!app->font)
        app->font = sfFont_createFromFile(ARIAL_FONT);
    if (!app->menu->settings_btn[0])
        create_settings_buttons(app);
}
