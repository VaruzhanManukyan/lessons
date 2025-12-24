#include <bits/stdc++.h>

using namespace std;

long substrCount(int n, string s) {
    vector<pair<char, int>> groups;
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        groups.push_back({s[i], j - i});
        i = j;
    }

    long count = 0;

    for (auto &g : groups) {
        count += (long)g.second * (g.second + 1) / 2;
    }

    for (int i = 1; i + 1 < groups.size(); i++) {
        if (groups[i].second == 1 &&
            groups[i - 1].first == groups[i + 1].first) {
            count += min(groups[i - 1].second, groups[i + 1].second);
            }
    }

    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
