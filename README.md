# 🧺 HSRL Laundry Management System With C++

Program ini adalah aplikasi sederhana berbasis **C++** untuk mengelola data pelanggan laundry. Sistem ini mencakup proses input pelanggan, pencatatan status laundry, pembayaran, serta pencatatan total omzet. Data pelanggan disimpan menggunakan file teks untuk mempertahankan histori bahkan setelah program ditutup.

---

## 📂 Fitur Utama

✅ **Input Pelanggan**

* Menyimpan data pelanggan baru ke file `input/`
* Menampilkan dan menyimpan ke `onprocess.txt`

✅ **On-Process Customer**

* Menampilkan daftar pelanggan yang sedang diproses

✅ **Pembayaran**

* Proses pencatatan pembayaran dan pemindahan data dari proses ke folder `pembayaran/`
* Meningkatkan total omzet

✅ **Total Omzet**

* Menampilkan dan menyimpan omzet ke file `totalOmset.txt`

✅ **Data Keseluruhan**

* Menampilkan seluruh histori input pelanggan (`input/`)
* Menampilkan seluruh histori pembayaran pelanggan (`pembayaran/`)

✅ **Persistensi Data**

* Menyimpan ID terakhir ke `lastId.txt`
* Menyimpan jumlah input ke `countInput.txt`
* Menampilkan data yang masih "on process" dari `onprocess.txt`

---

## 📁 Struktur Folder yang Diperlukan

Pastikan program ini dijalankan dengan struktur folder berikut, buat folder input dan pembayaran terlebih dahulu, lainnya otomatis terbentuk saat pertama kali dijalankan, tapi bisa dibuat manual:

```
.
├── input/
├── pembayaran/
├── countInput.txt
├── lastId.txt
├── totalOmset.txt
├── onprocess.txt
├── seluruhInput.txt
├── seluruhPembayaran.txt
└── main.cpp
```

---

## 🛠️ Cara Menggunakan

1. **Compile**:

   ```bash
   g++ main.cpp -o laundryApp
   ```

2. **Jalankan program**:

   ```bash
   ./laundryApp   # atau .\laundryApp.exe untuk Windows
   ```

3. Ikuti petunjuk menu:

   ```
   [1] INPUT PELANGGAN
   [2] ONPROCESS CUSTOMER
   [3] PEMBAYARAN
   [4] TOTAL OMZET
   [5] DATA KESELURUHAN INPUT
   [6] DATA KESELURUHAN PEMBAYARAN
   [7] KELUAR
   ```

---

## 📌 Contoh Harga Paket

| Kode | Nama Paket         | Harga     |
| ---- | ------------------ | --------- |
| 1    | Cuci Aja           | 10.000/kg |
| 2    | Cuci Lipat         | 15.000/kg |
| 3    | Cuci Aja Express   | 15.000/kg |
| 4    | Cuci Lipat Express | 20.000/kg |

---

## 💡 Fitur Tambahan yang Bisa Dikembangkan

* Export ke Excel/CSV
* Interface berbasis GUI (Qt / C++ CLI / Web)
* Sorting dan pencarian pelanggan
* Backup otomatis seluruh file
* Login admin

---

## 📄 Lisensi

Kode ini bersifat open-source dan bebas digunakan untuk pembelajaran, pengembangan tugas akhir, atau pengembangan usaha kecil. Jika digunakan, mohon cantumkan atribusi kepada pembuat asli.

---
