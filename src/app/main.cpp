#include <iostream>

#include "LabeledDataProcessor.h"
#include "LabeledKnn.h"
#include "SLDConfig.h"
#include "SLDString.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " config" << endl;
        return -1;
    }

    SLDConfig config(argv[1]);
    config.output_config();
    const map<string, string> config_map = config.get_config();
    const string base_image_name = config_map.at("base_image_name");
    const string positive_image_name = config_map.at("positive_image_name");
    const string negtive_image_name = config_map.at("negtive_image_name");
    const string train_file_name = config_map.at("train_file_name");
    const string train_result_name = config_map.at("train_result_name");
    const string image_result_name = config_map.at("image_result_name");
    const string is_make_train_data = config_map.at("make_train_data");

    LabeledDataProcessor data_processor;
    data_processor.load_base_bmp_file(base_image_name);
    if (is_make_train_data.at(0) == 'y' || is_make_train_data.at(0) == 'Y')
    {
        data_processor.load_positive_image(positive_image_name);
        data_processor.load_negtive_image(negtive_image_name);
        int train_data_num = data_processor.generate_train_data(train_file_name);
        cout << "generate train data done! " << train_data_num << endl;
    }

    LabeledKnn knn(atoi(config_map.at("k").c_str()));
    int train_data_size = knn.load_training_data(train_file_name);
    cout << "train data size: " << train_data_size << endl;
    cout << "start training, k = " << knn.get_k() << endl;
    knn.do_train();
    knn.output_result(train_result_name);
    cout << "train done!" << endl;

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
