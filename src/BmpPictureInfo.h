#ifndef __BMPPICTUREINFO_H__
#define __BMPPICTUREINFO_H__

#include "PictureInfo.h"

class BmpPixel : public Pixel
{
public:
    BmpPixel() {}
    ~BmpPixel() {}

    virtual int set_data(const char *data);

    static const int _pixel_size = 3;
};

class BmpPictureInfo : public PictureInfo
{
public:
    BmpPictureInfo ();
    virtual ~BmpPictureInfo ();

    virtual int set_picture_data(const char *data, const int size);
    virtual Pixel *get_pixel_by_index(int index);

private:
    /* data */
    BmpPixel *_data;
};

#endif
