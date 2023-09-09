#include <unordered_map>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words) {
        return find_substring_2(s, words);
    }
    std::vector<int> find_substring_1(const std::string& s, const std::vector<std::string>& words) {
        std::vector<int> result;
        const int n = s.length();
        const int numWords = words.size();
        if (n == 0 || numWords == 0) { return result; }

        const int wordLen = words[0].length();
        //int totalLen = numWords * wordLen;
        std::unordered_map<std::string, int> wordCount; // Stores the count of each word

        for (const std::string& word : words) { wordCount[word]++; }
        for (int i = 0; i < wordLen; ++i) {
            int left = i, right = i;
            int count = 0; // the number of valid words in the current window
            std::unordered_map<std::string, int> currentCount; // Stores count of words in current window
            while (right + wordLen <= n) {
                std::string currentWord = s.substr(right, wordLen);
                right += wordLen;
                if (wordCount.contains(currentWord)) {
                    currentCount[currentWord]++;
                    count++;
                    while (currentCount[currentWord] > wordCount[currentWord]) {
                        std::string leftWord = s.substr(left, wordLen);
                        left += wordLen;
                        currentCount[leftWord]--;
                        count--;
                    }
                    if (count == numWords) { result.push_back(left); }
                }
                else {
                    currentCount.clear();
                    count = 0;
                    left = right;
                }
            }
        }
        return result;
    }
    std::vector<int> find_substring_2(const std::string& s, const std::vector<std::string>& words) {
        std::vector<int> ans;
        std::unordered_map<std::string, int> required_occurrence_count; {
            for (auto& word : words) { required_occurrence_count[word]++; }
        }
        const int Lw = words[0].length();
        int L = 0, R = 0;            // current window. Note: The step length of these 2 endpoints is always single word length.
        const int N = s.length();           // length of input string s
        std::unordered_map<std::string, int> occurrence_count_in_window;
        // We iterate staring from every index in [0, word_len) to get every possible combination
        for (int i = 0; i < Lw; i++) {
            // right is used to expand the current window, and left is used to shrink the current window whenever the window becomes invalid
            L = i, R = i;
            occurrence_count_in_window.clear();
            int word_count_in_window = 0;
            // We start iterating till end of string. Once we pick a word of length word_len, then we go to next index = right + word_len
            while (R < N) {
                const auto curr = s.substr(R, std::min(N - R, Lw));
                // If the curr picked word does not exist in the word array given, then the current window is no longer useful, so we discard all the words we have used, until now and increment right and left to point to the next word in sequence
                if (required_occurrence_count.contains(curr) == false) {
                    occurrence_count_in_window.clear();
                    word_count_in_window = 0;
                    R += Lw;
                    L = R;
                    continue;
                }
                // If freq of curr word is less then required freq of that word, we can add it to our usedWords, and also increment the no. of words that we have used in the current window
                if (occurrence_count_in_window[curr] < required_occurrence_count[curr]) { occurrence_count_in_window[curr]++, word_count_in_window++; }
                // If the freq gets higher, then we start removing words from the beginning of window, until the window becomes valid again
                else {
                    while (L < R and occurrence_count_in_window[curr] >= required_occurrence_count[curr]) {
                        auto word_to_remove = s.substr(L, Lw);
                        occurrence_count_in_window[word_to_remove]--;
                        if (occurrence_count_in_window[word_to_remove] == 0) { occurrence_count_in_window.erase(word_to_remove); }
                        word_count_in_window--;
                        L += Lw;
                    }
                    // Now the window has becomes valid so we can add the curr word to the usedWords
                    occurrence_count_in_window[curr]++, word_count_in_window++;
                }
                R += Lw;
                // if the words of our current window get equal to the total words required, then we can add the index of the starting of the window (left pointer) to our answer array, and move the left pointer 1 step forward.
                // We can't set the left pointer to point to right because we might have an answer starting from left + word_len. So we only increment it 1 step forward.
                if (word_count_in_window == words.size()) { // Note: Here len[left, right) == total_words * word_len
                    ans.push_back(L);
                    auto word_to_remove = s.substr(L, Lw);
                    occurrence_count_in_window[word_to_remove]--;
                    if (occurrence_count_in_window[word_to_remove] == 0) { occurrence_count_in_window.erase(word_to_remove); }
                    word_count_in_window--;
                    L += Lw;
                }
            }
        }
        return ans;
    }
    std::vector<int> find_substring_3(const std::string& s, const std::vector<std::string>& words) {
        struct matcher {
            struct info { int mtindex, count; };
            std::unordered_map<std::string_view, info> dict;
            int different_word_count;

            std::vector<int> slot;
            int maching_slot_count;

            matcher(const std::vector<std::string>& words) {
                int mtind = 0;
                for (auto& word : words) {
                    auto find = dict.find(word);
                    if (find != dict.end()) { ++find->second.count; }
                    else { dict[word] = { mtind++,1 }; }
                }
                different_word_count = mtind;
                slot = std::vector<int>(different_word_count, 0);
                maching_slot_count = 0;
            }
            void reset() {
                for (auto& i : slot) { i = 0; }
                maching_slot_count = 0;
            }
            bool match() { return maching_slot_count == different_word_count; }
            void push(std::string_view sv) {
                auto find = dict.find(sv);
                if (find == dict.end())return;
                if (++slot[find->second.mtindex] == find->second.count) { ++maching_slot_count; }
            }
            void pop(std::string_view sv) {
                auto find = dict.find(sv);
                if (find == dict.end())return;
                if (--slot[find->second.mtindex] == find->second.count - 1) { --maching_slot_count; }
            }
        };

        const int word_count = words.size();
        const int word_len = words[0].size();

        matcher matcher(words);

        const char* str = s.c_str();
        const int len = s.size();
        std::vector<int> ret;

        for (int off = 0; off < word_len; off++) {
            const char* beg = str + off, * end = str + len;
            if (beg + word_len * word_count <= end) {
                matcher.reset();
                for (int i = 0; i < word_count; i++) {
                    const std::string_view sv(beg + i * word_len, word_len);
                    matcher.push(sv);
                }
                if (matcher.match()) { ret.push_back(beg - str); }
                const char* pos = beg + word_len * word_count;
                while (pos + word_len <= end) {
                    const std::string_view del(beg, word_len);
                    const std::string_view add(pos, word_len);
                    beg += word_len;
                    pos += word_len;
                    matcher.pop(del);
                    matcher.push(add);
                    if (matcher.match()) { ret.push_back(beg - str); }
                }
            }
        }
        return ret;
    }
};