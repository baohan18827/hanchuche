#ifndef NODE_H_INCLUDED_
#define NODE_H_INCLUDED_

#include <cstddef>
#include <iostream>

template <class DataType>
class LinkedList;

// Nut trong danh sach lien ket don
template <class DataType>
class Node
{
public:
    explicit Node(const DataType& duLieu) : m_data(duLieu), m_pNext(NULL)
    {
    }

    ~Node()
    {
    }

    DataType& getData()
    {
        return this->m_data;
    }

    const DataType& getData() const
    {
        return this->m_data;
    }

    Node<DataType>* getNext()
    {
        return this->m_pNext;
    }

    const Node<DataType>* getNext() const
    {
        return this->m_pNext;
    }

    void display() const
    {
        std::cout << this->m_data << "\n";
    }

    friend class LinkedList<DataType>;

private:
    DataType m_data;
    Node<DataType>* m_pNext;
};

#endif
