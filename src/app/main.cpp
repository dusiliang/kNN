#include <iostream>
#include "LabeledDataProcessor.h"
#include "knn.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "Usage: " << argv[0]
             << " base_image positive_image negtive_image train_file" << endl;
        return -1;
    }

    const string base_image_name = argv[1];
    const string positive_image_name = argv[2];
    const string negtive_image_name = argv[3];
    const string train_file_name = argv[4];

    LabeledDataProcessor data_processor;
    data_processor.load_base_bmp_file(base_image_name);
    data_processor.load_positive_image(positive_image_name);
    data_processor.load_negtive_image(negtive_image_name);
    data_processor.generate_train_data(train_file_name);

/*
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
    */

    /*
    KNN knn(atoi(argv[2]));
    knn.load_training_data("knn_train_data");
    cout << "training set size: " << knn.get_training_set_size() << endl;
    knn.do_train(8);
    knn.write_result("knn_train_result");

    data_processor.load_train_result("knn_train_result");
    data_processor.output_image("result_bmp.bmp");
    */

    return 0;
}
