#include <unordered_map>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words) {
        return find_substring_1(s, words);
    }
    // https://leetcode.com/problems/substring-with-concatenation-of-all-words/solutions/2419835/c-most-optimal-solution-beats-96-easy-readable-and-commented-code/
    std::vector<int> find_substring_1(const std::string& s, const std::vector<std::string>& words) {
        std::vector<int> ans;
        std::unordered_map<std::string, int> required_occurrence_count; {
            for (auto& word : words) { required_occurrence_count[word]++; }
        }
        const int l = words[0].length();    // length of each word in words array
        int L = 0, R = 0;                   // current window. Note: The step length of these 2 endpoints always equals to single word length.
        const int N = s.length();           // length of input string s
        std::unordered_map<std::string, int> occurrence_count_in_window;
        // We only need to let the left endpoint of the window be in [0, word length) to get every possible combination. The cases where the left endpoint is in [word length, n) will be covered by the iterations of the right endpoint.
        for (int i = 0; i < l; i++) {
            L = i, R = i; // At the beginning of each iteration, the window size is 0
            occurrence_count_in_window.clear();
            int word_count_in_window = 0;
            while (R < N) {
                const auto word = s.substr(R, std::min(N - R, l)); // the current word
                if (required_occurrence_count.contains(word) == false) {
                    occurrence_count_in_window.clear(); // All the accumulated words are of no use now
                    word_count_in_window = 0;
                    R += l;                             // The current word is skipped since it is not in the words array so it cannot form an answer
                    L = R;                              // The left endpoint of the window must be at the position of the next word
                    continue;
                }
                while (L < R and occurrence_count_in_window[word] >= required_occurrence_count[word]) { // The current word has already appeared more than the required times
                    auto word_to_remove = s.substr(L, l); // Optimization available: Recording all the occurrence positions of each word in the words array
                    occurrence_count_in_window[word_to_remove]--;
                    if (occurrence_count_in_window[word_to_remove] == 0) { occurrence_count_in_window.erase(word_to_remove); }
                    word_count_in_window--;
                    L += l; // we need to shrink the window with the left endpoint, until the current word has the required occurrence count
                }
                occurrence_count_in_window[word]++, word_count_in_window++;
                R += l; // expand the window by 1 word via the right endpoint
                if (word_count_in_window == words.size()) { // Note: Here len[left, right) == total_words * word_len
                    ans.push_back(L);
                    auto word_to_remove = s.substr(L, l);
                    occurrence_count_in_window[word_to_remove]--;
                    if (occurrence_count_in_window[word_to_remove] == 0) { occurrence_count_in_window.erase(word_to_remove); }
                    word_count_in_window--;
                    L += l; // shrink the window by 1 word via the left endpoint
                }
            }
        }
        return ans;
    }
    // TODO: Comment on this solution
    std::vector<int> find_substring_2(const std::string& s, const std::vector<std::string>& words) {
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