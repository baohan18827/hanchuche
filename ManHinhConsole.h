#ifndef MANHINHCONSOLE_H_INCLUDED_
#define MANHINHCONSOLE_H_INCLUDED_

#include <string>
#include <vector>

class ManHinhConsole
{
public:
    enum MauChu
    {
        MAU_MAC_DINH = 7,
        MAU_XAM = 8,
        MAU_XANH_LA = 10,
        MAU_TIEU_DE = 11,
        MAU_DO = 12,
        MAU_TIM = 13,
        MAU_VANG = 14,
        MAU_TRANG = 15,
        MAU_VIEN = 3
    };

    // Khoi tao ma hoa UTF-8 cho man hinh Console Windows
    static void khoiTao();

    static bool laCheDoTuongTac();
    static void tamNghiMs(const int iSoMiliGiay);
    static void xoaManHinh();
    static void datMau(const MauChu eMau);
    static void inChuMau(const std::string& strNoiDung, const MauChu eMau);

    static void baoLoi(const std::string& strThongBao);
    static void baoThanhCong(const std::string& strThongBao);
    static void baoCanhBao(const std::string& strThongBao);
    static void baoLoiVaHuy(const std::string& strThongBao);

    static void inTieuDeMuc(const std::string& strTieuDe);
    static void inBannerThuVien();
    static void inKhungDangNhap();
    static void inMenu(const std::string& strTenMenu,
                       const std::vector<std::string>& vecMuc,
                       const std::string& strMucThoat);

    static void inDauBang(const int mangDoRong[], const char* const mangTieuDe[],
                          const bool mangCanPhai[], const int iSoCot);
    static void inChanBang(const int mangDoRong[], const int iSoCot);
    static void inVienDoc();
    static void inO(const std::string& strNoiDung, const MauChu eMau);

    static bool docDong(const std::string& strNhan, std::string& strKetQua);
    static bool xacNhan(const std::string& strCauHoi);
    static bool hoiTiepTucChuongTrinh();
    static int chonMucMenu(const int iMucToiDa);

    // Nhap user/password co an dau '*' va ho tro phim ESC
    static bool nhapTruongDangNhap(const std::string& strNhan, std::string& strKetQua,
                                   const bool bAnMatKhau);

    static void choNhanEnter(const std::string& strNhan);

private:
    static std::string lapKyTu(const std::string& strMau, const int iSoLan);
    static void inDuongKeBang(const int mangDoRong[], const int iSoCot,
                              const char* szGocTrai, const char* szGiua, const char* szGocPhai);
};

#endif
