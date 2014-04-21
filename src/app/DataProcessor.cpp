#include <fstream>
#include <iostream>

#include "DataProcessor.h"

using namespace std;

DataProcessor::DataProcessor()
{}

DataProcessor::DataProcessor(PictureInfo *picture)
{
    _picture = picture;
}

DataProcessor::~DataProcessor()
{}

int DataProcessor::read_smallend(const char *ori, int size, int *result)
{
    // by swap
    if (size > 4)
    {
        return -1;
    }

    *result = 0;
    char *tmp = (char *)result;
    for (int i = 0; i < size; ++i)
    {
        tmp[i] = ori[i];
    }
    return 0;
}

int DataProcessor::read_image_str_info(
        ifstream &in_file, const int size, char *result)
{
    if (!in_file)
    {
        return -1;
    }
    in_file.read(result, size);
    return 0;
}

int DataProcessor::read_image_num_info(
        ifstream &in_file, const int size, int *result)
{
    if (!in_file)
    {
        return -1;
    }
    char *buf = new char[size];
    in_file.read(buf, size);
    if (read_smallend(buf, size, result) != 0)
    {
        return -1;
    }
    delete[] buf;
    return 0;
}

int DataProcessor::load_bmp_file(const string &name)
{
    ifstream in_file(name.c_str(), ifstream::binary);
    if (in_file)
    {
        char image_type[2];
        read_image_str_info(in_file, 2, image_type);
        cout << image_type << endl;

        read_image_num_info(in_file, 4, &(_picture->_file_size));
        cout << "file size: " << _picture->_file_size << endl;

        in_file.seekg(4, ios_base::cur); // 4 empty bytes
        read_image_num_info(in_file, 4, &(_picture->_bmp_offset));
        cout << "bmp offset: " << _picture->_bmp_offset << endl;

        // image head info
        read_image_num_info(in_file, 4, &(_picture->_head_size));
        cout << "head size: " << _picture->_head_size << endl;

        read_image_num_info(in_file, 4, &(_picture->_image_width));
        cout << "image width: " << _picture->_image_width << endl;

        read_image_num_info(in_file, 4, &(_picture->_image_height));
        cout << "image height: " << _picture->_image_height << endl;

        in_file.seekg(2, ios_base::cur);
        int pixel_size = 0;
        if (read_image_num_info(in_file, 2, &pixel_size) != 0)
        {
            cerr << "read pixel size error" << endl;
            return -1;
        }
        pixel_size /= 8;
        cout << "pixel size: " << pixel_size << endl;

        char *meta_data_buf = new char[_picture->_bmp_offset];
        in_file.seekg(0, ios_base::beg);
        in_file.read(meta_data_buf, _picture->_bmp_offset);
        _picture->set_picture_meta_data(meta_data_buf, _picture->_bmp_offset);
        delete[] meta_data_buf;

        // goto real picture data
        char *data_buf = new char[_picture->_file_size];
        in_file.seekg(_picture->_bmp_offset, ios_base::beg);
        in_file.read(data_buf, _picture->_file_size - _picture->_bmp_offset);
        cout << "pixel num before load data: " << _picture->_pixel_num << endl;
        _picture->set_picture_data(
                data_buf,
                _picture->_file_size - _picture->_bmp_offset,
                pixel_size);
        cout << "pixel num after load data: " << _picture->_pixel_num << endl;
        delete[] data_buf;

        /*
        Pixel *pixel = _picture->get_pixel_by_index(2);
        printf("%x, %x, %x\n", 0x000000FF & (char)(pixel->_data[0]),
                0x000000FF & (char)(pixel->_data[1]),
                0x000000FF & (char)(pixel->_data[2]));
                */

        in_file.close();
    }
    return 0;
}

int DataProcessor::generate_train_data(const string &name) const
{
    ofstream out_file(name.c_str());
    if (!out_file)
    {
        return -1;
    }

    for (int i = 0; i < _picture->_pixel_num; ++i)
    {
        const Pixel *pixel = _picture->get_pixel_by_index(i);
        out_file << i;

        unsigned int co[2];
        get_coordinate_by_index(i, co);
        out_file << "\t" << co[0] << "\t" << co[1];

        for (int j = 0; j < pixel->_pixel_size; ++j)
        {
            out_file << "\t" << (int)pixel->_data[j];
        }
        out_file << endl;
    }
    out_file.close();

    return 0;
}

void DataProcessor::output_image(const string &name) const
{
    ofstream out_file(name.c_str(), ios::binary);
    if (!out_file)
    {
        return;
    }
    out_file.write(_picture->_meta_data, _picture->_bmp_offset);
    _picture->write_to_file(out_file);
    out_file.close();
}

int DataProcessor::set_pixel(const int index, const Pixel &pixel)
{
    if (_picture->set_pixel(index, pixel) !=0 )
    {
        cerr << "error" << endl;
        return -1;
    }
    const Pixel *p = _picture->get_pixel_by_index(0);
    return 0;
}

void DataProcessor::get_coordinate_by_index(const int index, unsigned *result) const
{
    result[0] = index % _picture->_image_width;
    result[1] = index / _picture->_image_width;
}
