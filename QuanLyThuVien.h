#ifndef QUANLYTHUVIEN_H_INCLUDED_
#define QUANLYTHUVIEN_H_INCLUDED_

#include <string>
#include <vector>

#include "BanDoc.h"
#include "BinarySearchTree.h"
#include "DanhSachDac.h"
#include "HangSoThuVien.h"
#include "LinkedList.h"
#include "PhieuMuon.h"
#include "Sach.h"
#include "Stack.h"
#include "TaiKhoanNV.h"

class QuanLyThuVien
{
public:
    QuanLyThuVien();
    ~QuanLyThuVien();

    // Khoi chay toan bo chuong trinh quan ly thu vien
    int chayChuongTrinh();

private:
    // Dang nhap va dieu huong menu
    bool dangNhapHeThong();
    void chayMenuChinh();
    bool chayMenuSach();
    bool chayMenuPhieuMuon();
    bool chayMenuBanDoc();

    // Quan ly sach
    void hienThiSach() const;
    void timKiemSach() const;
    bool nhapThongTinSachMoi(Sach& sachKetQua) const;
    void themSach();
    void xoaSach();

    // Quan ly phieu muon va ngan xep lich su
    void hienThiPhieu() const;
    void muonSach();
    void traSach();
    void xemLichSu();

    // Quan ly ban doc
    void hienThiBanDoc() const;
    void themBanDoc();

    // Doc va ghi 4 file du lieu (Admin, Sach, BanDoc, PhieuMuon)
    void taiTatCaDuLieu();
    void docFileAdmin();
    void docFileSach();
    void docFileBanDoc();
    void docFilePhieu();

    bool ghiFileSach() const;
    bool ghiNoiFileSach(const Sach& sachMoi) const;
    bool ghiFilePhieu() const;
    bool ghiFileBanDoc() const;

    // Ho tro tra cuu va in bang
    Sach* timSachTheoMa(const std::string& strMaSach) const;
    bool themSachVaoBoNho(const Sach& sachMoi);
    void xoaSachKhoiBoNho(const Sach& sachXoa);
    Node<PhieuMuon>* timPhieuTheoSo(const int iSoPhieu) const;
    int timMaxSoPhieu() const;
    int demSachSanSang() const;
    int demDangMuonCuaBanDoc(const std::string& strMaBanDoc) const;
    std::string getTenBanDoc(const std::string& strMaBanDoc) const;
    bool khopTaiKhoan(const std::string& strUser, const std::string& strPass) const;

    void saoSachRaVector(std::vector<Sach>& vecKetQua) const;
    void saoSachTheoMaTang(std::vector<Sach>& vecKetQua) const;
    void inBangDanhSachSach(const std::vector<Sach>& vecSach) const;
    void inTieuDeBangPhieu() const;
    void inChanBangPhieu() const;
    void inMotDongPhieu(const PhieuMuon& phieu) const;
    static std::string taoGhiChuPhieu(const PhieuMuon& phieu);

    LinkedList<Sach> m_listSach;
    LinkedList<PhieuMuon> m_listPhieu;
    BinarySearchTree<Sach> m_cayMaSach;
    Stack<std::string> m_stackLichSu;
    DanhSachDac<BanDoc, SO_BAN_DOC_TOI_DA> m_dsBanDoc;
    LinkedList<TaiKhoanNV> m_listTaiKhoan;

    std::string m_strUserHienTai;
    std::string m_strFileAdmin;
    std::string m_strFileSach;
    std::string m_strFileBanDoc;
    std::string m_strFilePhieu;
};

#endif
