#ifndef TRIE_UTILS_H
#define TRIE_UTILS_H

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

    static inline std::size_t map_idx(char ch) {
        if (ch == ' ')      return 26;           // space
        if ('a' <= ch && ch <= 'z')
            return static_cast<std::size_t>(ch - 'a');
        throw std::runtime_error("unsupported character");
    }

    /* ----------- insert to trie tree ----------- */
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

    /* ----------- insert word OR phrase ----------- */
    void insert_extended_ver(std::string text)
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

    /* ----------- word autocomplete ----------- */
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
        for(char char_:prefix){
            size_t idx = char_ - 'a';          // get the index of the character in alphabetical order (0 for 'a', 1 for 'b', ..., 25 for 'z')
            if(idx>=26 || !cur->child[idx]) // if index is out of bounds (not a-z) or the child node does not exist, return empty vector
                return {}; 
            cur = cur->child[idx];          // set current node to the child node corresponding to the current character
        }
        // if we reach here, it means trie has the path to this prefix. Proceed to collect all words that start with this prefix.
        vector<string> out;
        string buffer = prefix;
        // create a lambda function to collect words that start with the prefix
        // the syntax [&]() captures all variables by reference, allow us to modify 'out' vector
        Collector collector{out, max_suggestion};
        // perform a depth-first-search starting from the current node and maintaining the prefix stored in 'buf'
        depth_first_search(cur, buffer, collector);
        return out;
    }

    /* ----------- recommendation search ----------- */
    vector<string> recommend(string query,
                                       size_t max = 20) const
    {
        for (char& c : query)
            c = std::tolower(static_cast<unsigned char>(c)); // convert to lowercase

        const Node* curr_node = &root_;         // create starting node (root node)
        std::string prefix;                     // create an empty prefix string to build the prefix as we traverse the trie

        // Traverse the trie to find the longest prefix that matches the query. Loop through each character in the query
        for (char char_ : query) {
            std::size_t idx = char_ - 'a';
            if (idx >= 26 || !curr_node->child[idx]){
                break;                          // if idx is out-of-bounds or child node is NULL, break out the for-loop, move to next character
            }
            curr_node = curr_node->child[idx];  // otherwise, move to child node
            prefix.push_back(char_);            // append the character to the prefix to build prefix.
        }

        // After we built the prefix:
        // If the whole word is present, nothing to “recommend”.
        if (prefix.size() == query.size() && curr_node->is_word) return {};

        // Else, Collect completions under the matched prefix node using autocomplete function.
        std::vector<std::string> out;
        out = autocomplete(prefix, max); // call autocomplete with the prefix and max number of suggestions
        return out;
    }

    vector<string> phrases_autocomplete(string prefix,
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
    std::vector<std::string> phrases_recommendation(std::string query,
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
        return phrases_autocomplete(prefix, max);
    }

private:
    Node root_; // root node of the trie should be private

    // here we use a template to allow any callable type (function, lambda, structure, etc.) to be passed
    // and since we are using a structure (collector) to collect words, we can use a template to make generic pass
    template<class WC>
    static void depth_first_search_old(const Node* curr_node, std::string& prefix_, WC& words_collection){
        if(curr_node->is_word) {
            words_collection(prefix_);              // sanity check: if the current node is a word, append prefix_ to word collection b/c it is a word at this point
        }
        for(std::size_t i=0;i<26;++i)               // iterate through all children (a->z) of the current node
            if(curr_node->child[i]){                // if child node of current node exists then go deeper to collect characters
                prefix_.push_back(char('a'+i));     // found character, push_back it to the prefix
                depth_first_search(curr_node->child[i], prefix_, words_collection);  // recursive call to go deeper into the trie with root now @ child node of n
                prefix_.pop_back();                 // under chacracter to restore
            }
    }

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

#endif