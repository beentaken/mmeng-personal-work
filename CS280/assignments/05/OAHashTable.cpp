#include <cmath> /* ceil */
#include <cstring> /* strcmp */

#include "Support.h"
#include "OAHashTable.h"

/*****************************************************************************
 * Public function interface definitions.
 */
OAHashTable::OAHashTable(const OAHashTable::OAHTConfig& Config)
	:myConfig(config), myTable(NULL)
{
	// Puts stats struct in a useful state.
	myStats.Count_ = 0;
	myStats.TableSize_ = myConfig.InitialTableSize_;
	myStats.Probes_ = 0;
	myStats.Expansions_ = 0;
	myStats.PrimaryHashFunc_ = myConfig.PrimaryHashFunc_;
	myStats.SecondaryHashFunc_ = myConfig.SecondaryHashFunc_;

	InitTable();
}

OAHashTable::~OAHashTable()
{
	delete[] myTable;
}

void OAHashTable::insert(const char *key, const T& data)
	throw(OAHashTableException)
{
	if (index != -1)
	{
		throw(OAHashTableException(
				OAHashTableException::E_DUPLICATE,
				"Key already exists in table."));
	}
	else
	{
		// TODO: Insert stuff.
	}
}

void OAHashTable::remove(const char *Key)
	throw(OAHashTableException)
{
	myRemoveAtIndex(IndexOf(Key));
}

const T& OAHashTable::find(const char *Key) const
	throw(OAHashTableException)
{
	int index = IndexOf(Key);

	if (index != -1)
	{
		return(MyTable[index].Data);
	}
	else
	{
		throw(OAHashTableException(
				OAHashTableException::E_ITEM_NOT_FOUND,
				"Could not locate item for retrieval."));
	}
}

void OAHashTable::clear()
{
	for(unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		if (myTable[i].State == OAHTSlot::OCCUPIED)
		{
			myRemoveAtIndex(static_cast<int>(i));
		}
	}
}

OAHTStats OAHashTable::GetStats() const
{
	return(myStats);
}

const OAHashTable::OAHTSlot *OAHashTable::GetTable() const
{
	return(myTable);
}

/*****************************************************************************
 * Private function implementations.
 */

void OAHashTable::InitTable()
{
	try
	{
		myTable = new OAHTSlot[myStats.TableSize_];
	}
	catch(std::bad_alloc)
	{
		throw(OAHashTableException());
	}

	for(unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		myTable[i].State = OAHTSlot::UNOCCUPIED;
	}
}

void OAHashTable::GrowTable() throw(OAHashTableException)
{
	double factor = std::ceil(myStats.TableSize_ * myConfig.GrowthFactor_);
	unsigned old_size = myStats.TableSize_;

	myStats.TableSize_ = GetClosestPrime(static_cast<unsigned>(factor));

	OAHTSlot* temp = myTable;

	InitTable();

	// Insert everything in old table into new table...
	for(unsigned i = 0; i < old_size; ++i)
	{
		// If not empty, stick into table.
	}

	delete[] temp;
}

int OAHashTable::IndexOf(const char *Key, OAHTSlot* &Slot) const
{
	for (unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		if (myTable[i].State == OAHTSlot::OCCUPIED
			&& strcmp(Key, myTable[i].Key) == 0)
		{
			Slot = myTable[i];

			return(static_cast<int>(i));
		}
	}

	return(-1);
}

void OAHashTable::myRemoveAtIndex(int index) throw(OAHashTableException)
{
	if (index != -1)
	{
		if (NULL != myConfig.FreeProc)
		{
			*myConfig.FreeProc(myTable[index].Data);
		}

		myTable[index].State = OAHTSlot::DELETED;
	}
	else
	{
		throw(OAHashTableException(
				OAHashTableException::E_ITEM_NOT_FOUND,
				"Could not locate item for removal."));
	}
}

