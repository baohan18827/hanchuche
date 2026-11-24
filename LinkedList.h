#ifndef LINKEDLIST_H_INCLUDED_
#define LINKEDLIST_H_INCLUDED_

#include <utility>

#include "Node.h"

// Danh sach lien ket don
template <class DataType>
class LinkedList
{
public:
    LinkedList() : m_pHead(NULL), m_pTail(NULL), m_iSize(0)
    {
    }

    ~LinkedList()
    {
        this->clear();
    }

    int getSize() const
    {
        return this->m_iSize;
    }

    Node<DataType>* getHead() const
    {
        return this->m_pHead;
    }

    Node<DataType>* getTail() const
    {
        return this->m_pTail;
    }

    // Them vao dau danh sach
    void addHead(const DataType& duLieu)
    {
        Node<DataType>* pAdd = new Node<DataType>(duLieu);
        if (this->m_pHead == NULL)
        {
            this->m_pHead = pAdd;
            this->m_pTail = pAdd;
        }
        else
        {
            pAdd->m_pNext = this->m_pHead;
            this->m_pHead = pAdd;
        }
        ++this->m_iSize;
    }

    // Them vao cuoi danh sach
    void addTail(const DataType& duLieu)
    {
        Node<DataType>* pAdd = new Node<DataType>(duLieu);
        if (this->m_pHead == NULL)
        {
            this->m_pHead = pAdd;
            this->m_pTail = pAdd;
        }
        else
        {
            this->m_pTail->m_pNext = pAdd;
            this->m_pTail = pAdd;
        }
        ++this->m_iSize;
    }

    // Them sau mot nut
    void addAfter(Node<DataType>* pNode, const DataType& duLieu)
    {
        if (pNode == NULL)
        {
            this->addHead(duLieu);
            return;
        }
        Node<DataType>* pAdd = new Node<DataType>(duLieu);
        pAdd->m_pNext = pNode->m_pNext;
        pNode->m_pNext = pAdd;
        if (pNode == this->m_pTail)
        {
            this->m_pTail = pAdd;
        }
        ++this->m_iSize;
    }

    // Tim nut theo gia tri
    Node<DataType>* search(const DataType& duLieu) const
    {
        Node<DataType>* pCur = this->m_pHead;
        while (pCur != NULL && !(pCur->m_data == duLieu))
        {
            pCur = pCur->m_pNext;
        }
        return pCur;
    }

    // Tim nut dung truoc pNode
    Node<DataType>* searchPre(const Node<DataType>* pNode) const
    {
        if (pNode == NULL || pNode == this->m_pHead)
        {
            return NULL;
        }
        Node<DataType>* pCur = this->m_pHead;
        while (pCur != NULL && pCur->m_pNext != pNode)
        {
            pCur = pCur->m_pNext;
        }
        return pCur;
    }

    void removeHead()
    {
        if (this->m_pHead == NULL)
        {
            return;
        }
        Node<DataType>* pTemp = this->m_pHead;
        this->m_pHead = this->m_pHead->m_pNext;
        delete pTemp;
        if (this->m_pHead == NULL)
        {
            this->m_pTail = NULL;
        }
        --this->m_iSize;
    }

    void removeTail()
    {
        if (this->m_pHead == NULL)
        {
            return;
        }
        if (this->m_pHead == this->m_pTail)
        {
            this->removeHead();
            return;
        }
        Node<DataType>* pTemp = this->m_pTail;
        this->m_pTail = this->searchPre(this->m_pTail);
        delete pTemp;
        if (this->m_pTail == NULL)
        {
            this->m_pHead = NULL;
        }
        else
        {
            this->m_pTail->m_pNext = NULL;
        }
        --this->m_iSize;
    }

    void removeAfter(Node<DataType>* pNode)
    {
        if (pNode == NULL)
        {
            this->removeHead();
            return;
        }
        Node<DataType>* pTemp = pNode->m_pNext;
        if (pTemp == NULL)
        {
            return;
        }
        if (pTemp == this->m_pTail)
        {
            this->m_pTail = pNode;
        }
        pNode->m_pNext = pTemp->m_pNext;
        delete pTemp;
        --this->m_iSize;
    }

    // Xoa nut theo gia tri
    void remove(const DataType& duLieu)
    {
        Node<DataType>* pTemp = NULL;
        Node<DataType>* pCur = this->m_pHead;
        while (pCur != NULL && !(pCur->m_data == duLieu))
        {
            pTemp = pCur;
            pCur = pCur->m_pNext;
        }
        if (pCur == NULL)
        {
            return;
        }
        if (pTemp == NULL)
        {
            this->removeHead();
            return;
        }
        if (pCur == this->m_pTail)
        {
            this->m_pTail = pTemp;
        }
        pTemp->m_pNext = pCur->m_pNext;
        delete pCur;
        --this->m_iSize;
    }

    void clear()
    {
        while (this->m_pHead != NULL)
        {
            this->removeHead();
        }
    }

    // Sap xep chon tren danh sach lien ket
    void selectionSort()
    {
        if (this->m_pHead == NULL)
        {
            return;
        }
        for (Node<DataType>* pDau = this->m_pHead; pDau->m_pNext != NULL; pDau = pDau->m_pNext)
        {
            Node<DataType>* pMin = pDau;
            for (Node<DataType>* pSau = pDau->m_pNext; pSau != NULL; pSau = pSau->m_pNext)
            {
                if (pSau->m_data < pMin->m_data)
                {
                    pMin = pSau;
                }
            }
            if (pMin != pDau)
            {
                std::swap(pMin->m_data, pDau->m_data);
            }
        }
    }

private:
    LinkedList(const LinkedList<DataType>&);
    LinkedList<DataType>& operator=(const LinkedList<DataType>&);

    Node<DataType>* m_pHead;
    Node<DataType>* m_pTail;
    int m_iSize;
};

#endif
