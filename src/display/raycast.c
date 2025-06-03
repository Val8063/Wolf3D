/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** raycast.c
*/

#include "wolf.h"

static void calculate_step_and_side_dist(raycast_data_t *data)
{
    float wall_distX = data->wall_dist[0];
    float wall_distY = data->wall_dist[1];
    int mapX = data->map_pos[0];
    int mapY = data->map_pos[1];

    if (data->ray_dir[0] < 0) {
        data->step[0] = -1;
        data->side_dist[0] = (data->player->x - mapX) * wall_distX;
    } else {
        data->step[0] = 1;
        data->side_dist[0] = (mapX + 1.0f - data->player->x) * wall_distX;
    }
    if (data->ray_dir[1] < 0) {
        data->step[1] = -1;
        data->side_dist[1] = (data->player->y - mapY) * wall_distY;
    } else {
        data->step[1] = 1;
        data->side_dist[1] = (mapY + 1.0f - data->player->y) * wall_distY;
    }
}

static void update_ray_position(raycast_data_t *data, int *side, int *hit)
{
    if (data->side_dist[0] < data->side_dist[1]) {
        data->side_dist[0] += data->wall_dist[0];
        data->map_pos[0] += data->step[0];
        *side = 0;
    } else {
        data->side_dist[1] += data->wall_dist[1];
        data->map_pos[1] += data->step[1];
        *side = 1;
    }
    if (data->map_pos[0] < 0 || data->map_pos[0] >= MAP_WIDTH ||
        data->map_pos[1] < 0 || data->map_pos[1] >= MAP_HEIGHT) {
        *hit = 1;
    } else if (data->map[data->map_pos[1]][data->map_pos[0]] > 0) {
        *hit = 1;
    }
}

int process_dda(raycast_data_t *data)
{
    int hit = 0;
    int side = 0;

    while (hit == 0) {
        update_ray_position(data, &side, &hit);
    }
    return side;
}

float calculate_wall_distance(int side, raycast_data_t *data)
{
    float perp_wall_dist;
    float ray_dir_x = data->ray_dir[0];
    float ray_dir_y = data->ray_dir[1];

    if (side == 0) {
        perp_wall_dist = (data->map_pos[0] - data->player->x +
        (1 - data->step[0]) / 2.0f) / ray_dir_x;
    } else {
        perp_wall_dist = (data->map_pos[1] - data->player->y +
        (1 - data->step[1]) / 2.0f) / ray_dir_y;
    }
    if (perp_wall_dist < 0)
        perp_wall_dist = 0.01f;
    return perp_wall_dist;
}

void init_raycast_data(raycast_data_t *data, app_t *app)
{
    data->player = app->g->p;
    data->map = app->g->map;
}

void calculate_ray(raycast_data_t *data, int x, player_t *player)
{
    float cameraX;

    cameraX = 2 * x / (float)SCR_W - 1;
    data->ray_dir[0] = player->dx + player->planeX * cameraX;
    data->ray_dir[1] = player->dy + player->planeY * cameraX;
    data->map_pos[0] = (int)player->x;
    data->map_pos[1] = (int)player->y;
    data->wall_dist[0] = fabs(1.0f / data->ray_dir[0]);
    data->wall_dist[1] = fabs(1.0f / data->ray_dir[1]);
}

void process_ray(raycast_data_t *data, draw_context_t *ctx, app_t *app, int x)
{
    int side;
    float perp_wall_dist;
    float wallX;

    calculate_ray(data, x, data->player);
    calculate_step_and_side_dist(data);
    side = process_dda(data);
    perp_wall_dist = calculate_wall_distance(side, data);
    if (perp_wall_dist < 0.01f)
        perp_wall_dist = 0.01f;
    ctx->x = x;
    ctx->side = side;
    ctx->perp_wall_dist = perp_wall_dist;
    if (side == 0)
        wallX = data->player->y + perp_wall_dist * data->ray_dir[1];
    else
        wallX = data->player->x + perp_wall_dist * data->ray_dir[0];
    wallX -= floor(wallX);
    ctx->texX = TEXTURE_WIDTH - (int)(wallX * TEXTURE_WIDTH) - 1;
    draw_wall_slice(ctx, app, x);
}
