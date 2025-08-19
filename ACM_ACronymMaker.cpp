
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

static long long maxCount(const vector<string> &words, const string &acroLower) {
    long long sum[75][75] = {0};
    long long sum2[75][75] = {0};

    sum[0][0] = 1;

    for (int i = 0; i < (int)words.size(); i++) {
        const string &w = words[i];
        int wrdLen = (int)w.size();
        for (int j = 0; j < (int)acroLower.size(); j++) {
            int mx = min(wrdLen, (int)acroLower.size() - j);

            // fill first column with 1 and clear row 0 beyond column 0 for this mx window
            for (int k = 0; k <= wrdLen; k++) sum2[k][0] = 1;
            for (int m = 1; m <= mx; m++) sum2[0][m] = 0;

            for (int k = 0; k < wrdLen; k++) {
                for (int m = 0; m < mx; m++) {
                    sum2[k + 1][m + 1] = sum2[k][m + 1];
                    if (w[k] == acroLower[j + m]) {
                        sum2[k + 1][m + 1] += sum2[k][m];
                    }
                }
            }

            for (int k = 1; k <= mx; k++) {
                sum[i + 1][j + k] += sum[i][j] * sum2[wrdLen][k];
            }
        }
    }

    return sum[words.size()][acroLower.size()];
}

static string trim(const string &s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    if (a == b) return "";
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
}

static vector<string> splitBySpace(const string &line) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(line[i]);
        }
    }
    tokens.push_back(token);
    return tokens;
}

static vector<string> filterWords(const string &line, const vector<string> &insigwords) {
    vector<string> words = splitBySpace(line);
    int k = (int)words.size();

    for (const string &insRaw : insigwords) {
        string ins = trim(insRaw);
        for (int j = 0; j < (int)words.size(); j++) {
            string wrd = words[j];
            if (!wrd.empty()) wrd = trim(wrd);
            if (!wrd.empty() && !ins.empty() && ins == wrd) {
                words[j].clear();
                k--;
            }
        }
    }

    vector<string> filtered;
    filtered.reserve(k);
    for (const string &w : words) if (!w.empty()) filtered.push_back(w);
    return filtered;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int N;
        if (!(cin >> N)) return 0;
        if (N == 0) break;
        vector<string> insigwords(N);
        for (int i = 0; i < N; i++) cin >> insigwords[i];
        string dummy; getline(cin, dummy);

        string line;
        while (getline(cin, line)) {
            string trimmed = trim(line);
            if (trimmed == "LAST CASE") break;

            vector<string> filteredWords = filterWords(line, insigwords);
            if (filteredWords.empty()) continue;

            string acronym = filteredWords[0];
            string acroLower = acronym;
            for (char &c : acroLower) c = (char)tolower((unsigned char)c);

            vector<string> words;
            for (size_t i = 1; i < filteredWords.size(); i++) words.push_back(filteredWords[i]);

            long long count = maxCount(words, acroLower);
            if (count > 0) {
                cout << acronym << " can be formed in " << count << " ways\n";
            } else {
                cout << acronym << " is not a valid abbreviation\n";
            }
        }
    }
    return 0;
}