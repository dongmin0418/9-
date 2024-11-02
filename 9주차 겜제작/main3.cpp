#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 40

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 3D ���� ����ü
typedef struct {
    float x, y, w;
} vec3;

// 3x3 ��� ����ü
typedef struct {
    float m[3][3];
} Matrix3x3;

// 3x3 ���� ��� �ʱ�ȭ
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

// �̵� ��� ����
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    return mat;
}

// ��� ���� (Matrix3x3 * Matrix3x3)
Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// ���Ϳ� ����� ���� (vec3 * Matrix3x3)
vec3 MulVec(vec3 v, Matrix3x3 mat) {
    vec3 result;
    result.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.w * mat.m[0][2];
    result.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.w * mat.m[1][2];
    result.w = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.w * mat.m[2][2];
    return result;
}

// �ܼ� ȭ�� �����
void clearScreen() {
    system("cls");
}

// ȭ�� �׸���
void draw(int angle) {
    clearScreen();

    // �¾��� ��ġ
    int sX = WIDTH / 2;
    int sY = HEIGHT / 2;

    // ������ ���� �ʱ� ��ġ
    vec3 earthPos = { 0.0f, 0.0f, 1.0f };
    vec3 moonPos = { 0.0f, 0.0f, 1.0f };

    // �̵� �� ȸ�� ��� ����
    Matrix3x3 translationDistS = createTranslationMatrix(10, 6);
    Matrix3x3 translationDistE = createTranslationMatrix(0, 3);
    Matrix3x3 rotationE = createRotationMatrix(angle);
    Matrix3x3 rotationM = createRotationMatrix(angle * 12);
    Matrix3x3 translationToS = createTranslationMatrix(sX, sY);

    // ���� ��ġ ���
    Matrix3x3 combinedE = Mul(rotationE, translationDistS);
    combinedE = Mul(translationToS, combinedE);
    earthPos = MulVec(earthPos, combinedE);

    // �� ��ġ ���
    Matrix3x3 combinedM = Mul(rotationM, translationDistE);
    combinedM = Mul(createTranslationMatrix(earthPos.x, earthPos.y), combinedM);
    moonPos = MulVec(moonPos, combinedM);

    // ȭ�� ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sX && y == sY) {
                printf("S"); // �¾�
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // ����
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("M"); // ��
            }
            else {
                printf(" "); // �� ����
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
