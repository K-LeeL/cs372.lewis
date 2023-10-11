#pragma once
template< typename T >
class Tree
{
private:
     struct Node
     {
          T value;
          std::shared_ptr< Node > left;
          std::shared_ptr< Node > right;

          Node ( T v , std::shared_ptr< Node > l , std::shared_ptr< Node > r ) : value ( v ) , left ( l ) , right ( r )
          {
          }
     };

     explicit Tree ( std::shared_ptr< Node > &node ) : Root ( node )
     {
     }

     std::shared_ptr< Node > Root;

     bool deleteRec ( std::shared_ptr<Node> &node , const T &x )
     {
          if ( !node ) return false;

          if ( x < node->value )
          {
               return deleteRec ( node->left , x );
          } else if ( x > node->value )
          {
               return deleteRec ( node->right , x );
          } else
          {
               if ( !node->left )
               {
                    node = node->right;
               } else if ( !node->right )
               {
                    node = node->left;
               } else
               {
                    node->value = findAndRemoveMax ( node->left );
               }
               return true;
          }
     }

     T findAndRemoveMax ( std::shared_ptr<Node> &node )
     {
          if ( !node->right )
          {
               T maxValue = node->value;
               node = node->left;
               return maxValue;
          }
          return findAndRemoveMax ( node->right );
     }

public:
     Tree ( ) : Root ( )
     {
     }

     Tree ( Tree const &lft , T value , Tree const &rgt ) : Root ( std::make_shared< Node > ( value , lft.Root , rgt.Root ) )
     {
     }

     bool isEmpty ( ) const
     {
          return !Root;
     }

     T root ( ) const
     {
          if ( isEmpty ( ) )
          {
               throw std::out_of_range ( "Tree is empty" );
          }
          return Root->value;
     }

     Tree left ( ) const
     {
          if ( isEmpty ( ) )
          {
               return Tree ( );
          }
          return Tree ( Root->left );
     }

     Tree right ( ) const
     {
          if ( isEmpty ( ) )
          {
               return Tree ( );
          }
          return Tree ( Root->right );
     }

     bool member ( T x ) const
     {
          if ( isEmpty ( ) )
               return false;
          T y = root ( );
          if ( x < y )
               return left ( ).member ( x );
          else if ( y < x )
               return right ( ).member ( x );
          else
               return true;
     }

     bool isLeaf ( ) const
     {
          if ( isEmpty ( ) )
          {
               return false;
          }
          return !Root->left && !Root->right;
     }

     Tree insert ( T x ) const
     {
          if ( isEmpty ( ) )
               return Tree ( Tree ( ) , x , Tree ( ) );
          T y = root ( );
          if ( x < y )
               return Tree ( left ( ).insert ( x ) , y , right ( ) );
          else if ( y < x )
               return Tree ( left ( ) , y , right ( ).insert ( x ) );
          else
               return *this;  // no duplicates
     }

     bool deleteNode ( const T &x )
     {
          return deleteRec ( Root , x );
     }

};

void printElement ( const std::string &msg , bool value )
{
     std::cout << msg << ( value ? "true" : "false" ) << std::endl;
}

template <typename T>
class Vector
{
private:
     T *vArray = new T [ 1 ];
     int vCapacity = 1;
     int length = 0;

     // Method to expand the size of the vector
     void expand ( int newCapacity )
     {
          if ( newCapacity > vCapacity )
          {
               T *temp = new T [ newCapacity ];

               for ( int i = 0; i < length; i++ )
               {
// Copy existing elements to the new array
                    temp [ i ] = vArray [ i ];
               }

               delete [ ] vArray;
               vCapacity = newCapacity;
               vArray = temp;

          } else
          {
               std::cerr
                    << "vector::expand: new capacity is less than equal to current\n";
          }
     }

public:
 // Constructor
     Vector ( )
     {
          vArray = new T [ 1 ];
          vCapacity = 1;
          length = 0;
     }

     // Destructor
     ~Vector ( )
     {
          delete [ ] vArray;
          vArray = nullptr;
     }

     // Only special case where the index is equal to the capacity
     void put ( T data , int index )
     {
          if ( index == vCapacity )
          {
// If index is at the end, use push_back
               push_back ( data );

          } else
          {
    // Update the element at the specified index
               vArray [ index ] = data;
          }
     }

     // Method to add new data to the end of the vector
     void push_back ( T data )
     {
// if number of elements is equal to capacity
// than we need to reallocate and deep copy
          if ( length == vCapacity )
          {
// Double the capacity if needed
               expand ( 2 * vCapacity );
          }

          vArray [ length ] = data;
          length++;
     }

     // Access an element at a specific index
     T &at ( int index )
     {
          if ( index < 0 || index >= length )
          {
               std::cerr << "Vector: index out of bounds on access" << std::endl;
               exit ( 1 );
          } else
          {
               return vArray [ index ];
          }
     }

     // Get the current number of elements in the vector
     int size ( )
     {
          return length;
     }

// Get the current capacity of the vector
     int capacity ( )
     {
          return vCapacity;
     }

// Print all elements in the vector
     void traverse ( )
     {
          for ( int i = 0; i < length; i++ )
          {
               std::cout << vArray [ i ] << " ";
          }

          std::cout << std::endl;
     }

     // Compare two vectors for equality
     bool operator==( Vector &other ) const
     {
          if ( other.size ( ) != length )
          {
               return false;
          } else
          {
               for ( int i = 0; i < length; i++ )
               {
                    if ( vArray [ i ] != other.at ( i ) )
                    {
                         return false;
                    }
               }
          }
          return true;
     };

     // Indexing operator to access elements by index
     T &operator[]( int i )
     {
          if ( ( i < 0 ) || ( i >= length ) )
          {
               std::cerr << std::endl << "Vector index out of bounds" << std::endl;
               exit ( 1 );
          }

          return vArray [ i ];
     }

     // Copy constructor to work in concert with new operator
     Vector ( const Vector &obj )
     {
// Reset self
          this->vArray = new T [ obj.capacity ( ) ];

          for ( int i = 0; i < obj.size ( ); i++ )
          {
               vArray [ i ] = obj.at ( i );
          }
     }

     // Copy assignment operator
     Vector &operator=( const Vector &source )
     {
// Do a self check.
          if ( this == &source )
          {
               return *this;
          }

          // Clean up
          delete [ ] vArray;
          vArray = new T [ 1 ];
          vCapacity = 1;
          length = 1;

          for ( int i = 0; i < source.size ( ); i++ )
          {
               push_back ( source.at ( i ) );
          }

          return *this;
     }

     // Method to return an iterator to the beginning of the vector
     T *begin ( )
     {
          return vArray;
     }

// Method to return an iterator to the end of the vector
     T *end ( )
     {
          return vArray + length;
     }
};

// Template parameter 'T', size_t parameter specifies size of array
template <typename T , size_t Size>

class Array
{
private:
     T cArray [ Size ];
     size_t length = 0;

public:
 // Constructor
     Array ( ) : length ( 0 )
     {
     }

     // Destructor
     ~Array ( )
     {
     }

     // Method to add new data to the array
     void push_back ( T data )
     {
          if ( length < Size )
          {
               cArray [ length ] = data;
               length++;
          } else
          {
               std::cerr << "Array can not be added to. " << std::endl;
          }
     }

     // Access an element at a specific index
     T &at ( size_t index )
     {
          if ( index >= length )
          {
               std::cerr << "Array: index out of bounds on access" << std::endl;
               exit ( 1 );
          } else
          {
               return cArray [ index ];
          }
     }

     // Get the number of elements currently in the array
     size_t size ( ) const
     {
          return length;
     }

// Get the maximum capacity of the array
     size_t capacity ( ) const
     {
          return Size;
     }

// Indexing operator to access elements by index
     T &operator[]( size_t index )
     {
          if ( index >= length )
          {
               std::cerr << "Array index out of bounds" << std::endl;
               exit ( 1 );
          }

          return cArray [ index ];
     }

     // Print all elements in the array
     void traverse ( )
     {
          for ( size_t i = 0; i < length; ++i )
          {
               std::cout << cArray [ i ] << " ";
          }

          std::cout << std::endl;
     }

     // Copy Constructor
     Array ( const Array &other ) : length ( other.length )
     {
          for ( size_t i = 0; i < length; ++i )
          {
               cArray [ i ] = other.cArray [ i ];
          }
     }

     // Copy Assignment Operator
     Array &operator=( const Array &other )
     {
          if ( this != &other )
          {
               length = other.length;
               for ( size_t i = 0; i < length; ++i )
               {
                    cArray [ i ] = other.cArray [ i ];
               }
          }
          return *this;
     }

     // Method to return an iterator to the beginning of the array
     T *begin ( )
     {
          return cArray;
     }

// Method to return an iterator to the end of the array
     T *end ( )
     {
          return cArray + length;
     }
};

template <typename T>
class SeqContainer
{
protected:
     class Node
     {
     public:
          T data;
          Node *prev;
          Node *next;
          bool isHiddenNode = false;
          Node ( ) = default;
          Node ( T d , Node *p , Node *n ) : data ( d ) , prev ( p ) , next ( n )
          {
          };
     };
     Node *head;
     Node *tail;

     void setupList ( )
     {
          Node *newNode = new Node ( );
          newNode->next = tail;
          newNode->prev = head;
          head->next = newNode;
          tail->prev = newNode;
     }
     void deleteListContents ( )
     {
          Node *current = head->next;
          Node *temp = nullptr;
          while ( current != tail->prev )
          {
               temp = current->next;
               delete current;
               current = temp;
          }
     }

public:
     class const_iterator
     {
     protected:
          Node *current;
          T &retrieve ( ) const
          {
               return current->data;
          }
          const_iterator ( Node *p ) : current ( p )
          {
          }
          friend class SeqContainer<T>;

     public:
          const_iterator ( ) : current ( nullptr )
          {
          }

          T &operator*( ) const
          {
               return retrieve ( );
          }

          const_iterator &operator++( )
          {
               current = current->next;
               return *this;
          }

          const_iterator operator++( int )
          {
               const_iterator old = *this;
               ++( *this );
               return old;
          }

          bool operator==( const const_iterator &rhs ) const
          {
               return current == rhs.current;
          }
          bool operator!=( const const_iterator &rhs ) const
          {
               return !( *this == rhs );
          }
     };

public:
     class iterator : public const_iterator
     {
     protected:
          iterator ( Node *p ) : const_iterator ( p )
          {
          }
          friend class SeqContainer<T>;

     public:
          iterator ( )
          {
          }

          T &operator*( )
          {
               return const_iterator::retrieve ( );
          }

          const T &operator*( ) const
          {
               return const_iterator::operator*( );
          }

          iterator &operator++( )
          {
               this->current = const_iterator::current->next;
               return *this;
          }

          iterator operator++( int )
          {
               iterator old = *this;
               ++( *this );
               return old;
          }
     };

     SeqContainer ( )
     {
          head = new Node ( );
          head->isHiddenNode = true;
          tail = new Node ( );
          tail->isHiddenNode = true;
          head->prev = nullptr;
          head->next = tail;
          tail->prev = head;
          tail->next = nullptr;
     }

     SeqContainer ( T newData )
     {
          setupList ( );
          ( head->next )->data = newData;
     }

     SeqContainer ( SeqContainer &rhs )
     {
// copy constructor
          deleteListContents ( );
          head = rhs.head;
          tail = rhs.tail;
     }

     virtual ~SeqContainer ( )
     {
// And a destructor
          deleteListContents ( );
          delete head;
          delete tail;
     }
     // iterator related methods
     virtual iterator begin ( )
     {
          return { head->next };
     }

     virtual iterator end ( )
     {
          return tail;
     }

     virtual const_iterator cbegin ( ) const
     {
          return { head->next };
     }

     virtual const_iterator cend ( ) const
     {
          return { tail };
     }

     virtual iterator insert ( iterator itr , const T &x )
     {
          Node *p = itr.current;
          Node *newNode = new Node { x, p->prev, p };
          p->prev = p->prev->next = newNode;
          return itr;
     }

     virtual iterator erase ( iterator itr )
     {
          Node *p = itr.current;
          iterator iterToReturn { p->next };
          p->prev->next = p->next;
          p->next->prev = p->prev;
          return iterToReturn;
     }

     virtual iterator erase ( iterator from , iterator to )
     {
          iterator itr = from;
          while ( itr != to )
          {
               itr = erase ( itr );
          }
          return to;
     }
};