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
    int diff(const Pixel *p) const;
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
    int copy_meta_data(const PictureInfo &picture);

    inline int get_file_size() const {return _file_size;}
    inline int get_bmp_offset() const {return _bmp_offset;}
    inline int get_head_size() const {return _head_size;}
    inline int get_image_width() const {return _image_width;}
    inline int get_image_height() const {return _image_height;}
    inline int get_pixel_num() const {return _pixel_num;}
    inline int get_pixel_size() const {return _pixel_size;}
    inline int get_meta_data_size() const {return _meta_data_size;}
    inline const char *get_meta_data() const {return _meta_data;}

private:
    /* data */
    int _file_size;
    int _bmp_offset;
    int _head_size;
    int _image_width;
    int _image_height;
    int _pixel_num;
    int _pixel_size;
    int _meta_data_size;
    char *_meta_data;
    Pixel *_data;
};

#endif
