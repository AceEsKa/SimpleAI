#pragma once
#include <string>
#include <iostream>

//custom iterator for our binar tree so we can iterate over its elementes
template<typename bintree>
class bintreePreOrderIterator
{
public:
	//defines an alias for the underlying container(node) within the bintree class
	using _node = typename bintree::node;

	//defines an alias for the value type stored within the underlying container(node) of our bin tree
	using ValueType = _node::ValueType;

	//defines an alias for a pointer to a our bintrees underlying container(node)
	using NodePointer = _node*;

	//defines an alias for a pointer to the value type stored in the underlying container(node) of our bin tree
	using PointerType = ValueType*;

	//defines an alias for a reference to the value type stored in the underlying container(node) of our bin tree
	// (const ensures the value isn't modified)
	using ReferenceType = const ValueType&;

	bintreePreOrderIterator(const NodePointer ptr)
		: m_Ptr(ptr) { }


	//increments operator
	//operator for ++iterator
	bintreePreOrderIterator& operator++();

	//increments operator
	//operator for iterator++
	bintreePreOrderIterator& operator++(int);

	//moves iterator to the left child
	bintreePreOrderIterator& move_left();

	//moves iterator to the right child
	bintreePreOrderIterator& move_right();

	//decrement operator, moves iterator to the parent
	bintreePreOrderIterator& operator--();

	//decrement operator, moves iterator to the parent but returns child node
	bintreePreOrderIterator& operator--(int);

	//returns reference to value stored in our node m_Ptr->value
	ReferenceType operator*();

	//tbd
	NodePointer operator->();

	//operator for comaprisons between given iterators
	bool operator==(const bintreePreOrderIterator& other) const;

	//operator for comaprisons between given iterators
	bool operator!=(const bintreePreOrderIterator& other) const;

private:
	//stores pointer to the underlying container of our bin tree 
	NodePointer m_Ptr;
};

template<typename T>
class bintree
{
private:
	struct node;
public:
	//defines an alias for the value type of our bin tree
	using ValueType = T;
	//defines an alias for the iterator of our bin tree
	using Iterator = bintreePreOrderIterator<bintree<T>>;
public:
	//default constructor
	bintree();

	//returns element in the front
	T const& front() const;

	//builds root node,m_head
	void BuildRoot(T value);

	//pushes back an elemnt to the left
	void push_left(T value);

	//pushes back an elemnt to the right
	void push_right(T value);

	//sets current node to root
	void goToRoot();

	//moves up trough our bin tree
	void moveUp();

	//deletes at iterator position
	void DeleteLeaf(Iterator at);

	//deletes a value
	void DeleteLeaf(T value);

	//deletes on index
	void DeleteLeaf(int index);

	//stores given string value
	void StoreData(std::string value);

	//returns size of our queue
	int size();

	//returns whether tree is contains any nodes
	bool empty();

	//returns iterator to the begining(1st element) of our queue
	Iterator begin();

	//returns adress past our last element as for us to know when to stop iterating
	Iterator end();

	//inserts before the leaf 
	void InsertBefore(Iterator at, T value1/*question(in our case)*/, T value2/*answer(in our case)*/);

	//clears our stack so there are no data left
	void clear();

	//destructor ensures safe memory freeing
	~bintree();

	//private members
private:
	//declare our custom iterator as friend as to have him access our private members
	template<typename>
	friend class bintreePreOrderIterator;

	//stores the size of our queue(number of elements)
	size_t m_size = 0;

	//our underlying container
	struct node
	{
		using ValueType = T;
		T m_Value;

		//checks if this node is a leaf node
		bool IsLeaf()
		{
			return (left == nullptr && right == nullptr);
		}

		//previous node/parent node
		node* parent = nullptr;

		//left child
		node* left = nullptr;

		//right child
		node* right = nullptr;
	};

	//store references to head
	node* m_head = nullptr;

	//stores reference to current node that we are working with
	node* m_current = nullptr;

	//if we are to store data and the data is separated on new lines and previous line ends on -1 indicating no children and we move up a parent
	//then call StoreData() again this flag will still be "up" preventing us from pushing left and creating memory leak
	bool flag = false;
};



