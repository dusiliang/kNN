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
    virtual ~DataProcessor ();

    int load_base_bmp_file(const string &name);

    int generate_train_data(const string &name) const;
    void output_image(const string &name) const;
    int set_pixel(const int index, const Pixel &pixel);
    void get_coordinate_by_index(const int index, unsigned *result) const;
    int load_train_result(const string &name);

private:
    int read_smallend(const char *ori, int size, int *result);
    int read_image_num_info(ifstream &in_file, const int size, int *result);
    int read_image_str_info(ifstream &in_file, const int size, char *result);

protected:
    int load_bmp_file(const string &name, PictureInfo *picture);
    
    /* data */
    PictureInfo _picture;

};

#endif
