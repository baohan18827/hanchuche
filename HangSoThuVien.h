#ifndef HANGSOTHUVIEN_H_INCLUDED_
#define HANGSOTHUVIEN_H_INCLUDED_

// Hang so nghiep vu
const int SO_NGAY_HAN_MUON = 7;
const int SO_BAN_DOC_TOI_DA = 500;
const int SO_TAI_KHOAN_TOI_DA = 20;
const int SO_LAN_THU_DANG_NHAP = 3;

// Hang so rang buoc du lieu nhap
const int DO_DAI_MA_TOI_THIEU = 2;
const int DO_DAI_MA_TOI_DA = 15;
const int DO_DAI_CHUOI_TOI_THIEU = 2;
const int DO_DAI_TEN_SACH_TOI_DA = 60;
const int DO_DAI_TAC_GIA_TOI_DA = 40;
const int DO_DAI_NXB_TOI_DA = 40;
const int DO_DAI_HO_TEN_TOI_DA = 40;
const int DO_DAI_MAT_KHAU_TOI_DA = 30;
const int SO_CHU_SO_TOI_DA = 12;
const int SO_CHU_SO_INT_TOI_DA = 9;

const long long GIA_SACH_TOI_THIEU = 1000LL;
const long long GIA_SACH_TOI_DA = 1000000000LL;
const int NAM_PHAT_HANH_TOI_THIEU = 1900;
const int NAM_TOI_DA = 9999;
const int SO_TRANG_TOI_THIEU = 1;
const int SO_TRANG_TOI_DA = 10000;
const long long SO_PHIEU_TOI_DA = 999999999LL;

// Hang so ngay thang
const int THANG_DAU_NAM = 1;
const int THANG_HAI = 2;
const int THANG_CUOI_NAM = 12;
const int SO_THANG_MOT_NAM = 12;
const int NGAY_THANG_HAI_NHUAN = 29;
const int DO_DAI_NAM_CHUOI = 4;
const int DO_DAI_NGAY_THANG_CHUOI = 2;

// Hang so dinh dang file
const int SO_TRUONG_NGAY = 3;
const int SO_TRUONG_SACH = 9;
const int SO_TRUONG_BAN_DOC = 3;
const int SO_TRUONG_PHIEU_MUON = 6;
const int SO_TRUONG_ADMIN = 2;

// Hang so giao dien va ban phim
const int DO_RONG_BANNER = 70;
const int SO_COT_BANG_SACH = 9;
const int SO_COT_BANG_PHIEU = 8;
const int SO_COT_BANG_BAN_DOC = 4;
const int THOI_GIAN_NGHI_DANG_NHAP_MS = 500;

const int MA_PHIM_CTRL_C = 3;
const int MA_PHIM_BACKSPACE = 8;
const int MA_PHIM_ENTER_LF = 10;
const int MA_PHIM_ENTER_CR = 13;
const int MA_PHIM_ESC = 27;
const int MA_PHIM_XOA_DEL = 127;
const int KY_TU_ASCII_DAU = 32;
const int KY_TU_ASCII_CUOI = 126;
const int PHIM_MO_RONG_0 = 0;
const int PHIM_MO_RONG_224 = 224;

// Enum tinh trang phieu muon
enum TinhTrangPhieu
{
    PHIEU_DA_TRA = 0,
    PHIEU_DANG_MUON = 1
};

#endif
