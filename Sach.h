#ifndef SACH_H_INCLUDED_
#define SACH_H_INCLUDED_

#include <ostream>
#include <string>

#include "Ngay.h"

class Sach
{
public:
    Sach();
    Sach(const std::string& strMaSach, const std::string& strTenSach,
         const std::string& strTacGia, const std::string& strNhaXuatBan,
         const long long lGiaBan, const int iNamPhatHanh, const int iSoTrang,
         const Ngay& ngayNhapKho, const int iTinhTrang);
    Sach(const Sach& khac);
    Sach& operator=(const Sach& khac);
    ~Sach();

    const std::string& getMaSach() const;
    const std::string& getTenSach() const;
    const std::string& getTacGia() const;
    const std::string& getNhaXuatBan() const;
    long long getGiaBan() const;
    int getNamPhatHanh() const;
    int getSoTrang() const;
    const Ngay& getNgayNhapKho() const;
    int getTinhTrang() const;

    void setMaSach(const std::string& strMaSach);
    void setTenSach(const std::string& strTenSach);
    void setTacGia(const std::string& strTacGia);
    void setNhaXuatBan(const std::string& strNhaXuatBan);
    void setGiaBan(const long long lGiaBan);
    void setNamPhatHanh(const int iNamPhatHanh);
    void setSoTrang(const int iSoTrang);
    void setNgayNhapKho(const Ngay& ngayNhapKho);
    void setTinhTrang(const int iTinhTrang);

    bool operator==(const Sach& khac) const;
    bool operator!=(const Sach& khac) const;
    bool operator<(const Sach& khac) const;
    bool operator>(const Sach& khac) const;

    // Chuyen thong tin sach thanh 1 dong luu file Sach.txt
    std::string toString() const;

    // Doc 1 dong tu file Sach.txt va kiem tra hop le
    static bool docTuDongFile(const std::string& strDong, Sach& sachKetQua,
                              std::string& strThongBaoLoi);

    static bool dungTruocTheoGiaTang(const Sach& sachTrai, const Sach& sachPhai);
    static bool dungTruocTheoNamGiam(const Sach& sachTrai, const Sach& sachPhai);
    bool khopTuKhoa(const std::string& strTuKhoaThuong) const;

    friend std::ostream& operator<<(std::ostream& os, const Sach& sach);

private:
    std::string m_strMaSach;
    std::string m_strTenSach;
    std::string m_strTacGia;
    std::string m_strNhaXuatBan;
    long long m_lGiaBan;
    int m_iNamPhatHanh;
    int m_iSoTrang;
    Ngay m_ngayNhapKho;
    int m_iTinhTrang;
};

#endif
