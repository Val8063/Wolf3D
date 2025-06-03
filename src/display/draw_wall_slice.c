/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** draw_wall_slice.c
*/

#include "wolf.h"

static void clamp_texture_x(draw_context_t *ctx, sfVector2u texture_size)
{
    if (ctx->texX < 0)
        ctx->texX = 0;
    else if ((unsigned int)ctx->texX >= texture_size.x)
        ctx->texX = texture_size.x - 1;
}

static void compute_wall_bounds(int *draw_start, int *draw_end,
    int line_height)
{
    *draw_start = -line_height / 2 + SCR_H / 2;
    *draw_end = line_height / 2 + SCR_H / 2;
    if (*draw_start < 0)
        *draw_start = 0;
    if (*draw_end >= SCR_H)
        *draw_end = SCR_H - 1;
}

static void get_and_apply_pixel(app_t *app, draw_context_t *ctx,
    float light_intensity, int x)
{
    sfColor color = sfImage_getPixel(app->wall_textures->wall_img,
        ctx->texX, ctx->texY);

    color = apply_lighting(color, light_intensity);
    sfImage_setPixel(app->fb->fb, x, ctx->y, color);
}

static void draw_texture_column(app_t *app, draw_context_t *ctx,
    int x, int line_height)
{
    sfVector2u buffer_size = sfImage_getSize(app->fb->fb);
    sfVector2u texture_size = sfImage_getSize(app->wall_textures->wall_img);
    float light_intensity = calculate_light_intensity(ctx->perp_wall_dist,
    app->g->p->light_intensity, app->g->p->flashlight_on);

    clamp_texture_x(ctx, texture_size);
    compute_wall_bounds(&ctx->draw_start, &ctx->draw_end, line_height);
    for (ctx->y = ctx->draw_start; ctx->y < ctx->draw_end; ctx->y++) {
        if (x < 0 || x >= (int)buffer_size.x
        || ctx->y < 0 || ctx->y >= (int)buffer_size.y)
            continue;
        ctx->d = (ctx->y * 256) - (SCR_H * 128) + (line_height * 128);
        ctx->texY = (ctx->d * TEXTURE_HEIGHT) / (line_height * 256);
        if (ctx->texY < 0)
            ctx->texY = 0;
        if ((unsigned int)ctx->texY >= texture_size.y)
            ctx->texY = texture_size.y - 1;
        get_and_apply_pixel(app, ctx, light_intensity, x);
    }
}

void draw_wall_slice(draw_context_t *ctx, app_t *app, int x)
{
    float wall_dist = ctx->perp_wall_dist;
    int line_height;

    if (!app || !app->fb || !app->fb->fb || !app->wall_textures ||
    !app->wall_textures->wall_img)
        return;
    if (!app->wall_textures->wall_img) {
        printf("Erreur: wall_img est NULL dans draw_wall_slice.\n");
        return;
    }
    if (wall_dist < 0.05f)
        wall_dist = 0.005f;
    line_height = (int)(SCR_H / wall_dist);
    draw_texture_column(app, ctx, x, line_height);
}
