/******************************************************************************/
/*!
\file   OAHashTable.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #5
\date   2010-03-31
\brief
  This is the implementation for a simple hash table supporting arbitrary
  hash functions and linear probing or double hashing collision resolution
  methods.

Hours Spent: 4

  Getting things to come out exactly like the output is surprisingly tricky.
*/
/******************************************************************************/
#include <cmath> /* ceil */
#include <cstring> /* strcmp, strcpy */

#include "Support.h"
#include "OAHashTable.h"

//#define MARCUS_DEBUG

#ifdef MARCUS_DEBUG
#include <iostream>
#endif

/*****************************************************************************
 * Public function interface definitions.
 */

/*!\brief A constructor.
 *
 * \param Config
 * 	A configuration struct to pass into the hash table. This struct will
 * 	control various aspects of how the hash table works, such as whether
 * 	to use double hashes or linear probing to resolve collisions, and
 * 	whether data in the table needs to be finalized on removal.
 */
template<typename T>
OAHashTable<T>::OAHashTable(const OAHTConfig& Config)
	:myConfig(Config), myTable(NULL), myStats()
{
	// Puts stats struct in a useful state.
	myStats.TableSize_ = myConfig.InitialTableSize_;
	myStats.PrimaryHashFunc_ = myConfig.PrimaryHashFunc_;
	myStats.SecondaryHashFunc_ = myConfig.SecondaryHashFunc_;

	InitTable();
}

/*!\brief Destructor.
 *
 * Ensures that data is freed appropriately and the hash table itself is
 * properly deallocated.
 */
template<typename T>
OAHashTable<T>::~OAHashTable()
{
	clear();
	delete[] myTable;
}

/*!\brief Inserts the given data in to the table with the given key.
 *
 * Will return an exception if the key already exists in the table.
 *
 * \param key
 * 	The key to use to set and retrieve the data.
 *
 * \param data
 * 	The data to store at the location the key provides.
 */
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
					> myConfig.MaxLoadFactor_)
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

/*!\brief Removes data with the given key from the hash table.
 *
 * Will return an exception if the key does not actually exist.
 *
 * It may rearrange parts of the table if the table is told to repack on
 * removal of data.
 *
 * \param Key
 * 	They key referring to the data to be removed.
 */
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

/*!\brief Locates data with the given key and provides it to the user.
 *
 * Returns an exception if the key does not actually exist in the table.
 *
 * \param Key
 * 	The key to search for.
 *
 * \return A constant reference to the data pointed to by the key.
 */
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

/*!\brief Clears all data in the table.
 *
 * Works in O(n) time.
 *
 * Will call finalizers on data before removal.
 *
 * All slots in the table should be set to UNOCCUPIED when finished.
 */
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

/*!\brief Obtains various runtime statistics about the hash table.
 */
template<typename T>
OAHTStats OAHashTable<T>::GetStats() const
{
	return(myStats);
}

/*!\brief Debug function. Returns a pointer to the hash table itself.
 *
 * Do not call outside of debug systems.
 *
 * \return A pointer to the hash table.
 */
template<typename T>
const typename OAHashTable<T>::OAHTSlot *OAHashTable<T>::GetTable() const
{
	return(myTable);
}

/*****************************************************************************
 * Private function implementations.
 */

/*!\brief Allocates and initializes a table to a sane state.
 *
 * Will reset the Count statistic back to 0.
 *
 * Does NOT check to see whether myTable is already initialized.
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

/*!\brief Grows the table based on the provided growth factor.
 */
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

/*!\brief Locates the index of a given key using an appropriate probe method.
 *
 * \param Key
 * 	The key to look for.
 *
 * \param Slot
 * 	Set to the slot that holds the key being looked for.
 *
 * \return The index of the key, or -1 if the key was not found.
 */
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

/*!\brief Helper fucntion to remove data from a slot.
 *
 * Calls appropriate finalizers on the data before setting the state to
 * a value appropriate for the current deletion policy.
 *
 * \param to_remove
 * 	The slot to clear out.
 */
template<typename T>
void OAHashTable<T>::myRemove(OAHTSlot &to_remove) throw(OAHashTableException)
{
	if (NULL != myConfig.FreeProc_)
	{
		(*myConfig.FreeProc_)(to_remove.Data);
	}

	to_remove.State = myConfig.DeletionPolicy_ == MARK ? OAHTSlot::DELETED: OAHTSlot::UNOCCUPIED;

	--myStats.Count_;
}

/*!\brief Helper function to help calculate an appropriate index.
 *
 * Takes into account the current hash value, the current stride, and the
 * table size.
 *
 * \param hash
 * 	The hash of the key in question.
 *
 * \param stride
 * 	The current stride value.
 *
 * \param index
 * 	The number of jumps past the first occurance of the hash.
 *
 * \return The index in myTable of the calculated item.
 */
template<typename T>
inline
int OAHashTable<T>::myIndex(const unsigned &hash, const unsigned &stride, const unsigned& index) const
{
	return((hash + index * stride) % myStats.TableSize_);
}

/*!\brief Helper function to call a primary hash on a key.
 *
 * \param key
 * 	The key to hash.
 *
 * \return The hashed value of the key.
 */
template<typename T>
inline
unsigned OAHashTable<T>::myPrimaryHash(const char* key) const
{
	return((*myStats.PrimaryHashFunc_)(key, myStats.TableSize_));
}

/*!\brief Helper function to call a secondary hash on a key.
 *
 * Ensures that the secondary hash falls within a valid range.
 *
 * \param key
 * 	The key to hash.
 *
 * \return The hashed value of the key.
 */
template<typename T>
inline
unsigned OAHashTable<T>::mySecondaryHash(const char* key) const
{
	return((*myStats.SecondaryHashFunc_)(key, myStats.TableSize_ - 1) + 1);
}

