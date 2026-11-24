#ifndef CHUOI_TIEN_ICH_H_INCLUDED_
#define CHUOI_TIEN_ICH_H_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>

class ChuoiTienIch
{
public:
    // Loai bo BOM UTF-8 va khoang trang o hai dau chuoi
    static std::string catKhoangTrang(const std::string& strChuoi);

    static std::string inHoaAscii(const std::string& strChuoi);
    static std::string inThuongAscii(const std::string& strChuoi);
    static std::vector<std::string> tachChuoi(const std::string& strChuoi, const char cKyTuCach);

    static bool laDayChuSo(const std::string& strChuoi);
    static bool laSoNguyenInt(const std::string& strChuoi);
    static bool kiemTraMaHopLe(const std::string& strNhap, const std::string& strTenTruong,
                               std::string& strMaChuan, std::string& strThongBaoLoi);
    static bool kiemTraChuoiHopLe(const std::string& strNhap, const std::string& strTenTruong,
                                  const size_t iDoDaiToiDa, std::string& strKetQua,
                                  std::string& strThongBaoLoi);
    static bool kiemTraTenNguoi(const std::string& strNhap, const std::string& strTenTruong,
                                const size_t iDoDaiToiDa, std::string& strKetQua,
                                std::string& strThongBaoLoi);
    static bool kiemTraSoNguyenTrongKhoang(const std::string& strNhap,
                                           const std::string& strTenTruong,
                                           const long long lCanDuoi, const long long lCanTren,
                                           long long& lKetQua, std::string& strThongBaoLoi);

    // Dem so ky tu hien thi cua chuoi UTF-8 de can bang
    static size_t doDaiHienThi(const std::string& strChuoi);

    static std::string catVuaO(const std::string& strChuoi, const size_t iDoRong);
    static std::string canTrai(const std::string& strChuoi, const size_t iDoRong);
    static std::string canPhai(const std::string& strChuoi, const size_t iDoRong);
    static std::string canGiua(const std::string& strChuoi, const size_t iDoRong);
    static std::string dinhDangTien(const long long lSoTien);
};

#endif
