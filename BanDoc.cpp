#include "BanDoc.h"

#include <vector>

#include "ChuoiTienIch.h"
#include "HangSoThuVien.h"

using namespace std;

BanDoc::BanDoc() : m_strMaBanDoc(""), m_strHoTen(""), m_ngayDangKy()
{
}

BanDoc::BanDoc(const string& strMaBanDoc)
    : m_strMaBanDoc(strMaBanDoc), m_strHoTen(""), m_ngayDangKy()
{
}

BanDoc::BanDoc(const string& strMaBanDoc, const string& strHoTen, const Ngay& ngayDangKy)
    : m_strMaBanDoc(strMaBanDoc), m_strHoTen(strHoTen), m_ngayDangKy(ngayDangKy)
{
}

BanDoc::BanDoc(const BanDoc& khac)
    : m_strMaBanDoc(khac.m_strMaBanDoc), m_strHoTen(khac.m_strHoTen),
      m_ngayDangKy(khac.m_ngayDangKy)
{
}

BanDoc& BanDoc::operator=(const BanDoc& khac)
{
    if (this != &khac)
    {
        this->m_strMaBanDoc = khac.m_strMaBanDoc;
        this->m_strHoTen = khac.m_strHoTen;
        this->m_ngayDangKy = khac.m_ngayDangKy;
    }
    return *this;
}

BanDoc::~BanDoc()
{
}

const string& BanDoc::getMaBanDoc() const
{
    return this->m_strMaBanDoc;
}

const string& BanDoc::getHoTen() const
{
    return this->m_strHoTen;
}

const Ngay& BanDoc::getNgayDangKy() const
{
    return this->m_ngayDangKy;
}

void BanDoc::setMaBanDoc(const string& strMaBanDoc)
{
    this->m_strMaBanDoc = strMaBanDoc;
}

void BanDoc::setHoTen(const string& strHoTen)
{
    this->m_strHoTen = strHoTen;
}

void BanDoc::setNgayDangKy(const Ngay& ngayDangKy)
{
    this->m_ngayDangKy = ngayDangKy;
}

bool BanDoc::operator==(const BanDoc& khac) const
{
    return (this->m_strMaBanDoc == khac.m_strMaBanDoc);
}

bool BanDoc::operator!=(const BanDoc& khac) const
{
    return !(*this == khac);
}

bool BanDoc::operator<(const BanDoc& khac) const
{
    return (this->m_strMaBanDoc < khac.m_strMaBanDoc);
}

bool BanDoc::operator>(const BanDoc& khac) const
{
    return (this->m_strMaBanDoc > khac.m_strMaBanDoc);
}

string BanDoc::toString() const
{
    return this->m_strMaBanDoc + "|" + this->m_strHoTen + "|" + this->m_ngayDangKy.toString();
}

bool BanDoc::docTuDongFile(const string& strDong, BanDoc& ketQua, string& strThongBaoLoi)
{
    vector<string> vecTruong = ChuoiTienIch::tachChuoi(strDong, '|');
    if (static_cast<int>(vecTruong.size()) != SO_TRUONG_BAN_DOC)
    {
        strThongBaoLoi = "Sai định dạng dòng (cần 3 trường)";
        return false;
    }

    string strMa = "";
    string strHoTen = "";
    Ngay ngayDk;
    if (!ChuoiTienIch::kiemTraMaHopLe(vecTruong[0], "Mã bạn đọc", strMa, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraTenNguoi(vecTruong[1], "Họ tên", DO_DAI_HO_TEN_TOI_DA,
                                       strHoTen, strThongBaoLoi))
    {
        return false;
    }
    if (!Ngay::phanTichChuoi(vecTruong[2], ngayDk) || ngayDk > Ngay::homNay())
    {
        strThongBaoLoi = "Ngày đăng ký không hợp lệ";
        return false;
    }

    ketQua = BanDoc(strMa, strHoTen, ngayDk);
    return true;
}

ostream& operator<<(ostream& os, const BanDoc& banDoc)
{
    os << banDoc.toString();
    return os;
}
