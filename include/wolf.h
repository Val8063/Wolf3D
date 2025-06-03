/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** wolf.h
*/

#include "struct_wolf.h"
#include "lib.h"

#ifndef WOLF
    #define WOLF
    #define TITLE               "Wolfenstein 3D"
    #define TILE_SIZE           64
    #define MAP_WIDTH           32
    #define MAP_HEIGHT          32
    #define SCR_H               1000
    #define SCR_W               1600
    #define TEXTURE_WIDTH       1024
    #define TEXTURE_HEIGHT      1024
    #define ENEMY_TEXTURE_SIZE  250
    #define ENEMY_COUNT         5
    #define WEAPON_MAX          6
    #define FRAME_COUNT         4
    #define FRAME_TIME          0.1f
    #define WALL_DISTANCE       0.075f
    #define MAX_VISIBILITY      8.0f
    #define LIGHT_DECAY         0.7f
    #define MIN_LIGHT_LEVEL     0.2f
    #define MAZE_DENSITY        0.4f

    #define ARIAL_FONT          "assets/arial.ttf"

    #define HEART_ASSET         "assets/heart.png"
    #define ENNEMY_ASSET        "assets/enemy.png"
    #define HUD_ASSET           "assets/hud.png"
    #define WEAPON_ASSET        "assets/weapons.png"
    #define MENU_ASSET          "assets/menu.jpg"
    #define WALL_ASSET          "assets/wall.png"
    #define CROSSHAIR_ASSET     "assets/crosshair.png"

    #define PISTOL_SOUND        "assets/pistol_shot.mp3"
    #define KNIFE_SOUND         "assets/knife_swing.mp3"
    #define H_HUD               195

    #define INITIAL_AMMO        4
    #define INITIAL_ENNEMIES    5


void handling_event(app_t *app);
void free_game(app_t *app);

/* INIT APP */
app_t *init_application(void);
void generate_procedural_maze(int **map, float cycle_density);

/* INIT WEAPON */
weapon_t *init_weapon(void);

/* INIT HUD */
hud_t *init_hud(app_t *app);

/* FREE FUNCTIONS */
void free_map(int **map);
void free_map_lines(int **map, int nb_lines);
void free_app(app_t *app);
void free_menu(app_t *app);

/* RAYCAST FUNCTIONS*/
void process_ray(raycast_data_t *data, draw_context_t *ctx, app_t *app, int x);
float calculate_wall_distance(int side, raycast_data_t *data);
void init_raycast_data(raycast_data_t *data, app_t *app);
int process_dda(raycast_data_t *data);

/* DISPLAY FUNCTIONS */
void display(app_t *app);
void draw_wall_slice(draw_context_t *ctx, app_t *app, int x);
void update_player_rotation(app_t *app);
void render_hud(app_t *app);

/* MOVEMENT FUNCTIONS */
void player_move_forward(app_t *app);
void player_move_backward(app_t *app);
void player_move_leftward(app_t *app);
void player_move_rightward(app_t *app);
int player_will_collide(app_t *app, float newX, float newY);
void update_player_movement(app_t *app);
int is_in_bounds(int x, int y);

/* MENU FUNCTIONS */
void process_event(app_t *app);
void handling_menu_event(app_t *app);
void is_clicking_on_play(app_t *app);
void is_clicking_on_settings(app_t *app);
void is_clicking_on_exit(app_t *app);
void draw_exit_button(app_t *app);
void handle_settings_click(app_t *app);
void free_settings(app_t *app);
void display_settings(app_t *app);
void create_button(sfRectangleShape **button, sfVector2f pos,
    const sfColor color, sfVector2f size);
void create_text(sfText **text, sfFont *font, const char *str, sfVector2f pos);
sfVector2f get_normalized_mouse_pos(app_t *app);
void scale_menu_sprite(app_t *app);
void create_settings_bg(app_t *app);
void free_menu_struct(menu_t *menu);

/* LIGHTING FUNCTIONS */
float calculate_light_intensity(float distance,
    float player_light, int flashlight_on);
sfColor apply_lighting(sfColor color, float light_intensity);

/* WEAPON */
void draw_weapon(app_t *app);

/* BLOOD PARTICLES */
void create_blood_particles(app_t *app, int enemyScreenX, int enemyScreenY);
void update_blood_particles(app_t *app);
void draw_blood_particles(app_t *app);

/* LIGHTING */
float calculate_light_intensity(float distance,
    float player_light, int flashlight_on);
sfColor apply_lighting(sfColor color, float light_intensity);

/* SOUND */
void play_weapon_sound(weapon_t *w);
void update_sound_volume(app_t *app, float delta);

/* ENEMY */
int init_enemies(app_t *app, int count);
int process_enemy(app_t *app);
void draw_enemies(app_t *app);
int is_enemy_visible(app_t *app, enemy_t *enemy);
int set_pos_if_valid(int x, int y, int enemy_index, app_t *app);

/* PLAYER INIT */
player_t *init_player(void);

/* MAP INIT */
int init_map_line(int **map, int line_index);
int **init_map(void);

/* WINDOW INIT */
sfRenderWindow *init_window(void);

/* VICTORY SCREEN */
void check_all_enemies_dead(app_t *app);
void display_victory_screen(app_t *app);
void init_victory_screen(app_t *app);

/* GAME INIT */
int init_game(app_t *app);

/* UPDATE HUD */
void update_life(hud_t *hud, int life);
void update_ammo(hud_t *hud, int ammo);
void update_score(hud_t *hud, int score);
void update_e_left(hud_t *hud, int e_left);

/* SAVE */
void save_game(app_t *app, const char *filename);
void load_game(app_t *app, const char *filename);

#endif
