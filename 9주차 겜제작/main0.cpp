#include <stdio.h>
#include <math.h>
#include <windows.h> // Sleep 함수를 사용하기 위해 포함

#define WIDTH 40
#define HEIGHT 20
#define CENTER_X 20
#define CENTER_Y 10
#define INITIAL_X 30 // 초기 x 위치 (30, 20)
#define INITIAL_Y 20 // 초기 y 위치 (30, 20)
#define DISTANCE 15

// M_PI 정의
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void draw_star(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        printf("\033[%d;%dH*", y + 1, x + 1); // +1 to account for terminal's 1-indexing
    }
}

void clear_screen() {
    printf("\033[H\033[J"); // 화면 지우기
}

int main() {
    // 각도 초기화
    int angle = 0;

    // 무한 루프
    while (1) {
        clear_screen(); // 화면 지우기

        // (20, 10)을 중심으로 (30, 20)에서 시작하여 5칸 떨어진 별의 위치 계산
        double radians = angle * M_PI / 180; // 각도를 라디안으로 변환
        int x = CENTER_X + (int)(DISTANCE * cos(radians)); // x 좌표
        int y = CENTER_Y + (int)(DISTANCE * 0.5 * sin(radians)); // y 좌표

        // 별 찍기
        draw_star(CENTER_X, CENTER_Y); // 중앙 별 찍기
        draw_star(x, y); // 회전하는 별 찍기

        // 화면 업데이트
        printf("\033[0m"); // 색상 초기화

        // 3초 대기 (100 밀리초)
        Sleep(100);
        angle += 15; // 각도 10도 증가
        if (angle >= 360) {
            angle -= 360; // 각도가 360도 이상이면 다시 0도로
        }
    }

    return 0;
}
