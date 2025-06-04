
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

    auto suggestions = trie.autocomplete(prefix, 10); // use autocomplete_phrase to get suggestions for the prefix
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
    auto recommended_suggestions = trie.recommend(query, 10);   // misspelled “apple”
    if (recommended_suggestions.empty())
        cout << "Exact match found.\n";
    else {
        cout << "Did you mean:\n";
        for (auto& s : recommended_suggestions) std::cout << "  " << s << '\n';
    }

    return 0;
}