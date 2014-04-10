#ifndef __KNN_DATA_PROCESSOR_H__
#define __KNN_DATA_PROCESSOR_H__ value

#include <string>
#include "PictureInfo.h"

class DataProcessor
{
public:
    DataProcessor ();
    DataProcessor (PictureInfo *picture);
    ~DataProcessor ();

    int load_bmp_file(const string &name);
    int generate_train_data(const string &name);

private:
    int read_smallend(const string &ori);

    /* data */
    PictureInfo *_picture;
};

#endif
