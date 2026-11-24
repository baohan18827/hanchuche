#ifndef BINARYSEARCHTREE_H_INCLUDED_
#define BINARYSEARCHTREE_H_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>

// Cay nhi phan tim kiem (BST)
template <class DataType>
class BinarySearchTree
{
public:
    BinarySearchTree() : m_pRoot(NULL), m_iSoNut(0)
    {
    }

    ~BinarySearchTree()
    {
        this->clear();
    }

    int getSize() const
    {
        return this->m_iSoNut;
    }

    void clear()
    {
        this->destroy(this->m_pRoot);
        this->m_pRoot = NULL;
        this->m_iSoNut = 0;
    }

    // Them nut vao cay
    bool insert(const std::string& strKey, DataType* pVal)
    {
        bool bAdded = false;
        this->m_pRoot = this->insertRec(this->m_pRoot, strKey, pVal, bAdded);
        return bAdded;
    }

    // Xoa nut theo khoa
    bool remove(const std::string& strKey)
    {
        bool bRemoved = false;
        this->m_pRoot = this->removeRec(this->m_pRoot, strKey, bRemoved);
        return bRemoved;
    }

    // Tim kiem theo khoa
    DataType* search(const std::string& strKey) const
    {
        TNode* pCur = this->m_pRoot;
        while (pCur != NULL)
        {
            if (strKey == pCur->m_strKey)
            {
                return pCur->m_pVal;
            }
            pCur = (strKey < pCur->m_strKey) ? pCur->m_pLeft : pCur->m_pRight;
        }
        return NULL;
    }

    // Duyet LNR lay danh sach tang dan
    void inOrder(std::vector<DataType*>& vecKetQua) const
    {
        vecKetQua.clear();
        this->inOrderRec(this->m_pRoot, vecKetQua);
    }

private:
    class TNode
    {
    public:
        TNode(const std::string& strKey, DataType* pVal)
            : m_strKey(strKey), m_pVal(pVal), m_pLeft(NULL), m_pRight(NULL)
        {
        }

        std::string m_strKey;
        DataType* m_pVal;
        TNode* m_pLeft;
        TNode* m_pRight;
    };

    BinarySearchTree(const BinarySearchTree<DataType>&);
    BinarySearchTree<DataType>& operator=(const BinarySearchTree<DataType>&);

    TNode* insertRec(TNode* pRoot, const std::string& strKey, DataType* pVal, bool& bAdded)
    {
        if (pRoot == NULL)
        {
            bAdded = true;
            ++this->m_iSoNut;
            return new TNode(strKey, pVal);
        }
        else if (strKey < pRoot->m_strKey)
        {
            pRoot->m_pLeft = this->insertRec(pRoot->m_pLeft, strKey, pVal, bAdded);
        }
        else if (strKey > pRoot->m_strKey)
        {
            pRoot->m_pRight = this->insertRec(pRoot->m_pRight, strKey, pVal, bAdded);
        }
        else
        {
            bAdded = false;
        }
        return pRoot;
    }

    TNode* minNode(TNode* pRoot) const
    {
        TNode* pCur = pRoot;
        while (pCur != NULL && pCur->m_pLeft != NULL)
        {
            pCur = pCur->m_pLeft;
        }
        return pCur;
    }

    TNode* removeRec(TNode* pRoot, const std::string& strKey, bool& bRemoved)
    {
        if (pRoot == NULL)
        {
            bRemoved = false;
            return NULL;
        }
        if (strKey < pRoot->m_strKey)
        {
            pRoot->m_pLeft = this->removeRec(pRoot->m_pLeft, strKey, bRemoved);
        }
        else if (strKey > pRoot->m_strKey)
        {
            pRoot->m_pRight = this->removeRec(pRoot->m_pRight, strKey, bRemoved);
        }
        else
        {
            bRemoved = true;
            if (pRoot->m_pLeft == NULL)
            {
                TNode* pRight = pRoot->m_pRight;
                delete pRoot;
                --this->m_iSoNut;
                return pRight;
            }
            if (pRoot->m_pRight == NULL)
            {
                TNode* pLeft = pRoot->m_pLeft;
                delete pRoot;
                --this->m_iSoNut;
                return pLeft;
            }
            TNode* pMin = this->minNode(pRoot->m_pRight);
            std::string strKeyMin = pMin->m_strKey;
            pRoot->m_strKey = pMin->m_strKey;
            pRoot->m_pVal = pMin->m_pVal;
            bool bTemp = false;
            pRoot->m_pRight = this->removeRec(pRoot->m_pRight, strKeyMin, bTemp);
        }
        return pRoot;
    }

    void inOrderRec(TNode* pRoot, std::vector<DataType*>& vecKetQua) const
    {
        if (pRoot == NULL)
        {
            return;
        }
        this->inOrderRec(pRoot->m_pLeft, vecKetQua);
        vecKetQua.push_back(pRoot->m_pVal);
        this->inOrderRec(pRoot->m_pRight, vecKetQua);
    }

    void destroy(TNode* pRoot)
    {
        if (pRoot == NULL)
        {
            return;
        }
        this->destroy(pRoot->m_pLeft);
        this->destroy(pRoot->m_pRight);
        delete pRoot;
    }

    TNode* m_pRoot;
    int m_iSoNut;
};

#endif
