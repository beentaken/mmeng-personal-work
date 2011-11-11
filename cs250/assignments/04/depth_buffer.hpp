#pragma once
#ifndef DEPTH_BUFFER_H
#define DEPTH_BUFFER_H

#include <vector>

class DepthBuffer
{
    public:
        DepthBuffer(int width, int height, float far);

        bool test(int x, int y, float z);
        void clear();

    private:
        std::vector<std::vector<float>> myBuffer;

        float myFarPlane;
};

#endif // DEPTH_BUFFER_H

