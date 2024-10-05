#include <stdio.h>

void render_canvas(int ball_x, int ball_y);
int move_ball_x(int ball_x, char direction_rl);
int move_ball_y(int ball_y, char direction_ud);

int main() {
    int p1 = 0;
    int p2 = 0;
    char action;
    int win = 0;
    int ball_y = 12;
    int ball_x = 38;
    char direction_rl = 'r';
    char direction_ud = 'd';
    while (!win) {
        render_canvas(ball_x, ball_y);
        scanf("%c", &action);
        ball_x = move_ball_x(ball_x, direction_rl);
        ball_y = move_ball_y(ball_y, direction_ud);
        if (ball_x == 78) {
            direction_rl = 'l';
        } else if (ball_x == 1) {
            direction_rl = 'r';
        }
        if (ball_y == 23) {
            direction_ud = 'u';
        } else if (ball_y == 1) {
            direction_ud = 'd';
        }
        
        //if (p1 == 21) {
        //    printf("Player 1 wins!");
        //} else if (p2 == 21) {
        //    printf("Player 2 wins!");
        //}
    }
    return 0;
}


void render_canvas(int ball_x, int ball_y){
    char border_lr = '|';
    char border_ud = '-';
    //char rocket_left = "]";
    //char rocket_right = "[";
    char ball = 'O';
    printf("\033[H\033[J");
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == ball_y && j == ball_x) {
                printf("%c", ball);
            } else if (i == 0 || i == 24) {
                printf("%c", border_ud);
            } else if (i > 0 && i < 24 && (j == 0 || j == 38 || j == 79)) {
                printf("%c", border_lr);
            } else { printf(" "); }
        }
        printf("\n");
    }
}

int move_ball_x(int ball_x, char direction_rl) {
    if (direction_rl == 'r'){
        return ball_x + 1;
    } else {
        return ball_x - 1;
    }
}

int move_ball_y(int ball_y, char direction_ud) {
    if (direction_ud == 'u'){
        return ball_y - 1;
    } else {
        return ball_y + 1;
    }
}    