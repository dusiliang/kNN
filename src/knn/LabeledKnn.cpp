#include <fstream>
#include <iostream>
#include <map>

#include "mylib.h"
#include "TrainData.h"

#include "LabeledKnn.h"

using namespace std;

Neighbor::Neighbor() : _data(0), _distance(0.0)
{}

Neighbor::Neighbor(TrainDataT *data, double dis) : _data(data), _distance(dis)
{}

LabeledKnn::LabeledKnn() : _k(0)
{}

LabeledKnn::LabeledKnn(const int k) : _k(k)
{}

LabeledKnn::~LabeledKnn()
{
    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        if (_train_data[i] != 0)
        {
            delete _train_data[i];
        }
    }
}

int LabeledKnn::load_training_data(const string &name)
{
    // id feature_list label
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
        TrainData<int> *train_data = new TrainData<int>;
        _train_data.push_back(train_data);
        ///< first item is id, last item is label
        for (int i = 1; i < fields.size() - 1; ++i)
        {
            train_data->_data.push_back(atoi(fields[i].c_str()));
        }
        train_data->_label = atoi(fields[fields.size() - 1].c_str());
    }
    in_file.close();
    return _train_data.size();
}

int LabeledKnn::do_train()
{
    if (_k == 0)
    {
        return -1;
    }

    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        if (i % 2000 == 0)
        {
            cout << i << " lines trained!" << endl;
        }
        if (_train_data[i]->_label != 0)
        {
            continue;
        }
        list<Neighbor> neighbors;
        if (get_k_neighbors(i, neighbors) != _k)
        {
            continue;
        }
        /*
        // debug
        if (i == 10)
        {
            for (list<Neighbor>::iterator it = neighbors.begin();
                 it != neighbors.end(); ++it)
            {
                cout << (*it)._data->_data[0] << " " << (*it)._data->_data[1] << " "
                     << (*it)._data->_data[2] << " " << (*it)._data->_data[3] << " "
                     << (*it)._data->_data[4] << endl;
            }
        }
        */
        _train_data[i]->_label = get_label(i, neighbors);
    }
    return 0;
}

int LabeledKnn::output_result(const string &name)
{
    ofstream out_file(name.c_str());
    if (!out_file)
    {
        return -1;
    }
    for (size_t i = 0; i < _train_data.size(); ++i)
    {
        out_file << i;
        for (size_t j = 0; j < _train_data[i]->_data.size(); ++j)
        {
            out_file << "\t" << _train_data[i]->_data[j];
        }
        out_file << "\t" << _train_data[i]->_label << endl;
    }
    out_file.close();
    return 0;
}

double LabeledKnn::get_distance(const int id_1, const int id_2) const
{
    if (id_1 == id_2)
    {
        return 0.0;
    }

    if (id_1 >= _train_data.size() || id_2 >= _train_data.size())
    {
        return -1.0;
    }

    double dis = 0.0;
    for (int i = 0; i < _train_data[id_1]->_data.size(); ++i)
    {
        double tmp = _train_data[id_1]->_data[i] - _train_data[id_2]->_data[i];
        dis += tmp * tmp;
    }
    return dis;
}

int LabeledKnn::get_k_neighbors(const int id, list<Neighbor> &neighbors) const
{
    neighbors.clear();
    for (int i = 0; i < _train_data.size(); ++i)
    {
        if (i == id || _train_data[i]->_label == 0)
        {
            continue;
        }

        double dis = get_distance(id, i);
        if (neighbors.size() >= _k && dis >= neighbors.back()._distance)
        {
            continue;
        }

        for (list<Neighbor>::iterator it = neighbors.begin();
             it != neighbors.end(); ++it)
        {
            if (dis < (*it)._distance)
            {
                Neighbor tmp(_train_data[i], dis);
                neighbors.insert(it, tmp);
                dis = -1.0; // as a flag which means inserted
                break;
            }
        }

        // if inserted
        if (dis >= 0.0 && neighbors.size() < _k)
        {
            Neighbor tmp(_train_data[i], dis);
            neighbors.push_back(tmp);
        }
        else if (neighbors.size() > _k)
        {
            neighbors.resize(_k);
        }
    }
    return neighbors.size();
}

int LabeledKnn::get_label(const int id, const list<Neighbor> &neighbors) const
{
    // vote
    int label = 0;
    int count = 0, tmp;
    map<int, int> label_count;
    for (list<Neighbor>::const_iterator cit = neighbors.begin();
         cit != neighbors.end(); ++cit)
    {
        if ((tmp = ++label_count[(*cit)._data->_label]) > count)
        {
            label = (*cit)._data->_label;
            count = tmp;
        }
    }

    return label;
}