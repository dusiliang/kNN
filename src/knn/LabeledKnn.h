#ifndef __LABELED_KNN_H__
#define __LABELED_KNN_H__

#include <list>

#include "TrainData.h"

typedef TrainData<int> TrainDataT;
typedef vector<TrainDataT *> TrainDataSetT;

class Neighbor
{
public:
    Neighbor();
    Neighbor(TrainDataT *data, double dis);

    TrainDataT *_data;
    double _distance;
};

class LabeledKnn
{
public:
    LabeledKnn();
    LabeledKnn(const int k);
    virtual ~LabeledKnn();

    int load_training_data(const string &name);
    int do_train();
    int output_result(const string &name);

    inline int get_k() const {return _k;}
    inline void set_k(const int k) {_k = k;}
    inline const TrainDataSetT& get_train_data() {return _train_data;}

private:
    double get_distance(const int id_1, const int id_2) const;

    /*
     * return: neighbors number
     */
    int get_k_neighbors(const int id, list<Neighbor> &neighbors) const;
    int get_label(const int id, const list<Neighbor> &neighbors) const;

    int _k;
    TrainDataSetT _train_data;
};

#endif
