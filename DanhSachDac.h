#ifndef DANHSACHDAC_H_INCLUDED_
#define DANHSACHDAC_H_INCLUDED_

// Danh sach dac co sap xep
template <class DataType, int SO_PHAN_TU_TOI_DA>
class DanhSachDac
{
public:
    DanhSachDac() : m_iSoLuong(0)
    {
    }

    ~DanhSachDac()
    {
    }

    int getSoLuong() const
    {
        return this->m_iSoLuong;
    }

    bool daDay() const
    {
        return (this->m_iSoLuong >= SO_PHAN_TU_TOI_DA);
    }

    DataType& operator[](const int iChiSo)
    {
        return this->m_mang[iChiSo];
    }

    const DataType& operator[](const int iChiSo) const
    {
        return this->m_mang[iChiSo];
    }

    DataType& getPhanTu(const int iChiSo)
    {
        return this->m_mang[iChiSo];
    }

    const DataType& getPhanTu(const int iChiSo) const
    {
        return this->m_mang[iChiSo];
    }

    // Tim kiem nhi phan
    int binarySearch(const DataType& khoaMau) const
    {
        int iLeft = 0;
        int iRight = this->m_iSoLuong - 1;
        while (iLeft <= iRight)
        {
            int iMid = (iLeft + iRight) / 2;
            if (this->m_mang[iMid] == khoaMau)
            {
                return iMid;
            }
            else if (this->m_mang[iMid] < khoaMau)
            {
                iLeft = iMid + 1;
            }
            else
            {
                iRight = iMid - 1;
            }
        }
        return -1;
    }

    // Them phan tu giu thu tu tang dan
    bool themTheoThuTu(const DataType& phanTuMoi)
    {
        if (this->daDay() || this->binarySearch(phanTuMoi) != -1)
        {
            return false;
        }
        int iPos = this->m_iSoLuong;
        while (iPos > 0 && this->m_mang[iPos - 1] > phanTuMoi)
        {
            this->m_mang[iPos] = this->m_mang[iPos - 1];
            --iPos;
        }
        this->m_mang[iPos] = phanTuMoi;
        ++this->m_iSoLuong;
        return true;
    }

    // Xoa phan tu khoi mang
    bool xoaPhanTu(const DataType& khoaMau)
    {
        int iPos = this->binarySearch(khoaMau);
        if (iPos == -1)
        {
            return false;
        }
        for (int i = iPos; i < this->m_iSoLuong - 1; ++i)
        {
            this->m_mang[i] = this->m_mang[i + 1];
        }
        --this->m_iSoLuong;
        return true;
    }

private:
    DataType m_mang[SO_PHAN_TU_TOI_DA];
    int m_iSoLuong;
};

#endif
