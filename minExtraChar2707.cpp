#include "cppCommonHeaders.hpp"

class Solution {
struct TrieNode {
    bool isWord = false;
    array<unique_ptr<TrieNode>, 26> kids {};
};
unique_ptr<TrieNode> root;
template<typename It>
void insert(It curr, It end){
    auto node = this->root.get();
    while(curr != end){
        if(!node->kids[*curr - 'a'].get()){
            node->kids[*curr - 'a'] = make_unique<TrieNode>();
        }
        node = node->kids[*curr++ - 'a'].get();
    }
    node->isWord = true;
}
template<typename It>
bool search(It curr, It end){
    auto node = this->root.get();
    while(curr != end){
        if(!node->kids[*curr - 'a'].get()){
            return false;
        }
        node = node->kids[*curr++ - 'a'].get();
    }
    return node->isWord;
}
public:
    Solution(): root {std::make_unique<TrieNode>()} {}
    int minExtraChar(string s, vector<string> dictionary) {
        for(auto& word: dictionary){
            this->insert(word.cbegin(), word.cend());
        }
        const int kN = s.size();
        vector<int> dp(kN + 1);
        for(int i = 1; i <= kN; ++i){
            dp[i] = dp[i - 1] + 1;
            for(int j = 0; j < i && dp[i]; ++j){
                if(this->search(s.cbegin() + j, s.cbegin() + i)){
                    dp[i] = min(dp[i], dp[j]);
                }
            }
        }
        for(auto cnt: dp){
            cout << cnt << "\t";
        }
        cout << endl;
        return dp[kN];
    }
};

int main(){
    auto sol = Solution();
    sol.minExtraChar("sayhelloworld", {"hello","world"});
}


