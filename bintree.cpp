#include "bintree.h"

template<typename T>
bintree<T>::bintree() { }

template<typename T>
bintree<T>::~bintree()
{
	clear();
};

template<typename T>
void bintree<T>::StoreData(std::string data)
{
	std::stringstream ss(data);

	std::string value;
	while (std::getline(ss, value, ','))
	{
		if (flag == true)
		{
			push_right(value);
		}
		if (value != "-1")
		{
			//we wanna enter but just reset the flag
			if (!flag)
			{
				push_left(value);
			}
			flag = false;
		}
		else
		{
			flag = true;
			moveUp();
		}
	}
}

template<typename T>
int bintree<T>::size() { return m_size; }

template<typename T>
bool bintree<T>::empty() { return m_size == 0; }

template<typename T>
void bintree<T>::push_left(T value)
{
	if (m_size++ == 0)
	{
		BuildRoot(value);
		return;
	}

	node* new_node = new node;
	new_node->m_Value = value;

	m_current->left = new_node;
	new_node->parent = m_current;
	m_current = new_node;
}

template<typename T>
void bintree<T>::push_right(T value)
{

	if (m_size++ == 0)
	{
		BuildRoot(value);
		return;

	}
	node* new_node = new node;
	new_node->m_Value = value;

	m_current->right = new_node;
	new_node->parent = m_current;
	m_current = new_node;
}

template<typename T>
void bintree<T>::goToRoot()
{
	m_current = m_head;
}

template<typename T>
void bintree<T>::moveUp()
{
	m_current = m_current->parent;
	while (m_current->left != nullptr && m_current->right != nullptr && m_current->parent != nullptr)
	{
		m_current = m_current->parent;
	}
}

template<typename T>
void bintree<T>::DeleteLeaf(Iterator at)
{
	node* parent = at->parent;
	node* toDelete;
	if (at->parent->right == at)
	{
		toDelete = parent->right;
		if (toDelete->IsLeaf())
		{
			delete toDelete;
			parent->right = nullptr;
		}
	}
	else
	{
		toDelete = parent->left;
		if (toDelete->IsLeaf())
		{
			delete toDelete;
			parent->left = nullptr;
		}
	}
}

template<typename T>
void bintree<T>::DeleteLeaf(T value)
{
	node* tmp;
	for (bintree<std::string>::Iterator it = begin(); it != end(); ++it)
	{
		if (*it->m_Value == value && !(*it->IsLeaf())) { return; }

		if (*it->IsLeaf() && *it->m_Value == value)
		{
			tmp = *it;
			node* tmp_p = tmp->parent;
			if (tmp->parent->right == tmp)
			{
				delete tmp;
				tmp->right = nullptr;
			}
			else
			{
				delete tmp;
				tmp->left = nullptr;
			}
			return;
		}
	}
}

template<typename T>
void bintree<T>::DeleteLeaf(int index)
{
	if (index > m_size)
	{
		index = m_size;
	}
	node* tmp;
	bintree<std::string>::Iterator it = begin();
	for (int i= 0; i < index+1; ++i)
	{
		it++;
		if (i == index && !(*it->IsLeaf())) { return; }

		if (*it->IsLeaf() && i == index)
		{
			tmp = *it;
			node* tmp_p = tmp->parent;
			if (tmp->parent->right == tmp)
			{
				delete tmp;
				tmp->right = nullptr;
			}
			else
			{
				delete tmp;
				tmp->left = nullptr;
			}
			return;
		}
	}
}

template<typename T>
T const& bintree<T>::front() const
{
	return m_head->m_Value;
}

template<typename T>
void bintree<T>::BuildRoot(T value)
{
	node* new_node = new node;
	new_node->m_Value = value;
	m_head = new_node;
	/*new_node->parent = m_head;*/
	m_current = new_node;
}

template<typename T>
void bintree<T>::clear()
{
	if (m_size == 0) { return; }

	if (m_size-- == 1)
	{
		delete m_head;
		m_current = m_head = nullptr;
		return;
	}

	node* tmp = m_head->left;
	while (m_size != 0)
	{
		if (tmp->left != nullptr)
		{
			tmp = tmp->left;
		}
		else if (tmp->right != nullptr)
		{
			tmp = tmp->right;
		}

		if (tmp->right == nullptr && tmp->left == nullptr)
		{
			node* to_delete = tmp;
			tmp = tmp->parent;
			if (tmp->right == to_delete)
			{
				tmp->right = nullptr;
			}
			else
			{
				tmp->left = nullptr;
			}
			delete to_delete;
			to_delete = nullptr;
			--m_size;
		}
	}

	delete m_head;
	m_head = nullptr;
	m_current = nullptr;
}


template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::operator++()
{
	if (this->m_Ptr->left)
	{
		*this = this->m_Ptr->left;
		return *this;
	}
	else if (this->m_Ptr->right)
	{
		*this = this->m_Ptr->right;
		return *this;
	}

	//if we reach the root, node with no parent, and this is not a left child return end iterator(past the end), which should be parent
	if (this->m_Ptr && this->m_Ptr->parent->parent == nullptr && this->m_Ptr != this->m_Ptr->parent->left)
	{
		*this = this->m_Ptr->parent;
		return *this;
	}
	//bintreePreOrderIterator iterator = *this;

	//if this->m_ptr is a right child of its parent move up
	while (this->m_Ptr != nullptr && this->m_Ptr->parent != nullptr && this->m_Ptr == this->m_Ptr->parent->right)
	{
		*this = this->m_Ptr->parent;
	}
	
	if (this->m_Ptr->parent == nullptr)
	{
		*this = this->m_Ptr->parent;
		return *this;
	}

	*this = this->m_Ptr->parent->right;

	return *this;
}

template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::operator++(int)
{
	bintreePreOrderIterator iterator = *this;
	//if 
	if (this->m_Ptr->left)
	{
		*this = m_Ptr->left;
		return iterator;
	}
	else if (this->m_Ptr->right)
	{
		*this = this->m_Ptr->right;
		return iterator;
	}

	//if this->m_ptr is a right child of its parent move up
	while (this->m_Ptr != nullptr && this->m_Ptr->parent != nullptr && this->m_Ptr == this->m_Ptr->parent->right)
	{
		*this = this->m_Ptr->parent;
	}

	if (this->m_Ptr->parent == nullptr)
	{
		*this = this->m_Ptr->parent;
		return *this;
	}

	*this = this->m_Ptr->parent->right;

	return iterator;
}

template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::move_left()
{
	if (this->m_Ptr && this->m_Ptr->left != nullptr)
	{
		*this = this->m_Ptr->left;
	}

	return *this;
}

template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::move_right()
{
	if (this->m_Ptr && this->m_Ptr->right != nullptr)
	{
		*this = this->m_Ptr->right;
	}

	return *this;
}


template<typename bintree>
bintreePreOrderIterator<bintree>::ReferenceType bintreePreOrderIterator<bintree>::operator*()
{
	return this->m_Ptr->m_Value;
}

template<typename bintree>
bool bintreePreOrderIterator<bintree>::operator==(const bintreePreOrderIterator& other) const
{
	return this->m_Ptr == other.m_Ptr;
}

template<typename bintree>
bool bintreePreOrderIterator<bintree>::operator!=(const bintreePreOrderIterator& other) const
{
	return !(*this == other);
}


template<typename bintree>
bintreePreOrderIterator<bintree>::NodePointer bintreePreOrderIterator<bintree>::operator->()
{
	return this->m_Ptr;
}

template<typename T>
bintree<T>::Iterator bintree<T>::begin()
{
	return Iterator(m_head);
}

template<typename T>
bintree<T>::Iterator bintree<T>::end()
{
	//return adress past our last element (which is nulptr in our case)
	return Iterator(m_head->parent);
}

//inserts node before given position/iterator and creates its left child
template<typename T>
void bintree<T>::InsertBefore(Iterator at, T value1/*question(in our case)*/, T value2/*answer(in our case)*/)
{
	Iterator it= at;
	--it;
	it = it.move_right();
	node* n_parent = at->parent;
	node* n_value1 = new node;//question
	node* n_value2 = new node;//answer
	node* n_current;//at, previous answer

	n_value1->m_Value = value1;
	n_value2->m_Value = value2;

	if (it == at)
	{
		n_current = n_parent->right;
		n_parent->right = n_value1;
	}
	else
	{
		n_current = n_parent->left;
		n_parent->left = n_value1;
	}
	n_value1->parent = n_current->parent;
	n_value1->left = n_current;
	n_current->parent = n_value1;
	n_value1->right = n_value2;
	n_value2->parent = n_value1;
}

template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::operator--()
{
	if (this->m_Ptr)
	{
		*this = m_Ptr->parent;
	}
	return *this;
}

template<typename bintree>
bintreePreOrderIterator<bintree>& bintreePreOrderIterator<bintree>::operator--(int)
{
	bintreePreOrderIterator iterator = *this;

	if (this->m_Ptr)
	{
		*this->m_Ptr = this->m_Ptr->parent;
	}
	return iterator;
}