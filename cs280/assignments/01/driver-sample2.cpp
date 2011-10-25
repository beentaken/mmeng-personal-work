#ifdef _MSC_VER
#pragma warning(disable: 4101)
#endif

#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using std::cout;
using std::endl;

#include "ObjectAllocator.h"
#include "PRNG.h"

#define SHOW_EXCEPTIONSx
#define SHOWADDRESS1x
#define SHOWADDRESS2x
#define SHOWREALx

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
  char firstName[12];  // 12
  char lastName[12];   // 12
  float salary;        //  4
  int years;           //  4
};


ObjectAllocator *studentObjectMgr;
ObjectAllocator *employeeObjectMgr;

void PrintCounts(const ObjectAllocator *nm);
void PrintCounts2(const ObjectAllocator *nm);
void DumpPages(const ObjectAllocator *nm, unsigned width = 16);
void DoStudentsWithPadding(unsigned padding);
void DoStudents(void);
void DoEmployees(void);
void TestDebug(void);
void TestPadding(void);
void DisableOA(void);
void TestCorruption(void);
void TestLeak(void);

struct Person
{
  char lastName[12];   
  char firstName[12];  
  float salary;        
  unsigned years;           
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

void CheckAndDumpLeaks(const ObjectAllocator* oa)
{
  if (oa->GetStats().ObjectsInUse_)
  {
    printf("Detected memory leaks!\n");
    printf("Dumping objects ->\n");
    int leaks = oa->DumpMemoryInUse(DumpCallback);
    printf("Object dump complete. [%i]\n", leaks);
  }
  else
    printf("No leaks detected.\n");
}


int RandomInt(int low, int high)
{
  //return rand() % (high - low + 1) + low;
  return Digipen::Utils::Random(low, high);
}

template <typename T>
void SwapInt(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void Shuffle(T *array, int count)
{
  for (int i = 0; i < count; i++)
  {
    int r = RandomInt(0, count - 1);
    SwapInt(array[i], array[r]);
  }
}

template <typename T>
void PrintArray(T *array, int count)
{
  for (int i = 0; i < count; i++)
    std::cout << array[i] << std::endl;
}

//****************************************************************************************************
//****************************************************************************************************
void TestDebug(void)
{
  cout << "\n============================== Test debug..." << endl;

  ObjectAllocator *oa = 0;
  unsigned total_size = 0;
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 2;
    unsigned header = 4;
    unsigned alignment = 16;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    oa = new ObjectAllocator(sizeof(Student), config);
    total_size = oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction of Student in TestDebug."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in TestDebug: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in TestDebug: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in TestDebug: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in TestDebug: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in TestDebug: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in TestDebug."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from AllocateObject."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in TestDebug: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in TestDebug: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in TestDebug: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in TestDebug: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in TestDebug: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in TestDebug."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from AllocateObject."  << endl;
  }

  DumpPages(oa, total_size);

  delete oa;
}


//****************************************************************************************************
//****************************************************************************************************
void DoStudents(void)
{
  cout << "============================== Students..." << endl;

  DoStudentsWithPadding(0);
}

//****************************************************************************************************
//****************************************************************************************************
void TestPadding(void)
{
  cout << "\n============================== Test padding..." << endl;

  DoStudentsWithPadding(16);
}

//****************************************************************************************************
//****************************************************************************************************
void DoStudentsWithPadding(unsigned padding)
{
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = padding;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    studentObjectMgr = new ObjectAllocator(sizeof(Student), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction for Student."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Student constructor."  << endl;
  }

  cout << "Page size = " << studentObjectMgr->GetStats().PageSize_;
  cout << ", Pad bytes = " << studentObjectMgr->GetConfig().PadBytes_;
  cout << " ObjectsPerPage = 4, MaxPages = 2, MaxObjects = 8" << endl;

  PrintCounts(studentObjectMgr);

  Student *pStudent1 = 0, *pStudent2 = 0, *pStudent3 = 0;
  try
  {
    pStudent1 = (Student *) studentObjectMgr->Allocate();
    PrintCounts(studentObjectMgr);
    pStudent2 = (Student *) studentObjectMgr->Allocate();
    PrintCounts(studentObjectMgr);
    pStudent3 = (Student *) studentObjectMgr->Allocate();
    PrintCounts(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DoStudents: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DoStudents: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DoStudents: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DoStudents: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DoStudents: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DoStudents."  << endl;
    }
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
      pStudent4[i] = (Student *) studentObjectMgr->Allocate();
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DoStudents: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DoStudents: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DoStudents: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DoStudents: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DoStudents: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DoStudents."  << endl;
    }
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate in DoStudents."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoStudents: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoStudents: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoStudents: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoStudents: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoStudents: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoStudents."  << endl;
    }
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
void DoEmployees(void)
{
  cout << "\n============================== Employees..." << endl;

  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 12;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    employeeObjectMgr = new ObjectAllocator(sizeof(Employee), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction for Employee."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Employee constructor."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DoEmployees."  << endl;
    }
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
      pEmployee4[i] = (Employee *) employeeObjectMgr->Allocate();
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
      cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DoEmployees."  << endl;
    }
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate in DoEmployees."  << endl;
    }
  }
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoEmployees."  << endl;
    }
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoEmployees."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoEmployees."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoEmployees."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoEmployees."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoEmployees."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoEmployees."  << endl;
  }

  cout << "Most employees in use: " << employeeObjectMgr->GetStats().MostObjects_ << endl;
  delete employeeObjectMgr;
}

//****************************************************************************************************
//****************************************************************************************************
void DisableOA(void)
{
  cout << "\n============================== Test using new/delete..." << endl;

  try 
  {
    bool newdel = true;
    bool debug = true;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    studentObjectMgr = new ObjectAllocator(sizeof(Student), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction for Student."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Student constructor."  << endl;
  }

  PrintCounts2(studentObjectMgr);

  Student *pStudent1 = 0, *pStudent2 = 0, *pStudent3 = 0;
  try
  {
    pStudent1 = (Student *) studentObjectMgr->Allocate();
    PrintCounts2(studentObjectMgr);
    pStudent2 = (Student *) studentObjectMgr->Allocate();
    PrintCounts2(studentObjectMgr);
    pStudent3 = (Student *) studentObjectMgr->Allocate();
    PrintCounts2(studentObjectMgr);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DisableOA: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DisableOA: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DisableOA: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DisableOA: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DisableOA: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DisableOA."  << endl;
    }
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
      pStudent4[i] = (Student *) studentObjectMgr->Allocate();
    }
    catch (const OAException& e)
    {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Allocate in DisableOA: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Allocate in DisableOA: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Allocate in DisableOA: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Allocate in DisableOA: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Allocate in DisableOA: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Allocate in DisableOA."  << endl;
    }
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from Allocate in DisableOA."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DisableOA: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DisableOA: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DisableOA: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DisableOA: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DisableOA: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DisableOA."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DisableOA."  << endl;
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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DisableOA: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DisableOA: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DisableOA: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DisableOA: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DisableOA: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DisableOA."  << endl;
    }
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
  cout << "\n============================== Test corruption..." << endl;

  ObjectAllocator *oa = 0;
  unsigned char *p;
  unsigned i, padbytes = 8;
  Student *pStudent1, *pStudent2 = 0;
  try 
  {
    bool newdel = false;
    bool debug = true;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
    oa = new ObjectAllocator(sizeof(Student), config);
    pStudent1 = (Student *) oa->Allocate();
    pStudent2 = (Student *) oa->Allocate();
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction/allocation of Student in TestCorruption."  << endl;
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
      cout << "Exception thrown from FreeObject: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from FreeObject. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
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
      cout << "Exception thrown from FreeObject: E_CORRUPTED_BLOCK on right"  << endl;
    else
      cout << "****** Unknown OAException thrown from FreeObject. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
  }

  delete oa;
}

//****************************************************************************************************
//****************************************************************************************************
void TestLeak(void)
{
  cout << "\n============================== Test leak..." << endl;

  int count = 0;
  Employee **pEmps = 0;

  try
  {
      // 2 obj/page, 4 pages, 6 bytes of padding
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 6;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, 2, 4, debug, padbytes, header, alignment);
    employeeObjectMgr = new ObjectAllocator(sizeof(Employee), config);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction for Employee."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Employee constructor."  << endl;
  }

  cout << "Page size = " << employeeObjectMgr->GetStats().PageSize_;
  cout << ", Pad bytes = " << employeeObjectMgr->GetConfig().PadBytes_;
  //cout << ", ObjectsPerPage = 4, MaxPages = 8, MaxObjects = 32" << endl;
  
	cout << ", ObjectsPerPage = " << employeeObjectMgr->GetConfig().ObjectsPerPage_;
	cout << ", MaxPages = " << employeeObjectMgr->GetConfig().MaxPages_;
	cout << ", MaxObjects = " << employeeObjectMgr->GetConfig().MaxPages_ * employeeObjectMgr->GetConfig().ObjectsPerPage_ <<  endl;

  PrintCounts(employeeObjectMgr);

  count = employeeObjectMgr->GetConfig().MaxPages_ * employeeObjectMgr->GetConfig().ObjectsPerPage_;
  pEmps = new Employee *[count];

  for (int i = 0; i < count; i++)
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
      cout << "Exception thrown from AllocateObject."  << endl;
#endif
      break;
    }
    catch(...)
    {
      cout << "Unexpected exception thrown from AllocateObject."  << endl;
    }
  }
  PrintCounts(employeeObjectMgr); 

  try
  {
    for (int i = 0; i < count; i += 2)
      employeeObjectMgr->Free(pEmps[i]);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from FreeObject."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
  }

  PrintCounts(employeeObjectMgr);

  cout << "Most employees in use: " << employeeObjectMgr->GetStats().MostObjects_<< endl;

  cout << "\nChecking for leaks...\n";
  CheckAndDumpLeaks(employeeObjectMgr);

  try
  {
    for (int i = 1; i < count; i += 2)
      employeeObjectMgr->Free(pEmps[i]);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown from FreeObject."  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
  }

  cout << "\nChecking for leaks...\n";
  CheckAndDumpLeaks(employeeObjectMgr);

  delete employeeObjectMgr;
  delete [] pEmps;
}

//****************************************************************************************************
//****************************************************************************************************
void TestStress(void)
{
  cout << "\n============================== Test stress using allocator..." << endl;

  int Objects = 1024;
  int Pages = 4048;

  clock_t start, end;
  ObjectAllocator *oa;
  int total = Objects * Pages;
  void **ptrs = new void *[total];
    
  std::cout << "Stressing: " << Pages << " pages with " << Objects << " objects per page\n";
  try
  {
    bool newdel = false;
    bool debug = false;
    unsigned padbytes = 0;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, Objects, Pages, debug, padbytes, header, alignment);
    oa  = new ObjectAllocator(sizeof(Student), config);
    start = clock();
    for (int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }

    Shuffle(ptrs, total);
    for (int i = 0; i < total; i++)
    {
      oa->Free(ptrs[i]);
    }

    delete oa;
    end = clock();
    bool show_time = false;
    if (show_time)
    {
      printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
      printf("Elapsed time: %lu ms\n", end - start);
    }
    delete [] ptrs;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown in Stress: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown in Stress: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown in Stress: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown in Stress: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown in Stress: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown in Stress."  << endl;
    }
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown in Stress."  << endl;
  }

  return;
}


void PrintCounts(const ObjectAllocator *nm)
{
  OAStats stats = nm->GetStats();
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

void DumpPages(const ObjectAllocator *nm, unsigned width)
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

//****************************************************************************************************
//****************************************************************************************************
void TestEmptyPages(void)
{
  if (!ObjectAllocator::ImplementedExtraCredit())
    return;

  cout << "\n============================== Test FreeEmptyPages..." << endl;


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
    oa  = new ObjectAllocator(sizeof(Student), config);

    unsigned header_size = oa->GetConfig().HeaderBlocks_;
    unsigned width = oa->GetStats().ObjectSize_ + 2 * oa->GetConfig().PadBytes_ + header_size;

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
    //printf("Elapsed time: %3.2f secs\n", ((double)end - start) / 1000);
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown in TestEmptyPages."  << endl;
#endif
    return;
  }
}

//****************************************************************************************************
//****************************************************************************************************
void StressBadBoundary(void)
{
  cout << "\n============================== StressBadBoundary..." << endl;

  int Objects = 100000;
  int Pages = 1;

  clock_t start, end;
  ObjectAllocator *oa;
  int total = Objects * Pages;
  void **ptrs = new void *[total];
    
  std::cout << "Stressing: " << Pages << " pages with " << Objects << " objects per page\n";
  try
  {
    bool newdel = false;
    bool debug = true;
    unsigned padbytes = 2;
    unsigned header = 0;
    unsigned alignment = 0;

    OAConfig config(newdel, Objects, Pages, debug, padbytes, header, alignment);
    oa  = new ObjectAllocator(sizeof(Student), config);
    start = clock();
    for (int i = 0; i < total; i++)
    {
      void *p = oa->Allocate();
      ptrs[i] = p;
    }

    //int count = 0;
    for (int i = 0; i < 100000; i++)
    {
      try
      {
        char *pp = reinterpret_cast<char *>(ptrs[Objects - 1]) + 4;
        oa->Free(pp);
      }
      catch (const OAException&)
      {
        //count++;
        //if (count % 10000 == 0)
        //  printf("Caught exception in StressBadBoundary\n");
      }
    }

    end = clock();
    delete oa;
    bool show_time = false;
    if (show_time)
    {
      printf("Elapsed time: %3.2f secs\n", ((double)end - start) / CLOCKS_PER_SEC);
      printf("Elapsed time: %lu ms\n", end - start);
    }
    delete [] ptrs;
  }
  catch (const OAException& e)
  {
#ifdef SHOW_EXCEPTIONS
    cout << e.what() << endl;
#else
    cout << "Exception thrown during construction for Stress."  << endl;
#endif
    return;
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Stress."  << endl;
  }

/*

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
    switch(e.code())
    {
      case OAException::E_NO_MEMORY : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_MEMORY"  << endl;
        break;
      case OAException::E_NO_PAGES : 
        cout << "Exception thrown from Free in DoEmployees: E_NO_PAGES"  << endl;
        break;
      case OAException::E_BAD_BOUNDARY : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_BOUNDARY"  << endl;
        break;
      case OAException::E_BAD_ADDRESS : 
        cout << "Exception thrown from Free in DoEmployees: E_BAD_ADDRESS"  << endl;
        break;
      case OAException::E_MULTIPLE_FREE : 
        cout << "Exception thrown from Free in DoEmployees: E_MULTIPLE_FREE"  << endl;
        break;
      default:
        cout << "Unknown OAException thrown from Free in DoEmployees."  << endl;
    }
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from Free in DoEmployees."  << endl;
  }

  cout << "Most employees in use: " << employeeObjectMgr->GetStats().MostObjects_ << endl;
  delete employeeObjectMgr;
  */
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
void TestValidatePages(void)
{
  cout << "\n============================== TestValidatePages..." << endl;

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
    cout << "Exception thrown during construction/allocation of Student in TestCorruption."  << endl;
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
      cout << "Exception thrown from FreeObject: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from FreeObject. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
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
      cout << "Exception thrown from FreeObject: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from FreeObject. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
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
      cout << "Exception thrown from FreeObject: E_CORRUPTED_BLOCK on left"  << endl;
    else
      cout << "****** Unknown OAException thrown from FreeObject. ******"  << endl;
#endif
  }
  catch(...)
  {
    cout << "Unexpected exception thrown from FreeObject."  << endl;
  }

  delete oa;
}

//****************************************************************************************************
//****************************************************************************************************
void TestHeaderBlocks(unsigned size)
{
  cout << "\n============================== HeaderBlocks..." << endl;

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

void TestHeaderBlocks1(void)
{
  TestHeaderBlocks(1);
}

void TestHeaderBlocks2(void)
{
  TestHeaderBlocks(2);
}

void TestHeaderBlocks4(void)
{
  TestHeaderBlocks(4);
}

//****************************************************************************************************
//****************************************************************************************************
void TestAlignment(void)
{
  cout << "\n============================== Alignment..." << endl;

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

//****************************************************************************************************
//****************************************************************************************************
int main(void)
{
  DoStudents();
  DoEmployees();
  TestPadding();
  TestHeaderBlocks1();
  TestHeaderBlocks2();
  TestHeaderBlocks4();
  TestDebug();
  TestCorruption();
  DisableOA();
  TestLeak();
  TestEmptyPages();
  TestAlignment();
  TestValidatePages();

  return 0;
}

