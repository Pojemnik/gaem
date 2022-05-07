#include "inputAdapter.h"

vec2 InputAdapter::mouseDeltaToCameraInput(vec2 delta)
{
    if (!enabled)
    {
        return vec2(0);
    }
    delta.x *= mouseSensitivity;
    delta.y *= mouseSensitivity;

    return delta;
}
