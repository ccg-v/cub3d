#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_map {
    char **array;
    bool **visited;
    size_t *row_widths; // Array to store the width of each row
    size_t height;
    size_t player_x;
    size_t player_y;
    bool closed;
} t_map;

void print_visited_map(t_map *map) {
    printf("\nVisited map:\n");
    for (size_t k = 0; k < map->height; k++) {
        // Print each cell in the row up to its actual width
        for (size_t j = 0; j < map->row_widths[k]; j++) {
            printf("%c", map->visited[k][j] ? '1' : '0');
        }
        printf("\n");
    }
}

bool is_boundary_closed(t_map *map) {
    // Check top and bottom boundaries
    for (size_t i = 0; i < map->row_widths[0]; i++) {
        if (map->array[0][i] != '1' || map->array[map->height - 1][i] != '1')
            return false;
    }
    // Check left and right boundaries
    for (size_t i = 0; i < map->height; i++) {
        if (map->array[i][0] != '1' || map->array[i][map->row_widths[i] - 1] != '1')
            return false;
    }
    return true;
}

void dfs(t_map *map, size_t x, size_t y) {
    int dx[] = {0, 0, -1, 1}; // Changes in x for moving up, down, left, right
    int dy[] = {-1, 1, 0, 0}; // Changes in y for moving up, down, left, right

    if (x >= map->row_widths[y] || y >= map->height || map->array[y][x] == '1' || map->visited[y][x])
        return;

    map->visited[y][x] = true;

    // Continue to adjacent cells
    for (int i = 0; i < 4; ++i) {
        size_t new_x = x + dx[i];
        size_t new_y = y + dy[i];
        if (new_x < map->row_widths[new_y] && new_y < map->height) {
            dfs(map, new_x, new_y);
        }
    }
}

bool check_navigability(t_map *map) {
    // Check if the boundary is closed
    if (!is_boundary_closed(map)) {
        printf("Boundary check failed.\n");
        return false;
    }

    // Initialize the visited array
    map->visited = calloc(map->height, sizeof(bool *));
    if (map->visited == NULL)
        return false;

    for (size_t i = 0; i < map->height; ++i) {
        map->visited[i] = calloc(map->row_widths[i], sizeof(bool));
        if (map->visited[i] == NULL) {
            for (size_t k = 0; k < i; ++k)
                free(map->visited[k]);
            free(map->visited);
            return false;
        }
    }

    // Perform DFS from the player's starting position
    map->closed = true;
    dfs(map, map->player_x, map->player_y);

    // Check if all accessible areas are enclosed
    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->row_widths[y]; x++) {
            if (map->array[y][x] == '0' && !map->visited[y][x]) {
                map->closed = false;
                break;
            }
        }
        if (!map->closed) {
            break;
        }
    }

    // Print visited map for debugging
    print_visited_map(map);

    // Free the visited array
    for (size_t i = 0; i < map->height; ++i)
        free(map->visited[i]);
    free(map->visited);

    return map->closed;
}

// Example usage:
int main() {
    t_map map;
    char *array[] = {
        "11111",
        "10001",
        "10S01",
        "10001",
        "10001",
        "1000111",
        "1100001",
        "1000111",
        "10001",
        "10001",
        "10001",
        "10001",
        "11111"
    };

    map.array = array;
    map.height = sizeof(array) / sizeof(array[0]);
    map.row_widths = malloc(map.height * sizeof(size_t));
    if (map.row_widths == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    // Find player starting position and calculate row widths
    map.closed = false;
    for (size_t y = 0; y < map.height; y++) {
        map.row_widths[y] = strlen(array[y]);
        for (size_t x = 0; x < map.row_widths[y]; x++) {
            if (array[y][x] == 'S') {
                map.player_x = x;
                map.player_y = y;
                break;
            }
        }
    }

    bool closed = check_navigability(&map);
    printf("Map is %s\n", closed ? "closed" : "not closed");

    // Free allocated memory
    free(map.row_widths);
    return 0;
}

