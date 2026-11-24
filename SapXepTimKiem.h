#ifndef SAPXEPTIMKIEM_H_INCLUDED_
#define SAPXEPTIMKIEM_H_INCLUDED_

#include <utility>
#include <vector>

// Cac ham sap xep va tim kiem
class SapXepTimKiem
{
public:
    // Sap xep nhanh (Quick Sort)
    template <class DataType>
    static void quickSort(std::vector<DataType>& vecA,
                          bool (*pDungTruoc)(const DataType&, const DataType&))
    {
        if (vecA.empty())
        {
            return;
        }
        SapXepTimKiem::quickSortDeQuy(vecA, 0, static_cast<int>(vecA.size()) - 1, pDungTruoc);
    }

    // Sap xep chon (Selection Sort)
    template <class DataType>
    static void selectionSort(std::vector<DataType>& vecA,
                              bool (*pDungTruoc)(const DataType&, const DataType&))
    {
        int iN = static_cast<int>(vecA.size());
        for (int iDau = 0; iDau < iN - 1; ++iDau)
        {
            int iMin = iDau;
            for (int iSau = iDau + 1; iSau < iN; ++iSau)
            {
                if (pDungTruoc(vecA[iSau], vecA[iMin]))
                {
                    iMin = iSau;
                }
            }
            if (iMin != iDau)
            {
                std::swap(vecA[iMin], vecA[iDau]);
            }
        }
    }

    // Tim kiem tuan tu
    template <class DataType>
    static int linearSearch(const std::vector<DataType>& vecA, const DataType& giaTriTim)
    {
        int iN = static_cast<int>(vecA.size());
        int iChiSo = 0;
        while (iChiSo < iN && !(vecA[iChiSo] == giaTriTim))
        {
            ++iChiSo;
        }
        if (iChiSo < iN)
        {
            return iChiSo;
        }
        return -1;
    }

private:
    template <class DataType>
    static void quickSortDeQuy(std::vector<DataType>& vecA, const int iLeft, const int iRight,
                               bool (*pDungTruoc)(const DataType&, const DataType&))
    {
        int iTrai = iLeft;
        int iPhai = iRight;
        DataType giaTriChot = vecA[(iLeft + iRight) / 2];

        do
        {
            while (pDungTruoc(vecA[iTrai], giaTriChot))
            {
                ++iTrai;
            }
            while (pDungTruoc(giaTriChot, vecA[iPhai]))
            {
                --iPhai;
            }
            if (iTrai <= iPhai)
            {
                std::swap(vecA[iTrai], vecA[iPhai]);
                ++iTrai;
                --iPhai;
            }
        } while (iTrai <= iPhai);

        if (iLeft < iPhai)
        {
            SapXepTimKiem::quickSortDeQuy(vecA, iLeft, iPhai, pDungTruoc);
        }
        if (iTrai < iRight)
        {
            SapXepTimKiem::quickSortDeQuy(vecA, iTrai, iRight, pDungTruoc);
        }
    }
};

#endif
