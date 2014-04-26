#include <iostream>
#include "LabeledDataProcessor.h"
#include "LabeledKnn.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 8)
    {
        cerr << "Usage: " << argv[0]
             << " base_image positive_image negtive_image train_file train_result k"
             << " result_image" << endl;
        return -1;
    }

    const string base_image_name = argv[1];
    const string positive_image_name = argv[2];
    const string negtive_image_name = argv[3];
    const string train_file_name = argv[4];
    const string train_result_name = argv[5];
    const string image_result_name = argv[7];

    LabeledDataProcessor data_processor;
    data_processor.load_base_bmp_file(base_image_name);
    /*
    data_processor.load_positive_image(positive_image_name);
    data_processor.load_negtive_image(negtive_image_name);
    int train_data_num = data_processor.generate_train_data(train_file_name);
    cout << "generate train data done! " << train_data_num << endl;

    LabeledKnn knn(atoi(argv[6]));
    int train_data_size = knn.load_training_data(train_file_name);
    cout << "train data size: " << train_data_size << endl;
    knn.do_train();
    knn.output_result(train_result_name);
    cout << "train done!" << endl;
    */

    cout << "loading train result..." << endl;
    data_processor.load_train_result(train_result_name);
    cout << "output result image..." << endl;
    if (data_processor.output_result(image_result_name) != 0)
    {
        cerr << "output result image error!" << endl;
    }
    cout << "output result image done!" << endl;

    return 0;
}
