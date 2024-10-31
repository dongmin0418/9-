#include <stdio.h>
#include <math.h>
#include <windows.h> // Sleep �Լ��� ����ϱ� ���� ����

#define WIDTH 40
#define HEIGHT 20
#define CENTER_X 20
#define CENTER_Y 10
#define INITIAL_X 30 // �ʱ� x ��ġ (30, 20)
#define INITIAL_Y 20 // �ʱ� y ��ġ (30, 20)
#define DISTANCE 15

// M_PI ����
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void draw_star(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        printf("\033[%d;%dH*", y + 1, x + 1); // +1 to account for terminal's 1-indexing
    }
}

void clear_screen() {
    printf("\033[H\033[J"); // ȭ�� �����
}

int main() {
    // ���� �ʱ�ȭ
    int angle = 0;

    // ���� ����
    while (1) {
        clear_screen(); // ȭ�� �����

        // (20, 10)�� �߽����� (30, 20)���� �����Ͽ� 5ĭ ������ ���� ��ġ ���
        double radians = angle * M_PI / 180; // ������ �������� ��ȯ
        int x = CENTER_X + (int)(DISTANCE * cos(radians)); // x ��ǥ
        int y = CENTER_Y + (int)(DISTANCE * 0.5 * sin(radians)); // y ��ǥ

        // �� ���
        draw_star(CENTER_X, CENTER_Y); // �߾� �� ���
        draw_star(x, y); // ȸ���ϴ� �� ���

        // ȭ�� ������Ʈ
        printf("\033[0m"); // ���� �ʱ�ȭ

        // 3�� ��� (100 �и���)
        Sleep(100);
        angle += 15; // ���� 10�� ����
        if (angle >= 360) {
            angle -= 360; // ������ 360�� �̻��̸� �ٽ� 0����
        }
    }

    return 0;
}
