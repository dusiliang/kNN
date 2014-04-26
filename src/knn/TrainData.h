#ifndef __TRAIN_DATA_H_
#define __TRAIN_DATA_H_

#include <vector>

template <class T>
class TrainData
{
public:
    TrainData() {}
    ~TrainData() {}

   vector<T> _data;
    int _label;
};

#endif
