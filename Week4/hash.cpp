
#include<iostream> 

const int TABLE_SIZE = 17;
 
class HashMap {
private:
       
       HashEntry *table;
public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] == NULL;
      }
 
      int get(int key) {
            int hash = (key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] == NULL)
                  return -1;
            else
                  return table[hash]->getValue();
      }
 
      void insert(int value) {
        int hash = (value % TABLE_SIZE);
            if(get(value) == -1){
              table.push_back(value);
            }
            else if(get(value) != -1){
              table[hash]->getValue()->value;
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
    HashMap Kirsten;
    Kirsten.insert(12);
}


