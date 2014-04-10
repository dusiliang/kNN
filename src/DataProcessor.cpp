#include <fstream>
#include <iostream>

#include "DataProcessor.h"

using namespace std;

DataProcessor::DataProcessor()
{}

DataProcessor::DataProcessor(PictureInfo *picture)
{
    _picture = picture;
}

DataProcessor::~DataProcessor()
{}

int DataProcessor::read_smallend(const char *ori, int size, int *result)
{
    // by swap
    if (size > 4)
    {
        return -1;
    }

    *result = 0;
    char *tmp = (char *)result;
    for (int i = 0; i < size; ++i)
    {
        tmp[i] = ori[i];
    }
    return 0;
}

int DataProcessor::load_bmp_file(const string &name)
{
    ifstream in_file(name.c_str(), ifstream::binary);
    if (in_file)
    {
        char *p_buf = new char[1024 + 1024*1024*100];
        char *buf = p_buf;
        in_file.read(buf, 2);
        cout << buf << endl;
        buf += 2;

        int file_size = 0;
        in_file.read(buf, 4);
        if (read_smallend(buf, 4, &file_size) != 0)
        {
            cerr << "get file size error!" << endl;
            delete[] p_buf;
            in_file.close();
            return -1;
        }
        if (file_size > 1024*1024*100)
        {
            // if file size bigger than 100M
            cerr << "file size if too large to open: " << file_size << endl;
            return -1;
        }
        _picture->file_size = file_size;
        cout << "file size: " << _picture->file_size << endl;
        buf += 4;

        in_file.seekg(4, ios_base::cur);
        in_file.read(buf, 4);
        int bmp_offset = 0;
        if (read_smallend(buf, 4, &bmp_offset) != 0)
        {
            cerr << "get bmp offset error!" << endl;
            delete[] p_buf;
            in_file.close();
            return -1;
        }
        _picture->bmp_offset = bmp_offset;
        cout << "bmp offset: " << _picture->bmp_offset << endl;
        buf += 4;

        // goto real picture data
        in_file.seekg(bmp_offset, ios_base::beg);
        in_file.read(buf, file_size - bmp_offset);
        _picture->set_picture_data(buf, file_size - bmp_offset);

        delete[] p_buf;
        in_file.close();
    }
    return 0;
}

int DataProcessor::generate_train_data(const string &name)
{
    return 0;
}
