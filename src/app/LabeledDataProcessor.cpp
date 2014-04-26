#include <iostream>
#include <map>

#include "mylib.h"

#include "LabeledDataProcessor.h"

using namespace std;

LabeledDataProcessor::LabeledDataProcessor()
{}

LabeledDataProcessor::~LabeledDataProcessor()
{}

int LabeledDataProcessor::load_positive_image(const string &name)
{
    return load_bmp_file(name, &_positive_picture);
}

int LabeledDataProcessor::load_negtive_image(const string &name)
{
    return load_bmp_file(name, &_negtive_picture);
}

int LabeledDataProcessor::generate_train_data(const string &name)
{
    if (_picture._data == 0 || _positive_picture._data == 0 ||
        _negtive_picture._data == 0)
    {
        return -1;
    }

    ofstream out_file(name.c_str());
    if (!out_file)
    {
        return -1;
    }

    /*
    Pixel label_pixel;
    vector<char> tmp;
    tmp.push_back(0x35);
    tmp.push_back(0x9c);
    tmp.push_back(0x67);
    tmp.push_back(0xff);
    label_pixel.set_pixel(tmp);
    */

    int i;
    for (i = 0; i < _picture._pixel_num; ++i)
    {
        int label = 0;
        const Pixel *pixel = _picture.get_pixel_by_index(i);
        const Pixel *positive_pixel = _positive_picture.get_pixel_by_index(i);
        const Pixel *negtive_pixel = _negtive_picture.get_pixel_by_index(i);

        if (pixel->diff(positive_pixel) > 50)
        {
            label = 1;
        }
        else if (pixel->diff(negtive_pixel) > 50)
        {
            label = -1;
        }
        /*
        if (*pixel != *positive_pixel)
        {
            label = 1;
        }
        else if (*pixel != *negtive_pixel)
        {
            label = -1;
        }
        */

        out_file << i;
        unsigned int co[2];
        get_coordinate_by_index(i,co);
        out_file << "\t" << co[0] << "\t" << co[1];
        for (int j = 0; j < pixel->_pixel_size; ++j)
        {
            out_file << "\t" << (int)pixel->_data[j];
        }
        out_file << "\t" << label << endl;
    }
    out_file.close();
    return i;
}

void LabeledDataProcessor::set_color(map<int, Pixel> &color_map)
{
    Pixel pixel;
    pixel._pixel_size = _picture._pixel_size;
    char pixel_str[_picture._pixel_size];
    for (int i = 0; i < _picture._pixel_size; ++i)
    {
        pixel_str[i] = (unsigned char)'0';
    }
    pixel.set_data(pixel_str);
    color_map[1] = pixel;

    for (int i = 0; i < _picture._pixel_size; ++i)
    {
        pixel_str[i] = (unsigned char)0xFF;
    }
    pixel.set_data(pixel_str);
    color_map[-1] = pixel;
}

int LabeledDataProcessor::load_train_result(const string &name)
{
    ifstream in_file(name.c_str());
    if (!in_file)
    {
        return -1;
    }

    int status = 0;
    map<int, Pixel> label_color;
    set_color(label_color);

    _result_picture.copy_meta_data(_picture);
    string line;
    while (getline(in_file, line))
    {
        vector<string> fields;
        split_string(line, '\t', fields);

        Pixel pixel;
        pixel._pixel_size = _picture._pixel_size;
        char pixel_str[_picture._pixel_size];
        for (int i = 0; i < _picture._pixel_size; ++i)
        {
            pixel_str[i] = (unsigned char)atoi(fields[3+i].c_str());
        }
        pixel.set_data(pixel_str);
        int label = atoi(fields.back().c_str());
        if (label_color.find(label) == label_color.end())
        {
            label_color[label] = pixel;
        }
        if (set_pixel(_result_picture, atoi(fields[0].c_str()), label_color[label])
            != 0)
        {
            status = -1;
            break;
        }
    }
    in_file.close();
    return status;
}

int LabeledDataProcessor::output_result(const string &name) const
{
    return output_image(_result_picture, name);
}