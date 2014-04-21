#include <fstream>
#include <list>
#include "mylib.h"

#include "knn.h"

using namespace std;

Neighbor::Neighbor() : _index(0), _distance(0.0) {}

Neighbor::Neighbor(const int index, const double dis) : _index(index), _distance(dis)
{}

KNN::KNN()
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
        if (i == 1184)
        {
            printf("dis: %f, last: %d, %f\n", dis, neighbors.back()._index, neighbors.back()._distance);
        }
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

int KNN::do_train()
{
    return 0;
}

int KNN::write_result(const string &name)
{
    return 0;
}

size_t KNN::get_training_set_size() const
{
    return _train_data.size();
}