#include <fstream>
#include <list>
#include <map>
#include <vector>
#include "SLDString.h"

#include "knn.h"

using namespace std;

Neighbor::Neighbor() : _index(0), _distance(0.0) {}

Neighbor::Neighbor(const int index, const double dis) : _index(index), _distance(dis)
{}

KNN::KNN() : _class_num(0), _SAME_THRESHOLD(200)
{}

KNN::KNN(const int threshold) : _class_num(0), _SAME_THRESHOLD(threshold)
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
        TrainData train_data;
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

int KNN::get_max_x() const
{
    return _train_data.back()._pos_x;
}

int KNN::get_max_y() const
{
    return _train_data.back()._pos_y;
}

int KNN::get_k_nearest(const int id, list<Neighbor> &neighbors) const
{
    int min_x = 0;
    int min_y = 0;
    int max_x = get_max_x();
    int max_y = get_max_y();

    if (_train_data[id]._pos_x == min_x || _train_data[id]._pos_y == min_y)
    {
        Neighbor tmp1(id + 1, 1);
        Neighbor tmp2(id + 2, 4);
        Neighbor tmp3(id + max_x + 1, 1);
        Neighbor tmp4(id + max_x + 2, 2);
        Neighbor tmp5(id + max_x + 3, 13);
        Neighbor tmp6(id + 2*(max_x + 1), 4);
        Neighbor tmp7(id + 2*(max_x + 1) + 1, 13);
        Neighbor tmp8(id + 2*(max_x + 1) + 2, 18);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == min_x || _train_data[id]._pos_y == max_y)
    {
        Neighbor tmp1(id + 1, 1);
        Neighbor tmp2(id + 2, 4);
        Neighbor tmp3(id - max_x - 1, 1);
        Neighbor tmp4(id - max_x, 2);
        Neighbor tmp5(id - max_x + 1, 13);
        Neighbor tmp6(id - 2*(max_x + 1), 4);
        Neighbor tmp7(id - 2*(max_x + 1) + 1, 13);
        Neighbor tmp8(id - 2*(max_x + 1) + 2, 18);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == max_x || _train_data[id]._pos_y == min_y)
    {
        Neighbor tmp1(id - 1, 1);
        Neighbor tmp2(id - 2, 4);
        Neighbor tmp3(id + max_x + 1, 1);
        Neighbor tmp4(id + max_x, 2);
        Neighbor tmp5(id + max_x - 1, 13);
        Neighbor tmp6(id + 2*(max_x + 1), 4);
        Neighbor tmp7(id + 2*(max_x + 1) - 1, 13);
        Neighbor tmp8(id + 2*(max_x + 1) - 2, 18);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == max_x || _train_data[id]._pos_y == max_y)
    {
        Neighbor tmp1(id - 1, 1);
        Neighbor tmp2(id - 2, 4);
        Neighbor tmp3(id - max_x - 1, 1);
        Neighbor tmp4(id - max_x - 2, 2);
        Neighbor tmp5(id - max_x - 3, 13);
        Neighbor tmp6(id - 2*(max_x + 1), 4);
        Neighbor tmp7(id - 2*(max_x + 1) - 1, 13);
        Neighbor tmp8(id - 2*(max_x + 1) - 2, 18);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == min_x)
    {
        Neighbor tmp1(id - (max_x + 1), 1);
        Neighbor tmp2(id - (max_x + 1) + 1, 4);
        Neighbor tmp3(id - (max_x + 1) + 2, 13);
        Neighbor tmp4(id + 1, 2);
        Neighbor tmp5(id + 2, 4);
        Neighbor tmp6(id + (max_x + 1), 1);
        Neighbor tmp7(id + (max_x + 1) + 1, 4);
        Neighbor tmp8(id + (max_x + 1) + 2, 13);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == max_x)
    {
        Neighbor tmp1(id - (max_x + 1), 1);
        Neighbor tmp2(id - (max_x + 1) - 1, 4);
        Neighbor tmp3(id - (max_x + 1) - 2, 13);
        Neighbor tmp4(id - 1, 2);
        Neighbor tmp5(id - 2, 4);
        Neighbor tmp6(id + (max_x + 1), 1);
        Neighbor tmp7(id + (max_x + 1) - 1, 4);
        Neighbor tmp8(id + (max_x + 1) - 2, 13);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == min_y)
    {
        Neighbor tmp1(id + (max_x + 1), 1);
        Neighbor tmp2(id + (max_x + 1) - 1, 4);
        Neighbor tmp3(id + (max_x + 1) + 1, 4);
        Neighbor tmp4(id - 1, 1);
        Neighbor tmp5(id + 1, 1);
        Neighbor tmp6(id + 2*(max_x + 1), 4);
        Neighbor tmp7(id + 2*(max_x + 1) - 1, 13);
        Neighbor tmp8(id + 2*(max_x + 1) + 1, 13);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else if (_train_data[id]._pos_x == max_y)
    {
        Neighbor tmp1(id - (max_x + 1), 1);
        Neighbor tmp2(id - (max_x + 1) - 1, 4);
        Neighbor tmp3(id - (max_x + 1) + 1, 4);
        Neighbor tmp4(id - 1, 1);
        Neighbor tmp5(id + 1, 1);
        Neighbor tmp6(id - 2*(max_x + 1), 4);
        Neighbor tmp7(id - 2*(max_x + 1) - 1, 13);
        Neighbor tmp8(id - 2*(max_x + 1) + 1, 13);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
    }
    else
    {
        Neighbor tmp1(id - (max_x + 1), 1);
        Neighbor tmp2(id - (max_x + 1) - 1, 2);
        Neighbor tmp3(id - (max_x + 1) + 1, 2);
        Neighbor tmp4(id - 1, 1);
        Neighbor tmp5(id + 1, 1);
        Neighbor tmp6(id + (max_x + 1), 1);
        Neighbor tmp7(id + (max_x + 1) - 1, 2);
        Neighbor tmp8(id + (max_x + 1) + 1, 2);
        neighbors.push_back(tmp1);
        neighbors.push_back(tmp2);
        neighbors.push_back(tmp3);
        neighbors.push_back(tmp4);
        neighbors.push_back(tmp5);
        neighbors.push_back(tmp6);
        neighbors.push_back(tmp7);
        neighbors.push_back(tmp8);
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
        //get_k_nearest(i, k, neighbors);
        get_k_nearest(i, neighbors);
        get_class_label(i, neighbors);
    }
    printf("class label number: %d\n", _class_num);
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
    const TrainData &data1 = _train_data[id1];
    const TrainData &data2 = _train_data[id2];

    if (data1._data.size() != data2._data.size())
    {
        return -1;
    }

    int diff = 0;
    for (size_t i = 0; i < data1._data.size(); ++i)
    {
        //if ((data1._data[i] & 0xFFFFFFE0) != (data2._data[i] & 0xFFFFFFE0))
        diff += abs(data1._data[i] - data2._data[i]);
        //printf("diff: %d\n", diff);
    }
    if (diff > _SAME_THRESHOLD)
    {
        return 0;
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
    map<int, int> label_map;
    int top_label = -1;
    int top_label_count = 0;
    for (size_t i = 0; i < same_samples.size(); ++i)
    {
        if (_train_data[same_samples[i]]._class_label != -1)
        {
            int tmp_num = ++label_map[_train_data[same_samples[i]]._class_label];
            if (tmp_num > top_label_count)
            {
                top_label = _train_data[same_samples[i]]._class_label;
                top_label_count = tmp_num;
            }
        }
    }
    if (top_label == -1)
    {
        top_label = ++_class_num;
    }
    for (size_t i = 0; i < same_samples.size(); ++i)
    {
        /*
        if (_train_data[same_samples[i]]._class_label != -1
            && _train_data[same_samples[i]]._class_label != label)
        {
            // something wrong;
            printf("wrong, id: %d, other id: %d\n", id, same_samples[i]);
        }
        */
        if (_train_data[same_samples[i]]._class_label == -1)
        {
            _train_data[same_samples[i]]._class_label = top_label;
        }
    }
    _train_data[id]._class_label = top_label;

    return 0;
}