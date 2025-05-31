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

    // /* ----------- insert to trie tree ----------- */
    // void insert(std::string w){
    //     // loop through every character in the word and convert each character to lowercase
    //     for(char& c:w)
    //         c = tolower(static_cast<unsigned char>(c));
    //     // create & start at root
    //     Node* cur = &root_;
    //     // loop through each character in the word
    //     for(char ch:w){
    //         size_t idx = ch - 'a'; // get the index of the alphabetical character (0 for 'a', 1 for 'b', ..., 25 for 'z')
    //         if(!cur->child[idx])   // if the current node's child of char 'ch' is null, create a new Node.
    //             cur->child[idx] = new Node;
    //         cur = cur->child[idx]; // then move to the (newly created/already existed) child node corresponding to the current character
    //     }
    //     cur->is_word = true;       // mark the end of the word. In particular, the word is stored and we mark the flag is_word as true.
    //     return;
    // }

    // /* ----------- word autocomplete ----------- */
    // vector<string> autocomplete(string prefix, size_t max_suggestion=50) const {
    //     /* Start with some prefix e.g., 'appl' & return a list of words that start with this particular prefix
    //        Maximum number of suggestions is given by parameter max_suggestion. 
    //     */
    //     // convert every character in the prefix to lowercase
    //     for(char& c:prefix) 
    //         c = tolower(static_cast<unsigned char>(c));
    //     // again, start @ root
    //     const Node* cur = &root_;
    //     // loop through each character in the prefix
    //     for(char char_:prefix){
    //         size_t idx = char_ - 'a';          // get the index of the character in alphabetical order (0 for 'a', 1 for 'b', ..., 25 for 'z')
    //         if(idx>=26 || !cur->child[idx]) // if index is out of bounds (not a-z) or the child node does not exist, return empty vector
    //             return {}; 
    //         cur = cur->child[idx];          // set current node to the child node corresponding to the current character
    //     }
    //     // if we reach here, it means trie has the path to this prefix. Proceed to collect all words that start with this prefix.
    //     vector<string> out;
    //     string buffer = prefix;
    //     // create a lambda function to collect words that start with the prefix
    //     // the syntax [&]() captures all variables by reference, allow us to modify 'out' vector
    //     Collector collector{out, max_suggestion};
    //     // perform a depth-first-search starting from the current node and maintaining the prefix stored in 'buf'
    //     depth_first_search(cur, buffer, collector);
    //     return out;
    // }

    /* ----------- insert word OR phrase ----------- */
    void insert(std::string text)           // e.g.  "binary search tree"
    {
        /* 0. Normalise the whole input to lowercase */
        for (char& c : text)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        /* 1. Split on spaces and insert each token separately */
        std::string word;
        Node*      cur;                     // reused per token

        auto flush_word = [&](void) {
            if (word.empty()) return;       // skip double-spaces

            cur = &root_;
            for (char ch : word) {          // <----- *unchanged inner loop*
                std::size_t idx = ch - 'a'; // assumes 'a'..'z'
                if (idx >= 26) return;      // ignore non-letters defensively
                if (!cur->child[idx])
                    cur->child[idx] = new Node;
                cur = cur->child[idx];
            }
            cur->is_word = true;            // mark the token as a stored word
            word.clear();                   // ready for next token
        };

        for (char ch : text) {
            if (ch == ' ')
                flush_word();               // finished one token
            else
                word.push_back(ch);         // keep building the token
        }
        flush_word();                       // flush the last token (if any)
    }

    vector<string> autocomplete(string query,
        size_t max_suggestion = 50) const
    {
        /* 0. Normalise case */
        for (char& c : query)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        /* 1. Split at the LAST space, if any */
        const auto last_space = query.rfind(' ');
        string fixed_part;                   // "binary "     – stays untouched
        string token;                        // "se"          – we’ll complete this

        if (last_space == string::npos) {    // no space → whole query is one token
        token      = query;
        } else {
        fixed_part = query.substr(0, last_space + 1);   // keep the trailing ' '
        token      = query.substr(last_space + 1);      // may be empty
        }

        /* 2. === ORIGINAL single-word logic on `token` === */
        // -------------------------------------------------
        const Node* cur = &root_;
        for (char ch : token) {
        size_t idx = ch - 'a';
        if (idx >= 26 || !cur->child[idx])
        return {};                    // prefix not present
        cur = cur->child[idx];
        }

        vector<string> words;                 // completions for *token*
        string buffer = token;
        Collector collector{words, max_suggestion};
        depth_first_search(cur, buffer, collector);

        /* 3.  Re-attach the untouched prefix section */
        vector<string> results;
        results.reserve(words.size());
        for (auto& w : words)
        results.emplace_back(fixed_part + w);

        return results;                       // full phrase suggestions
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

    bool is_word_in_trie(const string word) const
    {
        for (char c:word)
            c = std::tolower(static_cast<unsigned char>(c)); // convert to lowercase

        const Node* curr_node = &root_; // start at root node
        for (char char_:word) {
            std::size_t idx = char_ - 'a';      // get the index of the character in alphabetical order
            if (idx >= 26 || !curr_node->child[idx])
                return false;                   // if index is out of bounds or child node does not exist, return false
            curr_node = curr_node->child[idx];  // move to the child node corresponding to the current character
        }
        return curr_node->is_word;              // return true if the current node is a word, false otherwise
    }

    vector<string> autocomplete_phrase(string phrase,
        size_t max = 20) const
    {
        // 1. Normalise case
        for (char& c : phrase)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        // 2. Split at the *last* space
        const auto pos = phrase.rfind(' ');
        string fixed_part;                       // everything up to and incl. last space
        string last_token;                       // what user is currently typing

        if (pos == string::npos) {               // single word so far
        fixed_part.clear();
        last_token = phrase;                 // whole phrase = token
        } else {
        fixed_part = phrase.substr(0, pos + 1); // keep the trailing space
        last_token = phrase.substr(pos + 1);    // may be empty if phrase ends in ' '
        }

        // 3. Delegate to the existing word-level autocomplete
        vector<string> words = autocomplete(last_token, max);

        // 4. Re-attach the unchanged prefix
        vector<string> results;
        results.reserve(words.size());
        for (auto& w : words)
        results.emplace_back(fixed_part + w);

        return results;
    }

private:
    Node root_; // root node of the trie should be private

    // here we use a template to allow any callable type (function, lambda, structure, etc.) to be passed
    // and since we are using a structure (collector) to collect words, we can use a template to make generic pass
    template<class WC>
    static void depth_first_search(const Node* curr_node, std::string& prefix_, WC& words_collection){
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



// int main() {
//     cout << "\nPart I: Read Dictionary.txt, create a Trie and add words (from Dictionary.txt) to trie: " << endl;
//     // load dictionary from file
//     vector<string> dictionary;
//     ifstream file("Dictionary.txt");
//     string word;
//     while (file >> word) {
//         dictionary.push_back(word);
//     }

//     Trie trie;
//     // loop through each word in the dictionary and insert it into the trie using insert() method
//     for (const auto& word : dictionary) {
//         trie.insert(word);
//     }
//     cout << "Done" << endl;

//     // Part II: Autocomplete
//     string prefix;
//     cout << "\nPart II: Enter a prefix to autocomplete: ";
//     cin >> prefix;
//     // auto suggestions = trie.autocomplete(prefix, 10);
//     // cout << "Suggestions:\n";
//     // for (const auto& suggestion : suggestions) {
//     //     cout << suggestion << '\n';
//     // }

//     auto suggestions = trie.autocomplete(prefix, 10); // use autocomplete_phrase to get suggestions for the prefix
//     cout << "Suggestions:\n";
//     for (const auto& suggestion : suggestions) {
//         cout << suggestion << '\n';
//     }

//     // Part III: word recommendation
//     cout << "\nPart III: Word recommendations: ";
//     string query;
//     cout << "Enter search query: ";
//     cin >> query;
//     // perform words recommendation based on the query
//     auto recommended_suggestions = trie.recommend(query, 10);   // misspelled “apple”
//     if (recommended_suggestions.empty())
//         std::cout << "Exact match found.\n";
//     else {
//         std::cout << "Did you mean:\n";
//         for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
//     }

//     // Extra: Check if a word is in the trie
//     string check_word = query;
//     cout << "\nWe check whether the word '" << check_word << "' is in the trie.\n";
//     if (trie.is_word_in_trie(check_word)) {
//         cout << check_word << " is in the trie.\n";
//     } else {
//         cout << check_word << " is not in the trie.\n";
//     }
//     return 0;
// }

int main() {
    Trie trie;

    /* --- 1. insert single words --- */
    trie.insert("apple");
    trie.insert("apply");

    /* --- 2. insert whole phrases (tokens are added word-by-word) --- */
    trie.insert("binary search");
    trie.insert("binary search tree");
    trie.insert("breadth first search");

    /* --- 3. try autocompleting the *current* token in a phrase --- */
    for (auto& s : trie.autocomplete("binary se", 5))
        std::cout << s << '\n';

    /* --- 4. stand-alone word completion still works --- */
    for (auto& s : trie.autocomplete("app", 5))
        std::cout << s << '\n';
}