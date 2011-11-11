#include "depth_buffer.hpp"

#include <algorithm>

DepthBuffer::DepthBuffer(int width, int height, float far)
    :myBuffer(height), myFarPlane(far)
{
    for (auto it = myBuffer.begin(); it != myBuffer.end(); ++it)
    {
        it->resize(width);
    }
}

bool DepthBuffer::test(int x, int y, float z)
{
    if (z < myBuffer[y][x])
    {
        myBuffer[y][x] = z;
        return(true);
    }

    return(false);
}

void DepthBuffer::clear()
{
    const float far_plane = myFarPlane;
    std::for_each(myBuffer.begin(), myBuffer.end(), [&far_plane](std::vector<float> &x)
            {
                std::fill(x.begin(), x.end(), far_plane);
            });
}

