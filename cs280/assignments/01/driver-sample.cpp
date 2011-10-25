#include <iostream> 
#include <cstdio>
#include <cstring>

using std::cout;
using std::endl;
using std::printf;

#define SHOWADDRESS1
#define SHOWADDRESS2
#define SHOWREAL
#define SHOW_EXCEPTIONS

#include "ObjectAllocator.h"
#include "PRNG.h"

#ifdef _MSC_VER
#pragma warning(disable: 4101) // Suppress 'unreferenced local variable (what)'
#endif

struct Student
{
  int Age;        // 4
  long Year;      // 4
  float GPA;      // 4
  long ID;        // 4
};

struct Employee
{
  Employee *Next;      //  4
  char lastName[12];   // 12
  char firstName[12];  // 12
  float salary;        //  4
  int years;           //  4
};


ObjectAllocator *studentObjectMgr;
ObjectAllocator *employeeObjectMgr;

// Support functions
void PrintCounts(const ObjectAllocator *nm);
void PrintCounts2(const ObjectAllocator *nm);
void DumpPages(const ObjectAllocator *nm, unsigned width);

void DoStudents(unsigned padding);    // debug, padding=X
void DoEmployees(void);               // debug
void TestPadding(void);               // DoStudents(padding=16)
void TestHeaderBlocks(unsigned size); // debug, padding=4, header
void TestCorruption(void);            // debug, padding=8
void DisableOA(void);                 // cpp_mem_mgr
void TestLeak(void);                  // debug
void TestValidate(void);              // debug, padding=8
void TestAlignment(void);             // debug, padding=2, align=8
void TestFreeEmptyPages1(void);       // debug, padding=2
void TestFreeEmptyPages2(void);       // debug, padding=2, header, align=16
void TestFreeEmptyPages3(void);       // debug, padding=6
void StressFreeChecking(void);        //
void Stress(bool UseNewDelete);       // 

struct Person
{
  char lastName[12];   
  char firstName[12];  
  float salary;        
  int years;           
};

struct Person PEOPLE[] = {
  {"Faith", "Ian", 80000, 10},
  {"Tufnel", "Nigel", 90000, 12},
  {"Savage", "Viv", 50000, 4},
  {"Shrimpton", "Mick", 50000, 4},
  {"Besser", "Joe", 40000, 1},
  {"Smalls", "Derek", 80000, 10},
  {"St.Hubbins", "David", 90000, 12},
  {"Fleckman", "Bobbi", 120000, 8},
  {"Eton-Hogg", "Denis", 250000, 22},
  {"Upham", "Denny", 60000, 5},
  {"McLochness", "Ross", 60000, 5},
  {"Pudding", "Ronnie", 50000, 2},
  {"Schindler", "Danny", 60000, 3},
  {"Pettibone", "Jeanine", 85000, 3},
  {"Fame", "Duke", 95000, 8},
  {"Fufkin", "Artie", 45000, 1},
  {"DiBergi", "Marty", 15000, 7},
  {"Floyd", "Pink", 25000, 6},
  {"Zeppelin", "Led", 35000, 3},
  {"Mason", "Nick", 15000, 7},
  {"Wright", "Richard", 17000, 9},
  {"Waters", "Roger", 10000, 3},
  {"Gilmore", "David", 19000, 5}
};

void FillEmployee(Employee& emp)
{
  static unsigned int index = 0;

  strcpy(emp.firstName, PEOPLE[index].firstName);
  strcpy(emp.lastName, PEOPLE[index].lastName);
  emp.salary = PEOPLE[index].salary;
  emp.years = PEOPLE[index].years;
  index++;
  if (index >= sizeof(PEOPLE) / sizeof(*PEOPLE))
    index = 0;
}

void DumpCallback(const void *block, unsigned int actual_size)
{
  unsigned int size = actual_size;
    // limit to 16 bytes
  if (actual_size > 16)
    size = 16;

  unsigned char *data = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(block));

#ifdef SHOWADDRESS1
  printf("Block at 0x%p, %i bytes long.\n", block, actual_size);
#else
  printf("Block at 0x00000000, %i bytes long.\n", actual_size);
#endif

    // If we were passed a NULL pointer, do nothing
  if (!block)
    return;

  printf(" Data: <");
  for (unsigned int i = 0; i < size; i++)
  {
    unsigned char c = *data++;
    if (c > 31 && c < 128) // printable range
      printf("%c", c);
    else
      printf(" ");
  }
  printf(">");

  data = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(block));
  for (unsigned int i = 0; i < size; i++)
    printf(" %02X", (int)*data++);
  printf("\n");
}

void DumpCallback2(const void *, unsigned int)
{
}

void CheckAndDumpLeaks(const ObjectAllocator* oa)
{
  if (oa->GetStats().ObjectsInUse_)
  {
    printf("Detected memory leaks!\n");
    printf("Dumping objects ->\n");
    unsigned leaks = oa->DumpMemoryInUse(DumpCallback);
    printf("Object dump complete. [%u]\n", leaks);
  }
  else
    printf("No leaks detected.\n");
}

void ValidateCallback(const void *block, unsigned int actual_size)
{
#ifdef SHOWADDRESS2
  printf("Block at 0x%p, %i bytes long.\n", block, actual_size);
#else
  printf("Block at 0x00000000, %i bytes long.\n", actual_size);
#endif

  if (!block)
    return;
}

//****************************************************************************************************
//****************************************************************************************************
void DumpPagesx(ObjectAllocator *oa)
{
  unsigned header_size = oa->GetConfig().HeaderBlocks_;

    // Walk the pages looking for in-use (non-free) blocks
  const unsigned char *Page = reinterpret_cast<const unsigned char *>(oa->GetPageList());
  int count = 1;
  unsigned total_size = oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header_size;
  while (Page != 0)
  {
    const unsigned char *p = reinterpret_cast<const unsigned char *>(Page);

    printf("Page %i:\n", count);

      // Next pointer
    for (unsigned i = 0; i < sizeof(void *); i++)
      printf("%02X ", *p++);
    printf("\n");

    for (unsigned i = 0; i < total_size; i++)
      printf("%02X ", *p++);
    printf("\n");

      // Next page
    Page = reinterpret_cast<const unsigned char *>((reinterpret_cast<const GenericObject *>(Page))->Next);
  }

  delete oa;
}


//****************************************************************************************************
//****************************************************************************************************
#ifdef _MSC_VER
#pragma warning(disable: 4702) // Suppress 'unreachable code'
#endif

#ifdef _MSC_VER
#pragma warning(default: 4702) // Enable 'unreachable code'
#endif

int RandomInt(int low, int high)
{
  //return std::rand() % (high - low + 1) + low;
  return Digipen::Utils::Random(low, high);
}

template <typename T>
void SwapT(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void Shuffle(T *array, unsigned count)
{
  for (unsigned int i = 0; i < count; i++)
  {
    int r = RandomInt(i, (int)count - 1);
    SwapT(array[i], array[r]);
  }
}

template <typename T>
void PrintArray(T *array, unsigned count)
{
  for (unsigned i = 0; i < count; i++)
    std::cout << array[i] << std::endl;
}

const unsigned objects = 4096;
const unsigned pages = 100;
const unsigned total = objects * pages;
void *ptrs[total];

#include <ctime>
void Stress(bool UseNewDelete)
{
  std::clock_t start, end;
  ObjectAllocator *oa;
    
  try
  {
    bool newdel = UseNewDelete;
    bool debug = false;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, objects, pages, debug, padbytes, header, alignment);
    oa  = new ObjectAllocator(sizeof(Student), config);
    start = std::clock();
    for (unsigned i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }

    Shuffle(ptrs, total);
    for (unsigned i = 0; i < total; i++)
    {
      oa->Free(ptrs[i]);
    }

    delete oa;
    end = std::clock();
    printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction in Stress."  << endl;
#endif
    return;
  }
}

void StressFreeChecking(void)
{
  unsigned objects;
  unsigned pages;

  objects = 1000;
  pages = 2000;

  const unsigned total = objects * pages;

  std::clock_t start, end;
  ObjectAllocator *oa;
    
  char **ptrs = new char*[total];
  
  try
  { 
    bool newdel = false;
    bool debug = false;
    unsigned padbytes = 1;
    unsigned header = 4;
    unsigned alignment = 0;

    OAConfig config(newdel, objects, pages, debug, padbytes, header, alignment);
    //OAConfig config(newdel, objects, pages, debug, 1, use_header);
    oa  = new ObjectAllocator(sizeof(Student), config);
    cout << "Page size = " << oa->GetStats().PageSize_;
    cout << ", Pad bytes = " << oa->GetConfig().PadBytes_;
    cout << ", ObjectsPerPage = " << objects << ", MaxPages = " << pages << ", MaxObjects = " << total << endl;
    PrintCounts(oa);

    start = std::clock();
    for (unsigned int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = (char *)p;
    }

    Shuffle(ptrs, total);
    for (unsigned int i = 0; i < total; i++)
    {
      oa->Free(ptrs[i]);
    }

    oa->DumpMemoryInUse(DumpCallback2);
    end = std::clock();
    delete oa;
    printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during StressFreeChecking."  << endl;
    fflush(stdout);
#endif
    return;
  }
  delete [] ptrs;
}

void TestFreeEmptyPages1(void)
{
  if (!ObjectAllocator::ImplementedExtraCredit())
    return;

  ObjectAllocator *oa;
  const int objects = 4;
  const int pages = 3;
  const int total = objects * pages;
  void *ptrs[total];
  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 2;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, objects, pages, debug, padbytes, header, alignment);
    //OAConfig config(false, objects, pages, true, 2);
    oa  = new ObjectAllocator(sizeof(Student), config);

    /*
    unsigned header_size;
    if (oa->GetConfig().UseHeaderBlock_)
      header_size = OAConfig::HeaderBlockSize_;
    else
      header_size = 0;
     */

    //unsigned width = oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header_size + oa->GetConfig().InterAlignSize_;
    unsigned width = 32; //oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header_size;

    /*
    if (oa->GetConfig().Alignment_ > 1)
      width = oa->GetConfig().Alignment_;
    else
      width = 16;
    */

    for (int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }
    //****************************************************************************
    PrintCounts(oa);
    DumpPages(oa, width);

    for (int i = 0; i < objects; i++)
      oa->Free(ptrs[i + 0]);

    for (int i = 0; i < objects; i++)
      oa->Free(ptrs[i + 8]);

    //****************************************************************************
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    for (int i = 0; i < objects - 1; i++)
      oa->Free(ptrs[i + 4]);
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    oa->Free(ptrs[7]);
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);


    //****************************************************************************
    printf("\n\n");
    void *p = oa->Allocate();
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    oa->Free(p);
    //oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    delete oa;
    //printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during TestFreeEmptyPages1."  << endl;
#endif
    return;
  }
}

void TestFreeEmptyPages2(void)
{
  if (!ObjectAllocator::ImplementedExtraCredit())
    return;

  ObjectAllocator *oa;
  const int objects = 4;
  const int pages = 3;
  const int total = objects * pages;
  void *ptrs[total];
  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 2;
    unsigned header = 4;
    unsigned alignment = 16;

    OAConfig config(newdel, objects, pages, debug, padbytes, header, alignment);
    //OAConfig config(false, objects, pages, true, 2, true, 16);
    oa  = new ObjectAllocator(sizeof(Student), config);

    unsigned width = 32;

    /*
    if (oa->GetConfig().Alignment_ > 1)
      width = oa->GetConfig().Alignment_;
    else
      width = 16;
    */

    for (int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }
    //****************************************************************************
    PrintCounts(oa);
    DumpPages(oa, width);

    for (int i = 0; i < objects; i++)
      oa->Free(ptrs[i + 0]);

    for (int i = 0; i < objects; i++)
      oa->Free(ptrs[i + 8]);

    //****************************************************************************
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    for (int i = 0; i < objects - 1; i++)
      oa->Free(ptrs[i + 4]);
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    //****************************************************************************
    oa->Free(ptrs[7]);
    oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);

    delete oa;
    //printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during TestFreeEmptyPages2."  << endl;
#endif
    return;
  }
}

void TestFreeEmptyPages3(void)
{
  if (!ObjectAllocator::ImplementedExtraCredit())
    return;

  ObjectAllocator *oa;
  const int objects = 8;
  const int pages = 48;
  const int total = objects * pages;
  void *ptrs[total];
  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 6;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, objects, pages, debug, padbytes, header, alignment);
    //OAConfig config(false, objects, pages, true, 6);
    oa  = new ObjectAllocator(sizeof(Student), config);

    unsigned width = 32; 

    for (int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }
    PrintCounts(oa);
    //DumpPages(oa, width);

    Shuffle(ptrs, total);
    for (int i = 0; i < total - 5; i++)
    {
      oa->Free(ptrs[i]);
    }
    PrintCounts(oa);
    //DumpPages(oa, width);

    unsigned count = oa->FreeEmptyPages();
    PrintCounts(oa);
    DumpPages(oa, width);
    printf("%i pages freed\n", count);
    //CheckAndDumpLeaks(oa);


    delete oa;
    //printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during TestFreeEmptyPages3."  << endl;
#endif
    return;
  }
}



//****************************************************************************************************
//****************************************************************************************************
void TestHeaderBlocks(unsigned size)
{
  ObjectAllocator *oa = 0;

  unsigned total_size = 0;
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 4;
    unsigned header_size = size;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header_size, alignment);
    //OAConfig config(false, 4, 2, true, padbytes, use_header);
    oa = new ObjectAllocator(sizeof(Student), config);
    total_size = oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header_size;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction in TestHeaderBlocks."  << endl;
#endif
    return;
  }

  DumpPages(oa, total_size);

  Student *pStudent1 = 0;
  try
  {
    pStudent1 = reinterpret_cast<Student *>( oa->Allocate() );
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate in TestHeaderBlocks."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Allocate in TestHeaderBlocks."  << endl;
  }

  DumpPages(oa, total_size);

  try
  {
    oa->Free(pStudent1);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
      cout << "Exception thrown from Free in TestHeaderBlocks."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in TestHeaderBlocks."  << endl;
  }

  DumpPages(oa, total_size);

  delete oa;
}

//****************************************************************************************************
//****************************************************************************************************
void DoStudents(unsigned padding = 0)
{
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = padding;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    //OAConfig config(false, 4, 2, true, padbytes, header, alignment);
    studentObjectMgr = new ObjectAllocator(sizeof(Student), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction in DoStudents."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from constructor in DoStudents."  << endl;
  }

  cout << "Page size = " << studentObjectMgr->GetStats().PageSize_;
  cout << ", Pad bytes = " << studentObjectMgr->GetConfig().PadBytes_;
  cout << " ObjectsPerPage = 4, MaxPages = 2, MaxObjects = 8" << endl;

  PrintCounts(studentObjectMgr);

  Student *pStudent1 = 0, *pStudent2 = 0, *pStudent3 = 0;
  try
  {
    pStudent1 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts(studentObjectMgr);
    pStudent2 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts(studentObjectMgr);
    pStudent3 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate in DoStudents."  << endl;
#endif
  }
  catch(...)
  { 
    cout << "Unexpected exception thrown from Allocate in DoStudents."  << endl;
  }

  Student *pStudent4[6];
  for (int i = 0; i < 6; i++)
  {
    try
    {
      pStudent4[i] = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate (2) in DoStudents."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate (2) in DoStudents."  << endl;
    }

  }
  PrintCounts(studentObjectMgr);

  try
  {
    studentObjectMgr->Free(pStudent1);
    PrintCounts(studentObjectMgr);
    studentObjectMgr->Free(pStudent2);
    PrintCounts(studentObjectMgr);
    studentObjectMgr->Free(pStudent3);
    PrintCounts(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
      cout << "Exception thrown from Free in DoStudents."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoStudents."  << endl;
  }

  cout << "Most students in use: " << studentObjectMgr->GetStats().MostObjects_ << endl;
  delete studentObjectMgr;
}

//****************************************************************************************************
//****************************************************************************************************
void TestPadding(void)
{
  DoStudents(16);
}


//****************************************************************************************************
//****************************************************************************************************
void DoEmployees(void)
{
  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    //OAConfig config(false, 4, 2, true);
    employeeObjectMgr = new ObjectAllocator(sizeof(Employee), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction in DoEmployees."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown during constructor in DoEmployees."  << endl;
  }

  cout << "Page size = " << employeeObjectMgr->GetStats().PageSize_;
  cout << ", Pad bytes = " << employeeObjectMgr->GetConfig().PadBytes_;
  cout << ", ObjectsPerPage = 4, MaxPages = 2, MaxObjects = 8" << endl;

  PrintCounts(employeeObjectMgr);

  Employee *pEmployee1 = 0, *pEmployee2 = 0, *pEmployee3 = 0;
  try
  {
    pEmployee1 = (Employee *) employeeObjectMgr->Allocate();
    PrintCounts(employeeObjectMgr);
    pEmployee2 = (Employee *) employeeObjectMgr->Allocate();
    PrintCounts(employeeObjectMgr);
    pEmployee3 = (Employee *) employeeObjectMgr->Allocate();
    PrintCounts(employeeObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate in DoEmployees."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Allocate in DoEmployees."  << endl;
  }

  Employee *pEmployee4[7];
  for (int i = 0; i < 7; i++)
  {
    try 
    {
        // Need to use /EHa, not /EHs
        // ******************************************* Puts &employeeObjMgr in ecx
      pEmployee4[i] = (Employee *) employeeObjectMgr->Allocate();
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
         // ******************** Hoses the ecx register containing &employeeObjMgr
      cout << e.what() << endl;
#else
      cout << "Exception thrown from Allocate (2) in DoEmployees."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate (2) in DoEmployees."  << endl;
    }
  }
    // ************************* blindly pushes ecx as if it still has &empObjMgr
  PrintCounts(employeeObjectMgr); 

  try
  {
    employeeObjectMgr->Free(pEmployee1);
    PrintCounts(employeeObjectMgr);
    employeeObjectMgr->Free(pEmployee2);
    PrintCounts(employeeObjectMgr);
    employeeObjectMgr->Free(pEmployee3);
    PrintCounts(employeeObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free in DoEmployees."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoEmployees."  << endl;
  }

    // Free an object twice
  try {
    employeeObjectMgr->Free(pEmployee1);
  }
  catch (const OAException& e) 
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free (Freeing object twice) in DoEmployees."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (Freeing object twice) in DoEmployees."  << endl;
  }

    // Free an invalid pointer
  try {
    employeeObjectMgr->Free((void *)100);
  }
  catch (const OAException& e) 
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free (Freeing address 100) in DoEmployees."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (Freeing address 100) in DoEmployees."  << endl;
  }

    // Free an invalid pointer (bad boundary condition)
  try 
  {
    employeeObjectMgr->Free((char *)pEmployee4[0] + 4);
  }
  catch (const OAException& e) 
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free (Freeing address on bad boundary) in DoEmployees."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (Freeing address on bad boundary) in DoEmployees."  << endl;
  }

  cout << "Most employees in use: " << employeeObjectMgr->GetStats().MostObjects_<< endl;
  delete employeeObjectMgr;
}

//****************************************************************************************************
//****************************************************************************************************
void DisableOA(void)
{
  try 
  {
    bool newdel = true;
    bool debug = false;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    //OAConfig config(true, 4, 2, false);
    studentObjectMgr = new ObjectAllocator(sizeof(Student), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during constructor in DisableOA."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown during constructor in DisableOA."  << endl;
  }

  PrintCounts2(studentObjectMgr);

  Student *pStudent1 = 0, *pStudent2 = 0, *pStudent3 = 0;
  try
  {
    pStudent1 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts2(studentObjectMgr);
    pStudent2 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts2(studentObjectMgr);
    pStudent3 = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    PrintCounts2(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate in DisableOA."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Allocate in DisableOA."  << endl;
  }

  Student *pStudent4[6];
  for (int i = 0; i < 6; i++)
  {
    try
    {
      pStudent4[i] = reinterpret_cast<Student *>( studentObjectMgr->Allocate() );
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Allocate (2) in DisableOA."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate (2) in DisableOA."  << endl;
    }

  }
  PrintCounts2(studentObjectMgr);

  try
  {
    studentObjectMgr->Free(pStudent1);
    PrintCounts2(studentObjectMgr);
    studentObjectMgr->Free(pStudent2);
    PrintCounts2(studentObjectMgr);
    studentObjectMgr->Free(pStudent3);
    PrintCounts2(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
      cout << "Exception thrown from Free in DisableOA."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DIsableOA."  << endl;
  }

  for (int i = 0; i < 6; i++)
  {
    try
    {
      studentObjectMgr->Free(pStudent4[i]);
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free in DisableOA."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Free in DisableOA."  << endl;
    }

  }
  PrintCounts2(studentObjectMgr);

  cout << "Most students in use: " << studentObjectMgr->GetStats().MostObjects_ << endl;
  delete studentObjectMgr;
}

//****************************************************************************************************
//****************************************************************************************************
void TestCorruption(void)
{
  ObjectAllocator *oa = 0;
  unsigned char *p;
  unsigned padbytes = 8;
  unsigned i;
  Student *pStudent1, *pStudent2 = 0;
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    //OAConfig config(false, 4, 2, true, padbytes);
    oa = new ObjectAllocator(sizeof(Student), config);
    pStudent1 = reinterpret_cast<Student *>( oa->Allocate() );
    pStudent2 = reinterpret_cast<Student *>( oa->Allocate() );
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction/allocation in TestCorruption."  << endl;
#endif
    return;
  }

    // corrupt left pad bytes
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent1)) - padbytes;
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xFF;

    // corrupt right pad bytes
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent2)) + sizeof(Student);
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xEE;

  try
  {
    oa->Free(pStudent1);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
    if (e.code() == e.E_CORRUPTED_BLOCK)
      cout << "Exception thrown from Free: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from Free in TestCorruption. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in TestCorruption."  << endl;
  }

  try
  {
    oa->Free(pStudent2);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
    if (e.code() == e.E_CORRUPTED_BLOCK)
      cout << "Exception thrown from Free: E_CORRUPTED_BLOCK on right"  << endl;
    else
      cout << "****** Unknown OAException thrown from Free (2) in TestCorruption. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (2) in TestCorruption."  << endl;
  }

  delete oa;
}

//****************************************************************************************************
//****************************************************************************************************
void TestLeak(void)
{
  unsigned count = 0;
  Employee **pEmps = 0;

  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 8, debug, padbytes, header, alignment);
    //OAConfig config(false, 4, 8, true);
    employeeObjectMgr = new ObjectAllocator(sizeof(Employee), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during constructor in TestLeak."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown during constructor in TestLeak."  << endl;
  }

  cout << "Page size = " << employeeObjectMgr->GetStats().PageSize_;
  cout << ", Pad bytes = " << employeeObjectMgr->GetConfig().PadBytes_;
  cout << ", ObjectsPerPage = 4, MaxPages = 8, MaxObjects = 32" << endl;

  PrintCounts(employeeObjectMgr);

  count = employeeObjectMgr->GetConfig().MaxPages_ * employeeObjectMgr->GetConfig().ObjectsPerPage_;
  pEmps = new Employee *[count];

  for (unsigned i = 0; i < count; i++)
  {
    try 
    {
      pEmps[i] = (Employee *) employeeObjectMgr->Allocate();
      FillEmployee(*pEmps[i]);
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
      cout << e.what() << endl;
#else
      cout << "Exception thrown from Allocate in TestLeak."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate in TestLeak."  << endl;
    }
  }
  PrintCounts(employeeObjectMgr); 

  try
  {
    for (unsigned i = 0; i < count; i += 2)
      employeeObjectMgr->Free(pEmps[i]);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free in TestLeak."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in TestLeak."  << endl;
  }

  PrintCounts(employeeObjectMgr);

  cout << "Most employees in use: " << employeeObjectMgr->GetStats().MostObjects_<< endl;

  cout << "\nChecking for leaks...\n";
  CheckAndDumpLeaks(employeeObjectMgr);

  try
  {
    for (unsigned i = 1; i < count; i += 2)
      employeeObjectMgr->Free(pEmps[i]);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from Free (2) in TestLeak."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (2) in TestLeak."  << endl;
  }

  cout << "\nChecking for leaks...\n";
  CheckAndDumpLeaks(employeeObjectMgr);

  delete employeeObjectMgr;
  delete [] pEmps;
}


//****************************************************************************************************
//****************************************************************************************************
void TestValidate(void)
{
  ObjectAllocator *oa = 0;
  unsigned char *p;
  unsigned i, padbytes = 8;
  Student *pStudent1 = 0, *pStudent2 = 0, *pStudent7 = 0;
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    //OAConfig config(false, 4, 2, true, 8);
    oa = new ObjectAllocator(sizeof(Student), config);
    pStudent1 = reinterpret_cast<Student *>( oa->Allocate() );
    pStudent2 = reinterpret_cast<Student *>( oa->Allocate() );
    oa->Allocate(); // 3
    oa->Allocate(); // 4
    oa->Allocate(); // 5
    oa->Allocate(); // 6
    pStudent7 = reinterpret_cast<Student *>( oa->Allocate() );
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction/allocation in TestValidate."  << endl;
#endif
    return;
  }

  try
  {
      // Validate a good heap
    unsigned count = oa->ValidatePages(ValidateCallback);
    cout << "Number of corruptions: " << count << endl << endl;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
    if (e.code() == e.E_CORRUPTED_BLOCK)
      cout << "Exception thrown from Free: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from Free in TestValidate. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in TestValidate."  << endl;
  }

    // corrupt left pad bytes of 1
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent1)) - padbytes;
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xFF;

    // corrupt right pad bytes of 2
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent2)) + sizeof(Student);
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xEE;

  try
  {
      // Validate a corrupted heap
    unsigned count = oa->ValidatePages(ValidateCallback);
    cout << "Number of corruptions: " << count << endl << endl;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
    if (e.code() == e.E_CORRUPTED_BLOCK)
      cout << "Exception thrown from Free: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from Free (2) in TestValidate. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (2) in TestValidate."  << endl;
  }

    // corrupt left pad bytes of 7
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent7)) - padbytes;
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xFF;

    // corrupt right pad bytes of 7
  p = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(pStudent7)) + sizeof(Student);
  for (i = 0; i < padbytes - 2; i++)
    *p++ = 0xEE;

  try
  {
      // Validate a corrupted heap
    unsigned count = oa->ValidatePages(ValidateCallback);
    cout << "Number of corruptions: " << count << endl << endl;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
     cout << e.what() << endl;
#else
    if (e.code() == e.E_CORRUPTED_BLOCK)
      cout << "Exception thrown from Free: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from Free (3) in TestValidate. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free (3) in TestValidate."  << endl;
  }
  if (oa)
    delete oa;
}

//****************************************************************************************************
//****************************************************************************************************
void TestAlignment(void)
{
  if (!ObjectAllocator::ImplementedExtraCredit())
    return;

  ObjectAllocator *oa = 0;
  try 
  {
    unsigned wrap = 32;

    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 2;
    unsigned header = 0;
    unsigned alignment = 8;

    OAConfig config(newdel, 3, 2, debug, padbytes, header, alignment);
    //OAConfig config(false, 3, 2, true, padbytes, header, alignment);
    if (!oa)
      oa = new ObjectAllocator(sizeof(Student), config);
    PrintCounts(oa);
    DumpPages(oa, wrap);

    oa->Allocate(); // 1
    oa->Allocate(); // 2
    oa->Allocate(); // 3
    oa->Allocate(); // 4
    oa->Allocate(); // 5
    oa->Allocate(); // 6
    //oa->Allocate(); // 7

    PrintCounts(oa);
    DumpPages(oa, wrap);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction/allocation in TestAlignment."  << endl;
#endif
    return;
  }
  if (oa)
    delete oa;
}


void PrintCounts(const ObjectAllocator *nm)
{
  OAStats stats = nm->GetStats();
  //cout << "Page size: " << stats.PageSize_;
  cout << "Pages in use: " << stats.PagesInUse_;
  cout << ", Objects in use: " << stats.ObjectsInUse_;
  cout << ", Available objects: " << stats.FreeObjects_;
  cout << ", Allocs: " << stats.Allocations_;
  cout << ", Frees: " << stats.Deallocations_ << endl;
}

void PrintCounts2(const ObjectAllocator *nm)
{
  OAStats stats = nm->GetStats();
  cout << "Allocs: " << stats.Allocations_;
  cout << ", Frees: " << stats.Deallocations_ << endl;
}

void DumpPages(const ObjectAllocator *nm, unsigned width = 16)
{
  const unsigned char *pages = static_cast<const unsigned char *>(nm->GetPageList());
  const unsigned char *realpage = pages;
  
  unsigned header_size = nm->GetConfig().HeaderBlocks_;

  while (pages)
  {
    unsigned count = 0;

#ifdef SHOWREAL
    printf("%p\n", pages);
#else
    printf("00000000\n");
#endif

          // print column header
    for (unsigned j = 0; j < width; j++)
      printf(" %2i", j);
    printf("\n");

#ifdef SHOWREAL
    for (unsigned i = 0; i < sizeof(void *); i++, count++)
      printf(" %02X", *pages++);
#else
    for (unsigned j = 0; j < sizeof(void *); pages++, count++, j++)
      printf(" %02X", 0);
#endif

      // Left leading alignment bytes
    if (nm->GetConfig().Alignment_ > 1)
    {
        // leading alignment block (if any)
      for (unsigned j = 0; j < nm->GetConfig().LeftAlignSize_; count++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
        printf(" %02X", *pages++);
      }
    }

    for (unsigned int i = 0; i < nm->GetConfig().ObjectsPerPage_ ; i++)
    {
        // inter-block alignment (not on first block)
      if (i > 0)
      {
        for (unsigned j = 0; j < nm->GetConfig().InterAlignSize_; count++, j++)
        {
          if (count >= width)
          {
            printf("\n");
            count = 0;
          }
          printf(" %02X", *pages++);
        }
      }

        // header block bytes
      for (unsigned j = 0; j < header_size; count++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
        printf(" %02X", *pages++);
      }

        // left padding
      for (unsigned j = 0; j < nm->GetConfig().PadBytes_; count++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
        printf(" %02X", *pages++);
      }

        // possible next pointer (zero it out)
      for (unsigned j = 0; j < sizeof(void *); count++, pages++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
#ifdef SHOWREAL
        printf(" %02X", *pages);
#else
        printf(" %02X", 0);
#endif
      }
        
        // remaining bytes
      for (unsigned j = 0; j < nm->GetStats().ObjectSize_ - sizeof(void *); count++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
        printf(" %02X", *pages++);
      }

        // right pad bytes
      for (unsigned j = 0; j < nm->GetConfig().PadBytes_; count++, j++)
      {
        if (count >= width)
        {
          printf("\n");
          count = 0;
        }
        printf(" %02X", *pages++);
      }

    }
    printf("\n\n");
    //pages = (const unsigned char *)(((GenericObject *)(realpage))->Next);
    pages = reinterpret_cast<const unsigned char *>((reinterpret_cast<const GenericObject *>(realpage))->Next);
    realpage = pages;
  }
}

int main(void)
{
  try 
  {
    cout << "============================== Students..." << endl;
    DoStudents();
    cout << endl;
    cout << "============================== Employees..." << endl;
    DoEmployees();
    cout << endl;
    cout << "============================== Test padding..." << endl;
    TestPadding();
    cout << endl;
    cout << "============================== Test header blocks(1)..." << endl;
    TestHeaderBlocks(1);
    cout << endl;
    cout << "============================== Test header blocks(2)..." << endl;
    TestHeaderBlocks(2);
    cout << endl;
    cout << "============================== Test header blocks(4)..." << endl;
    TestHeaderBlocks(4);
    cout << endl;
    cout << "============================== Test corruption..." << endl;
    TestCorruption();
    cout << endl;
    cout << "============================== Test using new/delete..." << endl;
    DisableOA();
    cout << endl;
    cout << "============================== Test leak..." << endl;
    TestLeak(); 
    cout << endl;
    cout << "============================== Test validate..." << endl;
    TestValidate();
    cout << endl;
#if 1
    cout << "============================== Test alignment..." << endl;
    TestAlignment();
    cout << endl;
    cout << "============================== Test free empty pages 1..." << endl;
    TestFreeEmptyPages1(); 
    cout << endl;
    cout << "============================== Test free empty pages 2..." << endl;
    TestFreeEmptyPages2(); 
    cout << endl;
    cout << "============================== Test free empty pages 3..." << endl;
    TestFreeEmptyPages3(); 
    cout << endl;
#endif
    cout << "============================== Test free checking (stress)..." << endl;
    StressFreeChecking();
    cout << endl;
    cout << "============================== Test stress using new/delete..." << endl;
    Stress(true);
    cout << endl;
    cout << "============================== Test stress using allocator..." << endl;
    Stress(false);
  }
  catch (...) 
  {
    cout << "********************** Something bad happened ...." << endl;
  }

  //OAConfig config(false, 16, 4, false);
  //ObjectAllocator a(sizeof(Student), config);
  //ObjectAllocator b(sizeof(Student), config);

    // These should fail to compile:
  //ObjectAllocator c(a);
  //a = b;

  return 0;
}

