#include "rotation.h"
#include "board.h"
#include <stdlib.h>


void rotation_get_topleft(int pivot_row, int pivot_col, int zone_size, int *top_row, int *left_col) {
    int half = zone_size / 2;
    *top_row = pivot_row - half;
    *left_col = pivot_col - half;
}

int rotation_is_valid_pivot(int pivot_row, int pivot_col, int zone_size, int piece_row, int piece_col) {
    int top_row, left_col;
    rotation_get_topleft(pivot_row, pivot_col, zone_size, &top_row, &left_col);

    // Vérifie si la zone sort du plateau
    if (top_row < 0 || top_row + zone_size > ROWS) {
    return 0;
  }
    if (left_col < 0 || left_col + zone_size > COLS) {
    return 0;
  }
    // Vérifie si la pièce posée est bien dans la zone
    if (piece_row < top_row || piece_row >= top_row + zone_size) {
    return 0;
  }
    if (piece_col < left_col || piece_col >= left_col + zone_size) {
    return 0;
  }

    return 1;
}

void rotation_rotate_zone(Board *b, int pivot_row, int pivot_col, int zone_size, int direction) {
    int r, c;
    int top_row, left_col;
    rotation_get_topleft(pivot_row, pivot_col, zone_size, &top_row, &left_col);

    int tmp[5][5]; // On suppose que zone_size max est 5
    for (r = 0; r < zone_size; r++) {
        for (c = 0; c < zone_size; c++) {
            tmp[r][c] = b->cells[top_row + r][left_col + c];
        }
    }

    int n = zone_size;
    if (direction == ROT_CLOCKWISE) {
        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                b->cells[top_row + c][left_col + n - 1 - r] = tmp[r][c];
            }
        }
    }
    else if (direction == ROT_COUNTERCLOCKWISE) {
        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                b->cells[top_row + n - 1 - c][left_col + r] = tmp[r][c];
            }
        }
    }
}

int rotation_random_size(){
    int a, b;
    b = rand()%100;
    if (b%2 == 0){
      a = 3;
    }
    if (b%2 == 1){
      a = 5;
    }
  return a;
}

















