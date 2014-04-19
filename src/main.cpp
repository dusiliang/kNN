#include <iostream>
#include "DataProcessor.h"
#include "PictureInfo.h"

using namespace std;

int main(int argc, char *argv[])
{
    PictureInfo picture_info;
    DataProcessor data_processor(&picture_info);
    data_processor.load_bmp_file("/Users/maxwelldu/Pictures/1_inch_bmp.bmp");

    vector<char> p;
    p.push_back(25);
    p.push_back(25);
    p.push_back(25);
    Pixel black_pixel;
    black_pixel.set_pixel(p);
    data_processor.set_pixel(0, black_pixel);
    data_processor.set_pixel(1, black_pixel);
    data_processor.set_pixel(2, black_pixel);
    data_processor.set_pixel(3, black_pixel);
    data_processor.set_pixel(4, black_pixel);
    data_processor.set_pixel(5, black_pixel);

    data_processor.generate_train_data("knn_train_data");

    //data_processor.output_image("/Users/maxwelldu/Pictures/kNN_test.bmp");

    return 0;
}
