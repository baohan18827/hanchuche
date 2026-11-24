#ifndef TAIKHOANNV_H_INCLUDED_
#define TAIKHOANNV_H_INCLUDED_

#include <ostream>
#include <string>

class TaiKhoanNV
{
public:
    TaiKhoanNV();
    TaiKhoanNV(const std::string& strUser, const std::string& strPass);
    TaiKhoanNV(const TaiKhoanNV& khac);
    TaiKhoanNV& operator=(const TaiKhoanNV& khac);
    ~TaiKhoanNV();

    const std::string& getUser() const;
    const std::string& getPass() const;

    void setUser(const std::string& strUser);
    void setPass(const std::string& strPass);

    bool operator==(const TaiKhoanNV& khac) const;
    bool operator!=(const TaiKhoanNV& khac) const;

    bool khop(const std::string& strUser, const std::string& strPass) const;

    // Phan tich 1 dong trong file Admin.txt thanh TaiKhoanNV
    static bool docTuDongFile(const std::string& strDong, TaiKhoanNV& ketQua);

    friend std::ostream& operator<<(std::ostream& os, const TaiKhoanNV& taiKhoan);

private:
    std::string m_strUser;
    std::string m_strPass;
};

#endif
