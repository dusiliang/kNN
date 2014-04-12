#include <iostream>
#include <fstream>
#include <string>
#include "PictureInfo.h"

using namespace std;

Pixel::Pixel() : _pixel_size(0)
{}

Pixel::~Pixel()
{}

int Pixel::set_pixel(const vector<char> &pixel)
{
    for (int i = 0; i < pixel.size(); ++i)
    {
        _data.push_back(pixel[i]);
    }
    _pixel_size = pixel.size();
    return 0;
}

int Pixel::set_pixel(const Pixel &pixel)
{
    for (int i = 0; i < pixel._pixel_size; ++i)
    {
        _data[i] = pixel._data[i];
    }
    _pixel_size = pixel._pixel_size;
    return 0;
}

int Pixel::set_data(const char *data)
{
    if (_pixel_size == 0)
    {
        return -1;
    }

    for (int i = 0; i < _pixel_size; ++i)
    {
        _data.push_back(data[i]);
    }
    return 0;
}

void Pixel::write_to_file(ofstream &out_file) const
{
    for (int i = 0; i < _pixel_size; ++i)
    {
        out_file.put(_data[i]);
    }
}

PictureInfo::PictureInfo () :
        _file_size(0), _bmp_offset(0), _head_size(0),
        _image_width(0), _image_height(0), _pixel_num(0),
        _meta_data(0), _data(0)
{}

PictureInfo::~PictureInfo ()
{
    delete[] _meta_data;
    delete[] _data;
}

int PictureInfo::set_picture_meta_data(const char *data, const int size)
{
    if (size == 0)
    {
        return 0;
    }

    _meta_data = new char[size];
    memcpy(_meta_data, data, size);

    return 0;
}

const Pixel *PictureInfo::get_pixel_by_index(const int index) const
{
    return _data + index;
}

int PictureInfo::set_picture_data(
        const char *data, const int size, const int pixel_size)
{
    if (pixel_size == 0)
    {
        return -1;
    }
    if (size == 0)
    {
        return 0;
    }

    const char *pixel_ptr = data;
    _pixel_num = size / pixel_size;
    _data = new Pixel[_pixel_num];

    for (int i = 0; i < _pixel_num; ++i)
    {
        _data[i]._pixel_size = pixel_size;
        _data[i].set_data(pixel_ptr);
        pixel_ptr += pixel_size;
    }

    return 0;
}

void PictureInfo::write_to_file(ofstream &out_file) const
{
    if (!out_file)
    {
        return;
    }

    for (int i = 0; i < _pixel_num; ++i)
    {
        _data[i].write_to_file(out_file);
    }
}

int PictureInfo::set_pixel(const int index, const Pixel &pixel)
{
    if (pixel._pixel_size != _data[index]._pixel_size)
    {
        return -1;
    }
    _data[index].set_pixel(pixel);
    return 0;
}
