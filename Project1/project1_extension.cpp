#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <cstddef>

using namespace std;


struct Node {
    bool  is_word = false;
    Node* child[27]{nullptr};          // 0-25 = 'a'..'z', 26 = space ' '
    ~Node() { for (Node* p : child) delete p; }
};

class Trie {
public:

    static inline std::size_t map_idx(char ch) {
        if (ch == ' ')      return 26;           // space
        if ('a' <= ch && ch <= 'z')
            return static_cast<std::size_t>(ch - 'a');
        throw std::runtime_error("unsupported character");
    }

    // void insert(std::string text)
    // {
    //     for (char& c : text)               // lower-case *all* letters
    //         c = static_cast<char>(std::tolower((unsigned char)c));

    //     Node* cur = &root_;
    //     for (char ch : text) {
    //         std::size_t idx = map_idx(ch);
    //         if (!cur->child[idx]) cur->child[idx] = new Node;
    //         cur = cur->child[idx];
    //     }
    //     cur->is_word = true;
    // }

    /* ----------- insert word OR phrase ----------- */
    void insert(std::string text)
    {
        /* 0. normalise:   – lower-case letters
                        – replace any run of blanks with a single ' '       */
        std::string cleaned;
        cleaned.reserve(text.size());

        bool prev_space = false;
        for (unsigned char ch : text) {
            if (std::isspace(ch)) {                 // treat all whitespace alike
                if (!prev_space) {                  // collapse runs of blanks
                    cleaned.push_back(' ');
                    prev_space = true;
                }
            } else if ('A' <= ch && ch <= 'Z') {
                cleaned.push_back(static_cast<char>(ch + ('a' - 'A')));  // to lower
                prev_space = false;
            } else if ('a' <= ch && ch <= 'z') {
                cleaned.push_back(static_cast<char>(ch));
                prev_space = false;
            }
            /* else: skip punctuation / digits quietly */
        }
        /* trim a possible trailing space introduced above */
        if (!cleaned.empty() && cleaned.back() == ' ')
            cleaned.pop_back();
        if (cleaned.empty()) return;                // nothing to store

        /* 1. walk / create nodes for every char (letters + spaces) */
        Node* cur = &root_;
        for (char ch : cleaned) {
            std::size_t idx = map_idx(ch);          // 0-25 letters, 26 space
            if (!cur->child[idx]) cur->child[idx] = new Node;
            cur = cur->child[idx];
        }
        cur->is_word = true;                        // mark end of word/phrase
    }

    vector<string> autocomplete(string prefix,
        size_t max = 50) const
    {
        for (char& c : prefix)
        c = static_cast<char>(std::tolower((unsigned char)c));

        const Node* cur = &root_;
        for (char ch : prefix) {                  // walk prefix incl. spaces
        std::size_t idx = map_idx(ch);
        if (!cur->child[idx]) return {};
        cur = cur->child[idx];
        }

        vector<string> out;
        string buffer = prefix;
        Collector collector{out, max};
        depth_first_search(cur, buffer, collector);
        return out;
    }


    /* ----------- recommendation search ----------- */
    std::vector<std::string> recommend(std::string query,
        std::size_t max = 20) const
    {
        for (char& c : query)
        c = static_cast<char>(std::tolower((unsigned char)c));

        /* 1. Walk as far as the trie matches the query */
        const Node* cur = &root_;
        std::string prefix;

        for (char ch : query) {
        std::size_t idx = map_idx(ch);          //  <-- unified helper
        if (!cur->child[idx]) break;            //  no further match
        cur = cur->child[idx];
        prefix.push_back(ch);
        }

        /* 2. Collect completions under the longest-matched prefix
        (even if the query itself is already a stored word)        */
        return autocomplete(prefix, max);
    }

    

private:
    Node root_; // root node of the trie should be private

    // // here we use a template to allow any callable type (function, lambda, structure, etc.) to be passed
    // // and since we are using a structure (collector) to collect words, we can use a template to make generic pass
    // template<class WC>
    // static void depth_first_search(const Node* curr_node, std::string& prefix_, WC& words_collection){
    //     if(curr_node->is_word) {
    //         words_collection(prefix_);              // sanity check: if the current node is a word, append prefix_ to word collection b/c it is a word at this point
    //     }
    //     for(std::size_t i=0;i<26;++i)               // iterate through all children (a->z) of the current node
    //         if(curr_node->child[i]){                // if child node of current node exists then go deeper to collect characters
    //             prefix_.push_back(char('a'+i));     // found character, push_back it to the prefix
    //             depth_first_search(curr_node->child[i], prefix_, words_collection);  // recursive call to go deeper into the trie with root now @ child node of n
    //             prefix_.pop_back();                 // under chacracter to restore
    //         }
    // }

    template<class V>
    static void depth_first_search(const Node* n,
                                std::string& pre,
                                V& vis)
    {
        if (n->is_word) vis(pre);

        for (std::size_t i = 0; i < 27; ++i)
            if (n->child[i]) {
                pre.push_back(i == 26 ? ' '     // space branch
                                    : char('a' + static_cast<int>(i)));
                depth_first_search(n->child[i], pre, vis);
                pre.pop_back();
            }
    }

    /* Collector is a functor that collects words into the output vector. 
       It is written as struct to allow easy passing of parameters.
    */
    struct Collector {
        vector<string>& output_collection; // reference to the output vector;
        size_t num_words;                  // maximum number of words collected  
        // function call for Collector structure
        void operator()(const string& w) {
        if (output_collection.size() < num_words) // only add word if not exceeding max number of words
            output_collection.push_back(w);
        }
    };
};





int main(int argc, char* argv[]) {
    Trie trie;

    cout << "\nPart I: Read cs_phrases_500k_sorted.txt, create a Trie and add words (from Dictionary.txt) to trie: " << endl;
    /* 2. Read file into std::vector<std::string> */
    std::ifstream in("cs_phrases_500k_sorted.txt");
    std::vector<std::string> dictionary;
    std::string line;
    while (std::getline(in, line))
        if (!line.empty())         // skip blank lines
            dictionary.push_back(line);

    /* 3. Build the trie */
    for (const auto& phrase : dictionary)
        trie.insert(phrase);

    
    /* --- 3. try autocompleting the *current* token in a phrase --- */
    for (auto& s : trie.autocomplete("bina", 20))
        std::cout << s << '\n';

    /* --- 3. try autocompleting the *current* token in a phrase --- */
    for (auto& s : trie.autocomplete("binary tr", 20))
        std::cout << s << '\n';

    /* --- 4. stand-alone word completion still works --- */
    for (auto& s : trie.autocomplete("overf", 5))
        std::cout << s << '\n';

    /* --- 5. word recommendation works too --- */
    cout << "\nPart III: Word recommendations: " << endl;
    for (auto& s : trie.recommend("compiler wrri", 5))
        std::cout << s << '\n';
}