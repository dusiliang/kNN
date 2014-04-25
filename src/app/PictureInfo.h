#ifndef __KNN_PICTURE_INFO_H__
#define __KNN_PICTURE_INFO_H__

#include <vector>

using namespace std;

class DataProcessor;

class Pixel
{
public:
    Pixel();
    ~Pixel();

    int set_pixel(const vector<char> &pixel);
    int set_pixel(const Pixel &pixel);
    int set_data(const char *data);
    void write_to_file(ofstream &out_file) const;
    bool operator==(const Pixel &pixel) const;
    bool operator!=(const Pixel &pixel) const;

    int _pixel_size;
    vector<unsigned char> _data;
};

class PictureInfo
{
    friend class DataProcessor;
    friend class LabeledDataProcessor;

public:
    PictureInfo ();
    ~PictureInfo ();

    int set_picture_data(const char *data, const int size, const int  pixel_size);
    int set_picture_meta_data(const char *data, const int size);
    const Pixel *get_pixel_by_index(const int index) const;
    void write_to_file(ofstream &out_file) const;
    int set_pixel(const int index, const Pixel &pixel);

private:
    /* data */
    int _file_size;
    int _bmp_offset;
    int _head_size;
    int _image_width;
    int _image_height;
    int _pixel_num;
    char *_meta_data;
    Pixel *_data;
};

#endif
