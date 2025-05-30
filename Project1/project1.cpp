#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <cstddef>

using namespace std;


struct Node { 
    bool is_word{};                      // check if node is the end of a word
    Node* child[26]{};                   // ptr to children, 26 for each letter a-z
    ~Node(){                             // can be used to delete all children recursively
        for(auto p:child) delete p;
    }
};

class Trie {
public:
    void insert(std::string w){
        // loop through every character in the word and convert each character to lowercase
        for(char& c:w)
            c = tolower(static_cast<unsigned char>(c));
        // create & start at root
        Node* cur = &root_;
        // loop through each character in the word
        for(char ch:w){
            size_t idx = ch - 'a'; // get the index of the alphabetical character (0 for 'a', 1 for 'b', ..., 25 for 'z')
            if(!cur->child[idx])   // if the current node's child of char 'ch' is null, create a new Node.
                cur->child[idx] = new Node;
            cur = cur->child[idx]; // then move to the (newly created/already existed) child node corresponding to the current character
        }
        cur->is_word = true;       // mark the end of the word. In particular, the word is stored and we mark the flag is_word as true.
        return;
    }

    vector<string> autocomplete(string prefix, size_t max_suggestion=50) const {
        /* Start with some prefix e.g., 'appl' & return a list of words that start with this particular prefix
           Maximum number of suggestions is given by parameter max_suggestion. 
        */
        // convert every character in the prefix to lowercase
        for(char& c:prefix) 
            c = tolower(static_cast<unsigned char>(c));
        // again, start @ root
        const Node* cur = &root_;
        // loop through each character in the prefix
        for(char ch:prefix){
            size_t idx = ch - 'a';          // get the index of the character in alphabetical order (0 for 'a', 1 for 'b', ..., 25 for 'z')
            if(idx>=26 || !cur->child[idx]) // if index is out of bounds (not a-z) or the child node does not exist, return empty vector
                return {}; 
            cur = cur->child[idx];          // set current node to the child node corresponding to the current character
        }
        // if we reach here, it means trie has the path to this prefix. Proceed to collect all words that start with this prefix.
        vector<string> out;
        string buf = prefix;
        // create a lambda function to collect words that start with the prefix
        // the syntax [&]() captures all variables by reference, allow us to modify 'out' vector
        auto collector = [&](const string& w){
            if (out.size() < max_suggestion)
                out.push_back(w);
        };
        // perform a depth-first-search starting from the current node and maintaining the prefix stored in 'buf'
        depth_first_search(cur, buf, collector);
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
        depth_first_search(cur, buf, collector);
        return out;
    }

private:
    Node root_;
    template<class V>
    static void depth_first_search(const Node* n, std::string& pre, V& vis){
        if(n->is_word) vis(pre);
        for(std::size_t i=0;i<26;++i)
            if(n->child[i]){
                pre.push_back(char('a'+i));
                depth_first_search(n->child[i], pre, vis);
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
    // loop through each word in the dictionary and insert it into the trie using insert() method
    for (const auto& word : dictionary) {
        trie.insert(word);
    }

    // Example usage
    string prefix;
    cout << "Enter a prefix to autocomplete: ";
    cin >> prefix;
    auto suggestions = trie.autocomplete(prefix, 10);
    cout << "Suggestions:\n";
    for (const auto& suggestion : suggestions) {
        cout << suggestion << '\n';
    }

    // 
    auto recommended_suggestions = trie.recommend("hottr", 5);   // misspelled “apple”
    if (recommended_suggestions.empty())
        std::cout << "Exact match found.\n";
    else {
        std::cout << "Did you mean:\n";
        for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
    }

    return 0;
}