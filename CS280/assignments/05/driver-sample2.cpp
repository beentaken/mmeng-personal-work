#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "OAHashTable.h"

using std::cout;
using std::endl;
using std::ostream;
using std::setprecision;

const unsigned ID_LEN = 6;
struct Person
{
  char ID[ID_LEN + 1];
  char lastName[26];   
  char firstName[26];  
  float salary;        
  unsigned years;           
};

struct Person PEOPLE[] = {
  {"101001", "Faith", "Ian", 80000, 10},
  {"102001", "Tufnel", "Nigel", 90000, 12},
  {"103001", "Savage", "Viv", 50000, 4},
  {"104001", "Shrimpton", "Mick", 50000, 4},
  {"105001", "Besser", "Joe", 40000, 1},
  {"106001", "Smalls", "Derek", 80000, 10},
  {"107001", "St.Hubbins", "David", 90000, 12},
  {"108001", "Fleckman", "Bobbi", 120000, 8},
  {"109001", "Eton-Hogg", "Denis", 250000, 22},
  {"110001", "Upham", "Danny", 60000, 5},
  {"111001", "McLochness", "Ross", 60000, 5},
  {"112001", "Pudding", "Ronnie", 50000, 2},
  {"113001", "Schindler", "Danny", 60000, 3},
  {"114001", "Pettibone", "Jeanine", 85000, 3},
  {"115001", "Fame", "Duke", 95000, 8},
  {"116001", "Fufkin", "Artie", 45000, 1},
  {"117001", "DiBergi", "Marty", 15000, 7},
  {"118001", "Floyd", "Pink", 25000, 6},
  {"119001", "Zeppelin", "Led", 35000, 3},
  {"120001", "Mason", "Nick", 15000, 7},
  {"121001", "Wright", "Richard", 17000, 9},
  {"122001", "Waters", "Roger", 10000, 3},
  {"123001", "Gilmore", "David", 19000, 5}
};

Person **PersonRecs;

ostream& operator<<(ostream &os, const Person &person)
{
  char buffer[100];
  sprintf(buffer, "Key: %8s, Name: %12s, %12s \nSalary:%7.0f, Years: %2d", 
                  person.ID, person.lastName, person.firstName, person.salary, person.years);
  os << buffer;
  return os;
}

void FreePersonRecs(void)
{
  unsigned count = sizeof(PEOPLE) / sizeof(*PEOPLE);

  for (unsigned i = 0; i < count; i++)
    delete PersonRecs[i];

  delete[] PersonRecs;
}

void FillPersonRecs(void)
{
  unsigned count = sizeof(PEOPLE) / sizeof(*PEOPLE);
  PersonRecs = (Person **) new Person[count];

  unsigned index = 0;
  for (unsigned i = 0; i < count; i++)
  {
    Person *person = new Person;
    strcpy(person->ID, PEOPLE[i].ID);
    strcpy(person->lastName, PEOPLE[i].lastName);
    strcpy(person->firstName, PEOPLE[i].firstName);
    person->salary = PEOPLE[i].salary;
    person->years = PEOPLE[i].years;
    PersonRecs[index++] = person;
  }
}

unsigned ConstantHash(const char *, unsigned)
{
  return 1;
}

unsigned ReflexiveHash(const char *Key, unsigned TableSize)
{
  return atoi(Key) % TableSize;
}

void RevString(char *Key)
{
  size_t len = strlen(Key);
  for (size_t i = 0; i < len / 2; i++)
  {
    char t = Key[i];
    Key[i] = Key[len - i - 1];
    Key[len - i - 1] = t;
  }
}

unsigned PJWHash(const char *Key, unsigned TableSize)
{
    // Initial value of hash
  unsigned hash = 0;

    // Process each char in the string
  while (*Key)
  {
      // Shift hash left 4
    hash = (hash << 4);
      
      // Add in current char
    hash = hash + (*Key);   

      // Get the four high-order bits
    unsigned bits = hash & 0xF0000000;

      // If any of the four bits are non-zero,
    if (bits)
    {
        // Shift the four bits right 24 positions (...bbbb0000)
        // and XOR them back in to the hash
      hash = hash ^ (bits >> 24); 

        // Now, XOR the four bits back in
      hash = hash ^ bits;         
    }

      // Next char
    Key++;   
  }

    // Modulo so hash is within 0 - TableSize
  return hash % TableSize;  
}

unsigned SimpleHash(const char *Key, unsigned TableSize)
{
    // Initial value of hash
  unsigned hash = 0;

    // Process each char in the string
  while (*Key)
  {
      // Add in current char
    hash += *Key;

      // Next char
    Key++;
  }

    // Modulo so hash is within the table
  return hash % TableSize;
}

unsigned RSHash(const char *Key, unsigned TableSize)
{
  unsigned hash = 0;         // Initial value of hash
  unsigned multiplier = 127; // Prevent anomalies

    // Process each char in the string
  while (*Key)
  {
      // Adjust hash total
    hash = hash * multiplier;

      // Add in current char and mod result
    hash = (hash + *Key) % TableSize;

      // Next char
    Key++;
  }

    // Hash is within 0 - TableSize
  return hash;
}

unsigned UHash(const char *Key, unsigned TableSize)
{
  unsigned hash = 0;       // Initial value of hash
  unsigned rand1 = 31415; // "Random" 1
  unsigned rand2 = 27183; // "Random" 2

    // Process each char in string
  while (*Key)
  {
      // Multiply hash by random
    hash = hash * rand1;

      // Add in current char, keep within TableSize
    hash = (hash + *Key) % TableSize;

      // Update rand1 for next "random" number
    rand1 = (rand1 * rand2) % (TableSize - 1);

      // Next char
    Key++;
  }
    // Hash value is within 0 - TableSize - 1
  return hash;
}


struct HashData
{
  HASHFUNC Fn;
  const char *Name;
};

enum HASHFUNCS {NONE, CONSTANT, REFLEXIVE, SIMPLE, RS, UNIVERSAL, PJW};

HashData HashingFuncs[] = {
  {0, "None (Linear probing)"}
  ,{ConstantHash, "Constant Hash (1)"}
  ,{ReflexiveHash, "Reflexive Hash"}
  ,{SimpleHash, "Simple Hash"}
  ,{RSHash, "RS Hash"}
  ,{UHash, "Universal Hash"}
  ,{PJWHash, "PJW Hash"}
};

void Dispose(void *)
{
}

template <typename T>
void DummyDumpTable(const OAHashTable<T> &)
{
}


template <typename T>
void DumpTable(const OAHashTable<T> &ht)
{
  char buffer[80];
  const typename OAHashTable<T>::OAHTSlot *slots = ht.GetTable();
  HASHFUNC phf = ht.GetStats().PrimaryHashFunc_;
  HASHFUNC shf = ht.GetStats().SecondaryHashFunc_;
  for (unsigned i = 0; i < ht.GetStats().TableSize_; i++)
  {
    const typename OAHashTable<T>::OAHTSlot *slot = &slots[i]; 
    if (slot->State == OAHashTable<T>::OAHTSlot::OCCUPIED)
    {
      if (!shf)
        sprintf(buffer, "Slot: %3d, Key: %s (%d)\n", i, slot->Key, phf(slot->Key, ht.GetStats().TableSize_));
      else
        sprintf(buffer, "Slot: %3d, Key: %s (%d:%d)\n", i, slot->Key, phf(slot->Key, ht.GetStats().TableSize_), shf(slot->Key, ht.GetStats().TableSize_ - 1) + 1);
      cout << buffer;
    }
    else if (slot->State == OAHashTable<T>::OAHTSlot::DELETED)
    {
      sprintf(buffer, "Slot: %3d, Key: -- Deleted --\n", i);
      cout << buffer;
    }
    else // UNOCCUPIED
    {
      sprintf(buffer, "Slot: %3d, Key: *** Empty ***\n", i);
      cout << buffer;
    }
  }
}

template <typename T>
void DummyDumpStats(const OAHashTable<T> &, ostream &)
{
}

template <typename T>
void DumpStats(const OAHashTable<T> &ht, ostream &os = cout)
{
  os << "Number of probes: " << ht.GetStats().Probes_ << endl;
  os << "Number of expansions: " << ht.GetStats().Expansions_ << endl;
  os << "Items: " << ht.GetStats().Count_ << ", TableSize: " << ht.GetStats().TableSize_ << endl;
  os << "Load factor: " << setprecision(3) << (double) ht.GetStats().Count_ / (double) ht.GetStats().TableSize_ << endl;
}

// insert
void Test1(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test1";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 17;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      Person *person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert/grow
void Test2(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test2";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 5;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < 21; i++)
    {
      Person *person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert/delete (PACK)
void Test3(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test3";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 17;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      Person *person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.remove("110001");
    ht.remove("101001");
    ht.remove("102001");
    ht.remove("111001");

    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert/delete (MARK)/insert
void Test4(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test4";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 17;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    Person *person = 0;
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.remove("110001");
    ht.remove("101001");
    ht.remove("102001");
    ht.remove("111001");

    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.insert("122001", person);
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}


// insert/find/exception (NOT_FOUND)
void Test5(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test5";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 11;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

    // prep table
  typedef Person * T;
  Person *person = 0;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }

    // find existing
  const char *key = "106001";
  try
  {
    person = reinterpret_cast<Person *> (ht.find(key));
    cout << *person << endl;
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }

    // find non-existent
  key = "123456";
  try
  {
    person = reinterpret_cast<Person *> (ht.find(key));
    cout << *person << endl;
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert/exception (E_DUPLICATE)
void Test6(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test6";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 7;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    Person *person;
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.insert("101001", person); // duplicate

  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert/clear
void Test7(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test7";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 7;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    Person *person;
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.clear();

    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert double-hash
void Test9(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test9";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 17;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      Person *person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

// insert double-hash/delete
void Test10(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  const char *test = "Test10";
  cout << endl << "==================== " << test << " ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned initial_size = 13;
  double max_load_factor = 0.95;
  double growth_factor = 2.0;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    for (unsigned i = 0; i < initial_size - 2; i++)
    {
      Person *person = PersonRecs[i];
      ht.insert(person->ID, person);
    }
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;

    ht.remove("110001");
    ht.remove("111001");
    DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
  }
  catch (OAHashTableException &e)
  {
    std::cout << "Caught OAHashTableException in " << test << ": ";
    int value = e.code();
    if (value == OAHashTableException::E_DUPLICATE)
      std::cout << "E_DUPLICATE" << std::endl;
    else if (value == OAHashTableException::E_NO_MEMORY)
      std::cout << "E_NO_MEMORY" << std::endl;
    else if (value == OAHashTableException::E_ITEM_NOT_FOUND)
      std::cout << "E_ITEM_NOT_FOUND" << std::endl;
    else
      std::cout << "Unknown error code." << std::endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in " << test << endl << endl;
  }
}

void Test11(HashData *phd, HashData *shd,  OAHTDeletionPolicy policy)
{
  cout << endl << "==================== StressTest ====================" << endl;

  HASHFUNC phf = phd->Fn;
  HASHFUNC shf = shd->Fn;

  unsigned size = 100000;
  unsigned initial_size = 5;
  double max_load_factor = 0.90;
  double growth_factor = 1.5;

  cout << endl << "Creating table:" << endl;
  cout << "Primary hash function: " << phd->Name << endl;
  cout << "Secondary hash function: " << shd->Name << endl;
  cout << "Initial size: " << initial_size << endl;
  cout << "Max load factor: " << max_load_factor << endl;
  cout << "Growth factor: " << growth_factor << endl;
  cout << "Deletion policy: ";
  if (policy == PACK)
    cout << "PACK\n";
  else
    cout << "MARK\n";
  cout << endl;

  typedef Person * T;
  OAHashTable<T> ht(OAHashTable<T>::OAHTConfig(initial_size, phf, shf, max_load_factor, growth_factor, policy, 0));
  try
  {
    unsigned i;
    char buf[10];
    cout << "Inserting " << size << " items...\n";
    for (i = 1; i <= size; i++)
    {
      sprintf(buf, "%09i", i);
      ht.insert(buf, 0);
    }
    
    //DumpTable<T>(ht);
    DumpStats<T>(ht);
    cout << endl;
#if 1
    cout << "Deleting " << size << " items...";
    for (i = 1; i <= size; i++)
    {
      sprintf(buf, "%09i", i);
      ht.remove(buf);
    }
    cout << endl;
    DumpStats<T>(ht);
    cout << endl;
#endif
  }
  catch (OAHashTableException &)
  {
    //cout << endl << "errno: " << e.code() << ", " << e.what() << endl << endl;
    cout << endl << "**** Caught exception inserting/deleting item. (SimpleTest2) ****" << endl << endl;
  }
  catch (...) 
  {
    cout << endl << "**** Something bad happened inserting in SimpleTest2" << endl << endl;
  }
}

int main(void)
{
  FillPersonRecs();

  Test1(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test2(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test3(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test4(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], MARK);
  Test5(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test6(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test7(&HashingFuncs[SIMPLE], &HashingFuncs[NONE], PACK);
  Test9(&HashingFuncs[UNIVERSAL], &HashingFuncs[RS], MARK);
  Test10(&HashingFuncs[UNIVERSAL], &HashingFuncs[RS], MARK);
  Test11(&HashingFuncs[UNIVERSAL], &HashingFuncs[NONE], PACK);

  FreePersonRecs();
  return 0;
}
