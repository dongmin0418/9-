#include <stdio.h>
#include <math.h>
#include <windows.h> // Sleep �Լ� ����� ���� �߰�

#define WIDTH 40 // ���� ���� ����
#define HEIGHT 20 // ���� ���� ����
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void clearScreen() {
    system("cls"); // Windows���� �ܼ� ȭ�� �����
}

void draw(int angle) {
    clearScreen();

    // P ��ġ
    int pX = WIDTH / 2;
    int pY = HEIGHT / 2;

    // O�� ��ġ ��� (���� ������ ����)
    float radian = angle * M_PI / 180; // ������ �������� ��ȯ
    int oX = (int)(pX + 10 * cos(radian)); // O�� X ��ġ (���� ���� ����)
    int oY = (int)(pY + 5 * sin(radian)); // O�� Y ��ġ

    // ȭ�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("P"); // P ���
            }
            else if (x == oX && y == oY) {
                printf("O"); // O ���
            }
            else {
                printf(" "); // �� ���� ���
            }
        }
        printf("\n");
    }
}

int main() {
    for (int angle = 0; angle < 360; angle += 5) {
        draw(angle); // ȸ�� ������ ���� �׸���
        Sleep(100); // 0.1�� ���
    }
    return 0;
}