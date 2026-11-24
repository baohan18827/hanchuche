#ifndef STACK_H_INCLUDED_
#define STACK_H_INCLUDED_

#include <cstddef>

// Ngan xep (Stack)
template <class DataType>
class Stack
{
public:
    Stack() : m_pTop(NULL), m_iSize(0)
    {
    }

    ~Stack()
    {
        while (!this->empty())
        {
            this->pop();
        }
    }

    bool empty() const
    {
        return (this->m_pTop == NULL);
    }

    int getSize() const
    {
        return this->m_iSize;
    }

    // Them phan tu vao dinh stack
    void push(const DataType& duLieu)
    {
        SNode* pMoi = new SNode(duLieu);
        pMoi->m_pNext = this->m_pTop;
        this->m_pTop = pMoi;
        ++this->m_iSize;
    }

    // Xoa phan tu o dinh stack
    void pop()
    {
        if (this->empty())
        {
            return;
        }
        SNode* pTam = this->m_pTop;
        this->m_pTop = this->m_pTop->m_pNext;
        delete pTam;
        --this->m_iSize;
    }

    DataType& top()
    {
        return this->m_pTop->m_data;
    }

    const DataType& top() const
    {
        return this->m_pTop->m_data;
    }

private:
    class SNode
    {
    public:
        explicit SNode(const DataType& duLieu) : m_data(duLieu), m_pNext(NULL)
        {
        }

        DataType m_data;
        SNode* m_pNext;
    };

    Stack(const Stack<DataType>&);
    Stack<DataType>& operator=(const Stack<DataType>&);

    SNode* m_pTop;
    int m_iSize;
};

#endif
