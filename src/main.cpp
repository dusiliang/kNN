#include "DataProcessor.h"
#include "BmpPictureInfo.h"

int main(int argc, char *argv[])
{
    BmpPictureInfo picture_info;
    DataProcessor data_processor(&picture_info);
    data_processor.load_bmp_file("/Users/maxwelldu/Pictures/1_inch_bmp.bmp");

    return 0;
}
