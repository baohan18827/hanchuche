#include "Ngay.h"

#include <cstdio>
#include <ctime>
#include <vector>

#include "ChuoiTienIch.h"
#include "HangSoThuVien.h"

using namespace std;

Ngay::Ngay() : m_iNgay(1), m_iThang(1), m_iNam(2025)
{
}

Ngay::Ngay(const int iNgay, const int iThang, const int iNam)
    : m_iNgay(iNgay), m_iThang(iThang), m_iNam(iNam)
{
}

Ngay::Ngay(const Ngay& khac)
    : m_iNgay(khac.m_iNgay), m_iThang(khac.m_iThang), m_iNam(khac.m_iNam)
{
}

Ngay& Ngay::operator=(const Ngay& khac)
{
    if (this != &khac)
    {
        this->m_iNgay = khac.m_iNgay;
        this->m_iThang = khac.m_iThang;
        this->m_iNam = khac.m_iNam;
    }
    return *this;
}

Ngay::~Ngay()
{
}

int Ngay::getNgay() const
{
    return this->m_iNgay;
}

int Ngay::getThang() const
{
    return this->m_iThang;
}

int Ngay::getNam() const
{
    return this->m_iNam;
}

void Ngay::setNgay(const int iNgay)
{
    this->m_iNgay = iNgay;
}

void Ngay::setThang(const int iThang)
{
    this->m_iThang = iThang;
}

void Ngay::setNam(const int iNam)
{
    this->m_iNam = iNam;
}

bool Ngay::operator==(const Ngay& khac) const
{
    return (this->soSanhVoi(khac) == 0);
}

bool Ngay::operator!=(const Ngay& khac) const
{
    return (this->soSanhVoi(khac) != 0);
}

bool Ngay::operator<(const Ngay& khac) const
{
    return (this->soSanhVoi(khac) < 0);
}

bool Ngay::operator>(const Ngay& khac) const
{
    return (this->soSanhVoi(khac) > 0);
}

bool Ngay::laNamNhuan(const int iNam)
{
    const int CHU_KY_4 = 4;
    const int CHU_KY_100 = 100;
    const int CHU_KY_400 = 400;
    return ((iNam % CHU_KY_4 == 0 && iNam % CHU_KY_100 != 0) || (iNam % CHU_KY_400 == 0));
}

int Ngay::soNgayTrongThang(const int iThang, const int iNam)
{
    static const int SO_NGAY[SO_THANG_MOT_NAM] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (iThang < THANG_DAU_NAM || iThang > THANG_CUOI_NAM)
    {
        return 0;
    }
    if (iThang == THANG_HAI && Ngay::laNamNhuan(iNam))
    {
        return NGAY_THANG_HAI_NHUAN;
    }
    return SO_NGAY[iThang - 1];
}

bool Ngay::hopLe(const int iNgay, const int iThang, const int iNam)
{
    if (iNam < NAM_PHAT_HANH_TOI_THIEU || iNam > NAM_TOI_DA)
    {
        return false;
    }
    if (iThang < THANG_DAU_NAM || iThang > THANG_CUOI_NAM || iNgay < 1)
    {
        return false;
    }
    return (iNgay <= Ngay::soNgayTrongThang(iThang, iNam));
}

int Ngay::soSanhVoi(const Ngay& khac) const
{
    if (this->m_iNam != khac.m_iNam)
    {
        return (this->m_iNam - khac.m_iNam);
    }
    if (this->m_iThang != khac.m_iThang)
    {
        return (this->m_iThang - khac.m_iThang);
    }
    return (this->m_iNgay - khac.m_iNgay);
}

Ngay Ngay::congThemNgay(const int iSoNgayCong) const
{
    Ngay ngayKetQua = *this;
    for (int iDem = 0; iDem < iSoNgayCong; ++iDem)
    {
        ngayKetQua = ngayKetQua.tangMotNgay();
    }
    return ngayKetQua;
}

long long Ngay::chenhLechNgay(const Ngay& ngayA, const Ngay& ngayB)
{
    int iSoSanh = ngayA.soSanhVoi(ngayB);
    if (iSoSanh == 0)
    {
        return 0;
    }
    if (iSoSanh > 0)
    {
        Ngay ngayChay = ngayB;
        long long lDem = 0;
        while (ngayChay.soSanhVoi(ngayA) < 0)
        {
            ngayChay = ngayChay.tangMotNgay();
            ++lDem;
        }
        return lDem;
    }
    return -Ngay::chenhLechNgay(ngayB, ngayA);
}

Ngay Ngay::homNay()
{
    const int NAM_GOC_TM = 1900;
    time_t tHienTai = time(NULL);
    tm* pLich = localtime(&tHienTai);
    if (pLich == NULL)
    {
        return Ngay();
    }
    return Ngay(pLich->tm_mday, pLich->tm_mon + 1, pLich->tm_year + NAM_GOC_TM);
}

string Ngay::toString() const
{
    const int KICH_THUOC_DEM = 20;
    char szDem[KICH_THUOC_DEM];
    snprintf(szDem, sizeof(szDem), "%02d/%02d/%04d", this->m_iNgay, this->m_iThang, this->m_iNam);
    return string(szDem);
}

bool Ngay::phanTichChuoi(const string& strChuoi, Ngay& ketQua)
{
    vector<string> vecPhan = ChuoiTienIch::tachChuoi(ChuoiTienIch::catKhoangTrang(strChuoi), '/');
    if (static_cast<int>(vecPhan.size()) != SO_TRUONG_NGAY)
    {
        return false;
    }
    for (int iChiSo = 0; iChiSo < SO_TRUONG_NGAY; ++iChiSo)
    {
        if (!ChuoiTienIch::laDayChuSo(vecPhan[iChiSo]))
        {
            return false;
        }
    }
    if (static_cast<int>(vecPhan[0].size()) > DO_DAI_NGAY_THANG_CHUOI ||
        static_cast<int>(vecPhan[1].size()) > DO_DAI_NGAY_THANG_CHUOI ||
        static_cast<int>(vecPhan[2].size()) != DO_DAI_NAM_CHUOI)
    {
        return false;
    }

    int iNgay = stoi(vecPhan[0]);
    int iThang = stoi(vecPhan[1]);
    int iNam = stoi(vecPhan[2]);
    if (!Ngay::hopLe(iNgay, iThang, iNam))
    {
        return false;
    }
    ketQua = Ngay(iNgay, iThang, iNam);
    return true;
}

ostream& operator<<(ostream& os, const Ngay& ngay)
{
    os << ngay.toString();
    return os;
}

Ngay Ngay::tangMotNgay() const
{
    int iNgayMoi = this->m_iNgay + 1;
    int iThangMoi = this->m_iThang;
    int iNamMoi = this->m_iNam;
    if (iNgayMoi > Ngay::soNgayTrongThang(iThangMoi, iNamMoi))
    {
        iNgayMoi = 1;
        ++iThangMoi;
        if (iThangMoi > THANG_CUOI_NAM)
        {
            iThangMoi = THANG_DAU_NAM;
            ++iNamMoi;
        }
    }
    return Ngay(iNgayMoi, iThangMoi, iNamMoi);
}
