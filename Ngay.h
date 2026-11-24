#ifndef NGAY_H_INCLUDED_
#define NGAY_H_INCLUDED_

#include <ostream>
#include <string>

class Ngay
{
public:
    Ngay();
    Ngay(const int iNgay, const int iThang, const int iNam);
    Ngay(const Ngay& khac);
    Ngay& operator=(const Ngay& khac);
    ~Ngay();

    int getNgay() const;
    int getThang() const;
    int getNam() const;

    void setNgay(const int iNgay);
    void setThang(const int iThang);
    void setNam(const int iNam);

    bool operator==(const Ngay& khac) const;
    bool operator!=(const Ngay& khac) const;
    bool operator<(const Ngay& khac) const;
    bool operator>(const Ngay& khac) const;

    static bool laNamNhuan(const int iNam);
    static int soNgayTrongThang(const int iThang, const int iNam);
    static bool hopLe(const int iNgay, const int iThang, const int iNam);

    // So sanh ngay hien tai voi ngay khac
    int soSanhVoi(const Ngay& khac) const;

    // Cong them so ngay vao ngay hien tai (vd +7 ngay han tra)
    Ngay congThemNgay(const int iSoNgayCong) const;

    // Tinh so ngay chenh lech (ngayA - ngayB)
    static long long chenhLechNgay(const Ngay& ngayA, const Ngay& ngayB);

    static Ngay homNay();
    std::string toString() const;
    static bool phanTichChuoi(const std::string& strChuoi, Ngay& ketQua);

    friend std::ostream& operator<<(std::ostream& os, const Ngay& ngay);

private:
    Ngay tangMotNgay() const;

    int m_iNgay;
    int m_iThang;
    int m_iNam;
};

#endif
