#pragma once

template <typename T>
class List
{
public:
     struct Node
     {
     public:
          T data;
          Node *next;
          Node *prev;
          bool isHiddenNode = false;
     };

     Node *head;
     Node *tail;
     int length;

private:
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
          while ( current != tail )
          {
               Node *temp = current;
               current = current->next;
               delete temp;
          }
          head->next = tail;
          tail->prev = head;
     }

public:
     List ( )
     {
          head = new Node ( );
          head->isHiddenNode = true;
          tail = new Node ( );
          tail->isHiddenNode = true;
          head->prev = nullptr;
          head->next = tail;
          tail->prev = head;
          tail->next = nullptr;
          length = 0;
     }

     List ( T newData )
     {
          setupList ( );
          ( head->next )->data = newData;
     }

     List ( const List &rhs )
     {
          head = new Node ( );
          tail = new Node ( );
          setupList ( );
          Node *current = rhs.head->next;
          while ( current != rhs.tail )
          {
               push_back ( current->data );
               current = current->next;
          }
     }

     ~List ( )
     {
          deleteListContents ( );
          delete head;
          delete tail;
          head = nullptr;
          tail = nullptr;
     }

     List &operator=( const List<T> &other )
     {
          if ( this == &other )
          {
               return *this;
          }
          clear ( );
          Node *current = other.head->next;
          while ( current != other.tail )
          {
               push_back ( current->data );
               current = current->next;
          }
          return *this;
     }

     bool empty ( ) const
     {
          return ( head->next == tail );
     }

     void push_front ( T data )
     {
          if ( this->empty ( ) )
          {
               setupList ( );
               Node *actualHead = head->next;
               actualHead->data = data;
          } else
          {
               Node *actualHead = head->next;
               Node *newNode = new Node ( );
               newNode->data = data;
               newNode->next = actualHead;
               actualHead->prev = newNode;
               newNode->prev = head;
               head->next = newNode;
          }
     }

     void push_back ( T data )
     {
          if ( this->empty ( ) )
          {
               setupList ( );
               Node *actualTail = tail->prev;
               actualTail->data = data;
          } else
          {
               Node *actualTail = tail->prev;
               Node *newNode = new Node ( );
               newNode->data = data;
               newNode->prev = actualTail;
               actualTail->next = newNode;
               newNode->next = tail;
               tail->prev = newNode;
          }
     }

     T front ( )
     {
          Node *actualHead = head->next;
          return ( actualHead->data );
     }

     T back ( )
     {
          Node *actualTail = tail->prev;
          return ( actualTail->data );
     }

     void pop_back ( )
     {
          if ( !empty ( ) )
          {
               Node *lastNode = tail->prev;
               tail->prev = lastNode->prev;
               Node *newLastNode = tail->prev;
               newLastNode->next = tail;
               delete lastNode;
               lastNode = nullptr;
               length--;
          } else
          {
               std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
          }
     }

     void pop_front ( )
     {
          if ( !empty ( ) )
          {
               Node *firstNode = head->next;
               head->next = firstNode->next;
               Node *newFirstNode = head->next;
               newFirstNode->prev = head;
               delete firstNode;
               firstNode = nullptr;
               length--;
          } else
          {
               std::cerr << "pop_front(): Attempt to pop from empty list. " << std::endl;
          }
     }

     void traverse ( void ( *doIt )( T &data ) )
     {
          Node *current = head;
          while ( current != nullptr )
          {
               doIt ( current->data );
               current = current->next;
          }
     }

     void clear ( )
     {
          while ( !empty ( ) )
          {
               pop_front ( );
          }
     }

     int size ( ) const
     {
          return length;
     }
};

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
               return *this;
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

     void expand ( int newCapacity )
     {
          if ( newCapacity > vCapacity )
          {
               T *temp = new T [ newCapacity ];

               for ( int i = 0; i < length; i++ )
               {
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
     Vector ( )
     {
          vArray = new T [ 1 ];
          vCapacity = 1;
          length = 0;
     }

     ~Vector ( )
     {
          delete [ ] vArray;
          vArray = nullptr;
     }

     void put ( T data , int index )
     {
          if ( index == vCapacity )
          {
               push_back ( data );

          } else
          {
               vArray [ index ] = data;
          }
     }

     void push_back ( T data )
     {
          if ( length == vCapacity )
          {
               expand ( 2 * vCapacity );
          }

          vArray [ length ] = data;
          length++;
     }

     T &at ( int index ) const
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

     int size ( ) const
     {
          return length;
     }

     int capacity ( ) const
     {
          return vCapacity;
     }

     void traverse ( )
     {
          for ( int i = 0; i < length; i++ )
          {
               std::cout << vArray [ i ] << " ";
          }

          std::cout << std::endl;
     }

     bool operator==( const Vector &other ) const
     {
          if ( other.size ( ) != length )
          {
               return false;
          }
          for ( int i = 0; i < length; i++ )
          {
               if ( vArray [ i ] != other.at ( i ) )
               {
                    return false;
               }
          }
          return true;
     }

     T &operator[]( int i )
     {
          if ( ( i < 0 ) || ( i >= length ) )
          {
               std::cerr << std::endl << "Vector index out of bounds" << std::endl;
               exit ( 1 );
          }

          return vArray [ i ];
     }

     Vector ( const Vector &obj )
     {

          this->vArray = new T [ obj.capacity ( ) ];
          this->vCapacity = obj.capacity ( );
          this->length = obj.size ( );

          for ( int i = 0; i < obj.size ( ); i++ )
          {
               vArray [ i ] = obj.at ( i );
          }
     }

     // Copy assignment operator
     Vector &operator=( const Vector &source )
     {
          if ( this == &source )
          {
               return *this;
          }

          delete [ ] vArray;

          this->vArray = new T [ source.capacity ( ) ];
          this->vCapacity = source.capacity ( );
          this->length = source.size ( );

          for ( int i = 0; i < source.size ( ); i++ )
          {
               this->vArray [ i ] = source.at ( i );
          }

          return *this;
     }

     T *begin ( )
     {
          return vArray;
     }

     T *end ( )
     {
          return vArray + length;
     }
};

template <typename T , size_t Size>
class Array
{
private:
     T cArray [ Size ];
     size_t length = 0;

public:
     Array ( ) : length ( 0 )
     {
     }

     ~Array ( )
     {
     }

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

     size_t size ( ) const
     {
          return length;
     }

     size_t capacity ( ) const
     {
          return Size;
     }

     T &operator[]( size_t index )
     {
          if ( index >= length )
          {
               std::cerr << "Array index out of bounds" << std::endl;
               exit ( 1 );
          }

          return cArray [ index ];
     }

     void traverse ( )
     {
          for ( size_t i = 0; i < length; ++i )
          {
               std::cout << cArray [ i ] << " ";
          }

          std::cout << std::endl;
     }

     Array ( const Array &other ) : length ( other.length )
     {
          for ( size_t i = 0; i < length; ++i )
          {
               cArray [ i ] = other.cArray [ i ];
          }
     }

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

     T *begin ( )
     {
          return cArray;
     }

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
          deleteListContents ( );
          head = rhs.head;
          tail = rhs.tail;
     }

     virtual ~SeqContainer ( )
     {
          deleteListContents ( );
          delete head;
          delete tail;
     }

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

template <class N>
class Graph
{
public:
    // Default constuctor, create empty
     Graph ( )
     {
     }
     Graph ( Vector<N> nodes , Vector<std::pair<N , N>> edges )
     {
     }
     virtual ~Graph ( )
     {
     }

     virtual bool adjacent ( N x , N y ) = 0;
     virtual Vector<N> neighbors ( N x ) = 0;
     virtual void addNode ( N x ) = 0;
     virtual void addEdge ( N x , N y ) = 0;
     virtual void deleteEdge ( N x , N y ) = 0;
};

template <class N>
class AdjListGraph : public Graph<N>
{
private:
     using Edges = List<std::pair<int , int>>;
     Vector<N> nodes;
     Vector<List<N>> edges;
public:
     AdjListGraph ( ) : Graph<N> ( )
     {
     }
     AdjListGraph ( const AdjListGraph &other ) : Graph<N> ( )
     {
     }
     AdjListGraph &operator= ( const AdjListGraph &source )
     {
          return *this;
     }
     AdjListGraph ( Vector<N> newNodes , Vector<std::pair<N , N>> newEdges ) :
          Graph<N> ( newNodes , newEdges )
     {
     }
     ~AdjListGraph ( )
     {
     }

     virtual bool adjacent ( N x , N y ) override
     {
          for ( const auto &neighbor : neighbors ( x ) )
          {
               if ( neighbor == y )
               {
                    return true;
               }
          }
          return false;
     }
     virtual Vector<N> neighbors ( N x ) override
     {
          int index = -1;
          Vector<N> neighborVector;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               List<N> &neighborList = edges.at ( index );
               typename List<N>::Node *current = neighborList.head->next;
               while ( current != neighborList.tail )
               {
                    neighborVector.push_back ( current->data );
                    current = current->next;
               }
          }
          return neighborVector;
     }
     virtual void addNode ( N x ) override
     {
          nodes.push_back ( x );
          edges.push_back ( List<N> ( ) );
     }
     virtual void addEdge ( N x , N y ) override
     {
          int index = -1;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               edges.at ( index ).push_back ( y );
          }
     }
     virtual void deleteEdge ( N x , N y ) override
     {
          int index = -1;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               List<N> &edgeList = edges.at ( index );
               typename List<N>::Node *current = edgeList.head->next;
               typename List<N>::Node *prev = edgeList.head;
               while ( current != edgeList.tail )
               {
                    if ( current->data == y )
                    {
                         prev->next = current->next;
                         current->next->prev = prev;
                         delete current;
                         break;
                    }
                    prev = current;
                    current = current->next;
               }
          }
     }
};

template <class N>
class AdjMatrixGraph : public Graph<N>
{
private:
     const static int MaxSize = 100;
     Vector<N> nodes;
     int adjMatrix [ MaxSize ] [ MaxSize ] = {};

public:
     AdjMatrixGraph ( ) : Graph<N> ( )
     {
     }
     AdjMatrixGraph ( const AdjMatrixGraph &other ) : Graph<N> ( )
     {
     }
     AdjMatrixGraph &operator= ( const AdjMatrixGraph &source )
     {
     }
     AdjMatrixGraph ( Vector<N> newNodes , Vector<std::pair<N , N>> newEdges ) :
          Graph<N> ( newNodes , newEdges )
     {
     }
     ~AdjMatrixGraph ( )
     {
     }

     int getIndex ( N node )
     {
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == node ) return i;
          }
          return -1;
     }
     virtual bool adjacent ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          return ix != -1 && iy != -1 && adjMatrix [ ix ] [ iy ] == 1;
     }
     Vector<N> neighbors ( N x ) override
     {
          Vector<N> neighborVector;
          int ix = getIndex ( x );  // Get the index of node x
          if ( ix != -1 )
          {
               for ( int i = 0; i < nodes.size ( ); ++i )
               {
                    if ( adjMatrix [ ix ] [ i ] )
                    {
                         neighborVector.push_back ( nodes.at ( i ) );
                    }
               }
          }
          return neighborVector;
     }
     virtual void addNode ( N x ) override
     {
          nodes.push_back ( x );
     }
     virtual void addEdge ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          if ( ix != -1 && iy != -1 )
          {
               adjMatrix [ ix ] [ iy ] = 1;
          }
     }
     virtual void deleteEdge ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          if ( ix != -1 && iy != -1 )
          {
               adjMatrix [ ix ] [ iy ] = 0;
          }
     }
};