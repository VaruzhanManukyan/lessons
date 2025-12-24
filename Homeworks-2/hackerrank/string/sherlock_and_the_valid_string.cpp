#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }

    unordered_map<int, int> freqCount;
    for (auto &p : freq) {
        freqCount[p.second]++;
    }

    if (freqCount.size() == 1) {
        return "YES";
    }

    if (freqCount.size() == 2) {
        auto it = freqCount.begin();
        auto [f1, c1] = *it++;
        auto [f2, c2] = *it;

        if ((f1 == 1 && c1 == 1) || (f2 == 1 && c2 == 1)) {
            return "YES";
        }

        if (abs(f1 - f2) == 1) {
            if ((f1 > f2 && c1 == 1) || (f2 > f1 && c2 == 1)) {
                return "YES";
            }
        }
    }

    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
