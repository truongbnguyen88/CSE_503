
#include "trie_utils.h"


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

    // Part II: Autocomplete
    string prefix;
    cout << "\nPart II: Enter a prefix to autocomplete: ";
    cin >> prefix;
    // auto suggestions = trie.autocomplete(prefix, 10);
    // cout << "Suggestions:\n";
    // for (const auto& suggestion : suggestions) {
    //     cout << suggestion << '\n';
    // }

    auto suggestions = trie.phrases_autocomplete(prefix, 10); // use autocomplete_phrase to get suggestions for the prefix
    cout << "Suggestions:\n";
    for (const auto& suggestion : suggestions) {
        cout << suggestion << '\n';
    }

    // Part III: word recommendation
    cout << "\nPart III: Word recommendations: ";
    string query;
    cout << "Enter search query: ";
    cin >> query;
    // perform words recommendation based on the query
    auto recommended_suggestions = trie.phrases_recommendation(query, 10);   // misspelled “apple”
    if (recommended_suggestions.empty())
        cout << "Exact match found.\n";
    else {
        cout << "Did you mean:\n";
        for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
    }

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
    Trie trie_extended;

    cout << "\n\nWord Autocomplete & Recommendation for both single words & phrase" << endl;

    cout << "\nFirst, Read cs_phrases_500k_sorted.txt, create a Trie and add words (from cs_phrases_500k_sorted.txt) to trie: " << endl;
    ifstream in("cs_phrases_500k_sorted.txt");
    vector<string> dictionary_of_phrases; // create a different vector of string to hold phrases / single words
    string line;
    while (getline(in, line))        // read each line from the file
        if (!line.empty())                // skip blank/empty lines
            dictionary_of_phrases.push_back(line);

    /* Build the trie using the extended version of insert() function 
       Recall: this version of insert() function takes into account spacing. Therefore, it can also handle phrases.
    */
    for (const auto& phrase : dictionary_of_phrases)
        trie_extended.insert_extended_ver(phrase);

    // string phrase;
    // cout << "Enter a phrase: ";
    // getline(cin, phrase); 
    // cout << "You entered: " << phrase << endl;
    // return 0;
    
    /* autocompleting (same as previous) but the search query is a single incomplete word */
    cout << "\nSecond, Enter a prefix to autocomplete (prefering incomplete single word): ";
    cin >> prefix;
    for (auto& s : trie_extended.phrases_autocomplete(prefix, 5))
        std::cout << s << '\n';

    /* autocompleting (same as previous) but the search query is an incomplete phrase */
    cout << "\nEnter a prefix to autocomplete (prefering incomplete phrase): ";
    std::getline(cin >> ws, prefix);   // std::ws consumes leading whitespace
    for (auto& s : trie_extended.phrases_autocomplete(prefix, 5))
        std::cout << s << '\n';

    /* word recommendation*/
    cout << "\nThird, Enter a query (prefering incomplete single word) where the word is spelled wrong: ";
    cin >> query;
    for (auto& s : trie_extended.phrases_recommendation(query, 5))
        std::cout << s << '\n';

    cout << "\nEnter a query (prefering incomplete phrase) where the phrase is spelled wrong: ";
    std::getline(cin >> ws, query);   // std::ws consumes leading whitespace
    for (auto& s : trie_extended.phrases_recommendation(query, 5))
        std::cout << s << '\n';

    return 0;
}