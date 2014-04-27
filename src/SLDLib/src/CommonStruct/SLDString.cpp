#include <string>
#include "SLDString.h"

using namespace std;

int split_string(
    const string &ori_str, const char splitor, vector<string> &result)
{
    size_t last_pos = 0, cur_pos = 0;
    for (size_t i = 0; i < ori_str.size(); ++i)
    {
        if (ori_str[i] == splitor)
        {
            result.push_back(ori_str.substr(last_pos, cur_pos - last_pos));
            last_pos = cur_pos + 1;
        }
        ++cur_pos;
    }
    result.push_back(ori_str.substr(last_pos, cur_pos - last_pos));

    return 0;
}