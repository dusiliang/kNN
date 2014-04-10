#include <string.h>
#include "PictureInfo.h"

int PictureInfo::set_picture_data(const char *data, const int size)
{
    _data = new char[size];
    memcpy(_data, data, size);
    return 0;
}
