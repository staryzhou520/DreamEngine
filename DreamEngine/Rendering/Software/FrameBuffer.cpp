#include "FrameBuffer.h"

#include <algorithm>   // std::fill


// _buffer 里面都换成纯黑色的
void FrameBuffer::Clear(SColor color)
{
    std::fill(_buffer.begin(), _buffer.end(), color);
}

void FrameBuffer::SetPixel(int x, int y, SColor color)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
    {
        return;
    }

    _buffer[y * _width + x] = color;
}
