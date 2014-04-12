#ifndef __KNN_PICTURE_INFO_H__
#define __KNN_PICTURE_INFO_H__

#include <vector>

using namespace std;

class DataProcessor;

class Pixel
{
public:
    Pixel() : _data(0) {}
    virtual ~Pixel() {}

    virtual int set_data(const char *data) = 0;

    vector<int> _data;
};

class PictureInfo
{
    friend class DataProcessor;

public:
    PictureInfo ();
    virtual ~PictureInfo ();

    virtual int set_picture_data(const char *data, const int size) = 0;
    virtual Pixel *get_pixel_by_index(const int index) = 0;

    inline int pixel_num() {return _pixel_num;}

private:
    /* data */
    int _file_size;
    int _bmp_offset;

protected:
    int _pixel_num;
};

#endif
