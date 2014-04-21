#include <fstream>
#include <list>
#include <vector>
#include "mylib.h"

#include "knn.h"

using namespace std;

Neighbor::Neighbor() : _index(0), _distance(0.0) {}

Neighbor::Neighbor(const int index, const double dis) : _index(index), _distance(dis)
{}

KNN::KNN() : _class_num(0)
{}

int KNN::load_training_data(const string &name)
{
    int status = 0;
    ifstream in_file(name.c_str());
    if (!in_file)
    {
        return -1;
    }

    string line;
    while (getline(in_file, line))
    {
        vector<string> fields;
        split_string(line, '\t', fields);
        if (fields.size() < 4)
        {
            status = -1;
            break;
        }
        Train_data train_data;
        train_data._pos_x = atoi(fields[1].c_str());
        train_data._pos_y = atoi(fields[2].c_str());
        for (size_t i = 3; i < fields.size(); ++i)
        {
            train_data._data.push_back(atoi(fields[i].c_str()));
        }
        train_data._class_label = -1;
        _train_data.push_back(train_data);
    }

    in_file.close();
    return status;
}

double KNN::get_distance(const int id1, const int id2) const
{
    if (id1 == id2)
    {
        return 0.0;
    }
    if (id1 >= _train_data.size() || id2 >= _train_data.size())
    {
        return -1.0;
    }
    return (_train_data[id1]._pos_x - _train_data[id2]._pos_x)
        * (_train_data[id1]._pos_x - _train_data[id2]._pos_x)
        + (_train_data[id1]._pos_y - _train_data[id2]._pos_y)
        * (_train_data[id1]._pos_y - _train_data[id2]._pos_y);
}

int KNN::get_k_nearest(const int id, const int k, list<Neighbor> &neighbors) const
{
    neighbors.clear();
    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        if (id == i)
        {
            continue;
        }

        double dis = get_distance(id, i);
        if (neighbors.size() >= k && dis >= neighbors.back()._distance)
        {
            continue;
        }

        for (list<Neighbor>::iterator it = neighbors.begin();
             it != neighbors.end(); ++it)
        {
            if (dis < (*it)._distance)
            {
                Neighbor tmp(i, dis);
                neighbors.insert(it, tmp);
                dis = -1.0; // as a flag which means inserted
                break;
            }
        }

        // if inserted
        if (dis >= 0.0 && neighbors.size() < k)
        {
            Neighbor tmp(i, dis);
            neighbors.push_back(tmp);
        }

        else if (neighbors.size() > k)
        {
            neighbors.resize(k);
        }
    }
    return 0;
}

int KNN::get_k_sorted_neareast(const int id, const int k, list<Neighbor> &neighbors) const
{
    return 0;
}

int KNN::init_training_data(const int sample_num)
{
    return 0;
}

int KNN::do_train(const int k)
{
    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        if (i % 1000 == 0)
        {
            printf("trained %lu lines...\n", i);
        }
        list<Neighbor> neighbors;
        get_k_nearest(i, k, neighbors);
        get_class_label(i, neighbors);
    }
    return 0;
}

int KNN::write_result(const string &name)
{
    ofstream out_file(name.c_str());
    if (!out_file)
    {
        return -1;
    }

    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        out_file << i << "\t" << _train_data[i]._pos_x << "\t" << _train_data[i]._pos_y;
        for (size_t j = 0; j < _train_data[i]._data.size(); ++j)
        {
            out_file << "\t" << _train_data[i]._data[j];
        }
        out_file << "\t" << _train_data[i]._class_label << endl;
    }
    out_file.close();
    return 0;
}

size_t KNN::get_training_set_size() const
{
    return _train_data.size();
}

int KNN::is_same_sample(const int id1, const int id2) const
{
    const Train_data &data1 = _train_data[id1];
    const Train_data &data2 = _train_data[id2];

    if (data1._data.size() != data2._data.size())
    {
        return -1;
    }

    for (size_t i = 0; i < data1._data.size(); ++i)
    {
        if ((data1._data[i] & 0xFFFFFFF0) != (data2._data[i] & 0xFFFFFFF0))
        {
            return 0;
        }
    }

    return 1;
}

int KNN::get_class_label(const int id, const list<Neighbor> &neighbors)
{
    if (id >= _train_data.size() || neighbors.size() == 0)
    {
        return -1;
    }
    // simplest is voting
    vector<int> same_samples;
    for (list<Neighbor>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        if (is_same_sample(id, (*it)._index) == 1)
        {
            same_samples.push_back((*it)._index);
        }
    }

    // a single point
    if (same_samples.size() == 0)
    {
        _train_data[id]._class_label = 0;
        return 0;
    }

    // get class label
    int label = -1;
    for (size_t i = 0; i < same_samples.size(); ++i)
    {
        if (_train_data[same_samples[i]]._class_label != -1)
        {
            label = _train_data[same_samples[i]]._class_label;
            break;
        }
    }
    if (label == -1)
    {
        label = ++_class_num;
    }
    for (size_t i = 0; i < same_samples.size(); ++i)
    {
        /*
        if (_train_data[same_samples[i]]._class_label != -1
            && _train_data[same_samples[i]]._class_label != lable)
        {
            // something wrong;
        }
        */
        _train_data[same_samples[i]]._class_label = label;
    }
    _train_data[id]._class_label = label;

    return 0;
}