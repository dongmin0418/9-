#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 40

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 3D 벡터 구조체
typedef struct {
    float x, y, w;
} vec3;

// 3x3 행렬 구조체
typedef struct {
    float m[3][3];
} Matrix3x3;

// 3x3 단위 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// 회전 행렬 생성
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

// 행렬 곱셈 (Matrix3x3 * Matrix3x3)
Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 벡터와 행렬의 곱셈 (vec3 * Matrix3x3)
vec3 MulVec(vec3 v, Matrix3x3 mat) {
    vec3 result;
    result.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.w * mat.m[0][2];
    result.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.w * mat.m[1][2];
    result.w = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.w * mat.m[2][2];
    return result;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(int angle) {
    clearScreen();

    // 태양의 위치
    int sX = WIDTH / 2;
    int sY = HEIGHT / 2;

    // 지구와 달의 초기 위치
    vec3 earthPos = { 0.0f, 0.0f, 1.0f };
    vec3 moonPos = { 0.0f, 0.0f, 1.0f };

    // 이동 및 회전 행렬 생성
    Matrix3x3 translationDistS = createTranslationMatrix(10, 6);
    Matrix3x3 translationDistE = createTranslationMatrix(0, 3);
    Matrix3x3 rotationE = createRotationMatrix(angle);
    Matrix3x3 rotationM = createRotationMatrix(angle * 12);
    Matrix3x3 translationToS = createTranslationMatrix(sX, sY);

    // 지구 위치 계산
    Matrix3x3 combinedE = Mul(rotationE, translationDistS);
    combinedE = Mul(translationToS, combinedE);
    earthPos = MulVec(earthPos, combinedE);

    // 달 위치 계산
    Matrix3x3 combinedM = Mul(rotationM, translationDistE);
    combinedM = Mul(createTranslationMatrix(earthPos.x, earthPos.y), combinedM);
    moonPos = MulVec(moonPos, combinedM);

    // 화면 출력
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sX && y == sY) {
                printf("S"); // 태양
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // 지구
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("M"); // 달
            }
            else {
                printf(" "); // 빈 공간
            }
        }
        printf("\n");
    }
}

int main() {
    for (int angle = 0; angle < 360; angle += 5) {
        draw(angle); // 회전 각도에 따라 그리기
        Sleep(100); // 0.1초 대기
    }
    return 0;
}
