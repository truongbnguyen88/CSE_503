#include<iostream>
#include <random>

using namespace std;

const int TABLE_SIZE = 7;
const double LOAD_FACTOR_THRESHOLD = 0.5;

// This class will help create a hash entry
// It will store the key variable and getKey() method provide a mean to retrieve it
class HashEntry {
      int key;
  public:
      explicit HashEntry(int key_) : key(key_) {}
      int getKey() const { return key; }
  };
 
class HashMap {
private:
      HashEntry ** table;           // pointer to an array of HashEntry pointers, use pointer to pointer to allow dynamic resizing
      int capacity;                 // maximum size of hash table, this can change during rehashing
      int size;                     // current size of hash table, i.e., number of elements in the table

      // A more complicated hash function using a combination of modulus, bitwise operations, and prime multiplication
      int complex_hash_func(int value, int table_size) {
            const int prime = 41;                 // Use small prime number for mixing
            value = ((value >> 4)^value) * prime; // Mix the bits and multiply by prime
            return value % table_size;
      }
      int simple_hash_func(int value, int table_size) {
            return value % table_size;
      }

      void rehash() {
            cout << "rehash(): perform rehashing" << endl;
            // create a temporary variable to store the current capacity --> old_capacity
            // do the same for HashMap's table
            int old_capacity = capacity;
            HashEntry** old_table = table;
            // compute new capacity by finding next_prime number of 2 * capacity
            capacity = next_prime(2 * capacity);
            // re-initialize the table with new capacity & clear all elements in it i.e., making them all NULL_PTR
            table = new HashEntry*[capacity];
            for (int i = 0; i < capacity; i++){
                  table[i] = NULL;
            }

            // start with size = 0 (at this point, we have a fresh table with no element)
            size = 0;
            // Now, we need to re-insert all elements from old_table into the new table, 
            // Put the values in the exact same positions as they were in old_table
            for (int i = 0; i < old_capacity; i++) {
                  if (old_table[i] != nullptr) {
                        insert(old_table[i]->getKey());
                        delete old_table[i];    // delete the old entry after making copy (memory management)
                  }
            }
            delete[] old_table;                 // finally delete the old table
      }
    
      // check if a number is prime, it will be useful in other functions
      bool is_prime(int n) {
            if (n<2) return false;
            for (int i=2; i*i<=n; i++) {
                  if (n % i == 0) 
                        return false;
            }
            return true;
      }

      // compute the next prime number greater than or equal to n
      int next_prime(int n) {
            while (!is_prime(n)) n++;
            return n;
      }

public:
      HashMap() {
            capacity = TABLE_SIZE;              // initialize HashMap capacity to TABLE_SIZE. Note: capacity can be updated during re-hash
            size = 0;                           // current size of HashMap is 0 (i.e., no element yet)
            table = new HashEntry*[capacity];   // initialize a fresh table of HashEntry pointers
            for (int i = 0; i < capacity; i++)
                  table[i] = NULL;

            // Here is how we can visualize table:
            // table = [ NULL_PTR[0], NULL_PTR[1], NULL_PTR[2], ...., NULL_PTR[capacity-2], NULL_PTR[capacity-1] ]
      }
 
      /* get() will take in a integer value and compute hash-index that we can put value in the HashMap table */
      int get(int value) {
            // first, compute the hash index using the hash function
            int hash = complex_hash_func(value, capacity);
            // Here, we're gonna find an index where there is no value is stored.
            // I.e., we need to find the index where NULL_PTR[such_index] is NULL and the input value is not yet inserted.
            // We are using quadratic probling to resolve values-collisions
            int j = 0;
            while (table[complex_hash_func(hash + j*j, capacity)] != NULL && 
                   table[complex_hash_func(hash + j*j, capacity)]->getKey() != value) {
                  j++;
                  if (j == capacity) return -1; // if we looped through the whole table and didn't find it, return -1 to avoid infinite loop
            }
            // re-compute correct hash index once we found the appropriate position
            hash = complex_hash_func(hash + j*j, capacity);  // again quadratic probing.
            // A quick trick that I've learned: to double check if value is in the table:
            // if table[hash] is NULL, then value is not in the table, return -1
            // if not, then extract the key.
            if (table[hash] == NULL) {
                  return -1;
            }
            else
                  return table[hash]->getKey();
      }
 
      void insert(int value) {
            // input value exists, no need to insert
            if (get(value) != -1) return;

            // implement rehashing if the table is full using load factor
            // Note on LOAD_FACTOR: 
            // - LOAD_FACTOR increases --> table becomes more full --> more collisions can happen --> this is bad for a hash table
            double load_factor = static_cast<double>(size) / capacity;
            // Therefore, we need to check if current load factor exceed the given threshold.
            // If it does, it means table is becoming more full, and we need to rehash.
            if (load_factor > LOAD_FACTOR_THRESHOLD) {
                  rehash();
            }
            // // Similar to get(), we compute hash index in the HashMap table for the input value
            int hash = complex_hash_func(value, capacity);
            int j = 0;
            while (table[complex_hash_func(hash + j*j, capacity)] != NULL && 
                   table[complex_hash_func(hash + j*j, capacity)]->getKey() != value) {
                  j++;
                  if (j == capacity) return; // if we looped through the whole table and didn't find it, return to avoid infinite loop
            }
            hash = complex_hash_func(hash + j*j, capacity); // compute correct hash index
            table[hash] = new HashEntry(value);
            size++;     // after we successfully insert a value, we increase the size of the HashMap 
      }

      void display() const {
            cout << "\nDisplaying HashMap table:" << endl;
            for (int i = 0; i < capacity; ++i) {
                  cout << "hash_index " << i << ": " << (table[i] ? to_string(table[i]->getKey()) : "__null_ptr__") << endl;
            }
        }
 
      ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};

int main(int argc, const char * argv[])
{
      cout << "Initial TABLE_SIZE =" << TABLE_SIZE << endl;
      HashMap myHashMap;
      myHashMap.insert(139);
      myHashMap.insert(99);
      myHashMap.insert(16);
      myHashMap.insert(134);
      myHashMap.insert(42);
      myHashMap.insert(0);
      myHashMap.insert(6);
      myHashMap.insert(9);
      myHashMap.insert(4);
      myHashMap.insert(53);
      myHashMap.insert(47);
      myHashMap.insert(66);

      /* Try generate random integer to insert to myHashMap 
         Goal: to see how rehashing works in the case of larger number of insertions
      */
      // random_device rd;                            // set random seed
      // mt19937 gen(rd());  
      // uniform_int_distribution<> distr(1, 1000);
      // for (int i = 1; i < 100; i++) {
      //       int random_value = distr(gen);
      //       myHashMap.insert(random_value);
      // }

      myHashMap.display();

      cout << "\nCheck if an integer is in myHashMap: return same integer if it exists, -1 otherwise" << endl;
      cout << "Check 53: " << myHashMap.get(53) << endl;
      cout << "Check 12: " << myHashMap.get(12) << endl;

      return 0;
}