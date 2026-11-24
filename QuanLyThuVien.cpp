#include "QuanLyThuVien.h"

#include <fstream>
#include <iostream>

#include "ChuoiTienIch.h"
#include "ManHinhConsole.h"
#include "SapXepTimKiem.h"

using namespace std;

QuanLyThuVien::QuanLyThuVien()
    : m_strUserHienTai(""), m_strFileAdmin("Admin.txt"), m_strFileSach("Sach.txt"),
      m_strFileBanDoc("BanDoc.txt"), m_strFilePhieu("PhieuMuon.txt")
{
}

QuanLyThuVien::~QuanLyThuVien()
{
}

int QuanLyThuVien::chayChuongTrinh()
{
    ManHinhConsole::khoiTao();
    this->taiTatCaDuLieu();

    if (this->m_listTaiKhoan.getSize() == 0)
    {
        ManHinhConsole::baoLoi("Không tìm thấy hoặc file Admin.txt trống / sai định dạng!");
        return 1;
    }

    if (!this->dangNhapHeThong())
    {
        if (ManHinhConsole::laCheDoTuongTac())
        {
            ManHinhConsole::choNhanEnter("\nNhấn Enter để đóng chương trình...");
        }
        return 0;
    }

    this->chayMenuChinh();
    cout << "\n";
    ManHinhConsole::inChuMau("Đã kết thúc chương trình quản lý thư viện. Tạm biệt!\n",
                             ManHinhConsole::MAU_VANG);
    return 0;
}

bool QuanLyThuVien::dangNhapHeThong()
{
    ManHinhConsole::xoaManHinh();
    ManHinhConsole::inBannerThuVien();
    ManHinhConsole::inKhungDangNhap();

    for (int iLan = 1; iLan <= SO_LAN_THU_DANG_NHAP; ++iLan)
    {
        string strUser = "";
        if (!ManHinhConsole::nhapTruongDangNhap("       User:     ", strUser, false))
        {
            ManHinhConsole::baoCanhBao("Đã nhấn phím ESC -> thoát khỏi hệ thống.");
            return false;
        }

        string strPass = "";
        if (!ManHinhConsole::nhapTruongDangNhap("       Password: ", strPass, true))
        {
            ManHinhConsole::baoCanhBao("Đã nhấn phím ESC -> thoát khỏi hệ thống.");
            return false;
        }

        if (ChuoiTienIch::catKhoangTrang(strUser).empty() || strPass.empty())
        {
            ManHinhConsole::baoLoi("User và Password không được để trống (lần " +
                                   to_string(iLan) + "/" + to_string(SO_LAN_THU_DANG_NHAP) + ").");
        }
        else if (this->khopTaiKhoan(strUser, strPass))
        {
            this->m_strUserHienTai = strUser;
            cout << "\n";
            ManHinhConsole::baoThanhCong("Đăng nhập thành công! Xin chào " + strUser + ".");
            if (ManHinhConsole::laCheDoTuongTac())
            {
                ManHinhConsole::tamNghiMs(THOI_GIAN_NGHI_DANG_NHAP_MS);
            }
            return true;
        }
        else
        {
            ManHinhConsole::baoLoi("Sai user hoặc password (lần " + to_string(iLan) + "/" +
                                   to_string(SO_LAN_THU_DANG_NHAP) + ").");
        }

        if (iLan < SO_LAN_THU_DANG_NHAP)
        {
            cout << "\n";
        }
    }

    ManHinhConsole::baoLoi("Đã nhập sai 3 lần -> thoát khỏi hệ thống.");
    return false;
}

void QuanLyThuVien::chayMenuChinh()
{
    const int SO_MUC_CHINH = 3;
    bool bTiepTuc = true;

    while (bTiepTuc && !cin.eof())
    {
        ManHinhConsole::xoaManHinh();
        ManHinhConsole::inBannerThuVien();
        cout << "Nhân viên: ";
        ManHinhConsole::inChuMau(this->m_strUserHienTai, ManHinhConsole::MAU_XANH_LA);
        cout << " | Ngày hệ thống: " << Ngay::homNay().toString() << "\n\n";

        vector<string> vecMuc;
        vecMuc.push_back("Quản lý sách");
        vecMuc.push_back("Quản lý phiếu mượn");
        vecMuc.push_back("Quản lý bạn đọc");
        ManHinhConsole::inMenu("MENU LỰA CHỌN CHÍNH", vecMuc, "Thoát chương trình");

        int iChon = ManHinhConsole::chonMucMenu(SO_MUC_CHINH);
        switch (iChon)
        {
            case 1:
                bTiepTuc = this->chayMenuSach();
                break;
            case 2:
                bTiepTuc = this->chayMenuPhieuMuon();
                break;
            case 3:
                bTiepTuc = this->chayMenuBanDoc();
                break;
            case 0:
                bTiepTuc = false;
                break;
            default:
                break;
        }
    }
}

bool QuanLyThuVien::chayMenuSach()
{
    const int SO_MUC_SACH = 4;
    while (!cin.eof())
    {
        ManHinhConsole::xoaManHinh();
        ManHinhConsole::inTieuDeMuc("QUẢN LÝ SÁCH");

        vector<string> vecMuc;
        vecMuc.push_back("Hiển thị thông tin sách");
        vecMuc.push_back("Tìm kiếm thông tin về sách");
        vecMuc.push_back("Thêm sách mới");
        vecMuc.push_back("Xóa sách theo mã sách");
        ManHinhConsole::inMenu("MENU QUẢN LÝ SÁCH", vecMuc, "Quay lại menu chính");

        int iChon = ManHinhConsole::chonMucMenu(SO_MUC_SACH);
        if (iChon == 0)
        {
            return true;
        }

        switch (iChon)
        {
            case 1:
                this->hienThiSach();
                break;
            case 2:
                this->timKiemSach();
                break;
            case 3:
                this->themSach();
                break;
            case 4:
                this->xoaSach();
                break;
            default:
                break;
        }

        if (!ManHinhConsole::hoiTiepTucChuongTrinh())
        {
            return false;
        }
    }
    return false;
}

bool QuanLyThuVien::chayMenuPhieuMuon()
{
    const int SO_MUC_PHIEU = 4;
    while (!cin.eof())
    {
        ManHinhConsole::xoaManHinh();
        ManHinhConsole::inTieuDeMuc("QUẢN LÝ PHIẾU MƯỢN");

        vector<string> vecMuc;
        vecMuc.push_back("Hiển thị thông tin các phiếu mượn");
        vecMuc.push_back("Mượn sách");
        vecMuc.push_back("Trả sách");
        vecMuc.push_back("Xem lịch sử mượn / trả trong phiên");
        ManHinhConsole::inMenu("MENU QUẢN LÝ PHIẾU MƯỢN", vecMuc, "Quay lại menu chính");

        int iChon = ManHinhConsole::chonMucMenu(SO_MUC_PHIEU);
        if (iChon == 0)
        {
            return true;
        }

        switch (iChon)
        {
            case 1:
                this->hienThiPhieu();
                break;
            case 2:
                this->muonSach();
                break;
            case 3:
                this->traSach();
                break;
            case 4:
                this->xemLichSu();
                break;
            default:
                break;
        }

        if (!ManHinhConsole::hoiTiepTucChuongTrinh())
        {
            return false;
        }
    }
    return false;
}

bool QuanLyThuVien::chayMenuBanDoc()
{
    const int SO_MUC_BAN_DOC = 2;
    while (!cin.eof())
    {
        ManHinhConsole::xoaManHinh();
        ManHinhConsole::inTieuDeMuc("QUẢN LÝ BẠN ĐỌC");

        vector<string> vecMuc;
        vecMuc.push_back("Hiển thị danh sách bạn đọc");
        vecMuc.push_back("Đăng ký bạn đọc mới");
        ManHinhConsole::inMenu("MENU QUẢN LÝ BẠN ĐỌC", vecMuc, "Quay lại menu chính");

        int iChon = ManHinhConsole::chonMucMenu(SO_MUC_BAN_DOC);
        if (iChon == 0)
        {
            return true;
        }

        switch (iChon)
        {
            case 1:
                this->hienThiBanDoc();
                break;
            case 2:
                this->themBanDoc();
                break;
            default:
                break;
        }

        if (!ManHinhConsole::hoiTiepTucChuongTrinh())
        {
            return false;
        }
    }
    return false;
}

void QuanLyThuVien::hienThiSach() const
{
    ManHinhConsole::inTieuDeMuc("HIỂN THỊ THÔNG TIN SÁCH");
    if (this->m_listSach.getSize() == 0)
    {
        ManHinhConsole::baoCanhBao("Thư viện hiện chưa có sách nào.");
        return;
    }

    cout << "Cách hiển thị:\n"
         << "  [1] Thứ tự mặc định\n"
         << "  [2] Sắp xếp theo mã sách (A - Z)\n"
         << "  [3] Sắp xếp theo giá bán tăng dần\n"
         << "  [4] Sắp xếp theo năm phát hành mới nhất\n";

    string strChon = "";
    ManHinhConsole::docDong("Chọn cách hiển thị (1-4): ", strChon);
    if (!ChuoiTienIch::laSoNguyenInt(strChon))
    {
        ManHinhConsole::baoLoiVaHuy("Lựa chọn không hợp lệ! Chỉ được nhập số từ 1 đến 4.");
        return;
    }

    int iCheDo = stoi(strChon);
    vector<Sach> vecSach;
    string strMoTa = "";
    switch (iCheDo)
    {
        case 1:
            this->saoSachRaVector(vecSach);
            strMoTa = "Thứ tự mặc định";
            break;
        case 2:
            this->saoSachTheoMaTang(vecSach);
            strMoTa = "Mã sách (A - Z)";
            break;
        case 3:
            this->saoSachRaVector(vecSach);
            SapXepTimKiem::quickSort(vecSach, &Sach::dungTruocTheoGiaTang);
            strMoTa = "Giá bán tăng dần";
            break;
        case 4:
            this->saoSachRaVector(vecSach);
            SapXepTimKiem::quickSort(vecSach, &Sach::dungTruocTheoNamGiam);
            strMoTa = "Năm phát hành mới nhất";
            break;
        default:
            ManHinhConsole::baoLoiVaHuy("Lựa chọn không hợp lệ! Chỉ được nhập số từ 1 đến 4.");
            return;
    }

    cout << "\n";
    ManHinhConsole::inChuMau("Đang hiển thị theo: " + strMoTa + "\n", ManHinhConsole::MAU_TIEU_DE);
    this->inBangDanhSachSach(vecSach);

    int iSoCon = this->demSachSanSang();
    int iTong = this->m_listSach.getSize();
    cout << "\nTổng: " << iTong << " cuốn | Sẵn sàng (TT = 0): ";
    ManHinhConsole::inChuMau(to_string(iSoCon), ManHinhConsole::MAU_XANH_LA);
    cout << " | Đang được mượn: ";
    ManHinhConsole::inChuMau(to_string(iTong - iSoCon), ManHinhConsole::MAU_DO);
    cout << "\n";
}

void QuanLyThuVien::timKiemSach() const
{
    ManHinhConsole::inTieuDeMuc("TÌM KIẾM THÔNG TIN VỀ SÁCH");
    if (this->m_listSach.getSize() == 0)
    {
        ManHinhConsole::baoCanhBao("Thư viện chưa có sách nào để tìm kiếm.");
        return;
    }

    cout << "  [1] Tìm theo mã sách\n"
         << "  [2] Tìm theo từ khóa (Tên sách / Tác giả / NXB)\n";
    string strChon = "";
    ManHinhConsole::docDong("Chọn kiểu tìm kiếm (1-2): ", strChon);
    if (strChon != "1" && strChon != "2")
    {
        ManHinhConsole::baoLoiVaHuy("Lựa chọn không hợp lệ! Chỉ nhập 1 hoặc 2.");
        return;
    }

    string strNhap = "";
    string strLoi = "";
    vector<Sach> vecKetQua;

    if (strChon == "1")
    {
        ManHinhConsole::docDong("Nhập mã sách cần tìm (vd S001): ", strNhap);
        string strMa = "";
        if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã sách", strMa, strLoi))
        {
            ManHinhConsole::baoLoiVaHuy(strLoi);
            return;
        }
        Sach* pSach = this->timSachTheoMa(strMa);
        if (pSach != NULL)
        {
            vecKetQua.push_back(*pSach);
        }
    }
    else
    {
        ManHinhConsole::docDong("Nhập từ khóa cần tìm: ", strNhap);
        string strTuKhoa = "";
        if (!ChuoiTienIch::kiemTraChuoiHopLe(strNhap, "Từ khóa", DO_DAI_TEN_SACH_TOI_DA,
                                             strTuKhoa, strLoi))
        {
            ManHinhConsole::baoLoiVaHuy(strLoi);
            return;
        }
        string strTuKhoaThuong = ChuoiTienIch::inThuongAscii(strTuKhoa);
        for (Node<Sach>* pChay = this->m_listSach.getHead(); pChay != NULL; pChay = pChay->getNext())
        {
            if (pChay->getData().khopTuKhoa(strTuKhoaThuong))
            {
                vecKetQua.push_back(pChay->getData());
            }
        }
    }

    if (vecKetQua.empty())
    {
        ManHinhConsole::baoLoi("Không tìm thấy cuốn sách nào phù hợp.");
    }
    else
    {
        ManHinhConsole::baoThanhCong("Tìm thấy " + to_string(vecKetQua.size()) + " cuốn sách:");
        this->inBangDanhSachSach(vecKetQua);
    }
}

bool QuanLyThuVien::nhapThongTinSachMoi(Sach& sachKetQua) const
{
    string strNhap = "";
    string strLoi = "";

    ManHinhConsole::docDong("Mã sách (vd S013)             : ", strNhap);
    string strMa = "";
    if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã sách", strMa, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }
    if (this->timSachTheoMa(strMa) != NULL)
    {
        ManHinhConsole::baoLoiVaHuy("Sách có mã " + strMa + " đã tồn tại trong thư viện -> không thêm.");
        return false;
    }

    ManHinhConsole::docDong("Tên sách                      : ", strNhap);
    string strTen = "";
    if (!ChuoiTienIch::kiemTraChuoiHopLe(strNhap, "Tên sách", DO_DAI_TEN_SACH_TOI_DA,
                                         strTen, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    ManHinhConsole::docDong("Tác giả                       : ", strNhap);
    string strTacGia = "";
    if (!ChuoiTienIch::kiemTraTenNguoi(strNhap, "Tác giả", DO_DAI_TAC_GIA_TOI_DA,
                                       strTacGia, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    ManHinhConsole::docDong("Nhà xuất bản                  : ", strNhap);
    string strNxb = "";
    if (!ChuoiTienIch::kiemTraChuoiHopLe(strNhap, "Nhà xuất bản", DO_DAI_NXB_TOI_DA,
                                         strNxb, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    ManHinhConsole::docDong("Giá bán (VNĐ)                 : ", strNhap);
    long long lGia = 0;
    if (!ChuoiTienIch::kiemTraSoNguyenTrongKhoang(strNhap, "Giá bán", GIA_SACH_TOI_THIEU,
                                                  GIA_SACH_TOI_DA, lGia, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    int iNamHienTai = Ngay::homNay().getNam();
    ManHinhConsole::docDong("Năm phát hành (1900-" + to_string(iNamHienTai) + ")     : ", strNhap);
    long long lNam = 0;
    if (!ChuoiTienIch::kiemTraSoNguyenTrongKhoang(strNhap, "Năm phát hành",
                                                  NAM_PHAT_HANH_TOI_THIEU, iNamHienTai,
                                                  lNam, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    ManHinhConsole::docDong("Số trang (1-10000)            : ", strNhap);
    long long lTrang = 0;
    if (!ChuoiTienIch::kiemTraSoNguyenTrongKhoang(strNhap, "Số trang", SO_TRANG_TOI_THIEU,
                                                  SO_TRANG_TOI_DA, lTrang, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return false;
    }

    ManHinhConsole::docDong("Ngày nhập kho (dd/mm/yyyy)    : ", strNhap);
    Ngay ngayNhap;
    if (!Ngay::phanTichChuoi(strNhap, ngayNhap))
    {
        ManHinhConsole::baoLoiVaHuy("Ngày nhập kho sai định dạng dd/mm/yyyy hoặc không tồn tại.");
        return false;
    }
    if (ngayNhap.soSanhVoi(Ngay::homNay()) > 0 || ngayNhap.getNam() < static_cast<int>(lNam))
    {
        ManHinhConsole::baoLoiVaHuy("Ngày nhập kho không hợp lệ (không vượt hôm nay và >= năm phát hành).");
        return false;
    }

    sachKetQua.setMaSach(strMa);
    sachKetQua.setTenSach(strTen);
    sachKetQua.setTacGia(strTacGia);
    sachKetQua.setNhaXuatBan(strNxb);
    sachKetQua.setGiaBan(lGia);
    sachKetQua.setNamPhatHanh(static_cast<int>(lNam));
    sachKetQua.setSoTrang(static_cast<int>(lTrang));
    sachKetQua.setNgayNhapKho(ngayNhap);
    sachKetQua.setTinhTrang(0);
    return true;
}

void QuanLyThuVien::themSach()
{
    ManHinhConsole::inTieuDeMuc("THÊM SÁCH MỚI");
    Sach sachMoi;
    if (!this->nhapThongTinSachMoi(sachMoi))
    {
        return;
    }

    this->themSachVaoBoNho(sachMoi);
    if (!this->ghiNoiFileSach(sachMoi))
    {
        this->xoaSachKhoiBoNho(sachMoi);
        ManHinhConsole::baoLoi("Không thể ghi vào file " + this->m_strFileSach + ".");
        return;
    }

    ManHinhConsole::baoThanhCong("Đã thêm sách " + sachMoi.getMaSach() + " - \"" +
                                 sachMoi.getTenSach() + "\" thành công!");
}

void QuanLyThuVien::xoaSach()
{
    ManHinhConsole::inTieuDeMuc("XÓA SÁCH THEO MÃ SÁCH");
    if (this->m_listSach.getSize() == 0)
    {
        ManHinhConsole::baoCanhBao("Danh sách sách đang trống.");
        return;
    }

    string strNhap = "";
    string strMa = "";
    string strLoi = "";
    ManHinhConsole::docDong("Nhập mã sách cần xóa (vd S012): ", strNhap);
    if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã sách", strMa, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }

    Sach* pSach = this->timSachTheoMa(strMa);
    if (pSach == NULL)
    {
        ManHinhConsole::baoLoiVaHuy("Không tìm thấy sách có mã " + strMa + " trong danh sách.");
        return;
    }

    Sach sachSaoLuu = *pSach;
    vector<Sach> vecMotCuon;
    vecMotCuon.push_back(sachSaoLuu);
    this->inBangDanhSachSach(vecMotCuon);

    if (sachSaoLuu.getTinhTrang() != 0)
    {
        ManHinhConsole::baoLoiVaHuy("Không thể xóa sách " + strMa +
                                    " do sách đang được mượn (tình trạng = " +
                                    to_string(sachSaoLuu.getTinhTrang()) + ").");
        return;
    }

    if (!ManHinhConsole::xacNhan("Bạn có chắc chắn muốn xóa cuốn sách này?"))
    {
        ManHinhConsole::baoCanhBao("Đã hủy thao tác xóa sách.");
        return;
    }

    this->xoaSachKhoiBoNho(sachSaoLuu);
    if (!this->ghiFileSach())
    {
        this->themSachVaoBoNho(sachSaoLuu);
        ManHinhConsole::baoLoi("Không thể ghi đè file " + this->m_strFileSach + ".");
        return;
    }

    ManHinhConsole::baoThanhCong("Đã xóa sách " + strMa + " thành công!");
}

void QuanLyThuVien::hienThiPhieu() const
{
    ManHinhConsole::inTieuDeMuc("HIỂN THỊ THÔNG TIN CÁC PHIẾU MƯỢN");
    if (this->m_listPhieu.getSize() == 0)
    {
        ManHinhConsole::baoCanhBao("Hiện chưa có phiếu mượn nào.");
        return;
    }

    cout << "  [1] Hiển thị tất cả phiếu mượn\n"
         << "  [2] Hiển thị phiếu đang mượn theo hạn trả gần nhất\n";
    string strChon = "";
    ManHinhConsole::docDong("Chọn cách hiển thị (1-2): ", strChon);
    if (strChon != "1" && strChon != "2")
    {
        ManHinhConsole::baoLoiVaHuy("Lựa chọn không hợp lệ! Chỉ nhập 1 hoặc 2.");
        return;
    }

    if (strChon == "2")
    {
        LinkedList<PhieuMuon> listTam;
        for (Node<PhieuMuon>* pChay = this->m_listPhieu.getHead(); pChay != NULL; pChay = pChay->getNext())
        {
            if (pChay->getData().getTinhTrang() == PHIEU_DANG_MUON)
            {
                listTam.addTail(pChay->getData());
            }
        }
        if (listTam.getSize() == 0)
        {
            ManHinhConsole::baoThanhCong("Hiện không có phiếu nào đang mượn.");
            return;
        }
        listTam.selectionSort();
        this->inTieuDeBangPhieu();
        for (Node<PhieuMuon>* pChay = listTam.getHead(); pChay != NULL; pChay = pChay->getNext())
        {
            this->inMotDongPhieu(pChay->getData());
        }
        this->inChanBangPhieu();
        return;
    }

    this->inTieuDeBangPhieu();
    int iDangMuon = 0;
    for (Node<PhieuMuon>* pChay = this->m_listPhieu.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        this->inMotDongPhieu(pChay->getData());
        if (pChay->getData().getTinhTrang() == PHIEU_DANG_MUON)
        {
            ++iDangMuon;
        }
    }
    this->inChanBangPhieu();

    ManHinhConsole::inChuMau("(TT = 1: đang mượn; TT = 0: đã trả)\n", ManHinhConsole::MAU_XAM);
    cout << "Tổng: " << this->m_listPhieu.getSize() << " phiếu | Đang mượn: ";
    ManHinhConsole::inChuMau(to_string(iDangMuon), ManHinhConsole::MAU_VANG);
    cout << " | Đã trả: ";
    ManHinhConsole::inChuMau(to_string(this->m_listPhieu.getSize() - iDangMuon),
                             ManHinhConsole::MAU_XANH_LA);
    cout << "\n";
}

void QuanLyThuVien::muonSach()
{
    ManHinhConsole::inTieuDeMuc("MƯỢN SÁCH");
    string strNhap = "";
    string strLoi = "";

    ManHinhConsole::docDong("Nhập mã sách (vd S002)     : ", strNhap);
    string strMaSach = "";
    if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã sách", strMaSach, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }

    Sach* pSach = this->timSachTheoMa(strMaSach);
    if (pSach == NULL)
    {
        ManHinhConsole::baoLoiVaHuy("Không tìm thấy sách mã " + strMaSach + " trong thư viện.");
        return;
    }
    cout << "  -> Sách: " << pSach->getTenSach() << " | Tình trạng: " << pSach->getTinhTrang() << "\n";

    if (pSach->getTinhTrang() != 0)
    {
        ManHinhConsole::baoLoiVaHuy("Sách " + strMaSach + " hiện đang được mượn (tình trạng = " +
                                    to_string(pSach->getTinhTrang()) + ").");
        return;
    }

    ManHinhConsole::docDong("Nhập mã bạn đọc (vd DG002) : ", strNhap);
    string strMaBanDoc = "";
    if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã bạn đọc", strMaBanDoc, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }

    int iViTriBanDoc = this->m_dsBanDoc.binarySearch(BanDoc(strMaBanDoc));
    if (iViTriBanDoc == -1)
    {
        ManHinhConsole::baoLoiVaHuy("Mã bạn đọc " + strMaBanDoc + " không có trong danh sách bạn đọc.");
        return;
    }
    cout << "  -> Bạn đọc: " << this->m_dsBanDoc.getPhanTu(iViTriBanDoc).getHoTen() << "\n";

    Ngay ngayHomNay = Ngay::homNay();
    PhieuMuon phieuMoi;
    phieuMoi.setSoPhieu(this->timMaxSoPhieu() + 1);
    phieuMoi.setMaBanDoc(strMaBanDoc);
    phieuMoi.setMaSach(strMaSach);
    phieuMoi.setNgayMuon(ngayHomNay);
    phieuMoi.setNgayPhaiTra(ngayHomNay.congThemNgay(SO_NGAY_HAN_MUON));
    phieuMoi.setTinhTrang(PHIEU_DANG_MUON);

    this->m_listPhieu.addTail(phieuMoi);
    pSach->setTinhTrang(phieuMoi.getSoPhieu());

    if (!this->ghiFileSach() || !this->ghiFilePhieu())
    {
        this->m_listPhieu.removeTail();
        pSach->setTinhTrang(0);
        ManHinhConsole::baoLoi("Không thể ghi cập nhật file dữ liệu. Đã hủy phiếu mượn.");
        return;
    }

    this->m_stackLichSu.push("Mượn sách - Phiếu #" + to_string(phieuMoi.getSoPhieu()) +
                             " (Sách " + strMaSach + ", Bạn đọc " + strMaBanDoc + ")");

    ManHinhConsole::baoThanhCong("Tạo phiếu mượn thành công!");
    cout << "  - Số phiếu mượn      : " << phieuMoi.getSoPhieu() << " (tình trạng = 1)\n"
         << "  - Ngày mượn          : " << phieuMoi.getNgayMuon().toString() << "\n"
         << "  - Ngày phải trả (+7) : " << phieuMoi.getNgayPhaiTra().toString() << "\n"
         << "  - Tình trạng sách    : " << pSach->getTinhTrang() << "\n";
}

void QuanLyThuVien::traSach()
{
    ManHinhConsole::inTieuDeMuc("TRẢ SÁCH");
    if (this->m_listPhieu.getSize() == 0)
    {
        ManHinhConsole::baoCanhBao("Hiện chưa có phiếu mượn nào trong hệ thống.");
        return;
    }

    string strNhap = "";
    string strLoi = "";
    long long lSoPhieu = 0;
    ManHinhConsole::docDong("Nhập số phiếu mượn cần trả: ", strNhap);
    if (!ChuoiTienIch::kiemTraSoNguyenTrongKhoang(strNhap, "Số phiếu mượn", 1, SO_PHIEU_TOI_DA,
                                                  lSoPhieu, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }

    Node<PhieuMuon>* pNutPhieu = this->timPhieuTheoSo(static_cast<int>(lSoPhieu));
    if (pNutPhieu == NULL)
    {
        ManHinhConsole::baoLoiVaHuy("Không tìm thấy phiếu mượn số " + to_string(lSoPhieu) + ".");
        return;
    }

    PhieuMuon& phieu = pNutPhieu->getData();
    this->inTieuDeBangPhieu();
    this->inMotDongPhieu(phieu);
    this->inChanBangPhieu();

    if (phieu.getTinhTrang() == PHIEU_DA_TRA)
    {
        ManHinhConsole::baoLoiVaHuy("Phiếu mượn số " + to_string(lSoPhieu) +
                                    " có tình trạng = 0 (đã được trả trước đó).");
        return;
    }

    Sach* pSach = this->timSachTheoMa(phieu.getMaSach());
    long long lSoNgayTre = phieu.soNgayTre();
    int iTinhTrangSachCu = (pSach != NULL) ? pSach->getTinhTrang() : 0;

    phieu.setTinhTrang(PHIEU_DA_TRA);
    if (pSach != NULL)
    {
        pSach->setTinhTrang(0);
    }

    if (!this->ghiFileSach() || !this->ghiFilePhieu())
    {
        phieu.setTinhTrang(PHIEU_DANG_MUON);
        if (pSach != NULL)
        {
            pSach->setTinhTrang(iTinhTrangSachCu);
        }
        ManHinhConsole::baoLoi("Không thể ghi cập nhật file dữ liệu. Đã hủy trả sách.");
        return;
    }

    this->m_stackLichSu.push("Trả sách  - Phiếu #" + to_string(phieu.getSoPhieu()) +
                             " (Sách " + phieu.getMaSach() + ", Bạn đọc " + phieu.getMaBanDoc() + ")");

    ManHinhConsole::baoThanhCong("Trả sách thành công! Phiếu #" + to_string(phieu.getSoPhieu()) +
                                 " và sách " + phieu.getMaSach() + " đã được cập nhật.");
    if (lSoNgayTre > 0)
    {
        ManHinhConsole::baoCanhBao("Lưu ý: Bạn đọc trả trễ " + to_string(lSoNgayTre) + " ngày.");
    }
}

void QuanLyThuVien::xemLichSu()
{
    ManHinhConsole::inTieuDeMuc("LỊCH SỬ MƯỢN / TRẢ TRONG PHIÊN");
    if (this->m_stackLichSu.empty())
    {
        ManHinhConsole::baoCanhBao("Chưa có thao tác mượn/trả nào trong phiên làm việc này.");
        return;
    }

    Stack<string> stackTam;
    int iThuTu = 0;
    while (!this->m_stackLichSu.empty())
    {
        string strDong = this->m_stackLichSu.top();
        this->m_stackLichSu.pop();
        stackTam.push(strDong);
        ++iThuTu;
        cout << "  " << iThuTu << ". " << strDong << "\n";
    }
    while (!stackTam.empty())
    {
        this->m_stackLichSu.push(stackTam.top());
        stackTam.pop();
    }
}

void QuanLyThuVien::hienThiBanDoc() const
{
    ManHinhConsole::inTieuDeMuc("DANH SÁCH BẠN ĐỌC");
    if (this->m_dsBanDoc.getSoLuong() == 0)
    {
        ManHinhConsole::baoCanhBao("Chưa có bạn đọc nào trong hệ thống.");
        return;
    }

    static const int DO_RONG_COT[SO_COT_BANG_BAN_DOC] = { 10, 26, 12, 10 };
    static const char* const TIEU_DE_COT[SO_COT_BANG_BAN_DOC] = {
        "Mã BĐ", "Họ tên bạn đọc", "Ngày ĐK", "Đang mượn"
    };
    static const bool CAN_PHAI[SO_COT_BANG_BAN_DOC] = { false, false, false, true };

    ManHinhConsole::inDauBang(DO_RONG_COT, TIEU_DE_COT, CAN_PHAI, SO_COT_BANG_BAN_DOC);
    for (int iChiSo = 0; iChiSo < this->m_dsBanDoc.getSoLuong(); ++iChiSo)
    {
        const BanDoc& banDoc = this->m_dsBanDoc.getPhanTu(iChiSo);
        int iDangMuon = this->demDangMuonCuaBanDoc(banDoc.getMaBanDoc());

        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(banDoc.getMaBanDoc(), DO_RONG_COT[0]),
                            ManHinhConsole::MAU_VANG);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(banDoc.getHoTen(), DO_RONG_COT[1]),
                            ManHinhConsole::MAU_TRANG);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(banDoc.getNgayDangKy().toString(), DO_RONG_COT[2]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canPhai(to_string(iDangMuon), DO_RONG_COT[3]),
                            ManHinhConsole::MAU_XANH_LA);
        ManHinhConsole::inVienDoc();
        cout << "\n";
    }
    ManHinhConsole::inChanBang(DO_RONG_COT, SO_COT_BANG_BAN_DOC);
}

void QuanLyThuVien::themBanDoc()
{
    ManHinhConsole::inTieuDeMuc("ĐĂNG KÝ BẠN ĐỌC MỚI");
    if (this->m_dsBanDoc.daDay())
    {
        ManHinhConsole::baoLoi("Danh sách bạn đọc đã đầy.");
        return;
    }

    string strNhap = "";
    string strLoi = "";

    ManHinhConsole::docDong("Mã bạn đọc (vd DG009)       : ", strNhap);
    string strMa = "";
    if (!ChuoiTienIch::kiemTraMaHopLe(strNhap, "Mã bạn đọc", strMa, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }
    if (this->m_dsBanDoc.binarySearch(BanDoc(strMa)) != -1)
    {
        ManHinhConsole::baoLoiVaHuy("Mã bạn đọc " + strMa + " đã tồn tại trong danh sách.");
        return;
    }

    ManHinhConsole::docDong("Họ tên bạn đọc              : ", strNhap);
    string strHoTen = "";
    if (!ChuoiTienIch::kiemTraTenNguoi(strNhap, "Họ tên bạn đọc", DO_DAI_HO_TEN_TOI_DA,
                                       strHoTen, strLoi))
    {
        ManHinhConsole::baoLoiVaHuy(strLoi);
        return;
    }

    ManHinhConsole::docDong("Ngày đăng ký (dd/mm/yyyy)   : ", strNhap);
    Ngay ngayDk;
    if (!Ngay::phanTichChuoi(strNhap, ngayDk) || ngayDk.soSanhVoi(Ngay::homNay()) > 0)
    {
        ManHinhConsole::baoLoiVaHuy("Ngày đăng ký không hợp lệ (định dạng dd/mm/yyyy và <= hôm nay).");
        return;
    }

    BanDoc banDocMoi;
    banDocMoi.setMaBanDoc(strMa);
    banDocMoi.setHoTen(strHoTen);
    banDocMoi.setNgayDangKy(ngayDk);

    this->m_dsBanDoc.themTheoThuTu(banDocMoi);
    if (!this->ghiFileBanDoc())
    {
        this->m_dsBanDoc.xoaPhanTu(banDocMoi);
        ManHinhConsole::baoLoi("Không thể ghi vào file " + this->m_strFileBanDoc + ".");
        return;
    }

    ManHinhConsole::baoThanhCong("Đã đăng ký bạn đọc " + strMa + " - " + strHoTen + " thành công!");
}

void QuanLyThuVien::taiTatCaDuLieu()
{
    this->docFileAdmin();
    this->docFileBanDoc();
    this->docFileSach();
    this->docFilePhieu();
}

void QuanLyThuVien::docFileAdmin()
{
    ifstream fileDoc;
    fileDoc.open(this->m_strFileAdmin.c_str());
    if (!fileDoc.is_open())
    {
        return;
    }

    string strDong = "";
    while (getline(fileDoc, strDong) && this->m_listTaiKhoan.getSize() < SO_TAI_KHOAN_TOI_DA)
    {
        strDong = ChuoiTienIch::catKhoangTrang(strDong);
        if (strDong.empty())
        {
            continue;
        }
        TaiKhoanNV taiKhoan;
        if (TaiKhoanNV::docTuDongFile(strDong, taiKhoan))
        {
            this->m_listTaiKhoan.addTail(taiKhoan);
        }
    }
    fileDoc.close();
}

void QuanLyThuVien::docFileSach()
{
    ifstream fileDoc;
    fileDoc.open(this->m_strFileSach.c_str());
    if (!fileDoc.is_open())
    {
        return;
    }

    int iSoDong = 0;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        ++iSoDong;
        strDong = ChuoiTienIch::catKhoangTrang(strDong);
        if (strDong.empty())
        {
            continue;
        }
        Sach sachDoc;
        string strLoi = "";
        if (!Sach::docTuDongFile(strDong, sachDoc, strLoi))
        {
            ManHinhConsole::baoCanhBao("Sach.txt dòng " + to_string(iSoDong) +
                                       " không hợp lệ (" + strLoi + ") -> bỏ qua.");
            continue;
        }
        if (!this->themSachVaoBoNho(sachDoc))
        {
            ManHinhConsole::baoCanhBao("Sach.txt dòng " + to_string(iSoDong) +
                                       ": trùng mã " + sachDoc.getMaSach() + " -> bỏ qua.");
        }
    }
    fileDoc.close();
}

void QuanLyThuVien::docFileBanDoc()
{
    ifstream fileDoc;
    fileDoc.open(this->m_strFileBanDoc.c_str());
    if (!fileDoc.is_open())
    {
        return;
    }

    int iSoDong = 0;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        ++iSoDong;
        strDong = ChuoiTienIch::catKhoangTrang(strDong);
        if (strDong.empty())
        {
            continue;
        }
        BanDoc banDoc;
        string strLoi = "";
        if (!BanDoc::docTuDongFile(strDong, banDoc, strLoi))
        {
            ManHinhConsole::baoCanhBao("BanDoc.txt dòng " + to_string(iSoDong) +
                                       " không hợp lệ (" + strLoi + ") -> bỏ qua.");
            continue;
        }
        if (!this->m_dsBanDoc.themTheoThuTu(banDoc))
        {
            ManHinhConsole::baoCanhBao("BanDoc.txt dòng " + to_string(iSoDong) +
                                       ": trùng mã hoặc đầy -> bỏ qua.");
        }
    }
    fileDoc.close();
}

void QuanLyThuVien::docFilePhieu()
{
    ifstream fileDoc;
    fileDoc.open(this->m_strFilePhieu.c_str());
    if (!fileDoc.is_open())
    {
        return;
    }

    int iSoDong = 0;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        ++iSoDong;
        strDong = ChuoiTienIch::catKhoangTrang(strDong);
        if (strDong.empty())
        {
            continue;
        }
        PhieuMuon phieuDoc;
        if (!PhieuMuon::docTuDongFile(strDong, phieuDoc))
        {
            ManHinhConsole::baoCanhBao("PhieuMuon.txt dòng " + to_string(iSoDong) +
                                       " không hợp lệ -> bỏ qua.");
            continue;
        }
        if (this->timPhieuTheoSo(phieuDoc.getSoPhieu()) != NULL)
        {
            ManHinhConsole::baoCanhBao("PhieuMuon.txt dòng " + to_string(iSoDong) +
                                       ": trùng số phiếu -> bỏ qua.");
            continue;
        }
        this->m_listPhieu.addTail(phieuDoc);
    }
    fileDoc.close();
}

bool QuanLyThuVien::ghiFileSach() const
{
    ofstream fileGhi;
    fileGhi.open(this->m_strFileSach.c_str(), ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }
    for (Node<Sach>* pChay = this->m_listSach.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        fileGhi << pChay->getData().toString() << "\n";
    }
    bool bThanhCong = static_cast<bool>(fileGhi);
    fileGhi.close();
    return bThanhCong;
}

bool QuanLyThuVien::ghiNoiFileSach(const Sach& sachMoi) const
{
    bool bCanXuongDong = false;
    ifstream fileKiemTra;
    fileKiemTra.open(this->m_strFileSach.c_str(), ios::ate | ios::binary);
    if (fileKiemTra.is_open())
    {
        if (fileKiemTra.tellg() > 0)
        {
            fileKiemTra.seekg(-1, ios::end);
            char cKyTuCuoi = '\n';
            fileKiemTra.get(cKyTuCuoi);
            if (cKyTuCuoi != '\n')
            {
                bCanXuongDong = true;
            }
        }
        fileKiemTra.close();
    }

    ofstream fileGhi;
    fileGhi.open(this->m_strFileSach.c_str(), ios::app);
    if (!fileGhi.is_open())
    {
        return false;
    }
    if (bCanXuongDong)
    {
        fileGhi << "\n";
    }
    fileGhi << sachMoi.toString() << "\n";
    bool bThanhCong = static_cast<bool>(fileGhi);
    fileGhi.close();
    return bThanhCong;
}

bool QuanLyThuVien::ghiFilePhieu() const
{
    ofstream fileGhi;
    fileGhi.open(this->m_strFilePhieu.c_str(), ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }
    for (Node<PhieuMuon>* pChay = this->m_listPhieu.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        fileGhi << pChay->getData().toString() << "\n";
    }
    bool bThanhCong = static_cast<bool>(fileGhi);
    fileGhi.close();
    return bThanhCong;
}

bool QuanLyThuVien::ghiFileBanDoc() const
{
    ofstream fileGhi;
    fileGhi.open(this->m_strFileBanDoc.c_str(), ios::trunc);
    if (!fileGhi.is_open())
    {
        return false;
    }
    for (int iChiSo = 0; iChiSo < this->m_dsBanDoc.getSoLuong(); ++iChiSo)
    {
        fileGhi << this->m_dsBanDoc.getPhanTu(iChiSo).toString() << "\n";
    }
    bool bThanhCong = static_cast<bool>(fileGhi);
    fileGhi.close();
    return bThanhCong;
}

Sach* QuanLyThuVien::timSachTheoMa(const string& strMaSach) const
{
    return this->m_cayMaSach.search(strMaSach);
}

bool QuanLyThuVien::themSachVaoBoNho(const Sach& sachMoi)
{
    if (this->timSachTheoMa(sachMoi.getMaSach()) != NULL)
    {
        return false;
    }
    this->m_listSach.addTail(sachMoi);
    Node<Sach>* pDuoi = this->m_listSach.getTail();
    if (pDuoi != NULL)
    {
        this->m_cayMaSach.insert(sachMoi.getMaSach(), &pDuoi->getData());
    }
    return true;
}

void QuanLyThuVien::xoaSachKhoiBoNho(const Sach& sachXoa)
{
    this->m_cayMaSach.remove(sachXoa.getMaSach());
    this->m_listSach.remove(sachXoa);
}

Node<PhieuMuon>* QuanLyThuVien::timPhieuTheoSo(const int iSoPhieu) const
{
    return this->m_listPhieu.search(PhieuMuon(iSoPhieu));
}

int QuanLyThuVien::timMaxSoPhieu() const
{
    int iLonNhat = 0;
    for (Node<PhieuMuon>* pChay = this->m_listPhieu.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        if (pChay->getData().getSoPhieu() > iLonNhat)
        {
            iLonNhat = pChay->getData().getSoPhieu();
        }
    }
    return iLonNhat;
}

int QuanLyThuVien::demSachSanSang() const
{
    int iDem = 0;
    for (Node<Sach>* pChay = this->m_listSach.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        if (pChay->getData().getTinhTrang() == 0)
        {
            ++iDem;
        }
    }
    return iDem;
}

int QuanLyThuVien::demDangMuonCuaBanDoc(const string& strMaBanDoc) const
{
    int iDem = 0;
    for (Node<PhieuMuon>* pChay = this->m_listPhieu.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        if (pChay->getData().getMaBanDoc() == strMaBanDoc &&
            pChay->getData().getTinhTrang() == PHIEU_DANG_MUON)
        {
            ++iDem;
        }
    }
    return iDem;
}

string QuanLyThuVien::getTenBanDoc(const string& strMaBanDoc) const
{
    int iViTri = this->m_dsBanDoc.binarySearch(BanDoc(strMaBanDoc));
    if (iViTri >= 0)
    {
        return this->m_dsBanDoc.getPhanTu(iViTri).getHoTen();
    }
    return "(không có)";
}

bool QuanLyThuVien::khopTaiKhoan(const string& strUser, const string& strPass) const
{
    for (Node<TaiKhoanNV>* pChay = this->m_listTaiKhoan.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        if (pChay->getData().khop(strUser, strPass))
        {
            return true;
        }
    }
    return false;
}

void QuanLyThuVien::saoSachRaVector(vector<Sach>& vecKetQua) const
{
    vecKetQua.clear();
    for (Node<Sach>* pChay = this->m_listSach.getHead(); pChay != NULL; pChay = pChay->getNext())
    {
        vecKetQua.push_back(pChay->getData());
    }
}

void QuanLyThuVien::saoSachTheoMaTang(vector<Sach>& vecKetQua) const
{
    vecKetQua.clear();
    vector<Sach*> vecConTro;
    this->m_cayMaSach.inOrder(vecConTro);
    for (size_t iChiSo = 0; iChiSo < vecConTro.size(); ++iChiSo)
    {
        if (vecConTro[iChiSo] != NULL)
        {
            vecKetQua.push_back(*vecConTro[iChiSo]);
        }
    }
}

void QuanLyThuVien::inBangDanhSachSach(const vector<Sach>& vecSach) const
{
    static const int DO_RONG_COT[SO_COT_BANG_SACH] = { 6, 26, 17, 14, 9, 5, 5, 10, 4 };
    static const char* const TIEU_DE_COT[SO_COT_BANG_SACH] = {
        "Mã", "Tên sách", "Tác giả", "NXB", "Giá bán", "Năm", "Trang", "Ngày nhập", "TT"
    };
    static const bool CAN_PHAI[SO_COT_BANG_SACH] = {
        false, false, false, false, true, true, true, false, true
    };

    ManHinhConsole::inDauBang(DO_RONG_COT, TIEU_DE_COT, CAN_PHAI, SO_COT_BANG_SACH);
    for (size_t iChiSo = 0; iChiSo < vecSach.size(); ++iChiSo)
    {
        const Sach& sach = vecSach[iChiSo];
        ManHinhConsole::MauChu eMauTT =
            (sach.getTinhTrang() == 0) ? ManHinhConsole::MAU_XANH_LA : ManHinhConsole::MAU_DO;

        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(sach.getMaSach(), DO_RONG_COT[0]),
                            ManHinhConsole::MAU_VANG);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(sach.getTenSach(), DO_RONG_COT[1]),
                            ManHinhConsole::MAU_TRANG);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(sach.getTacGia(), DO_RONG_COT[2]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(sach.getNhaXuatBan(), DO_RONG_COT[3]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canPhai(ChuoiTienIch::dinhDangTien(sach.getGiaBan()),
                                                  DO_RONG_COT[4]),
                            ManHinhConsole::MAU_XANH_LA);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canPhai(to_string(sach.getNamPhatHanh()), DO_RONG_COT[5]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canPhai(to_string(sach.getSoTrang()), DO_RONG_COT[6]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canTrai(sach.getNgayNhapKho().toString(), DO_RONG_COT[7]),
                            ManHinhConsole::MAU_MAC_DINH);
        ManHinhConsole::inVienDoc();
        ManHinhConsole::inO(ChuoiTienIch::canPhai(to_string(sach.getTinhTrang()), DO_RONG_COT[8]),
                            eMauTT);
        ManHinhConsole::inVienDoc();
        cout << "\n";
    }
    ManHinhConsole::inChanBang(DO_RONG_COT, SO_COT_BANG_SACH);
    ManHinhConsole::inChuMau(
        "(TT = 0: chưa có người mượn; TT khác 0: số thứ tự phiếu mượn đang giữ sách)\n",
        ManHinhConsole::MAU_XAM);
}

void QuanLyThuVien::inTieuDeBangPhieu() const
{
    static const int DO_RONG_PHIEU[SO_COT_BANG_PHIEU] = { 8, 7, 20, 7, 10, 10, 3, 17 };
    static const char* const TIEU_DE_PHIEU[SO_COT_BANG_PHIEU] = {
        "Số phiếu", "Mã BĐ", "Họ tên bạn đọc", "Mã sách", "Ngày mượn", "Ngày trả", "TT", "Ghi chú"
    };
    static const bool CAN_PHAI_PHIEU[SO_COT_BANG_PHIEU] = {
        false, false, false, false, false, false, true, false
    };
    ManHinhConsole::inDauBang(DO_RONG_PHIEU, TIEU_DE_PHIEU, CAN_PHAI_PHIEU, SO_COT_BANG_PHIEU);
}

void QuanLyThuVien::inChanBangPhieu() const
{
    static const int DO_RONG_PHIEU[SO_COT_BANG_PHIEU] = { 8, 7, 20, 7, 10, 10, 3, 17 };
    ManHinhConsole::inChanBang(DO_RONG_PHIEU, SO_COT_BANG_PHIEU);
}

void QuanLyThuVien::inMotDongPhieu(const PhieuMuon& phieu) const
{
    static const int DO_RONG_PHIEU[SO_COT_BANG_PHIEU] = { 8, 7, 20, 7, 10, 10, 3, 17 };
    string strHoTen = this->getTenBanDoc(phieu.getMaBanDoc());
    string strGhiChu = QuanLyThuVien::taoGhiChuPhieu(phieu);

    ManHinhConsole::MauChu eMauGhiChu = ManHinhConsole::MAU_VANG;
    if (phieu.getTinhTrang() == PHIEU_DA_TRA)
    {
        eMauGhiChu = ManHinhConsole::MAU_XANH_LA;
    }
    else if (phieu.soNgayTre() > 0)
    {
        eMauGhiChu = ManHinhConsole::MAU_DO;
    }

    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(to_string(phieu.getSoPhieu()), DO_RONG_PHIEU[0]),
                        ManHinhConsole::MAU_VANG);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(phieu.getMaBanDoc(), DO_RONG_PHIEU[1]),
                        ManHinhConsole::MAU_MAC_DINH);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(strHoTen, DO_RONG_PHIEU[2]),
                        ManHinhConsole::MAU_TRANG);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(phieu.getMaSach(), DO_RONG_PHIEU[3]),
                        ManHinhConsole::MAU_MAC_DINH);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(phieu.getNgayMuon().toString(), DO_RONG_PHIEU[4]),
                        ManHinhConsole::MAU_MAC_DINH);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(phieu.getNgayPhaiTra().toString(), DO_RONG_PHIEU[5]),
                        ManHinhConsole::MAU_MAC_DINH);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canPhai(to_string(static_cast<int>(phieu.getTinhTrang())),
                                              DO_RONG_PHIEU[6]),
                        ManHinhConsole::MAU_MAC_DINH);
    ManHinhConsole::inVienDoc();
    ManHinhConsole::inO(ChuoiTienIch::canTrai(strGhiChu, DO_RONG_PHIEU[7]), eMauGhiChu);
    ManHinhConsole::inVienDoc();
    cout << "\n";
}

string QuanLyThuVien::taoGhiChuPhieu(const PhieuMuon& phieu)
{
    switch (phieu.getTinhTrang())
    {
        case PHIEU_DA_TRA:
            return "Đã trả";
        case PHIEU_DANG_MUON:
            if (phieu.soNgayTre() > 0)
            {
                return "QUÁ HẠN " + to_string(phieu.soNgayTre()) + " ngày";
            }
            return "Đang mượn";
        default:
            return "Không rõ";
    }
}
