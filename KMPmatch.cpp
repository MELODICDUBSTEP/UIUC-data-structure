#include <string>
#include <vector>

int KMPmatch(const std::string& text, const std::string& pattern)
{
    int n = text.size();
    int m = pattern.size();
    std::vector<int> fail = computeFailFunction(pattern);
    int i = 0;
    int j = 0;
    while(i < n)
    {
        if(pattern[j] == text[i])
        {
            if(j == m - 1)
            {
                return i - m + 1;
            }
            i++;
            j++;
        }
        else if(j > 0)
        {
            j = fail[j - 1];
        }
        else
        {
            i++;
        }
    }
    return -1;
}

std::vector<int> computeFailFunction(const std::string& pattern)
{
    int l = pattern.size();
    std::vector<int> fail(l);
    fail[0] = 0;
    int j = 0;
    int i = 1;
    while(i < l)
    {
        if(pattern[j] == pattern[i])
        {
            fail[i] = j + 1;
            i++;
            j++;
        }
        else if(j > 0)
        {
            j = fail[j - 1];
        }
        else
        {
            fail[i] = 0;
            i++;
        }
    }
    return fail;
}

