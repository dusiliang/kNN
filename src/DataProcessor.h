#ifndef __KNN_DATA_PROCESSOR_H__
#define __KNN_DATA_PROCESSOR_H__

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

private:
    int read_smallend(const char *ori, int size, int *result);

    /* data */
    PictureInfo *_picture;
};

#endif
