/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** process_display.c
*/

#include "wolf.h"

static sfView *init_view(sfRenderWindow *window)
{
    sfView *view = sfView_create();

    sfView_setSize(view, (sfVector2f){SCR_W, SCR_H});
    sfView_setCenter(view, (sfVector2f){SCR_W / 2, SCR_H / 2});
    sfView_setViewport(view, (sfFloatRect){0, 0, 1, 1});
    sfRenderWindow_setView(window, view);
    return view;
}

static int display_menu_if_needed(app_t *app, sfView *view)
{
    if (!app->menu || !app->menu->show_menu) {
        return 0;
    }
    sfRenderWindow_drawSprite(app->window, app->menu->menu_spr, NULL);
    draw_exit_button(app);
    sfView_destroy(view);
    return 1;
}

/**
 * @brief Dessine le sol et le plafond avec des couleurs unies
 * @param app Structure contenant les données de l'application
 */
static void draw_floor_ceiling(app_t *app)
{
    sfColor floor_color = sfColor_fromRGB(80, 80, 80);
    sfColor ceiling_color = sfColor_fromRGB(50, 50, 100);
    int middle = SCR_H / 2;

    if (!app || !app->fb || !app->fb->fb)
        return;
    for (int y = middle; y < SCR_H; y++) {
        for (int x = 0; x < SCR_W; x++)
            sfImage_setPixel(app->fb->fb, x, y, floor_color);
    }
    for (int y = 0; y < middle; y++) {
        for (int x = 0; x < SCR_W; x++)
            sfImage_setPixel(app->fb->fb, x, y, ceiling_color);
    }
}

static void render_scene(app_t *app)
{
    sfRectangleShape *column = sfRectangleShape_create();
    raycast_data_t data;
    draw_context_t ctx;

    draw_floor_ceiling(app);
    sfRectangleShape_setSize(column, (sfVector2f){1.0f, 0.0f});
    init_raycast_data(&data, app);
    ctx.window = app->window;
    ctx.column = column;
    for (int x = 0; x < SCR_W; x++) {
        process_ray(&data, &ctx, app, x);
    }
    sfRectangleShape_destroy(column);
}

static void draw_settings_ui(app_t *app)
{
    if (!app->menu || !app->menu->show_settings)
        return;
    if (!app->menu->settings_bg)
        create_settings_bg(app);
    if (!app->font)
        app->font = sfFont_createFromFile(ARIAL_FONT);
    sfTexture_updateFromImage(app->fb->frame_tex, app->fb->fb, 0, 0);
    sfRenderWindow_drawSprite(app->window, app->fb->frame_spr, NULL);
    sfRectangleShape_setSize(app->menu->settings_bg,
        (sfVector2f){SCR_W, SCR_H});
    sfRenderWindow_drawRectangleShape(app->window,
        app->menu->settings_bg, NULL);
    for (int i = 0; i < 4; i++) {
        if (app->menu->settings_btn[i] && app->menu->settings_txt[i]) {
            sfRenderWindow_drawRectangleShape(app->window,
                app->menu->settings_btn[i], NULL);
            sfRenderWindow_drawText(app->window,
                app->menu->settings_txt[i], NULL);
        }
    }
}

static void draw_weapon_and_ui(app_t *app)
{
    if (app->g->p->w && app->g->p->w->spr
    && app->g->p->w->tex && !app->menu->show_settings)
        draw_weapon(app);
    if (app->crosshair && app->crosshair->cross_spr &&
    app->crosshair->cross_tex && !app->menu->show_settings &&
    !app->victory->show_victory) {
        sfRenderWindow_drawSprite(app->window,
            app->crosshair->cross_spr, NULL);
        render_hud(app);
    }
    if (app->victory->show_victory)
        display_victory_screen(app);
}

void display(app_t *app)
{
    sfView *view = init_view(app->window);

    if (display_menu_if_needed(app, view))
        return;
    render_scene(app);
    process_enemy(app);
    check_all_enemies_dead(app);
    sfTexture_updateFromImage(app->fb->frame_tex, app->fb->fb, 0, 0);
    sfRenderWindow_drawSprite(app->window, app->fb->frame_spr, NULL);
    draw_enemies(app);
    draw_blood_particles(app);
    draw_settings_ui(app);
    draw_weapon_and_ui(app);
    sfView_destroy(view);
}
