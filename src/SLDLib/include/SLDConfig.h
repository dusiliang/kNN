#ifndef __SLD_CONFIG_H__
#define __SLD_CONFIG_H__

#include <map>

class SLDConfig
{
public:
    SLDConfig(const string &name);
    virtual ~SLDConfig();

    void output_config() const;
    inline const map<string, string> &get_config() const {return _config_map;}

private:
    int load_config_file();

    const string _config_file_name;
    map<string, string> _config_map;
};

#endif
