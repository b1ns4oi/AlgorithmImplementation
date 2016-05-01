#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> build_table(string& pattern) {
    vector<int> v(pattern.size()+1, -1);
    int i, j;

    for (j = 0; j < pattern.size(); ++j) {
        string s = pattern.substr(0, j+1);
        int max = 0;
        for (i = 1; i < s.size(); ++i) {
            // construct prefix and suffix
            string pre = s.substr(0, i);
            string suf = s.substr(s.size()-i, i);

            // compare
            if (pre == suf)
                max = i;
        }
        v[j+1] = max;
    }
    return v;
}

/*
** Implementation of KMP algorithm.
** Idea refer to: http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
** 
** Return the index of first match, or -1 if no match exists.
*/
int KMP(string& s, string& pattern) {
    int len_t = s.size(), len_p = pattern.size();
    if (len_p > len_t || len_t == 0)
        return -1;

    int i, j, k;

    vector<int> table = build_table(pattern);
    for (i = 0, j = 0; i <= len_t-len_p; j = 0) {
        for (k = i; j < len_p && s[k] == pattern[j]; ++k, ++j)
            ;
        if (j == len_p)
            return k-len_p;
        // i += j > 0 ? j - table[j] : 1;
        i += j - table[j];
    }
    return -1;
}


int main(int argc, char *argv[])
{
    string s(argv[1]);
    string pattern(argv[2]);
    cout << KMP(s, pattern) << endl;
}


