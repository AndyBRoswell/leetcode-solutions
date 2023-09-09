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
    // function to remove a word from usedWords hashmap
    void remove(std::unordered_map<std::string, int>& hashmap, std::string& key) {
        hashmap[key]--;
        if (hashmap[key] <= 0) { hashmap.erase(key); }
    }
    std::vector<int> find_substring_2(const std::string& s, const std::vector<std::string>& words) {
        std::unordered_map<std::string, int> wordDict;
        std::unordered_map<std::string, int> usedWords;
        const int word_len = words[0].length(), total_words = words.size();
        int left = 0, right = 0;
        const int n = s.length();
        int words_used = 0;
        std::vector<int> ans;
        // wordDict contains all words with their frequencies
        for (auto& word : words) { wordDict[word]++; }
        // We iterate staring from every index in [0, word_len) to get every possible combination
        for (int i = 0; i < word_len; i++) {
            // right is used to expand the current window, and left is used to shrink the current window whenever the window becomes invalid
            left = i, right = i;
            usedWords.clear();
            words_used = 0;
            // We start iterating till end of string. Once we pick a word of length word_len, then we go to next index = right + word_len
            while (right < n) {
                const auto curr = s.substr(right, std::min(n - right, word_len));
                // If the curr picked word does not exist in the word array given, then the current window is no longer useful, so we discard all the words we have used, until now and increment right and left to point to the next word in sequence
                if (wordDict.contains(curr) == false) {
                    usedWords.clear();
                    words_used = 0;
                    right += word_len;
                    left = right;
                    continue;
                }
                // If freq of curr word is less then required freq of that word, we can add it to our usedWords, and also increment the no. of words that we have used in the current window
                if (usedWords[curr] < wordDict[curr]) { usedWords[curr]++, words_used++; }
                // If the freq gets higher, then we start removing words from the beginning of window, until the window becomes valid again
                else {
                    while (left < right) {
                        auto to_remove = s.substr(left, word_len);
                        remove(usedWords, to_remove);
                        words_used--;
                        left += word_len;
                        if (usedWords[curr] < wordDict[curr]) { break; }
                    }
                    // Now the window has becomes valid so we can add the curr word to the usedWords
                    usedWords[curr]++, words_used++;
                }
                right += word_len;
                // if the words of our current window get equal to the total words required, then we can add the index of the starting of the window (left pointer) to our answer array, and move the left pointer 1 step forward.
                // We can't set the left pointer to point to right because we might have an answer starting from left + word_len. So we only increment it 1 step forward.
                if (words_used == total_words) {
                    ans.push_back(left);
                    auto to_remove = s.substr(left, word_len);
                    remove(usedWords, to_remove);
                    words_used--;
                    left += word_len;
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