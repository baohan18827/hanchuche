#include "TaiKhoanNV.h"

#include <sstream>
#include <vector>

#include "ChuoiTienIch.h"
#include "HangSoThuVien.h"

using namespace std;

TaiKhoanNV::TaiKhoanNV() : m_strUser(""), m_strPass("")
{
}

TaiKhoanNV::TaiKhoanNV(const string& strUser, const string& strPass)
    : m_strUser(strUser), m_strPass(strPass)
{
}

TaiKhoanNV::TaiKhoanNV(const TaiKhoanNV& khac)
    : m_strUser(khac.m_strUser), m_strPass(khac.m_strPass)
{
}

TaiKhoanNV& TaiKhoanNV::operator=(const TaiKhoanNV& khac)
{
    if (this != &khac)
    {
        this->m_strUser = khac.m_strUser;
        this->m_strPass = khac.m_strPass;
    }
    return *this;
}

TaiKhoanNV::~TaiKhoanNV()
{
}

const string& TaiKhoanNV::getUser() const
{
    return this->m_strUser;
}

const string& TaiKhoanNV::getPass() const
{
    return this->m_strPass;
}

void TaiKhoanNV::setUser(const string& strUser)
{
    this->m_strUser = strUser;
}

void TaiKhoanNV::setPass(const string& strPass)
{
    this->m_strPass = strPass;
}

bool TaiKhoanNV::operator==(const TaiKhoanNV& khac) const
{
    return (this->m_strUser == khac.m_strUser);
}

bool TaiKhoanNV::operator!=(const TaiKhoanNV& khac) const
{
    return !(*this == khac);
}

bool TaiKhoanNV::khop(const string& strUser, const string& strPass) const
{
    return (this->m_strUser == strUser && this->m_strPass == strPass);
}

bool TaiKhoanNV::docTuDongFile(const string& strDong, TaiKhoanNV& ketQua)
{
    string strUser = "";
    string strPass = "";
    if (strDong.find('|') != string::npos)
    {
        vector<string> vecPhan = ChuoiTienIch::tachChuoi(strDong, '|');
        if (static_cast<int>(vecPhan.size()) != SO_TRUONG_ADMIN)
        {
            return false;
        }
        strUser = ChuoiTienIch::catKhoangTrang(vecPhan[0]);
        strPass = ChuoiTienIch::catKhoangTrang(vecPhan[1]);
    }
    else
    {
        istringstream issDong(strDong);
        if (!(issDong >> strUser >> strPass))
        {
            return false;
        }
    }

    if (strUser.empty() || strPass.empty())
    {
        return false;
    }
    ketQua = TaiKhoanNV(strUser, strPass);
    return true;
}

ostream& operator<<(ostream& os, const TaiKhoanNV& taiKhoan)
{
    os << taiKhoan.m_strUser;
    return os;
}
