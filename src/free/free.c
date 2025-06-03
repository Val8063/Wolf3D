/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** free.c
*/

#include "wolf.h"

static void free_wall_textures(wall_textures_t *textures)
{
    if (!textures)
        return;
    if (textures->wall_tex) {
        sfTexture_destroy(textures->wall_tex);
        textures->wall_tex = NULL;
    }
    if (textures->wall_img) {
        sfImage_destroy(textures->wall_img);
        textures->wall_img = NULL;
    }
    free(textures);
}

static void free_crosshair_struct(crosshair_t *crosshair)
{
    if (!crosshair)
        return;
    if (crosshair->cross_spr) {
        sfSprite_destroy(crosshair->cross_spr);
        crosshair->cross_spr = NULL;
    }
    if (crosshair->cross_tex) {
        sfTexture_destroy(crosshair->cross_tex);
        crosshair->cross_tex = NULL;
    }
    free(crosshair);
}

static void free_framebuffer_struct(framebuffer_t *fb)
{
    if (!fb)
        return;
    if (fb->fb) {
        sfImage_destroy(fb->fb);
        fb->fb = NULL;
    }
    if (fb->frame_tex) {
        sfTexture_destroy(fb->frame_tex);
        fb->frame_tex = NULL;
    }
    if (fb->frame_spr) {
        sfSprite_destroy(fb->frame_spr);
        fb->frame_spr = NULL;
    }
    free(fb);
}

static void free_particles_struct(particles_t *particles)
{
    if (!particles)
        return;
    if (particles->particle_clock) {
        sfClock_destroy(particles->particle_clock);
        particles->particle_clock = NULL;
    }
    free(particles);
}

static void free_victory_struct(victory_screen_t *victory)
{
    if (!victory)
        return;
    if (victory->bg) {
        sfRectangleShape_destroy(victory->bg);
        victory->bg = NULL;
    }
    if (victory->victory_text) {
        sfText_destroy(victory->victory_text);
        victory->victory_text = NULL;
    }
    free(victory);
}

void free_app(app_t *app)
{
    if (!app)
        return;
    free_game(app);
    free_menu_struct(app->menu);
    free_victory_struct(app->victory);
    free_wall_textures(app->wall_textures);
    free_crosshair_struct(app->crosshair);
    free_framebuffer_struct(app->fb);
    free_particles_struct(app->particles);
    if (app->move_clk) {
        sfClock_destroy(app->move_clk);
        app->move_clk = NULL;
    }
    if (app->font) {
        sfFont_destroy(app->font);
        app->font = NULL;
    }
    free(app);
}
