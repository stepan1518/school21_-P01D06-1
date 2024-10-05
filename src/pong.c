#include <stdio.h>

void render_canvas(int ball_x, int ball_y);
int move_ball_x(int ball_x, char direction);
int move_ball_y(int ball_y, char direction);

int main() {
    int p1 = 0;
    int p2 = 0;
    char action;
    int win = 0;
    int ball_y = 12;
    int ball_x = 39;
    char direction = 'r';
    while (!win) {
        render_canvas(ball_x, ball_y);
        scanf("%c", &action);
        ball_x = move_ball_x(ball_x, direction);
        ball_y = move_ball_y(ball_y, direction);
        printf("%d %d", ball_x, ball_y);
        if (ball_x == 79) {
            direction = 'l';
        } else if (ball_x == 1) {
            direction = 'r';
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
    for (int i = 0; i <= 25; i++) {
        for (int j = 0; j <= 80; j++) {
            if (i == ball_y && j == ball_x) {
                printf("%c", ball);
            } else if (i == 0 || i == 25) {
                printf("%c", border_ud);
            } else if (i > 0 && i < 25 && (j == 0 || j == 39 || j == 80)) {
                printf("%c", border_lr);
            } else { printf(" "); }
        }
        printf("\n");
    }
}

int move_ball_x(int ball_x, char direction) {
    if (direction == 'r'){
        return ball_x + 1;
    } else {
        return ball_x - 1;
    }
}

int move_ball_y(int ball_y, char direction) {
    if (direction == 'r'){
        return ball_y;
    } else {
        return ball_y;
    }
}