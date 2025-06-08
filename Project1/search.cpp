
#include "trie_utils.h"


int main() {
    
    vector<string> dictionary;
    vector<string> dictionary_of_phrases; // create a different vector of string to hold phrases / single words
    string prefix;
    string query;
    string line;
    

    /* For Dictionary that has phrases of words and single word 
       This is to test the ability of class Trie to handle phrases and words.
       We will use a different dictionary file that contains phrases of words and also single words.
       The file is called cs_phrases_500k_sorted.txt. 
       To obtain this text file, I asked ChatGPT to generate.
            Basically it contains 500,000 phrases or single words. 
            These phrases and words related to computer sciences.
            These phrases and words are sorted in alphabetical order and have the starting characters ranging from a-z.
        The original file, provided by the course instructors, only contains single words.
    */
    Trie trie;

    cout << "\n\nWord Autocomplete & Recommendation for both single words & phrase" << endl;

    cout << "\nPart I: Read Dictionary.txt, create a Trie and insert words/phrases to trie: " << endl;
    ifstream in("Dictionary.txt");
    while (getline(in, line))        // read each line from the file
        if (!line.empty())                // skip blank/empty lines
            dictionary_of_phrases.push_back(line);

    /* Build the trie using the extended version of insert() function 
       Recall: this version of insert() function takes into account spacing. Therefore, it can also handle phrases.
    */
    for (const auto& phrase : dictionary_of_phrases)
        trie.phrases_insert(phrase);
    
    /* autocompleting (same as previous) but the search query is a single incomplete word */
    cout << "\nPart II (word-autocompletion): Please type search queries: ";
    std::getline(cin >> ws, prefix);   // std::ws consumes leading whitespace
    for (auto& s : trie.phrases_autocomplete(prefix, 5))
        std::cout << s << '\n';

    /* word recommendation*/
    cout << "\nPart III (word-recommendation): Please type search queries: ";
    std::getline(cin >> ws, query);   // std::ws consumes leading whitespace
    for (auto& s : trie.phrases_recommendation(query, 5))
        std::cout << s << '\n';

    return 0;
}