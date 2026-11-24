#include "Sach.h"

#include <vector>

#include "ChuoiTienIch.h"
#include "HangSoThuVien.h"

using namespace std;

Sach::Sach()
    : m_strMaSach(""), m_strTenSach(""), m_strTacGia(""), m_strNhaXuatBan(""),
      m_lGiaBan(0), m_iNamPhatHanh(0), m_iSoTrang(0), m_ngayNhapKho(), m_iTinhTrang(0)
{
}

Sach::Sach(const string& strMaSach, const string& strTenSach, const string& strTacGia,
           const string& strNhaXuatBan, const long long lGiaBan, const int iNamPhatHanh,
           const int iSoTrang, const Ngay& ngayNhapKho, const int iTinhTrang)
    : m_strMaSach(strMaSach), m_strTenSach(strTenSach), m_strTacGia(strTacGia),
      m_strNhaXuatBan(strNhaXuatBan), m_lGiaBan(lGiaBan), m_iNamPhatHanh(iNamPhatHanh),
      m_iSoTrang(iSoTrang), m_ngayNhapKho(ngayNhapKho), m_iTinhTrang(iTinhTrang)
{
}

Sach::Sach(const Sach& khac)
    : m_strMaSach(khac.m_strMaSach), m_strTenSach(khac.m_strTenSach),
      m_strTacGia(khac.m_strTacGia), m_strNhaXuatBan(khac.m_strNhaXuatBan),
      m_lGiaBan(khac.m_lGiaBan), m_iNamPhatHanh(khac.m_iNamPhatHanh),
      m_iSoTrang(khac.m_iSoTrang), m_ngayNhapKho(khac.m_ngayNhapKho),
      m_iTinhTrang(khac.m_iTinhTrang)
{
}

Sach& Sach::operator=(const Sach& khac)
{
    if (this != &khac)
    {
        this->m_strMaSach = khac.m_strMaSach;
        this->m_strTenSach = khac.m_strTenSach;
        this->m_strTacGia = khac.m_strTacGia;
        this->m_strNhaXuatBan = khac.m_strNhaXuatBan;
        this->m_lGiaBan = khac.m_lGiaBan;
        this->m_iNamPhatHanh = khac.m_iNamPhatHanh;
        this->m_iSoTrang = khac.m_iSoTrang;
        this->m_ngayNhapKho = khac.m_ngayNhapKho;
        this->m_iTinhTrang = khac.m_iTinhTrang;
    }
    return *this;
}

Sach::~Sach()
{
}

const string& Sach::getMaSach() const
{
    return this->m_strMaSach;
}

const string& Sach::getTenSach() const
{
    return this->m_strTenSach;
}

const string& Sach::getTacGia() const
{
    return this->m_strTacGia;
}

const string& Sach::getNhaXuatBan() const
{
    return this->m_strNhaXuatBan;
}

long long Sach::getGiaBan() const
{
    return this->m_lGiaBan;
}

int Sach::getNamPhatHanh() const
{
    return this->m_iNamPhatHanh;
}

int Sach::getSoTrang() const
{
    return this->m_iSoTrang;
}

const Ngay& Sach::getNgayNhapKho() const
{
    return this->m_ngayNhapKho;
}

int Sach::getTinhTrang() const
{
    return this->m_iTinhTrang;
}

void Sach::setMaSach(const string& strMaSach)
{
    this->m_strMaSach = strMaSach;
}

void Sach::setTenSach(const string& strTenSach)
{
    this->m_strTenSach = strTenSach;
}

void Sach::setTacGia(const string& strTacGia)
{
    this->m_strTacGia = strTacGia;
}

void Sach::setNhaXuatBan(const string& strNhaXuatBan)
{
    this->m_strNhaXuatBan = strNhaXuatBan;
}

void Sach::setGiaBan(const long long lGiaBan)
{
    this->m_lGiaBan = lGiaBan;
}

void Sach::setNamPhatHanh(const int iNamPhatHanh)
{
    this->m_iNamPhatHanh = iNamPhatHanh;
}

void Sach::setSoTrang(const int iSoTrang)
{
    this->m_iSoTrang = iSoTrang;
}

void Sach::setNgayNhapKho(const Ngay& ngayNhapKho)
{
    this->m_ngayNhapKho = ngayNhapKho;
}

void Sach::setTinhTrang(const int iTinhTrang)
{
    this->m_iTinhTrang = iTinhTrang;
}

bool Sach::operator==(const Sach& khac) const
{
    return (this->m_strMaSach == khac.m_strMaSach);
}

bool Sach::operator!=(const Sach& khac) const
{
    return !(*this == khac);
}

bool Sach::operator<(const Sach& khac) const
{
    return (this->m_strMaSach < khac.m_strMaSach);
}

bool Sach::operator>(const Sach& khac) const
{
    return (this->m_strMaSach > khac.m_strMaSach);
}

string Sach::toString() const
{
    return this->m_strMaSach + "|" + this->m_strTenSach + "|" + this->m_strTacGia + "|" +
           this->m_strNhaXuatBan + "|" + to_string(this->m_lGiaBan) + "|" +
           to_string(this->m_iNamPhatHanh) + "|" + to_string(this->m_iSoTrang) + "|" +
           this->m_ngayNhapKho.toString() + "|" + to_string(this->m_iTinhTrang);
}

bool Sach::docTuDongFile(const string& strDong, Sach& sachKetQua, string& strThongBaoLoi)
{
    vector<string> vecTruong = ChuoiTienIch::tachChuoi(strDong, '|');
    if (static_cast<int>(vecTruong.size()) != SO_TRUONG_SACH)
    {
        strThongBaoLoi = "Sai số trường dữ liệu (cần 9 trường)";
        return false;
    }

    string strMa = "";
    string strTen = "";
    string strTacGia = "";
    string strNxb = "";
    long long lGia = 0;
    long long lNam = 0;
    long long lTrang = 0;
    long long lTinhTrang = 0;
    Ngay ngayNhap;

    if (!ChuoiTienIch::kiemTraMaHopLe(vecTruong[0], "Mã sách", strMa, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraChuoiHopLe(vecTruong[1], "Tên sách", DO_DAI_TEN_SACH_TOI_DA,
                                         strTen, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraTenNguoi(vecTruong[2], "Tác giả", DO_DAI_TAC_GIA_TOI_DA,
                                       strTacGia, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraChuoiHopLe(vecTruong[3], "Nhà xuất bản", DO_DAI_NXB_TOI_DA,
                                         strNxb, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[4], "Giá bán", GIA_SACH_TOI_THIEU,
                                                  GIA_SACH_TOI_DA, lGia, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[5], "Năm phát hành",
                                                  NAM_PHAT_HANH_TOI_THIEU, Ngay::homNay().getNam(),
                                                  lNam, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[6], "Số trang", SO_TRANG_TOI_THIEU,
                                                  SO_TRANG_TOI_DA, lTrang, strThongBaoLoi) ||
        !ChuoiTienIch::kiemTraSoNguyenTrongKhoang(vecTruong[8], "Tình trạng", 0, SO_PHIEU_TOI_DA,
                                                  lTinhTrang, strThongBaoLoi))
    {
        return false;
    }

    if (!Ngay::phanTichChuoi(vecTruong[7], ngayNhap))
    {
        strThongBaoLoi = "Ngày nhập kho sai định dạng dd/mm/yyyy";
        return false;
    }
    if (ngayNhap > Ngay::homNay() || ngayNhap.getNam() < static_cast<int>(lNam))
    {
        strThongBaoLoi = "Ngày nhập kho không hợp lệ";
        return false;
    }

    sachKetQua = Sach(strMa, strTen, strTacGia, strNxb, lGia, static_cast<int>(lNam),
                      static_cast<int>(lTrang), ngayNhap, static_cast<int>(lTinhTrang));
    return true;
}

bool Sach::dungTruocTheoGiaTang(const Sach& sachTrai, const Sach& sachPhai)
{
    if (sachTrai.m_lGiaBan != sachPhai.m_lGiaBan)
    {
        return (sachTrai.m_lGiaBan < sachPhai.m_lGiaBan);
    }
    return (sachTrai.m_strMaSach < sachPhai.m_strMaSach);
}

bool Sach::dungTruocTheoNamGiam(const Sach& sachTrai, const Sach& sachPhai)
{
    if (sachTrai.m_iNamPhatHanh != sachPhai.m_iNamPhatHanh)
    {
        return (sachTrai.m_iNamPhatHanh > sachPhai.m_iNamPhatHanh);
    }
    return (sachTrai.m_strMaSach < sachPhai.m_strMaSach);
}

bool Sach::khopTuKhoa(const string& strTuKhoaThuong) const
{
    if (ChuoiTienIch::inThuongAscii(this->m_strMaSach).find(strTuKhoaThuong) != string::npos)
    {
        return true;
    }
    if (ChuoiTienIch::inThuongAscii(this->m_strTenSach).find(strTuKhoaThuong) != string::npos)
    {
        return true;
    }
    if (ChuoiTienIch::inThuongAscii(this->m_strTacGia).find(strTuKhoaThuong) != string::npos)
    {
        return true;
    }
    return (ChuoiTienIch::inThuongAscii(this->m_strNhaXuatBan).find(strTuKhoaThuong) !=
            string::npos);
}

ostream& operator<<(ostream& os, const Sach& sach)
{
    os << sach.toString();
    return os;
}
