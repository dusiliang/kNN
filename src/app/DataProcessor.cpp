#include <fstream>
#include <iostream>
#include <map>

#include "mylib.h"
#include "DataProcessor.h"

using namespace std;

DataProcessor::DataProcessor()
{}

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

int DataProcessor::load_base_bmp_file(const string &name)
{
    return load_bmp_file(name, &_picture);
}

int DataProcessor::load_bmp_file(const string &name, PictureInfo *picture)
{
    ifstream in_file(name.c_str(), ifstream::binary);
    if (in_file)
    {
        char image_type[2];
        read_image_str_info(in_file, 2, image_type);
        cout << image_type << endl;

        read_image_num_info(in_file, 4, &(picture->_file_size));
        cout << "file size: " << picture->_file_size << endl;

        in_file.seekg(4, ios_base::cur); // 4 empty bytes
        read_image_num_info(in_file, 4, &(picture->_bmp_offset));
        cout << "bmp offset: " << picture->_bmp_offset << endl;

        // image head info
        read_image_num_info(in_file, 4, &(picture->_head_size));
        cout << "head size: " << picture->_head_size << endl;

        read_image_num_info(in_file, 4, &(picture->_image_width));
        cout << "image width: " << picture->_image_width << endl;

        read_image_num_info(in_file, 4, &(picture->_image_height));
        cout << "image height: " << picture->_image_height << endl;

        in_file.seekg(2, ios_base::cur);
        int pixel_size = 0;
        if (read_image_num_info(in_file, 2, &pixel_size) != 0)
        {
            cerr << "read pixel size error" << endl;
            return -1;
        }
        pixel_size /= 8;
        cout << "pixel size: " << pixel_size << endl;

        char *meta_data_buf = new char[picture->_bmp_offset];
        in_file.seekg(0, ios_base::beg);
        in_file.read(meta_data_buf, picture->_bmp_offset);
        picture->set_picture_meta_data(meta_data_buf, picture->_bmp_offset);
        delete[] meta_data_buf;

        // goto real picture data
        char *data_buf = new char[picture->_file_size];
        in_file.seekg(picture->_bmp_offset, ios_base::beg);
        in_file.read(data_buf, picture->_file_size - picture->_bmp_offset);
        cout << "pixel num before load data: " << picture->_pixel_num << endl;
        picture->set_picture_data(
                data_buf,
                picture->_file_size - picture->_bmp_offset,
                pixel_size);
        cout << "pixel num after load data: " << picture->_pixel_num << endl;
        delete[] data_buf;

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

    for (int i = 0; i < _picture._pixel_num; ++i)
    {
        const Pixel *pixel = _picture.get_pixel_by_index(i);
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

int DataProcessor::output_image(const PictureInfo &picture, const string &name) const
{
    ofstream out_file(name.c_str(), ios::binary);
    if (!out_file)
    {
        return -1;
    }
    out_file.write(picture._meta_data, picture._bmp_offset);
    picture.write_to_file(out_file);
    out_file.close();
    return 0;
}

int DataProcessor::set_pixel(
    PictureInfo &picture, const int index, const Pixel &pixel)
{
    if (picture.set_pixel(index, pixel) != 0)
    {
        return -1;
    }

    return 0;
}

void DataProcessor::get_coordinate_by_index(const int index, unsigned *result) const
{
    result[0] = index % _picture._image_width;
    result[1] = index / _picture._image_width;
}

int DataProcessor::load_train_result(const string &name)
{
    map<int, Pixel> label_color;

    ifstream in_file(name.c_str());
    if (!in_file)
    {
        return -1;
    }

    string line;
    while (getline(in_file, line))
    {
        vector<string> fields;
        split_string(line, '\t', fields);
        Pixel pixel;
        pixel._pixel_size = 3;
        char pixel_str[3];
        pixel_str[0] = (unsigned char)atoi(fields[3].c_str());
        pixel_str[1] = (unsigned char)atoi(fields[4].c_str());
        pixel_str[2] = (unsigned char)atoi(fields[5].c_str());
        pixel.set_data(pixel_str);
        int label = atoi(fields[6].c_str());
        if (label_color.find(label) == label_color.end())
        {
            label_color[label] = pixel;
        }

        set_pixel(_picture, atoi(fields[0].c_str()), label_color[label]);
    }
    in_file.close();
    return 0;
}
