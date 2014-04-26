#ifndef __KNN_LABELED_DATA_PROCESSOR_H__
#define __KNN_LABELED_DATA_PROCESSOR_H__

#include <map>

#include "DataProcessor.h"

class LabeledDataProcessor : public DataProcessor
{
public:
    LabeledDataProcessor();
    virtual ~LabeledDataProcessor();

    int load_positive_image(const string &name);
    int load_negtive_image(const string &name);
    int generate_train_data(const string &name);
    int load_train_result(const string &name);
    int output_result(const string &name) const;

protected:
    void set_color(map<int, Pixel> &color_map);

    PictureInfo _positive_picture;
    PictureInfo _negtive_picture;
    PictureInfo _result_picture;
};

#endif
