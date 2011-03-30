#include <cmath> /* ceil */
#include <cstring> /* strcmp */

#include "Support.h"
#include "OAHashTable.h"

//#define MARCUS_DEBUG

#ifdef MARCUS_DEBUG
#include <iostream>
#endif

/*****************************************************************************
 * Public function interface definitions.
 */
template<typename T>
OAHashTable<T>::OAHashTable(const OAHashTable<T>::OAHTConfig& Config)
	:myConfig(Config), myTable(NULL)
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

template<typename T>
OAHashTable<T>::~OAHashTable()
{
	clear();
	delete[] myTable;
}

template<typename T>
void OAHashTable<T>::insert(const char *key, const T& data)
	throw(OAHashTableException)
{
	unsigned hash = myPrimaryHash(key);

	unsigned stride = 1;

	if (myConfig.SecondaryHashFunc_ != NULL)
	{
		stride = mySecondaryHash(key);
	}

	// Jump by stride size until we find an open spot.
	for (unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		++myStats.Probes_;
#ifdef MARCUS_DEBUG
		std::cerr << "Attempting to insert key " << key
			<< ", probe count is " << myStats.Probes_ << std::endl;
#endif
		if (static_cast<double>(myStats.Count_ + 1) / myStats.TableSize_
					>= myConfig.MaxLoadFactor_)
		{
#ifdef MARCUS_DEBUG
			std::cerr << "Growth factor too large, growing table..." << std::endl;
#endif
			GrowTable();

			hash = myPrimaryHash(key);
		}

		if (myTable[myIndex(hash, stride, i)].State !=
				OAHashTable::OAHTSlot::OCCUPIED)
		{
			myTable[myIndex(hash, stride, i)].State =
				OAHTSlot::OCCUPIED;
			/* Sometimes, if we're re-inserting during a remove
			 * operation, things end up in the same place.
			 *
			 * Let's short-circuit that.
			 */
			if (myTable[myIndex(hash, stride, i)].Key != key)
			{
#ifdef MARCUS_DEBUG
				std::cerr << "Unidentical node, copying..." << std::endl;
#endif
				myTable[myIndex(hash, stride, i)].Data = data;
				strcpy(myTable[myIndex(hash, stride, i)].Key, key);
			}
			++myStats.Count_;
			
			// Get out, we're done.
			return;
		}
		else
		{
			// Whoops, already in here.
			if (strcmp(key, myTable[myIndex(hash, stride, i)].Key) == 0)
			{
				throw(OAHashTableException(
					OAHashTableException::E_DUPLICATE,
					"Key already exists in table."));

			}
		}

#ifdef MARCUS_DEBUG
		std::cerr << "Collision, striding forward for justice..." << std::endl;
#endif
	}
}

template<typename T>
void OAHashTable<T>::remove(const char *Key)
	throw(OAHashTableException)
{
#ifdef MARCUS_DEBUG
	std::cerr << "Attempting to remove key " << Key << std::endl;
#endif
	OAHTSlot *temp;
	int index = IndexOf(Key, temp);
	
	if (index != -1)
	{
		myRemove(*temp);

		if (myConfig.DeletionPolicy_ == PACK)
		{
			// Re-insert everything after the removed item.
			for (int i = 0;
				myTable[myIndex(index + 1, 1, i)].State == OAHTSlot::OCCUPIED;
				++i)
			{
				myTable[myIndex(index + 1, 1, i)].State = OAHTSlot::UNOCCUPIED;
				--myStats.Count_;
				insert(myTable[myIndex(index + 1, 1, i)].Key,
						myTable[myIndex(index + 1, 1, i)].Data);
			}
		}
	}
	else
	{
		throw(OAHashTableException(
				OAHashTableException::E_ITEM_NOT_FOUND,
				"Key not in table."));
	}
}

template<typename T>
const T& OAHashTable<T>::find(const char *Key) const
	throw(OAHashTableException)
{
	OAHTSlot *temp;
	int index = IndexOf(Key, temp);

	if (index != -1)
	{
		return(temp->Data);
	}
	else
	{
		throw(OAHashTableException(
				OAHashTableException::E_ITEM_NOT_FOUND,
				"Item not found in table."));
	}
}

template<typename T>
void OAHashTable<T>::clear()
{
#ifdef MARCUS_DEBUG
	std::cerr << "(!!): Table cleared." << std::endl;
#endif
	for(unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		if (myTable[i].State == OAHTSlot::OCCUPIED)
		{
			myRemove(myTable[i]);
		}
		myTable[i].State = OAHTSlot::UNOCCUPIED;
	}
}

template<typename T>
OAHTStats OAHashTable<T>::GetStats() const
{
	return(myStats);
}

template<typename T>
const typename OAHashTable<T>::OAHTSlot *OAHashTable<T>::GetTable() const
{
	return(myTable);
}

/*****************************************************************************
 * Private function implementations.
 */

template<typename T>
void OAHashTable<T>::InitTable()
{
	try
	{
		myTable = new OAHTSlot[myStats.TableSize_];
	}
	catch(std::bad_alloc)
	{
		throw(OAHashTableException(
				OAHashTableException::E_NO_MEMORY,
				"Not enough memory to allocate table."));
	}

	for(unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		myTable[i].State = OAHTSlot::UNOCCUPIED;
	}

	myStats.Count_ = 0;
}

template<typename T>
void OAHashTable<T>::GrowTable() throw(OAHashTableException)
{
	double factor = std::ceil(myStats.TableSize_ * myConfig.GrowthFactor_);
	unsigned old_size = myStats.TableSize_;

	myStats.TableSize_ = GetClosestPrime(static_cast<unsigned>(factor));

	OAHTSlot* temp = myTable;

	InitTable();

	// Insert everything in old table into new table...
	for(unsigned i = 0; i < old_size; ++i)
	{
		if (temp[i].State == OAHTSlot::OCCUPIED)
		{
			insert(temp[i].Key, temp[i].Data);
		}
	}

	delete[] temp;

	++myStats.Expansions_;
}

template<typename T>
int OAHashTable<T>::IndexOf(const char *Key, OAHTSlot* &Slot) const
{
	unsigned hash = myPrimaryHash(Key);
	unsigned stride = 1;

	if (myStats.SecondaryHashFunc_ != NULL)
	{
		stride = mySecondaryHash(Key);
	}

	for (unsigned i = 0; i < myStats.TableSize_; ++i)
	{
		++myStats.Probes_;
		if (myTable[myIndex(hash, stride, i)].State == OAHTSlot::OCCUPIED
			&& strcmp(Key, myTable[myIndex(hash, stride, i)].Key) == 0)
		{
			Slot = &myTable[myIndex(hash, stride, i)];

			return(static_cast<int>(myIndex(hash, stride, i)));
		}

		// What if we hit an unoccupied spot?
		if (myTable[myIndex(hash, stride, i)].State == OAHTSlot::UNOCCUPIED)
		{
			break;
		}
#ifdef MARCUS_DEBUG
		std::cerr << "Did not find key " << Key << std::endl;
#endif
	}

	return(-1);
}

template<typename T>
void OAHashTable<T>::myRemove(OAHTSlot &to_remove) throw(OAHashTableException)
{
	if (NULL != myConfig.FreeProc_)
	{
		(*myConfig.FreeProc_)(to_remove.Data);
	}

	to_remove.State = (myConfig.DeletionPolicy_ == MARK) ? OAHTSlot::DELETED : OAHTSlot::UNOCCUPIED;

	--myStats.Count_;
}

template<typename T>
inline
int OAHashTable<T>::myIndex(const unsigned &hash, const unsigned &stride, const unsigned& index) const
{
	return((hash + index * stride) % myStats.TableSize_);
}

template<typename T>
inline
unsigned OAHashTable<T>::myPrimaryHash(const char* key) const
{
	return((*myStats.PrimaryHashFunc_)(key, myStats.TableSize_));
}

template<typename T>
inline
unsigned OAHashTable<T>::mySecondaryHash(const char* key) const
{
	return((*myStats.SecondaryHashFunc_)(key, myStats.TableSize_ - 1) + 1);
}

