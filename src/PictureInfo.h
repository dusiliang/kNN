#ifndef __KNN_PICTURE_INFO_H__
#define __KNN_PICTURE_INFO_H__

class DataProcessor;

class PictureInfo
{
    friend class DataProcessor;

public:
    PictureInfo () {}
    ~PictureInfo () {}

    virtual int set_picture_data(const char *data, const int size);

private:
    /* data */
    int file_size;
    int bmp_offset;
    char *_data;
};

#endif
