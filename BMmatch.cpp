#include <string>
#include <vector>

int BMmatch(const std::string& text, const std::string& pattern)
{
    std::vector<int> last = buildLastFunction(pattern);
    int n = text.size();
    int m = pattern.size();
    int i = m - 1;
    if(i > n - 1)
    {
        return -1;
    }
    int j = m - 1;
    do
    {
        if(pattern[j] == text[i])
        {
            if(j == 0)
            {
                return i;
            }
            else
            {
                i--;
                j--;
            }
        }
        else
        {
            i += m - std::min(j, 1 + last[text[i]]);
            j = m - 1;
        }
    } while (i <= n - 1);
    return -1;
}

std::vector<int> buildLastFunction(const std::string& pattern)
{
    const int N_ASCII = 128;
    int i;
    std::vector<int> last(N_ASCII);
    for(i = 0; i < N_ASCII; i++)
    {
        last[i] = -1;   //initialize
    }
    int l = pattern.size();
    for(i = 0; i < l; i++)
    {
        last[pattern[i]] = i;
    }
    return last;
}