#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct Node { 
    bool is_word{}; 
    Node* child[26]{}; 
    ~Node(){for(auto p:child) delete p;} 
};

class Trie {
public:
    void insert(std::string w){
        for(char& c:w) c = std::tolower(static_cast<unsigned char>(c));
        Node* cur = &root_;
        for(char ch:w){
            std::size_t idx = ch - 'a';
            if(!cur->child[idx]) cur->child[idx] = new Node;
            cur = cur->child[idx];
        }
        cur->is_word = true;
    }
    std::vector<std::string> autocomplete(std::string prefix, std::size_t max=50) const {
        for(char& c:prefix) c = std::tolower(static_cast<unsigned char>(c));
        const Node* cur = &root_;
        for(char ch:prefix){
            std::size_t idx = ch - 'a';
            if(idx>=26 || !cur->child[idx]) return {};
            cur = cur->child[idx];
        }
        std::vector<std::string> out;
        std::string buf = prefix;
        auto collector = [&](const std::string& w){
            if (out.size() < max) out.push_back(w);
        };
        dfs_impl(cur, buf, collector);   // l-value now binds fine
        return out;
    }

    /* ---------------- NEW: exact membership test ----------- */
    bool contains(std::string word) const {
        for (char& c : word)
            c = std::tolower(static_cast<unsigned char>(c));

        const Node* cur = &root_;
        for (char ch : word) {
            std::size_t idx = ch - 'a';
            if (idx >= 26 || !cur->child[idx])
                return false;
            cur = cur->child[idx];
        }
        return cur->is_word;
    }

    /* ---------------- NEW: recommendation search ----------- */
    std::vector<std::string> recommend(std::string query,
                                       std::size_t max = 10) const
    {
        for (char& c : query)
            c = std::tolower(static_cast<unsigned char>(c));

        const Node* cur = &root_;
        std::string prefix;                 // longest part that exists

        for (char ch : query) {
            std::size_t idx = ch - 'a';
            if (idx >= 26 || !cur->child[idx])
                break;                     // first mismatch → stop walk
            cur = cur->child[idx];
            prefix.push_back(ch);
        }

        // If the whole word is present, nothing to “recommend”.
        if (prefix.size() == query.size() && cur->is_word) return {};

        // Collect completions under the matched prefix node.
        std::vector<std::string> out;
        std::string buf = prefix;
        auto collector = [&](const std::string& w) {
            if (out.size() < max) out.push_back(w);
        };
        dfs_impl(cur, buf, collector);
        return out;
    }

private:
    Node root_;
    template<class V>
    static void dfs_impl(const Node* n, std::string& pre, V& vis){
        if(n->is_word) vis(pre);
        for(std::size_t i=0;i<26;++i)
            if(n->child[i]){
                pre.push_back(char('a'+i));
                dfs_impl(n->child[i], pre, vis);
                pre.pop_back();
            }
    }
};


/* ---------- Demo ---------- */
int main() {
    // load dictionary from file
    vector<string> dictionary;
    ifstream file("Dictionary.txt");
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }

    Trie trie;
    for (const auto& w : dictionary) {
        trie.insert(w);
    }

    // Example usage
    string prefix;
    cout << "Enter a prefix to autocomplete: ";
    cin >> prefix;
    auto suggestions = trie.autocomplete(prefix);
    cout << "Suggestions:\n";
    for (const auto& suggestion : suggestions) {
        cout << suggestion << '\n';
    }

    // 
    auto recommended_suggestions = trie.recommend("applf", 5);   // misspelled “apple”
    if (recommended_suggestions.empty())
        std::cout << "Exact match found.\n";
    else {
        std::cout << "Did you mean:\n";
        for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
    }

    return 0;
}