#include <stdio.h>

void render_canvas(int ball_x, int ball_y, int racket_first_pos, int racket_second_pos, int p1, int p2);
int move_ball_x(int ball_x, char direction_rl);
int move_ball_y(int ball_y, char direction_ud);
int move_racket(int cur_pos, int move);
int update_move(char action, char up, char down);
char switch_direction_rl(int ball_x, char direction_rl, int flag_first, int flag_second);
char switch_direction_ud(int ball_y, char direction_ud);
int flag_first_to_switch_rl(int ball_y, int racket_first_pos);
int flag_second_to_switch_rl(int ball_y, int racket_second_pos);
int flag_to_score(int ball_x);
int win_process(int p1, int p2);

int main() {
    int p1 = 0, p2 = 0;
    char action;
    int win = 0;
    int ball_y = 12, ball_x = 38;
    char direction_rl = 'r', direction_ud = 'd';
    int racket_first_move = 1, racket_second_move = -1, racket_first_pos = 1, racket_second_pos = 23 - 3 + 1;
    char up_first = 'z', down_first = 'a', up_second = 'm', down_second = 'k';
    render_canvas(ball_x, ball_y, racket_first_pos, racket_second_pos, p1, p2);
    while (!win) {
        int new_move;
        char trash;
        scanf("%c", &action);
        trash = action;
        while (trash != '\n') scanf("%c", &trash);
        int flag_first = 0;
        int flag_second = 0;
        if ((new_move = update_move(action, up_first, down_first)) != 0) racket_first_move = new_move;
        if ((new_move = update_move(action, up_second, down_second)) != 0) racket_second_move = new_move;
        racket_first_pos = move_racket(racket_first_pos, racket_first_move);
        racket_second_pos = move_racket(racket_second_pos, racket_second_move);
        ball_x = move_ball_x(ball_x, direction_rl);
        ball_y = move_ball_y(ball_y, direction_ud);
        direction_ud = switch_direction_ud(ball_y, direction_ud);
        flag_first = flag_first_to_switch_rl(ball_y, racket_first_pos);
        flag_second = flag_second_to_switch_rl(ball_y, racket_second_pos);
        direction_rl = switch_direction_rl(ball_x, direction_rl, flag_first, flag_second);
        render_canvas(ball_x, ball_y, racket_first_pos, racket_second_pos, p1, p2);
        if (flag_to_score(ball_x) == 1) {
            p1++;
            ball_x = 38;
            ball_y = 12;
        } else if (flag_to_score(ball_x) == 2) {
            p2++;
            ball_x = 38;
            ball_y = 12;
        }
        win = win_process(p1, p2);
        if (action == 'q') {
            break;
        }
    }
    return 0;
}

void render_canvas(int ball_x, int ball_y, int racket_first_pos, int racket_second_pos, int p1, int p2) {
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
            } else if (i >= racket_second_pos && i <= racket_second_pos + 2 && j == 78) {
                printf("%c", racket_right);
            } else if (i == 0 || i == 24) {
                printf("%c", border_ud);
            } else if (j == 38) {
                printf("%c", border_lr);
            } else if (i == 5 && j == 33) {
                printf("%d", p1);
            } else if (i == 5 && j == 43) {
                printf("%d", p2);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int move_ball_x(int ball_x, char direction_rl) {
    if (direction_rl == 'r') {
        ball_x = ball_x + 1;
    } else {
        ball_x = ball_x - 1;
    }
    return ball_x;
}

int move_ball_y(int ball_y, char direction_ud) {
    if (direction_ud == 'u') {
        ball_y = ball_y - 1;
    } else {
        ball_y = ball_y + 1;
    }
    return ball_y;
}

int update_move(char action, char up, char down) {
    int flag = 0;
    if (action == up) flag = 1;
    if (action == down) flag = -1;
    return flag;
}

int move_racket(int cur_pos, int move) {
    int res = cur_pos + move;
    if (cur_pos + 3 - 1 >= 23 && move > 0) res = cur_pos;
    if (cur_pos <= 1 && move < 0) res = cur_pos;
    return res;
}

char switch_direction_rl(int ball_x, char direction_rl, int flag_first, int flag_second) {
    if (ball_x == 77 && flag_second == 1) {
        direction_rl = 'l';
    } else if (ball_x == 2 && flag_first == 1) {
        direction_rl = 'r';
    }
    return direction_rl;
}

char switch_direction_ud(int ball_y, char direction_ud) {
    if (ball_y == 23) {
        direction_ud = 'u';
    } else if (ball_y == 1) {
        direction_ud = 'd';
    }
    return direction_ud;
}

int flag_first_to_switch_rl(int ball_y, int racket_first_pos) {
    int tmp = 0;
    if (ball_y == racket_first_pos + 1 || ball_y == racket_first_pos + 2 || ball_y == racket_first_pos) {
        tmp = 1;
    }
    return tmp;
}

int flag_second_to_switch_rl(int ball_y, int racket_second_pos) {
    int tmp = 0;
    if (ball_y == racket_second_pos + 1 || ball_y == racket_second_pos + 2 || ball_y == racket_second_pos) {
        tmp = 1;
    }
    return tmp;
}

int flag_to_score(int ball_x) {
    int flag = 0;
    if (ball_x == 79) {  // loose
        flag = 1;
    } else if (ball_x == 0) {
        flag = 2;
    }
    return flag;
}

int win_process(int p1, int p2) {
    int tmp = 0;
    if (p1 == 21) {
        printf("Player 1 wins!\n");
        tmp = 1;
    } else if (p2 == 21) {
        printf("Player 2 wins!\n");
        tmp = 1;
    }
    return tmp;
}