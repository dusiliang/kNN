#ifndef _KNN_H_
#define _KNN_H_

#include <list>

using namespace std;

class Train_data
{
public:
    int _pos_x;
    int _pos_y;
    vector<int> _data;
};

class Neighbor
{
public:
    Neighbor();
    Neighbor(const int index, const double dis);

    int _index;
    double _distance;
};

class KNN
{
public:
    KNN();

    int load_training_data(const string &name);
    int do_train();
    int write_result(const string &name);
    double get_distance(const int id1, const int id2) const;
    int get_k_nearest(const int id, const int k, list<Neighbor> &neighbors) const;
    int get_k_sorted_neareast(const int id, const int k,
        list<Neighbor> &neighbors) const;

    size_t get_training_set_size() const;

private:
    vector<Train_data> _train_data;
};

#endif
