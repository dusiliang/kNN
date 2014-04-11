#include "BmpPictureInfo.h"

int BmpPixel::set_data(const char *data)
{
    for (int i = 0; i < _pixel_size; ++i)
    {
        _data.push_back(data[i]);
    }
    return 0;
}

BmpPictureInfo::BmpPictureInfo() : _data(0)
{}

BmpPictureInfo::~BmpPictureInfo()
{
    delete[] _data;
}

int BmpPictureInfo::set_picture_data(const char *data, const int size)
{
    if (size == 0)
    {
        return 0;
    }

    const char *pixel_ptr = data;
    _pixel_num = size / BmpPixel::_pixel_size;
    _data = new BmpPixel[_pixel_num];

    for (int i = 0; i < _pixel_num; ++i)
    {
        _data[i].set_data(pixel_ptr);
        pixel_ptr += BmpPixel::_pixel_size;
    }

    return 0;
}

Pixel *BmpPictureInfo::get_pixel_by_index(int index)
{
    if (index >= _pixel_num)
    {
        return 0;
    }
    return _data + index;
}
