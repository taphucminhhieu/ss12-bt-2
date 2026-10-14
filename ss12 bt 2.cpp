#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

struct NhanVien {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
};

void hienThiMenu();
int timKiemTheoMa(const struct NhanVien ds[], int soLuong, int maNV);
void hienThiDanhSach(const struct NhanVien ds[], int soLuong);
int themNhanVien(struct NhanVien ds[], int soLuong);
void suaNhanVien(struct NhanVien ds[], int soLuong);
int xoaNhanVien(struct NhanVien ds[], int soLuong);

int main() {
    struct NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon;

    do {
        hienThiMenu();
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;
            case 2:
                soLuong = themNhanVien(ds, soLuong);
                break;
            case 3:
                suaNhanVien(ds, soLuong);
                break;
            case 4:
                soLuong = xoaNhanVien(ds, soLuong);
                break;
            case 0:
                printf("Dang thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (luaChon != 0);

    return 0;
}

void hienThiMenu() {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
    printf("Nhap lua chon: ");
}

int timKiemTheoMa(const struct NhanVien ds[], int soLuong, int maNV) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1;
}

void hienThiDanhSach(const struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].phutMuon > 15) ? 50000.0f : 0.0f;
        float tienOT = ds[i].soGioOT * (ds[i].luongCoBan / 160.0f) * 1.5f;
        float luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("Ma NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.1f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f\n", tienPhat);
        printf("Tien OT: %.0f\n", tienOT);
        printf("Luong thuc nhan: %.0f\n", luongThucNhan);
        printf("-------------------------\n");
    }
    printf("Tong so nhan vien: %d\n", soLuong);
}

int themNhanVien(struct NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NHAN_VIEN) {
        printf("\nDanh sach nhan vien da day!\n");
        return soLuong;
    }

    int ma;
    printf("\n--- THEM NHAN VIEN ---\n");
    printf("Ma NV: ");
    scanf("%d", &ma);

    if (ma <= 0) {
        printf("=> Loi: Ma nhan vien phai la so nguon duong!\n");
        return soLuong;
    }

    if (timKiemTheoMa(ds, soLuong, ma) != -1) {
        printf("=> Loi: Ma nhan vien da ton tai!\n");
        return soLuong;
    }

    ds[soLuong].maNV = ma;
    while (getchar() != '\n');

    printf("Ho ten: ");
    fgets(ds[soLuong].hoTen, sizeof(ds[soLuong].hoTen), stdin);
    ds[soLuong].hoTen[strcspn(ds[soLuong].hoTen, "\n")] = 0;

    do {
        printf("Luong co ban: ");
        scanf("%f", &ds[soLuong].luongCoBan);
        if (ds[soLuong].luongCoBan < 0) {
            printf("Luong co ban khong duoc am!\n");
        }
    } while (ds[soLuong].luongCoBan < 0);

    do {
        printf("Phut di muon: ");
        scanf("%d", &ds[soLuong].phutMuon);
        if (ds[soLuong].phutMuon < 0) {
            printf("Phut di muon khong duoc am!\n");
        }
    } while (ds[soLuong].phutMuon < 0);

    do {
        printf("So gio OT: ");
        scanf("%f", &ds[soLuong].soGioOT);
        if (ds[soLuong].soGioOT < 0) {
            printf("So gio OT khong duoc am!\n");
        }
    } while (ds[soLuong].soGioOT < 0);

    printf("\n=> Them nhan vien thanh cong!\n");
    return soLuong + 1;
}

void suaNhanVien(struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    int ma;
    printf("\nNhap ma NV can cap nhat: ");
    scanf("%d", &ma);

    int idx = timKiemTheoMa(ds, soLuong, ma);
    if (idx == -1) {
        printf("=> Loi: Khong tim thay nhan vien!\n");
        return;
    }

    do {
        printf("Nhap luong co ban moi: ");
        scanf("%f", &ds[idx].luongCoBan);
        if (ds[idx].luongCoBan < 0) {
            printf("Luong co ban khong duoc am!\n");
        }
    } while (ds[idx].luongCoBan < 0);

    do {
        printf("Nhap phut di muon moi: ");
        scanf("%d", &ds[idx].phutMuon);
        if (ds[idx].phutMuon < 0) {
            printf("Phut di muon khong duoc am!\n");
        }
    } while (ds[idx].phutMuon < 0);

    do {
        printf("Nhap so gio OT moi: ");
        scanf("%f", &ds[idx].soGioOT);
        if (ds[idx].soGioOT < 0) {
            printf("So gio OT khong duoc am!\n");
        }
    } while (ds[idx].soGioOT < 0);

    printf("=> Cap nhat thong tin thanh cong!\n");
}

int xoaNhanVien(struct NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return soLuong;
    }

    int ma;
    printf("\nMa NV can xoa: ");
    scanf("%d", &ma);

    int idx = timKiemTheoMa(ds, soLuong, ma);
    if (idx == -1) {
        printf("=> Loi: Khong tim thay nhan vien!\n");
        return soLuong;
    }

    for (int i = idx; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    printf("=> Xoa nhan vien thanh cong!\n");
    return soLuong - 1;
}
