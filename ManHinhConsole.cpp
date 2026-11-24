#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "ManHinhConsole.h"

#include <conio.h>
#include <io.h>
#include <windows.h>

#include <cstdlib>
#include <iostream>

#include "ChuoiTienIch.h"
#include "HangSoThuVien.h"

using namespace std;

void ManHinhConsole::khoiTao()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

bool ManHinhConsole::laCheDoTuongTac()
{
    return (_isatty(_fileno(stdin)) != 0);
}

void ManHinhConsole::tamNghiMs(const int iSoMiliGiay)
{
    Sleep(static_cast<DWORD>(iSoMiliGiay));
}

void ManHinhConsole::xoaManHinh()
{
    if (_isatty(_fileno(stdout)) != 0)
    {
        system("cls");
    }
    else
    {
        cout << "\n";
    }
}

void ManHinhConsole::datMau(const MauChu eMau)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(eMau));
}

void ManHinhConsole::inChuMau(const string& strNoiDung, const MauChu eMau)
{
    ManHinhConsole::datMau(eMau);
    cout << strNoiDung;
    ManHinhConsole::datMau(MAU_MAC_DINH);
}

void ManHinhConsole::baoLoi(const string& strThongBao)
{
    ManHinhConsole::inChuMau("[LỖI] " + strThongBao + "\n", MAU_DO);
}

void ManHinhConsole::baoThanhCong(const string& strThongBao)
{
    ManHinhConsole::inChuMau("[OK] " + strThongBao + "\n", MAU_XANH_LA);
}

void ManHinhConsole::baoCanhBao(const string& strThongBao)
{
    ManHinhConsole::inChuMau("[!] " + strThongBao + "\n", MAU_VANG);
}

void ManHinhConsole::baoLoiVaHuy(const string& strThongBao)
{
    ManHinhConsole::baoLoi(strThongBao);
    ManHinhConsole::baoCanhBao("Đã hủy chức năng đang thực hiện.");
}

void ManHinhConsole::inTieuDeMuc(const string& strTieuDe)
{
    const size_t DO_RONG_CAN = static_cast<size_t>(DO_RONG_BANNER + 2);
    cout << "\n";
    ManHinhConsole::inChuMau(ChuoiTienIch::canGiua("=== " + strTieuDe + " ===", DO_RONG_CAN) +
                                 "\n\n",
                             MAU_TIEU_DE);
}

void ManHinhConsole::inBannerThuVien()
{
    string strDuongKe = ManHinhConsole::lapKyTu("─", DO_RONG_BANNER);
    ManHinhConsole::inChuMau("╭" + strDuongKe + "╮\n", MAU_VIEN);

    ManHinhConsole::inVienDoc();
    ManHinhConsole::inChuMau(
        ChuoiTienIch::canGiua("HỆ THỐNG QUẢN LÝ THƯ VIỆN", static_cast<size_t>(DO_RONG_BANNER)),
        MAU_TIEU_DE);
    ManHinhConsole::inVienDoc();
    cout << "\n";

    ManHinhConsole::inVienDoc();
    ManHinhConsole::inChuMau(
        ChuoiTienIch::canGiua("Quản lý Sách  •  Bạn đọc  •  Phiếu mượn",
                              static_cast<size_t>(DO_RONG_BANNER)),
        MAU_XAM);
    ManHinhConsole::inVienDoc();
    cout << "\n";

    ManHinhConsole::inChuMau("╰" + strDuongKe + "╯\n", MAU_VIEN);
}

void ManHinhConsole::inKhungDangNhap()
{
    cout << "\n";
    ManHinhConsole::inChuMau("   * * * * * * * * * * * * * * * * * * * * *\n", MAU_VANG);
    ManHinhConsole::inChuMau("   *", MAU_VANG);
    ManHinhConsole::inChuMau("           DANG NHAP HE THONG          ", MAU_XANH_LA);
    ManHinhConsole::inChuMau("*\n", MAU_VANG);
    ManHinhConsole::inChuMau("   * * * * * * * * * * * * * * * * * * * * *\n", MAU_VANG);
    ManHinhConsole::inChuMau("   (Nhấn ESC để thoát | Nhập sai tối đa 3 lần)\n\n", MAU_XAM);
}

void ManHinhConsole::inMenu(const string& strTenMenu, const vector<string>& vecMuc,
                            const string& strMucThoat)
{
    ManHinhConsole::inChuMau("===== " + strTenMenu + " =====\n", MAU_TIM);
    for (size_t iChiSo = 0; iChiSo < vecMuc.size(); ++iChiSo)
    {
        ManHinhConsole::inChuMau("[" + to_string(iChiSo + 1) + "] ", MAU_VANG);
        cout << vecMuc[iChiSo] << "\n";
    }
    ManHinhConsole::inChuMau("[0] ", MAU_DO);
    cout << strMucThoat << "\n";
}

void ManHinhConsole::inDauBang(const int mangDoRong[], const char* const mangTieuDe[],
                               const bool mangCanPhai[], const int iSoCot)
{
    ManHinhConsole::inDuongKeBang(mangDoRong, iSoCot, "╭", "┬", "╮");
    ManHinhConsole::inVienDoc();
    for (int iCot = 0; iCot < iSoCot; ++iCot)
    {
        size_t iDoRongCot = static_cast<size_t>(mangDoRong[iCot]);
        string strO = mangCanPhai[iCot]
                          ? ChuoiTienIch::canPhai(mangTieuDe[iCot], iDoRongCot)
                          : ChuoiTienIch::canTrai(mangTieuDe[iCot], iDoRongCot);
        ManHinhConsole::inO(strO, MAU_TIM);
        ManHinhConsole::inVienDoc();
    }
    cout << "\n";
    ManHinhConsole::inDuongKeBang(mangDoRong, iSoCot, "├", "┼", "┤");
}

void ManHinhConsole::inChanBang(const int mangDoRong[], const int iSoCot)
{
    ManHinhConsole::inDuongKeBang(mangDoRong, iSoCot, "╰", "┴", "╯");
}

void ManHinhConsole::inVienDoc()
{
    ManHinhConsole::inChuMau("│", MAU_VIEN);
}

void ManHinhConsole::inO(const string& strNoiDung, const MauChu eMau)
{
    cout << " ";
    ManHinhConsole::inChuMau(strNoiDung, eMau);
    cout << " ";
}

bool ManHinhConsole::docDong(const string& strNhan, string& strKetQua)
{
    cout << strNhan;
    cout.flush();
    if (!getline(cin, strKetQua))
    {
        strKetQua.clear();
        return false;
    }
    strKetQua = ChuoiTienIch::catKhoangTrang(strKetQua);
    return true;
}

bool ManHinhConsole::xacNhan(const string& strCauHoi)
{
    while (!cin.eof())
    {
        string strTraLoi = "";
        if (!ManHinhConsole::docDong(strCauHoi + " (y/n): ", strTraLoi))
        {
            return false;
        }
        strTraLoi = ChuoiTienIch::inThuongAscii(strTraLoi);
        if (strTraLoi == "y" || strTraLoi == "c")
        {
            return true;
        }
        if (strTraLoi == "n" || strTraLoi == "k")
        {
            return false;
        }
        ManHinhConsole::baoLoi("Vui lòng chỉ nhập 'y' (đồng ý) hoặc 'n' (không).");
    }
    return false;
}

bool ManHinhConsole::hoiTiepTucChuongTrinh()
{
    if (cin.eof())
    {
        return false;
    }
    cout << "\n";
    while (!cin.eof())
    {
        string strTraLoi = "";
        if (!ManHinhConsole::docDong(
                "Bạn có muốn thực hiện chức năng khác? (y: Tiếp tục / n: Kết thúc): ",
                strTraLoi))
        {
            return false;
        }
        strTraLoi = ChuoiTienIch::inThuongAscii(strTraLoi);
        if (strTraLoi == "y" || strTraLoi == "c")
        {
            return true;
        }
        if (strTraLoi == "n" || strTraLoi == "k")
        {
            return false;
        }
        ManHinhConsole::baoLoi("Chỉ nhập 'y' (tiếp tục) hoặc 'n' (kết thúc chương trình).");
    }
    return false;
}

int ManHinhConsole::chonMucMenu(const int iMucToiDa)
{
    while (!cin.eof())
    {
        string strNhap = "";
        if (!ManHinhConsole::docDong("\nChọn chức năng (0-" + to_string(iMucToiDa) + "): ",
                                     strNhap))
        {
            return 0;
        }
        if (ChuoiTienIch::laSoNguyenInt(strNhap))
        {
            int iGiaTri = stoi(strNhap);
            if (iGiaTri >= 0 && iGiaTri <= iMucToiDa)
            {
                return iGiaTri;
            }
        }
        ManHinhConsole::baoLoi("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0 đến " +
                               to_string(iMucToiDa) + ".");
    }
    return 0;
}

bool ManHinhConsole::nhapTruongDangNhap(const string& strNhan, string& strKetQua,
                                        const bool bAnMatKhau)
{
    ManHinhConsole::inChuMau(strNhan, MAU_XANH_LA);
    cout.flush();
    strKetQua.clear();

    if (!ManHinhConsole::laCheDoTuongTac())
    {
        if (!getline(cin, strKetQua))
        {
            return false;
        }
        strKetQua = ChuoiTienIch::catKhoangTrang(strKetQua);
        return (strKetQua != "ESC");
    }

    ManHinhConsole::datMau(MAU_TRANG);
    while (true)
    {
        int iPhim = _getch();
        if (iPhim == PHIM_MO_RONG_0 || iPhim == PHIM_MO_RONG_224)
        {
            _getch();
            continue;
        }
        if (iPhim == MA_PHIM_ESC || iPhim == MA_PHIM_CTRL_C)
        {
            ManHinhConsole::datMau(MAU_MAC_DINH);
            cout << "\n";
            return false;
        }
        if (iPhim == MA_PHIM_ENTER_CR || iPhim == MA_PHIM_ENTER_LF)
        {
            ManHinhConsole::datMau(MAU_MAC_DINH);
            cout << "\n";
            return true;
        }
        if (iPhim == MA_PHIM_BACKSPACE || iPhim == MA_PHIM_XOA_DEL)
        {
            if (!strKetQua.empty())
            {
                strKetQua.erase(strKetQua.size() - 1);
                cout << "\b \b";
                cout.flush();
            }
            continue;
        }
        if (iPhim >= KY_TU_ASCII_DAU && iPhim <= KY_TU_ASCII_CUOI &&
            static_cast<int>(strKetQua.size()) < DO_DAI_MAT_KHAU_TOI_DA)
        {
            char cKyTu = static_cast<char>(iPhim);
            strKetQua += cKyTu;
            cout << (bAnMatKhau ? '*' : cKyTu);
            cout.flush();
        }
    }
}

void ManHinhConsole::choNhanEnter(const string& strNhan)
{
    cout << strNhan;
    cout.flush();
    string strBoQua = "";
    getline(cin, strBoQua);
}

string ManHinhConsole::lapKyTu(const string& strMau, const int iSoLan)
{
    string strKetQua = "";
    for (int iDem = 0; iDem < iSoLan; ++iDem)
    {
        strKetQua += strMau;
    }
    return strKetQua;
}

void ManHinhConsole::inDuongKeBang(const int mangDoRong[], const int iSoCot,
                                   const char* szGocTrai, const char* szGiua,
                                   const char* szGocPhai)
{
    ManHinhConsole::datMau(MAU_VIEN);
    cout << szGocTrai;
    for (int iCot = 0; iCot < iSoCot; ++iCot)
    {
        cout << ManHinhConsole::lapKyTu("─", mangDoRong[iCot] + 2)
             << (iCot < iSoCot - 1 ? szGiua : szGocPhai);
    }
    ManHinhConsole::datMau(MAU_MAC_DINH);
    cout << "\n";
}
