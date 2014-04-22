#include <iostream>
#include "DataProcessor.h"
#include "knn.h"
#include "PictureInfo.h"

using namespace std;

int main(int argc, char *argv[])
{
    PictureInfo picture_info;
    DataProcessor data_processor(&picture_info);
    data_processor.load_bmp_file(argv[1]);

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

    KNN knn(atoi(argv[2]));
    knn.load_training_data("knn_train_data");
    cout << "training set size: " << knn.get_training_set_size() << endl;
    /*
    cout << "distance: " << knn.get_distance(1, 2) << endl;
    cout << "distance: " << knn.get_distance(1, 3) << endl;
    cout << "distance: " << knn.get_distance(1, 592) << endl;
    cout << "distance: " << knn.get_distance(2, 592) << endl;
    list<Neighbor> neighbors;
    knn.get_k_nearest(0, 8, neighbors);
    for (list<Neighbor>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        cout << (*it)._index << "\t" << (*it)._distance << endl;
    }
    */
    knn.do_train(8);
    knn.write_result("knn_train_result");

    data_processor.load_train_result("knn_train_result");
    data_processor.output_image("result_bmp.bmp");

    return 0;
}
