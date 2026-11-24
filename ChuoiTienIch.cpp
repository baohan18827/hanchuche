#include "ChuoiTienIch.h"

#include <algorithm>
#include <cctype>

#include "HangSoThuVien.h"

using namespace std;

string ChuoiTienIch::catKhoangTrang(const string& strChuoi)
{
    const size_t DO_DAI_BOM = 3;
    const unsigned char BOM_0 = 0xEF;
    const unsigned char BOM_1 = 0xBB;
    const unsigned char BOM_2 = 0xBF;

    string strTam = strChuoi;
    if (strTam.size() >= DO_DAI_BOM &&
        static_cast<unsigned char>(strTam[0]) == BOM_0 &&
        static_cast<unsigned char>(strTam[1]) == BOM_1 &&
        static_cast<unsigned char>(strTam[2]) == BOM_2)
    {
        strTam.erase(0, DO_DAI_BOM);
    }

    size_t iDau = strTam.find_first_not_of(" \t\r\n");
    if (iDau == string::npos)
    {
        return "";
    }
    size_t iCuoi = strTam.find_last_not_of(" \t\r\n");
    return strTam.substr(iDau, iCuoi - iDau + 1);
}

string ChuoiTienIch::inHoaAscii(const string& strChuoi)
{
    const unsigned char GIOI_HAN_ASCII = 128;
    string strKetQua = strChuoi;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strKetQua[iViTri]);
        if (cKyTu < GIOI_HAN_ASCII)
        {
            strKetQua[iViTri] = static_cast<char>(toupper(cKyTu));
        }
    }
    return strKetQua;
}

string ChuoiTienIch::inThuongAscii(const string& strChuoi)
{
    const unsigned char GIOI_HAN_ASCII = 128;
    string strKetQua = strChuoi;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strKetQua[iViTri]);
        if (cKyTu < GIOI_HAN_ASCII)
        {
            strKetQua[iViTri] = static_cast<char>(tolower(cKyTu));
        }
    }
    return strKetQua;
}

vector<string> ChuoiTienIch::tachChuoi(const string& strChuoi, const char cKyTuCach)
{
    vector<string> vecKetQua;
    string strHienTai = "";
    for (size_t iViTri = 0; iViTri < strChuoi.size(); ++iViTri)
    {
        if (strChuoi[iViTri] == cKyTuCach)
        {
            vecKetQua.push_back(strHienTai);
            strHienTai = "";
        }
        else
        {
            strHienTai += strChuoi[iViTri];
        }
    }
    vecKetQua.push_back(strHienTai);
    return vecKetQua;
}

bool ChuoiTienIch::laDayChuSo(const string& strChuoi)
{
    if (strChuoi.empty() || static_cast<int>(strChuoi.size()) > SO_CHU_SO_TOI_DA)
    {
        return false;
    }
    for (size_t iViTri = 0; iViTri < strChuoi.size(); ++iViTri)
    {
        if (isdigit(static_cast<unsigned char>(strChuoi[iViTri])) == 0)
        {
            return false;
        }
    }
    return true;
}

bool ChuoiTienIch::laSoNguyenInt(const string& strChuoi)
{
    return (ChuoiTienIch::laDayChuSo(strChuoi) &&
            static_cast<int>(strChuoi.size()) <= SO_CHU_SO_INT_TOI_DA);
}

bool ChuoiTienIch::kiemTraMaHopLe(const string& strNhap, const string& strTenTruong,
                                  string& strMaChuan, string& strThongBaoLoi)
{
    strMaChuan = ChuoiTienIch::inHoaAscii(ChuoiTienIch::catKhoangTrang(strNhap));
    if (strMaChuan.empty())
    {
        strThongBaoLoi = strTenTruong + " không được để trống hoặc chỉ chứa khoảng trắng.";
        return false;
    }
    int iDoDai = static_cast<int>(strMaChuan.size());
    if (iDoDai < DO_DAI_MA_TOI_THIEU || iDoDai > DO_DAI_MA_TOI_DA)
    {
        strThongBaoLoi = strTenTruong + " phải có độ dài từ " + to_string(DO_DAI_MA_TOI_THIEU) +
                         " đến " + to_string(DO_DAI_MA_TOI_DA) + " ký tự.";
        return false;
    }
    for (size_t iViTri = 0; iViTri < strMaChuan.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strMaChuan[iViTri]);
        if (isalnum(cKyTu) == 0 && cKyTu != '_' && cKyTu != '-')
        {
            strThongBaoLoi = strTenTruong + " chỉ được gồm chữ cái, chữ số, '-' hoặc '_'.";
            return false;
        }
    }
    return true;
}

bool ChuoiTienIch::kiemTraChuoiHopLe(const string& strNhap, const string& strTenTruong,
                                     const size_t iDoDaiToiDa, string& strKetQua,
                                     string& strThongBaoLoi)
{
    const unsigned char GIOI_HAN_ASCII = 128;
    strKetQua = ChuoiTienIch::catKhoangTrang(strNhap);
    if (strKetQua.empty())
    {
        strThongBaoLoi = strTenTruong + " không được để trống hoặc chỉ chứa khoảng trắng.";
        return false;
    }
    if (strKetQua.find('|') != string::npos)
    {
        strThongBaoLoi = strTenTruong + " không được chứa ký tự '|'.";
        return false;
    }
    size_t iDoDai = ChuoiTienIch::doDaiHienThi(strKetQua);
    if (static_cast<int>(iDoDai) < DO_DAI_CHUOI_TOI_THIEU || iDoDai > iDoDaiToiDa)
    {
        strThongBaoLoi = strTenTruong + " phải có từ " + to_string(DO_DAI_CHUOI_TOI_THIEU) +
                         " đến " + to_string(iDoDaiToiDa) + " ký tự.";
        return false;
    }

    bool bCoNoiDung = false;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strKetQua[iViTri]);
        if (cKyTu >= GIOI_HAN_ASCII || isalnum(cKyTu) != 0)
        {
            bCoNoiDung = true;
            break;
        }
    }
    if (!bCoNoiDung)
    {
        strThongBaoLoi = strTenTruong + " phải chứa ít nhất một chữ cái hoặc chữ số.";
        return false;
    }
    return true;
}

bool ChuoiTienIch::kiemTraTenNguoi(const string& strNhap, const string& strTenTruong,
                                   const size_t iDoDaiToiDa, string& strKetQua,
                                   string& strThongBaoLoi)
{
    const unsigned char GIOI_HAN_ASCII = 128;
    if (!ChuoiTienIch::kiemTraChuoiHopLe(strNhap, strTenTruong, iDoDaiToiDa,
                                         strKetQua, strThongBaoLoi))
    {
        return false;
    }

    bool bCoChuCai = false;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strKetQua[iViTri]);
        if (cKyTu >= GIOI_HAN_ASCII || isalpha(cKyTu) != 0)
        {
            bCoChuCai = true;
        }
        else if (isdigit(cKyTu) != 0)
        {
            strThongBaoLoi = strTenTruong + " không được chứa chữ số.";
            return false;
        }
        else if (cKyTu != ' ' && cKyTu != '.' && cKyTu != '-')
        {
            strThongBaoLoi = strTenTruong + " không được chứa ký tự đặc biệt.";
            return false;
        }
    }
    if (!bCoChuCai)
    {
        strThongBaoLoi = strTenTruong + " phải chứa chữ cái.";
        return false;
    }
    return true;
}

bool ChuoiTienIch::kiemTraSoNguyenTrongKhoang(const string& strNhap, const string& strTenTruong,
                                              const long long lCanDuoi, const long long lCanTren,
                                              long long& lKetQua, string& strThongBaoLoi)
{
    string strSach = ChuoiTienIch::catKhoangTrang(strNhap);
    if (strSach.empty())
    {
        strThongBaoLoi = strTenTruong + " không được để trống.";
        return false;
    }
    if (strSach[0] == '-')
    {
        strThongBaoLoi = strTenTruong + " không được nhập số âm.";
        return false;
    }
    if (!ChuoiTienIch::laDayChuSo(strSach))
    {
        strThongBaoLoi = strTenTruong + " phải là số nguyên không âm (chỉ gồm chữ số 0-9).";
        return false;
    }
    long long lGiaTri = stoll(strSach);
    if (lGiaTri < lCanDuoi || lGiaTri > lCanTren)
    {
        strThongBaoLoi = strTenTruong + " phải nằm trong khoảng từ " + to_string(lCanDuoi) +
                         " đến " + to_string(lCanTren) + ".";
        return false;
    }
    lKetQua = lGiaTri;
    return true;
}

size_t ChuoiTienIch::doDaiHienThi(const string& strChuoi)
{
    const unsigned char MAT_NA_UTF8 = 0xC0;
    const unsigned char BYTE_TIEP_NOI = 0x80;
    size_t iSoKyTu = 0;
    for (size_t iViTri = 0; iViTri < strChuoi.size(); ++iViTri)
    {
        if ((static_cast<unsigned char>(strChuoi[iViTri]) & MAT_NA_UTF8) != BYTE_TIEP_NOI)
        {
            ++iSoKyTu;
        }
    }
    return iSoKyTu;
}

string ChuoiTienIch::catVuaO(const string& strChuoi, const size_t iDoRong)
{
    const size_t DO_DAI_BA_CHAM = 3;
    const unsigned char MAT_NA_4_BYTE = 0xF8;
    const unsigned char DAU_4_BYTE = 0xF0;
    const unsigned char MAT_NA_3_BYTE = 0xF0;
    const unsigned char DAU_3_BYTE = 0xE0;
    const unsigned char MAT_NA_2_BYTE = 0xE0;
    const unsigned char DAU_2_BYTE = 0xC0;

    if (iDoRong == 0)
    {
        return "";
    }
    if (ChuoiTienIch::doDaiHienThi(strChuoi) <= iDoRong)
    {
        return strChuoi;
    }
    if (iDoRong <= DO_DAI_BA_CHAM)
    {
        return string(iDoRong, '.');
    }

    const size_t SO_KY_TU_GIU = iDoRong - DO_DAI_BA_CHAM;
    string strKetQua = "";
    size_t iDemKyTu = 0;
    size_t iViTri = 0;
    while (iViTri < strChuoi.size() && iDemKyTu < SO_KY_TU_GIU)
    {
        unsigned char cDau = static_cast<unsigned char>(strChuoi[iViTri]);
        size_t iSoByte = 1;
        if ((cDau & MAT_NA_4_BYTE) == DAU_4_BYTE)
        {
            iSoByte = 4;
        }
        else if ((cDau & MAT_NA_3_BYTE) == DAU_3_BYTE)
        {
            iSoByte = 3;
        }
        else if ((cDau & MAT_NA_2_BYTE) == DAU_2_BYTE)
        {
            iSoByte = 2;
        }
        if (iViTri + iSoByte > strChuoi.size())
        {
            break;
        }
        strKetQua += strChuoi.substr(iViTri, iSoByte);
        iViTri += iSoByte;
        ++iDemKyTu;
    }
    return strKetQua + "...";
}

string ChuoiTienIch::canTrai(const string& strChuoi, const size_t iDoRong)
{
    string strCat = ChuoiTienIch::catVuaO(strChuoi, iDoRong);
    size_t iHienTai = ChuoiTienIch::doDaiHienThi(strCat);
    if (iHienTai >= iDoRong)
    {
        return strCat;
    }
    return strCat + string(iDoRong - iHienTai, ' ');
}

string ChuoiTienIch::canPhai(const string& strChuoi, const size_t iDoRong)
{
    string strCat = ChuoiTienIch::catVuaO(strChuoi, iDoRong);
    size_t iHienTai = ChuoiTienIch::doDaiHienThi(strCat);
    if (iHienTai >= iDoRong)
    {
        return strCat;
    }
    return string(iDoRong - iHienTai, ' ') + strCat;
}

string ChuoiTienIch::canGiua(const string& strChuoi, const size_t iDoRong)
{
    string strCat = ChuoiTienIch::catVuaO(strChuoi, iDoRong);
    size_t iHienTai = ChuoiTienIch::doDaiHienThi(strCat);
    if (iHienTai >= iDoRong)
    {
        return strCat;
    }
    size_t iBenTrai = (iDoRong - iHienTai) / 2;
    return string(iBenTrai, ' ') + strCat + string(iDoRong - iHienTai - iBenTrai, ' ');
}

string ChuoiTienIch::dinhDangTien(const long long lSoTien)
{
    const int BUOC_PHAN_NHOM = 3;
    string strSo = to_string(lSoTien);
    string strKetQua = "";
    int iDem = 0;
    for (int iViTri = static_cast<int>(strSo.size()) - 1; iViTri >= 0; --iViTri)
    {
        strKetQua += strSo[iViTri];
        ++iDem;
        if (iDem % BUOC_PHAN_NHOM == 0 && iViTri > 0)
        {
            strKetQua += '.';
        }
    }
    reverse(strKetQua.begin(), strKetQua.end());
    return strKetQua;
}
