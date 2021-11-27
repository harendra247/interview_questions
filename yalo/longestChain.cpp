#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'longestChain' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY words as parameter.
 */
int longestChain_helper(string word, unordered_set<string> &dics, unordered_map<string, int> &chain_map) {
    if (word.length() == 1) {
        return dics.count(word);
    }

    if (dics.count(word) == 0) {
        return 0;
    }

    if (chain_map.count(word)) {
        return chain_map[word];
    }

    int chain_len = 0;
    string new_word;
    for(int i = 0; i < word.length(); ++i) {
        new_word = word.substr(0, i) + word.substr(i+1);
        int len = longestChain_helper(new_word, dics, chain_map);

        if (chain_len < len) {
            chain_len = len;
        }
    }
    chain_map[word] = chain_len+1;
    return chain_len+1;
}

int longestChain(vector<string> words) {
    int chain_len = 0;
    unordered_set<string> dics(words.begin(), words.end());
    unordered_map<string, int> chain_map;

    for(auto a: words) {
        int len  = longestChain_helper(a, dics, chain_map);
        if (len > chain_len) {
            chain_len = len;
        }
    }

    return chain_len;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string words_count_temp;
    getline(cin, words_count_temp);
    int words_count = stoi(ltrim(rtrim(words_count_temp)));
    vector<string> words(words_count);

    for (int i = 0; i < words_count; i++) {
        string words_item;
        getline(cin, words_item);

        words[i] = words_item;
    }

    int result = longestChain(words);
    fout << result << "\n";
    fout.close();

    return 0;
}
