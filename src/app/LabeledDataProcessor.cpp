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

    for (int i = 0; i < _picture._pixel_num; ++i)
    {
        int label = 0;
        const Pixel *pixel = _picture.get_pixel_by_index(i);
        const Pixel *positive_pixel = _positive_picture.get_pixel_by_index(i);
        const Pixel *negtive_pixel = _negtive_picture.get_pixel_by_index(i);

        if (*pixel != *positive_pixel)
        {
            label = 1;
        }
        else if (*pixel != *negtive_pixel)
        {
            label = -1;
        }

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
    return 0;
}