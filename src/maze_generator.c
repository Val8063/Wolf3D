/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-valentin.rueda
** File description:
** maze_generator.c
*/

#include "wolf.h"

/**
 * @brief Initialise un labyrinthe avec des murs partout
 * @param maze Tableau 2D pour le labyrinthe
 */
static void init_solid_maze(int **maze)
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            maze[y][x] = 1;
        }
    }
}

/**
 * @brief Compte le nombre de cellules vides adjacentes
 * @param maze Labyrinthe
 * @param x Coordonnée X
 * @param y Coordonnée Y
 * @return Nombre de cellules vides adjacentes
 */
static int count_adjacent_empty(int **maze, int x, int y)
{
    int count = 0;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int nx = 0;
    int ny = 0;

    for (int i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (is_in_bounds(nx, ny) && maze[ny][nx] == 0)
            count++;
    }
    return count;
}

/**
 * @brief Mélange les directions pour l'algorithme de génération
 * @param dirs Tableau de directions à mélanger
 */
static void shuffle_directions(int *dirs)
{
    int j = 0;
    int temp = 0;

    for (int i = 0; i < 4; i++) {
        j = rand() % 4;
        temp = dirs[i];
        dirs[i] = dirs[j];
        dirs[j] = temp;
    }
}

/**
 * @brief algorithme de génération de labyrinthe
 * @param maze Labyrinthe à générer
 * @param x Coordonnée X de départ
 * @param y Coordonnée Y de départ
 */
static void carve_maze(int **maze, int x, int y)
{
    int dirs[4] = {0, 1, 2, 3};
    int dx_values[4] = {-2, 2, 0, 0};
    int dy_values[4] = {0, 0, -2, 2};
    int dir = 0;
    int dxy[2] = {0, 0};
    int nxy[2] = {0, 0};

    maze[y][x] = 0;
    shuffle_directions(dirs);
    for (int i = 0; i < 4; i++) {
        dir = dirs[i];
        dxy[0] = dx_values[dir];
        dxy[1] = dy_values[dir];
        nxy[0] = x + dxy[0];
        nxy[1] = y + dxy[1];
        if (is_in_bounds(nxy[0], nxy[1]) && maze[nxy[1]][nxy[0]] == 1) {
            maze[y + dxy[1] / 2][x + dxy[0] / 2] = 0;
            carve_maze(maze, nxy[0], nxy[1]);
        }
    }
}

static void init_maze_generation(int **maze, int *start_x, int *start_y)
{
    srand(time(NULL));
    init_solid_maze(maze);
    *start_x = 1 + 2 * (rand() % ((MAP_WIDTH - 2) / 2));
    *start_y = 1 + 2 * (rand() % ((MAP_HEIGHT - 2) / 2));
    if (*start_x >= MAP_WIDTH - 1)
        *start_x = MAP_WIDTH - 2;
    if (*start_y >= MAP_HEIGHT - 1)
        *start_y = MAP_HEIGHT - 2;
}

/**
 * @brief Configure les bordures et points d'entrée du labyrinthe
 * @param maze Labyrinthe à finaliser
 */
static void finalize_maze(int **maze)
{
    for (int i = 0; i < MAP_WIDTH; i++) {
        maze[0][i] = 1;
        maze[MAP_HEIGHT - 1][i] = 1;
    }
    for (int i = 0; i < MAP_HEIGHT; i++) {
        maze[i][0] = 1;
        maze[i][MAP_WIDTH - 1] = 1;
    }
    maze[1][1] = 0;
    maze[1][2] = 0;
    maze[2][1] = 0;
    maze[2][2] = 0;
}

/**
 * @brief Génère un labyrinthe avec l'algorithme de génération récursive
 * @return Le labyrinthe généré
 */
void generate_maze(int **maze)
{
    int start_x = 0;
    int start_y = 0;

    init_maze_generation(maze, &start_x, &start_y);
    carve_maze(maze, start_x, start_y);
    finalize_maze(maze);
}

static void process_cycle(int x, int y, int **maze, float density)
{
    int neighbors = 0;

    if (maze[y][x] == 1) {
        neighbors = count_adjacent_empty(maze, x, y);
        if (neighbors >= 2 && ((float)rand() / RAND_MAX) < density) {
            maze[y][x] = 0;
        }
    }
}

/**
 * @brief Ajoute des cycles au labyrinthe pour créer quelques boucles
 * @param maze Labyrinthe à modifier
 * @param density Densité des cycles (entre 0 et 1)
 */
void add_cycles(int **maze, float density)
{
    for (int y = 1; y < MAP_HEIGHT - 1; y++) {
        for (int x = 1; x < MAP_WIDTH - 1; x++) {
            process_cycle(x, y, maze, density);
        }
    }
}

/**
 * @brief Génère un labyrinthe procéduralement avec des cycles
 * @param map Carte à remplir
 * @param cycle_density Densité des cycles (entre 0 et 1)
 */
void generate_procedural_maze(int **map, float cycle_density)
{
    generate_maze(map);
    add_cycles(map, cycle_density);
}
