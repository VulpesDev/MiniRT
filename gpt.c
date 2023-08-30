#include "includes/vec3.h"
#include <stdio.h>

typedef struct {
    float m[4][4];
} Matrix4x4;

void createCameraTransformMatrix(t_vec3 vec3_unitdOrientation, Matrix4x4 *transformMatrix) {
    // Calculate the right vector (x-axis) using the cross product of the world up vector and vec3_unitd orientation vector
    t_vec3 worldUp = {0.0f, 1.0f, 0.0f}; // The world's up direction
    t_vec3 right = vec3_unit(vec3_cross(worldUp, vec3_unitdOrientation));

    // Calculate the local up vector (y-axis) by taking the cross product between vec3_unitd orientation vector and the right vector
    t_vec3 localUp = vec3_cross(vec3_unitdOrientation, right);

    // Calculate the forward vector (z-axis) by negating the vec3_unitd orientation vector
    t_vec3 forward = {-vec3_unitdOrientation.x, -vec3_unitdOrientation.y, -vec3_unitdOrientation.z};

    // Create the transformation matrix
    transformMatrix->m[0][0] = right.x;   transformMatrix->m[0][1] = right.y;   transformMatrix->m[0][2] = right.z;   transformMatrix->m[0][3] = 0.0f;
    transformMatrix->m[1][0] = localUp.x;  transformMatrix->m[1][1] = localUp.y;  transformMatrix->m[1][2] = localUp.z;  transformMatrix->m[1][3] = 0.0f;
    transformMatrix->m[2][0] = forward.x;  transformMatrix->m[2][1] = forward.y;  transformMatrix->m[2][2] = forward.z;  transformMatrix->m[2][3] = 0.0f;
    transformMatrix->m[3][0] = 0.0f;       transformMatrix->m[3][1] = 0.0f;       transformMatrix->m[3][2] = 0.0f;       transformMatrix->m[3][3] = 1.0f;
}

int main() {
    t_vec3 vec3_unitdOrientation = {0.5f, 0.3f, -0.8f}; // Example vec3_unitd orientation vector
    Matrix4x4 transformMatrix;

    createCameraTransformMatrix(vec3_unitdOrientation, &transformMatrix);

    // Print the transformation matrix
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%f ", transformMatrix.m[row][col]);
        }
        printf("\n");
    }

    return 0;
}
