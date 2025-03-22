#include <math.h>
#include "matrix.h"

static void multiply(
    float matrix[4][4],
    const float a[4][4],
    const float b[4][4])
{
    float c[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                c[i][j] += a[k][j] * b[i][k];
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = c[i][j];
        }
    }
}

static void translate(
    float matrix[4][4],
    const float x,
    const float y,
    const float z)
{
    matrix[0][0] = 1.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f;
    matrix[1][1] = 1.0f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 1.0f;
    matrix[2][3] = 0.0f;
    matrix[3][0] = x;
    matrix[3][1] = y;
    matrix[3][2] = z;
    matrix[3][3] = 1.0f;
}

static void rotate(
    float matrix[4][4],
    const float x,
    const float y,
    const float z,
    const float angle)
{
    const float s = sinf(angle);
    const float c = cosf(angle);
    const float i = 1.0f - c;
    matrix[0][0] = i * x * x + c;
    matrix[0][1] = i * x * y - z * s;
    matrix[0][2] = i * z * x + y * s;
    matrix[0][3] = 0.0f;
    matrix[1][0] = i * x * y + z * s;
    matrix[1][1] = i * y * y + c;
    matrix[1][2] = i * y * z - x * s;
    matrix[1][3] = 0.0f;
    matrix[2][0] = i * z * x - y * s;
    matrix[2][1] = i * y * z + x * s;
    matrix[2][2] = i * z * z + c;
    matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

static void perspective(
    float matrix[4][4],
    const float fov,
    const float aspect,
    const float near,
    const float far)
{
    const float f = 1.0f / tanf(fov / 2.0f);
    matrix[0][0] = f / aspect;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f;
    matrix[1][1] = f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = -(far + near) / (far - near);
    matrix[2][3] = -1.0f;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = -(2.0f * far * near) / (far - near);
    matrix[3][3] = 0.0f;
}

void get_view_proj(
    float matrix[4][4],
    const float fov,
    const float width,
    const float height,
    const float near,
    const float far,
    const float distance,
    const float pitch,
    const float yaw)
{
    float a[4][4];
    float b[4][4];
    const float x = distance * sinf(yaw) * cosf(pitch);
    const float y = distance * cosf(yaw) * cosf(pitch);
    const float z = distance * sinf(pitch);
    translate(a, -x, -y, -z);
    rotate(b, cosf(yaw), 0.0f, sinf(yaw), pitch);
    multiply(a, b, a);
    rotate(b, 0.0f, 1.0f, 0.0f, -yaw);
    multiply(a, b, a);
    perspective(b, fov, width / height, near, far);
    multiply(matrix, b, a);
}