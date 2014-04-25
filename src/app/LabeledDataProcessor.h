#ifndef __KNN_LABELED_DATA_PROCESSOR_H__
#define __KNN_LABELED_DATA_PROCESSOR_H__

#include "DataProcessor.h"

class LabeledDataProcessor : public DataProcessor
{
public:
    LabeledDataProcessor();
    virtual ~LabeledDataProcessor();

    int load_positive_image(const string &name);
    int load_negtive_image(const string &name);
    int generate_train_data(const string &name);

protected:
    PictureInfo _positive_picture;
    PictureInfo _negtive_picture;
};

#endif
