#include <stdio.h>

#define Y_START 1
#define Y_LIMIT 23
#define X_LIMIT 78
#define RACKET_SIZE 3

void render_canvas(int ball_x, int ball_y, int racket_first_pos, int racket_second_pos);
int move_ball_x(int ball_x, char direction_rl);
int move_ball_y(int ball_y, char direction_ud);
int move_racket(int cur_pos, int move);
int update_move(char action, char up, char down);
char switch_direction_rl(int ball_x, int racket_first_pos, int racket_second_pos, char direction_rl, int flag);
char switch_direction_ud(int ball_y, int racket_first_pos, int racket_second_pos, char direction_ud);
int flag_to_switch_rl(int ball_y, int racket_first_pos, int racket_second_pos);


int main() {
    int p1 = 0;
    int p2 = 0;
    char action;
    int win = 0;
    int ball_y = 12;
    int ball_x = 38;
    char direction_rl = 'r';
    char direction_ud = 'd';

    int racket_first_move = 1, racket_second_move = -1, racket_first_pos = Y_START,
        racket_second_pos = Y_LIMIT - RACKET_SIZE + 1, new_move;
    char up_first = 'z', down_first = 'a', up_second = 'm',
        down_second = 'k';

    while (!win) {
        int flag;
        render_canvas(ball_x, ball_y, racket_first_pos, racket_second_pos);
        scanf("%c", &action);
        ball_x = move_ball_x(ball_x, direction_rl);
        ball_y = move_ball_y(ball_y, direction_ud);
        direction_ud = switch_direction_ud(ball_y, racket_first_pos, racket_second_pos, direction_ud);
        flag = flag_to_switch_rl(ball_y, racket_first_pos, racket_second_pos);
        direction_rl = switch_direction_rl(ball_x, racket_first_pos, racket_second_pos, direction_rl, flag);

        if ((new_move = update_move(action, up_first, down_first)) != 0)
            racket_first_move = new_move;
        if ((new_move = update_move(action, up_second, down_second)) != 0)
            racket_second_move = new_move;

        racket_first_pos = move_racket(racket_first_pos, racket_first_move);
        racket_second_pos = move_racket(racket_second_pos, racket_second_move);
        
        //if (p1 == 21) {
        //    printf("Player 1 wins!");
        //} else if (p2 == 21) {
        //    printf("Player 2 wins!");
        //}
    }
    return 0;
}


void render_canvas(int ball_x, int ball_y, int racket_first_pos, int racket_second_pos){
    char border_lr = '|';
    char border_ud = '-';
    char racket_left = ']';
    char racket_right = '[';
    char ball = 'O';
    printf("\033[H\033[J");
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == ball_y && j == ball_x) {
                printf("%c", ball);
            } else if (i >= racket_first_pos && i <= racket_first_pos + 2 && j == 1) {
                printf("%c", racket_left);
            } else if (i >= racket_second_pos && i <= racket_second_pos + 2 && j == X_LIMIT) {
                printf("%c", racket_right);
            } else if (i == 0 || i == 24) {
                printf("%c", border_ud);
            } else if (i > 0 && i < 24 && (j == 38)) {
                printf("%c", border_lr);
            } else { printf(" "); }
        }
        printf("\n");
    }
}

int move_ball_x(int ball_x, char direction_rl) {
    if (direction_rl == 'r'){
        ball_x = ball_x + 1;
    } else {
        ball_x = ball_x - 1;
    }
    return ball_x;
}

int move_ball_y(int ball_y, char direction_ud) {
    if (direction_ud == 'u'){
        ball_y = ball_y - 1;
    } else {
        ball_y = ball_y + 1;
    }
    return ball_y;
}

int update_move(char action, char up, char down) {
    int flag = 0;
    if (action == up)
        flag = 1;
    if (action == down)
        flag = -1;
    return flag;
}

int move_racket(int cur_pos, int move) {
    if (cur_pos + RACKET_SIZE - 1 >= Y_LIMIT && move > 0)
        return cur_pos;
    if (cur_pos <= Y_START && move < 0)
        return cur_pos;
    return cur_pos + move;
}

char switch_direction_rl(int ball_x, int racket_first_pos, int racket_second_pos, char direction_rl, int flag) {
    if (ball_x == 79) { //loose
        direction_rl = 'l';
    } else if (ball_x == 0) {
        direction_rl = 'r';
    }
    if (ball_x == 77 && flag == 1) {
        direction_rl = 'l';
    } else if (ball_x == 2 && flag == 1) {
        direction_rl = 'r';
    }
    return direction_rl;
}

char switch_direction_ud(int ball_y, int racket_first_pos, int racket_second_pos, char direction_ud) {
    if (ball_y == 23) {
        direction_ud = 'u';
    } else if (ball_y == 1) {
        direction_ud = 'd';
    }
    return direction_ud;

}

int flag_to_switch_rl(int ball_y, int racket_first_pos, int racket_second_pos) {
    int tmp;
    if (ball_y == racket_first_pos + 1 || ball_y == racket_first_pos + 2 || ball_y == racket_first_pos) {
        tmp = 1;
    }
    if (ball_y == racket_second_pos + 1 || ball_y == racket_second_pos + 2 || ball_y == racket_second_pos) {
        tmp = 1;
    }
    return tmp;
}
