#ifndef BANDOC_H_INCLUDED_
#define BANDOC_H_INCLUDED_

#include <ostream>
#include <string>

#include "Ngay.h"

class BanDoc
{
public:
    BanDoc();
    explicit BanDoc(const std::string& strMaBanDoc);
    BanDoc(const std::string& strMaBanDoc, const std::string& strHoTen, const Ngay& ngayDangKy);
    BanDoc(const BanDoc& khac);
    BanDoc& operator=(const BanDoc& khac);
    ~BanDoc();

    const std::string& getMaBanDoc() const;
    const std::string& getHoTen() const;
    const Ngay& getNgayDangKy() const;

    void setMaBanDoc(const std::string& strMaBanDoc);
    void setHoTen(const std::string& strHoTen);
    void setNgayDangKy(const Ngay& ngayDangKy);

    bool operator==(const BanDoc& khac) const;
    bool operator!=(const BanDoc& khac) const;
    bool operator<(const BanDoc& khac) const;
    bool operator>(const BanDoc& khac) const;

    std::string toString() const;

    // Doc 1 dong tu file BanDoc.txt va kiem tra hop le
    static bool docTuDongFile(const std::string& strDong, BanDoc& ketQua,
                              std::string& strThongBaoLoi);

    friend std::ostream& operator<<(std::ostream& os, const BanDoc& banDoc);

private:
    std::string m_strMaBanDoc;
    std::string m_strHoTen;
    Ngay m_ngayDangKy;
};

#endif
