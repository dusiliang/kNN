#ifndef __KNN_DATA_PROCESSOR_H__
#define __KNN_DATA_PROCESSOR_H__

#include <fstream>
#include <string>
#include "PictureInfo.h"

using namespace std;

class DataProcessor
{
public:
    DataProcessor ();
    DataProcessor (PictureInfo *picture);
    ~DataProcessor ();

    int load_bmp_file(const string &name);
    int generate_train_data(const string &name);
    void output_image(const string &name);
    int set_pixel(const int index, const Pixel &pixel);

private:
    int read_smallend(const char *ori, int size, int *result);
    int read_image_num_info(ifstream &in_file, const int size, int *result);
    int read_image_str_info(ifstream &in_file, const int size, char *result);

    /* data */
    PictureInfo *_picture;
};

#endif
