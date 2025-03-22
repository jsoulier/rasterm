#pragma once

void get_view_proj(
    float matrix[4][4],
    const float fov, /* radians */
    const float width,
    const float height,
    const float near,
    const float far,
    const float distance,
    const float pitch, /* radians */
    const float yaw /* radians */ );