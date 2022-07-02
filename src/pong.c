#include <stdio.h>

#define WIDTH_SCRING 80
#define HEIGHT_SCRING 25

void screen_rendering(int ballX, int ballY, int rocket_one, int rocket_two, int score_o, int score_t);
int rocket_one_move(int rocket_o, int height_scring, char c);
int rocket_two_move(int rocket_t, int height_scring, char c);
int znach_ofs(int coorY, int height_scring, int ofs);
int znach_ofsX(int coorX, int coorY, int rocket_one_position, int rocket_two_position, int width_scring, int ofsX);
int score_add_two(int score, int coorX);
int score_add_one(int score, int coorX, int width_scring);
int win_score(int score_one, int score_two);
int start_stop_ball_x(int coorX, int width_scring);
int start_stop_ball_y(int coorX, int coorY, int width_scring, int height_scring);

int main() {
  int ball_position_x = WIDTH_SCRING / 2;
  int ball_position_y = HEIGHT_SCRING / 2;
  int rocket_one_position = HEIGHT_SCRING /2;
  int rocket_two_position = HEIGHT_SCRING /2;
  int score_one = 0;
  int score_two = 0;
  int offset = 1;
  int offsetX = 1;
  int game = 1;
  char c;

while(game) {
c = getchar();
if ((c == 'a') || (c == 'z')) {
       rocket_one_position = rocket_one_move(rocket_one_position, HEIGHT_SCRING, c);
} else if ((c == 'k') || (c == 'm')) {
           rocket_two_position = rocket_two_move(rocket_two_position, HEIGHT_SCRING, c);
}
offset = znach_ofs(ball_position_y, HEIGHT_SCRING, offset);
offsetX = znach_ofsX(ball_position_x, ball_position_y, rocket_one_position, rocket_two_position, WIDTH_SCRING, offsetX);
ball_position_x = start_stop_ball_x(ball_position_x, WIDTH_SCRING);

screen_rendering(ball_position_x, ball_position_y, rocket_one_position, rocket_two_position, score_one, score_two);

ball_position_y = ball_position_y + offset;
ball_position_x = ball_position_x + offsetX;
score_one = score_add_one(score_one, ball_position_x, WIDTH_SCRING);
score_two = score_add_two(score_two, ball_position_x);
game = win_score(score_one, score_two);
}
}

void screen_rendering(int ballX, int ballY, int rocket_one, int rocket_two, int score_o, int score_t) {
    for (int y = 0; y < HEIGHT_SCRING; ++y) {
        for (int x = 0; x < WIDTH_SCRING; ++x) {
             if (y == 2 && x == (WIDTH_SCRING / 2 - 5)) {
                 printf("%d", score_o);
             } else if (y == 2 && x == (WIDTH_SCRING / 2 + 5)) {
                 printf("%d", score_t);
             } else if ((y == ballY) && (x == ballX)) {
                 printf("0");
             } else if ((y == 0 && x != 0 && x != WIDTH_SCRING) ||
                        (y == HEIGHT_SCRING - 1 && x != 0 && x != WIDTH_SCRING - 1)) {
                printf("-");
            } else if ((x == 0 && y != 0 && y != HEIGHT_SCRING - 1) ||
                        (x == WIDTH_SCRING - 1 && y != 0 && y != HEIGHT_SCRING - 1) ||
                        (x == WIDTH_SCRING / 2) || (x == 3 && (y == rocket_one || y == rocket_one + 1 || y == rocket_one - 1)) ||
                        (x == WIDTH_SCRING - 4  && (y == rocket_two || y == rocket_two + 1 || y == rocket_two - 1))) {
                                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int rocket_one_move(int rocket_o, int height_scring, char c) {
    int f;
    if (c == 'a') {
        if (rocket_o < 3) {
             f = rocket_o;
        } else {
             f = rocket_o - 2;
        }
    } else if (c == 'z') {
        if (rocket_o > (height_scring - 4)) {
            f = rocket_o;
        } else {
            f = rocket_o + 2;
        }
    } else {
        f = rocket_o;
    }
    return f;
}

int rocket_two_move(int rocket_t, int height_scring, char c) {
    int f;
    if (c == 'k') {
        if (rocket_t < 3) {
             f = rocket_t;
        } else {
             f = rocket_t - 2;
        }
    } else if (c == 'm') {
        if (rocket_t > (height_scring - 4)) {
            f = rocket_t;
        } else {
            f = rocket_t + 2;
        }
    } else {
        f = rocket_t;
    }
    return f;
}


int znach_ofs(int coorY, int height_scring, int ofs) {
    if ((coorY == 1) || (coorY == height_scring - 1)) {
    ofs = -(ofs);
    }
    return ofs;
}

int znach_ofsX(int coorX, int coorY, int rocket_one_position, int rocket_two_position, int width_scring, int ofsX) {
    if ((coorX == 3 && (coorY == rocket_one_position || coorY == rocket_one_position + 1 ||
     coorY == rocket_one_position - 1)) || (coorX == width_scring - 4  && (coorY == rocket_two_position ||
     coorY == rocket_two_position + 1 || coorY == rocket_two_position - 1))) {
        ofsX = -(ofsX);
    }
    return ofsX;
}

int score_add_two(int score, int coorX) {
    if (coorX == 2) {
        score = score + 3;
    }
    return score;
}

int score_add_one(int score, int coorX, int width_scring) {
    if (coorX == width_scring - 2) {
        score = score + 3;
    }
    return score;
}

int win_score(int score_one, int score_two) {
    if ((score_one == 21) || (score_two == 21)) {
        if (score_one == 21) {
                printf("ПОЗДРАВЛЯЮ!!! Игрок 1 победил");
        } else {
            printf("ПОЗДРАВЛЯЮ!!! Игрок 2 победил");
        }
        return 0;
    } else {
        return 1;
    }
}

int start_stop_ball_x(int coorX, int width_scring) {
    if ((coorX == 1) || (coorX == width_scring - 1)) {
        return width_scring / 2;
    }
    return coorX;
}







