#ifndef PHIEUMUON_H_INCLUDED_
#define PHIEUMUON_H_INCLUDED_

#include <ostream>
#include <string>

#include "HangSoThuVien.h"
#include "Ngay.h"

class PhieuMuon
{
public:
    PhieuMuon();
    explicit PhieuMuon(const int iSoPhieu);
    PhieuMuon(const int iSoPhieu, const std::string& strMaBanDoc, const std::string& strMaSach,
              const Ngay& ngayMuon, const Ngay& ngayPhaiTra, const TinhTrangPhieu eTinhTrang);
    PhieuMuon(const PhieuMuon& khac);
    PhieuMuon& operator=(const PhieuMuon& khac);
    ~PhieuMuon();

    int getSoPhieu() const;
    const std::string& getMaBanDoc() const;
    const std::string& getMaSach() const;
    const Ngay& getNgayMuon() const;
    const Ngay& getNgayPhaiTra() const;
    TinhTrangPhieu getTinhTrang() const;

    void setSoPhieu(const int iSoPhieu);
    void setMaBanDoc(const std::string& strMaBanDoc);
    void setMaSach(const std::string& strMaSach);
    void setNgayMuon(const Ngay& ngayMuon);
    void setNgayPhaiTra(const Ngay& ngayPhaiTra);
    void setTinhTrang(const TinhTrangPhieu eTinhTrang);

    bool operator==(const PhieuMuon& khac) const;
    bool operator!=(const PhieuMuon& khac) const;
    bool operator<(const PhieuMuon& khac) const;
    bool operator>(const PhieuMuon& khac) const;

    std::string toString() const;
    long long soNgayTre() const;

    // Doc 1 dong tu file PhieuMuon.txt va kiem tra hop le
    static bool docTuDongFile(const std::string& strDong, PhieuMuon& ketQua);

    friend std::ostream& operator<<(std::ostream& os, const PhieuMuon& phieu);

private:
    int m_iSoPhieu;
    std::string m_strMaBanDoc;
    std::string m_strMaSach;
    Ngay m_ngayMuon;
    Ngay m_ngayPhaiTra;
    TinhTrangPhieu m_eTinhTrang;
};

#endif
