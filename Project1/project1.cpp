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
        string buffer = prefix;
        // create a lambda function to collect words that start with the prefix
        // the syntax [&]() captures all variables by reference, allow us to modify 'out' vector
        Collector collector{out, max_suggestion};
        // perform a depth-first-search starting from the current node and maintaining the prefix stored in 'buf'
        depth_first_search(cur, buffer, collector);
        return out;
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
        std::string buffer = prefix;
        Collector collector{out, max};
        depth_first_search(cur, buffer, collector);
        return out;
    }

private:
    Node root_; // root node of the trie should be private

    // here we use a template to allow any callable type (function, lambda, structure, etc.) to be passed
    // and since we are using a structure (collector) to collect words, we can use a template to make generic pass
    template<class WC>
    static void depth_first_search(const Node* curr_node, std::string& prefix_, WC& words_collection){
        if(curr_node->is_word) {
            words_collection(prefix_);                           // sanity check: if the current node is a word, call the visitor with the current prefix b/c prefix_ is a word at this point
        }
        for(std::size_t i=0;i<26;++i)               // iterate through all children (a->z) of the current node
            if(curr_node->child[i]){                // if child node of current node exists then go deeper to collect characters
                prefix_.push_back(char('a'+i));     // found character, push_back it to the prefix
                depth_first_search(curr_node->child[i], prefix_, words_collection);  // recursive call to go deeper into the trie with root now @ child node of n
                prefix_.pop_back();                 // under chacracter to restore
            }
    }

    /* Collector is a functor that collects words into the output vector. 
       It is written as struct to allow easy passing of parameters. */
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


/* ---------- Demo ---------- */
int main() {
    cout << "\nPart I: Read Dictionary.txt, create a Trie and add words (from Dictionary.txt) to trie: " << endl;
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
    cout << "Done" << endl;

    // Example usage
    string prefix;
    cout << "\nPart II: Enter a prefix to autocomplete: ";
    cin >> prefix;
    auto suggestions = trie.autocomplete(prefix, 10);
    cout << "Suggestions:\n";
    for (const auto& suggestion : suggestions) {
        cout << suggestion << '\n';
    }

    // 
    cout << "\nPart III: Word recommendation: ";
    auto recommended_suggestions = trie.recommend("scag", 5);   // misspelled “apple”
    if (recommended_suggestions.empty())
        std::cout << "Exact match found.\n";
    else {
        std::cout << "Did you mean:\n";
        for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
    }

    return 0;
}