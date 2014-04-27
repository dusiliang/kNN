#include <fstream>
#include <iostream>

#include "SLDString.h"

#include "SLDConfig.h"

using namespace std;

SLDConfig::SLDConfig(const string &name) : _config_file_name(name)
{
    load_config_file();
}

int SLDConfig::load_config_file()
{
    ifstream in_file(_config_file_name.c_str());
    if (!in_file)
    {
        return -1;
    }

    string line;
    while (getline(in_file, line))
    {
        if (line.size() == 0)
        {
            continue;
        }

        if (line[0] == '#')
        {
            continue;
        }

        vector<string> fields;
        split_string(line, '=', fields);
        if (fields.size() != 2)
        {
            continue;
        }
        _config_map[fields[0]] = fields[1];
    }
    in_file.close();
    return 0;
}

void SLDConfig::output_config() const
{
    for (map<string, string>::const_iterator cit = _config_map.begin();
         cit != _config_map.end(); ++cit)
    {
        cout << cit->first << "=" << cit->second << endl;
    }
}