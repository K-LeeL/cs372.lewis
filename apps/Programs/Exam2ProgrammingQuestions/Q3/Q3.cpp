// Exam 2 Programming Questions
// Question 3 :
//In our discussion of hashing, we addressed hash collisions in two ways:
//   (1) linear probing, that looked ahead in the hash table for the next open entry,
//   and (2) double hashing.
//   A third method for doing this is quadratic probing, which will look for an open slot in the hash
//   table by looking ahead by first looking at the next entry, following by 2^2=4 slots ahead,
//   then 3^2=9 slots ahead, then 4^2=16 slots ahead in the hash table.
//   This continues until you find an empty slot in the table or you loop your way back to the point in the hash table where you started.
//   Note that the size of the hash table must be some power of 2 for this work correctly (for example, 256, 1024, 2048, 4096, and so on).
// Modify the following implementation of a HashTable to use quadratic probing rather than linear probing.
// For the hash function , use clock arithmetic ( index mod size ).
// If you have a collision , call a function named quadProbe ( int &index ) that will use quadratic probing to find the next open slot.

#include <cassert>
#include <iostream>
#include <memory>

struct RecordType
{
     int key;
     std::string data;
};

template <class RecordType>
class Table
{
public:
     static const std::size_t CAPACITY = 811;
     Table ( )
     {
          used = 0;
          for ( std::size_t i = 0; i < CAPACITY; ++i )
          {
               data [ i ].key = NEVERUSED;
          }
     }
     void insert ( const RecordType &entry )
     {
          bool alreadyPresent;
          std::size_t index;
          assert ( entry.key >= 0 );
          findIndex ( entry.key , alreadyPresent , index );
          if ( !alreadyPresent )
          {
               assert ( size ( ) < CAPACITY );
               index = hash ( entry.key );
               while ( !isVacant ( index ) )
               {
                    index = quadProbe ( index ); 
               }
               ++used;
          }
          data [ index ] = entry;
     }
     void remove ( int key )
     {
          bool found;
          std::size_t index;
          assert ( key >= 0 );
          findIndex ( key , found , index );
          if ( found )
          {
               data [ index ].key = PREVIOUSLYUSED;
               --used;
          }
     }
     bool isPresent ( int key ) const;
     void find ( int key , bool &found , RecordType &result ) const
     {
          std::size_t index;
          found = false;
          for ( index = 0; index < CAPACITY; ++index )
          {
               if ( data [ index ].key == key )
               {
                    found = true;
                    result = data [ index ];
                    break;
               }
          }
     }
     std::size_t size ( ) const
     {
          return used;
     }
private:
     static const int NEVERUSED = -1;
     static const int PREVIOUSLYUSED = -2;
     RecordType data [ CAPACITY ];
     std::size_t used;
     std::size_t hash ( int key ) const
     {
          return key % CAPACITY;  
     }

     std::size_t quadProbe ( std::size_t index ) const
     {
          std::size_t offset = 1;
          std::size_t originalIndex = index;
          std::size_t loopCount = 0;

          while ( !isVacant ( index ) && loopCount < CAPACITY )
          {
               index = ( originalIndex + offset * offset ) % CAPACITY;
               offset++;
               loopCount++;
          }

          return loopCount < CAPACITY ? index : originalIndex;
     }

     void findIndex ( int key , bool &found , std::size_t &index ) const
     {
          std::size_t count = 0;
          index = hash ( key );
          while ( ( count < CAPACITY ) && ( data [ index ].key != NEVERUSED ) && ( data [ index ].key != key ) )
          {
               count++;
               index = quadProbe ( index );
          }
          found = ( count < CAPACITY ) && ( data [ index ].key == key );
     }

     bool neverUsed ( std::size_t index ) const
     {
          return data [ index ].key == NEVERUSED;
     }

     bool isVacant ( std::size_t index ) const
     {
          return data [ index ].key == NEVERUSED || data [ index ].key == PREVIOUSLYUSED;
     }
};

int main ( )
{
     Table<RecordType> myHashTable;

     RecordType record1 = { 1, "Data 1" };
     RecordType record2 = { 2, "Data 2" };
     RecordType record3 = { 3, "Data 3" };

     myHashTable.insert ( record1 );
     myHashTable.insert ( record2 );
     myHashTable.insert ( record3 );

     bool found;
     RecordType result;
     myHashTable.find ( 1 , found , result );
     if ( found )
     {
          std::cout << "Record found: " << result.data << std::endl;
     } else
     {
          std::cout << "Record not found." << std::endl;
     }

     myHashTable.remove ( 2 );

     myHashTable.find ( 2 , found , result );
     if ( !found )
     {
          std::cout << "Record successfully removed." << std::endl;
     }

     return 0;
}