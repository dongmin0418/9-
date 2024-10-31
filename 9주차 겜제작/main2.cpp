#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;


// 3x3 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                mat->m[i][j] = 1;
            }
            else {
                mat->m[i][j] = 0;
            }
        }
    }
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx; // X축 이동
    mat.m[1][2] = ty; // Y축 이동
    return mat;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian); // cos(θ)
    mat.m[0][1] = -sin(radian); // -sin(θ)
    mat.m[1][0] = sin(radian); // sin(θ)
    mat.m[1][1] = cos(radian); // cos(θ)
    return mat;
}

// 행렬 곱셈
Matrix3x3 multiplyMatrices(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 점을 변환
void transformPoint(float* x, float* y, Matrix3x3 mat) {
    float newX = mat.m[0][0] * *x + mat.m[0][1] * *y + mat.m[0][2];
    float newY = mat.m[1][0] * *x + mat.m[1][1] * *y + mat.m[1][2];
    *x = newX;
    *y = newY;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}



// 화면 그리기
void draw(int angle) {
    clearScreen();

    // Sun 위치
    int sX = WIDTH / 2;
    int sY = HEIGHT / 2;

    // Earth의 초기 위치
    float eX = 0.0f;
    float eY = 0.0f;
    
    float mX = 0.0f;
    float mY = 0.0f;


    // 이동 행렬 생성 (Sun와의 거리)
    Matrix3x3 translationDistS = createTranslationMatrix (0, 6);
    // Earth와의 거리
    Matrix3x3 translationDistE = createTranslationMatrix (0, 5);

    // 회전 행렬 생성
    Matrix3x3 rotationE = createRotationMatrix(angle); // Earth 회전
    Matrix3x3 rotationM = createRotationMatrix(angle * 12); // Moon 더 빨리 회전 

    Matrix3x3 translationToS = createTranslationMatrix(sX, sY);
    Matrix3x3 translationToE = createTranslationMatrix(0, 5);

    // Earth의 위치 변환
    Matrix3x3 combinedE = multiplyMatrices(rotationE, translationDistS);
    combinedE = multiplyMatrices(translationToS, combinedE);
    transformPoint(&eX, &eY, combinedE);

    // Moon의 위치 변환
    Matrix3x3 combinedM = multiplyMatrices(rotationM, translationDistE);
    combinedM = multiplyMatrices(createTranslationMatrix(eX,eY), combinedM);
    transformPoint(&mX, &mY, combinedM);

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sX && y == sY) {
                printf("S"); // sun 출력
            }
            else if ((int)eX == x && (int)eY == y) {
                printf("E"); // Earth 출력
            }
            else if ((int)mX == x && (int)mY == y) {
                printf("M"); // Moon 출력
            }
            else {
                printf(" "); // 빈 공간 출력
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