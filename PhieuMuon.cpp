#include "PhieuMuon.h"

#include <vector>

#include "ChuoiTienIch.h"

using namespace std;

PhieuMuon::PhieuMuon()
    : m_iSoPhieu(0), m_strMaBanDoc(""), m_strMaSach(""), m_ngayMuon(),
      m_ngayPhaiTra(), m_eTinhTrang(PHIEU_DANG_MUON)
{
}

PhieuMuon::PhieuMuon(const int iSoPhieu)
    : m_iSoPhieu(iSoPhieu), m_strMaBanDoc(""), m_strMaSach(""), m_ngayMuon(),
      m_ngayPhaiTra(), m_eTinhTrang(PHIEU_DANG_MUON)
{
}

PhieuMuon::PhieuMuon(const int iSoPhieu, const string& strMaBanDoc, const string& strMaSach,
                     const Ngay& ngayMuon, const Ngay& ngayPhaiTra,
                     const TinhTrangPhieu eTinhTrang)
    : m_iSoPhieu(iSoPhieu), m_strMaBanDoc(strMaBanDoc), m_strMaSach(strMaSach),
      m_ngayMuon(ngayMuon), m_ngayPhaiTra(ngayPhaiTra), m_eTinhTrang(eTinhTrang)
{
}

PhieuMuon::PhieuMuon(const PhieuMuon& khac)
    : m_iSoPhieu(khac.m_iSoPhieu), m_strMaBanDoc(khac.m_strMaBanDoc),
      m_strMaSach(khac.m_strMaSach), m_ngayMuon(khac.m_ngayMuon),
      m_ngayPhaiTra(khac.m_ngayPhaiTra), m_eTinhTrang(khac.m_eTinhTrang)
{
}

PhieuMuon& PhieuMuon::operator=(const PhieuMuon& khac)
{
    if (this != &khac)
    {
        this->m_iSoPhieu = khac.m_iSoPhieu;
        this->m_strMaBanDoc = khac.m_strMaBanDoc;
        this->m_strMaSach = khac.m_strMaSach;
        this->m_ngayMuon = khac.m_ngayMuon;
        this->m_ngayPhaiTra = khac.m_ngayPhaiTra;
        this->m_eTinhTrang = khac.m_eTinhTrang;
    }
    return *this;
}

PhieuMuon::~PhieuMuon()
{
}

int PhieuMuon::getSoPhieu() const
{
    return this->m_iSoPhieu;
}

const string& PhieuMuon::getMaBanDoc() const
{
    return this->m_strMaBanDoc;
}

const string& PhieuMuon::getMaSach() const
{
    return this->m_strMaSach;
}

const Ngay& PhieuMuon::getNgayMuon() const
{
    return this->m_ngayMuon;
}

const Ngay& PhieuMuon::getNgayPhaiTra() const
{
    return this->m_ngayPhaiTra;
}

TinhTrangPhieu PhieuMuon::getTinhTrang() const
{
    return this->m_eTinhTrang;
}

void PhieuMuon::setSoPhieu(const int iSoPhieu)
{
    this->m_iSoPhieu = iSoPhieu;
}

void PhieuMuon::setMaBanDoc(const string& strMaBanDoc)
{
    this->m_strMaBanDoc = strMaBanDoc;
}

void PhieuMuon::setMaSach(const string& strMaSach)
{
    this->m_strMaSach = strMaSach;
}

void PhieuMuon::setNgayMuon(const Ngay& ngayMuon)
{
    this->m_ngayMuon = ngayMuon;
}

void PhieuMuon::setNgayPhaiTra(const Ngay& ngayPhaiTra)
{
    this->m_ngayPhaiTra = ngayPhaiTra;
}

void PhieuMuon::setTinhTrang(const TinhTrangPhieu eTinhTrang)
{
    this->m_eTinhTrang = eTinhTrang;
}

bool PhieuMuon::operator==(const PhieuMuon& khac) const
{
    return (this->m_iSoPhieu == khac.m_iSoPhieu);
}

bool PhieuMuon::operator!=(const PhieuMuon& khac) const
{
    return !(*this == khac);
}

bool PhieuMuon::operator<(const PhieuMuon& khac) const
{
    int iSoSanh = this->m_ngayPhaiTra.soSanhVoi(khac.m_ngayPhaiTra);
    if (iSoSanh != 0)
    {
        return (iSoSanh < 0);
    }
    return (this->m_iSoPhieu < khac.m_iSoPhieu);
}

bool PhieuMuon::operator>(const PhieuMuon& khac) const
{
    return (khac < *this);
}

string PhieuMuon::toString() const
{
    return to_string(this->m_iSoPhieu) + "|" + this->m_strMaBanDoc + "|" +
           this->m_strMaSach + "|" + this->m_ngayMuon.toString() + "|" +
           this->m_ngayPhaiTra.toString() + "|" + to_string(static_cast<int>(this->m_eTinhTrang));
}

long long PhieuMuon::soNgayTre() const
{
    if (this->m_eTinhTrang == PHIEU_DA_TRA)
    {
        return 0;
    }
    long long lTre = Ngay::chenhLechNgay(Ngay::homNay(), this->m_ngayPhaiTra);
    return (lTre > 0) ? lTre : 0;
}

bool PhieuMuon::docTuDongFile(const string& strDong, PhieuMuon& ketQua)
{
    vector<string> vecTruong = ChuoiTienIch::tachChuoi(strDong, '|');
    if (static_cast<int>(vecTruong.size()) != SO_TRUONG_PHIEU_MUON)
    {
        return false;
    }

    string strLoi = "";
    long long lSoPhieu = 0;
    string strMaBanDoc = "";
    string strMaSach = "";
    long long lTinhTrang = 0;
    Ngay ngayMuon;
    Ngay ngayTra;

    if (!ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[0], "Số phiếu", 1, SO_PHIEU_TOI_DA,
                                                  lSoPhieu, strLoi) ||
        !ChuoiTienIch::kiemTraMaHopLe(vecTruong[1], "Mã bạn đọc", strMaBanDoc, strLoi) ||
        !ChuoiTienIch::kiemTraMaHopLe(vecTruong[2], "Mã sách", strMaSach, strLoi) ||
        !ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[5], "Tình trạng phiếu", 0, 1,
                                                  lTinhTrang, strLoi))
    {
        return false;
    }
    if (!Ngay::phanTichChuoi(vecTruong[3], ngayMuon) ||
        !Ngay::phanTichChuoi(vecTruong[4], ngayTra) ||
        ngayTra < ngayMuon)
    {
        return false;
    }

    TinhTrangPhieu eTinhTrang = (lTinhTrang == 0) ? PHIEU_DA_TRA : PHIEU_DANG_MUON;
    ketQua = PhieuMuon(static_cast<int>(lSoPhieu), strMaBanDoc, strMaSach,
                       ngayMuon, ngayTra, eTinhTrang);
    return true;
}

ostream& operator<<(ostream& os, const PhieuMuon& phieu)
{
    os << phieu.toString();
    return os;
}
