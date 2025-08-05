#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits> // untuk numeric_limits
#include <ctime>
using namespace std;

struct node
{
    int id;
    string nama;
    float berat;
    string paket;
    int harga;
    string tglMasuk;
    string tglBayar;
    node *next;
};

node *head, *tail, *bantu, *insert, *hapus, *cari;

//untuk mengetahui total inputan
int bacaCountAllInput() {
    ifstream file("countInput.txt");
    int count = 0; // default kalau belum pernah ada file
    if (file.is_open()) {
        file >> count;
        file.close();
    }
    return count;
}
void simpanCountAllInput(int count){
    ofstream file("countInput.txt");
    file << count;
    file.close();
}

//akses omset dari file totalOmset terlebih dulu
int totalOmset() {
    ifstream file("totalOmset.txt");
    int total = 0; // default kalau belum pernah ada file
    if (file.is_open()) {
        file >> total;
        file.close();
    }
    return total;
}

int total = totalOmset(), countInput = bacaCountAllInput();
bool cekData = false, kondisiInput = true;

//menulis dan membaca omset dari file totalOmset.txt
void simpanAndShowOmset(){
    string baca;
    ofstream tulisfile("totalOmset.txt");
    tulisfile<<total<<endl;
    tulisfile.close();

    ifstream bacafile("totalOmset.txt");
    if (bacafile.is_open()) {
        bacafile>>baca;
        cout<< "\nTotal Omzet Laundry : "<<baca<<endl;
        bacafile.close();
    }
}


//Menampilkan pilihan menu
void menu() {
    cout << "\n------HSRL Laundry------" << endl;
    cout << "[1] INPUT PELANGGAN" << endl;
    cout << "[2] ONPROCESS CUSTOMER" << endl;
    cout << "[3] PEMBAYARAN" << endl;
    cout << "[4] TOTAL OMZET"<<endl;
    cout << "[5] DATA KESELURUHAN INPUT"<<endl;
    cout << "[6] DATA KESELURUHAN PEMBAYARAN"<<endl;
    cout << "[7] KELUAR" << endl;
}

//Validasi input menu
bool isAngka(const string &input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


//Input pelanggan yang masuk
void inputPelanggan(int id, string text, float berat, string paket, int harga, string tglMasuk) {
    insert = new node;
    insert->id = id;
    insert->nama = text;
    insert->berat = berat;
    insert->paket = paket;
    insert->harga = harga;
    insert->tglMasuk = tglMasuk;
    insert->next = NULL;

    tail = head;
    if (head == NULL) {
        head = insert;
    } else {
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = insert;
    }

    string filename = "input/pelanggan"+to_string(insert->id)+".txt"; //ubah id int menjadi string terlebih dulu, agar bisa di concat
    ofstream tulis_file(filename);
    tulis_file<<"ID : "<<insert->id<<endl;  
    tulis_file<<"Nama : "<<insert->nama<<endl;
    tulis_file<<"Berat : "<<insert->berat<<endl;
    tulis_file<<"Paket : "<<insert->paket<<endl;
    tulis_file<<"Harga : "<<insert->harga<<endl;
    tulis_file<<"Tanggal Masuk : "<<insert->tglMasuk<<endl;
    tulis_file.close();


    if (kondisiInput){
        countInput++;
        simpanCountAllInput(countInput);

        //tulis ulang semua isi ke onprocess.txt
        bantu = head;
        ofstream tulisfile("onprocess.txt");
        while (bantu != NULL) {
            //simpan ke file
            tulisfile<<bantu->id<<endl;  
            tulisfile<<bantu->nama<<endl;
            tulisfile<<bantu->berat<<endl;
            tulisfile<<bantu->paket<<endl;
            tulisfile<<bantu->harga<<endl;
            tulisfile<<bantu->tglMasuk<<endl;

            bantu = bantu->next;
        }
        tulisfile.close();
    }
   
}


//menampilkan proses tranksasi yang sedang berlangsung
void onprocess() {
    cout << "\nIsi Gudang : " << endl;
    if (head != NULL) {
        cekData = true;
        bantu = head;
        //tampilkan
        int no = 1;
        cout << left 
        << setw(3) << "No" << " | " 
        << setw(3) << "Id" << " | " 
        << setw(10) << "Nama" << " | "
        << setw(10) << "Berat"<< " | "
        << setw(13) << "Paket" << " | "
        << setw(10) << "Harga" << " | "
        << setw(20) << "Tanggal Masuk" << " | "
        << endl;
        cout << "-----------------------------------" << endl;

        //tulis ulang semua isi ke onprocess.txt
        ofstream tulisfile("onprocess.txt");
        while (bantu != NULL) {
            cout << left 
            << setw(3) << no << " | " 
            << setw(3) << bantu->id << " | " 
            << setw(10) << bantu->nama << " | " 
            << setw(10) << bantu->berat<< " | "
            << setw(13) << bantu->paket<< " | "
            << setw(10) << bantu->harga<< " | "
            << setw(20) << bantu->tglMasuk<< " | "
            << endl;
            no++;
            
            //simpan ke file
            tulisfile<<bantu->id<<endl;  
            tulisfile<<bantu->nama<<endl;
            tulisfile<<bantu->berat<<endl;
            tulisfile<<bantu->paket<<endl;
            tulisfile<<bantu->harga<<endl;
            tulisfile<<bantu->tglMasuk<<endl;

            bantu = bantu->next;
        }
        tulisfile.close();
        cout << endl;
    } else {
        cout << "Gudang Kosong ! " << endl;
        //hapus file onprocess.txt jika kosong (me-replace dengan file kosong)
        ofstream hapusIsi("onprocess.txt");
        hapusIsi.close();
    }
}



//mengakses jam dan tanggal secara realtime, lalu digunakan sebagai data pelanggan
string ambilTanggalHariIni() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char waktuLengkap[20];
    strftime(waktuLengkap, sizeof(waktuLengkap),"%H:%M - %d-%m-%Y",ltm);
    return string(waktuLengkap);
}


//proses pembayaran, pilih sesuai id, lalu total omset akan bertambah dan data yang dipilih akan terhapus dari onprocess
void pembayaran(int x ) {
    cari = head;
    string tglBayar = ambilTanggalHariIni(); //menambahkan tanggal bayar

    if(head->id==x) {
        string filename = "pembayaran/pelanggan"+to_string(head->id)+".txt"; //ubah id int menjadi string terlebih dulu, agar bisa di concat
        ofstream tulis_file(filename);
        tulis_file<<"ID : "<<head->id<<endl;  
        tulis_file<<"Nama : "<<head->nama<<endl;
        tulis_file<<"Berat : "<<head->berat<<endl;
        tulis_file<<"Paket : "<<head->paket<<endl;
        tulis_file<<"Harga : "<<head->harga<<endl;
        tulis_file<<"Tanggal Input : "<<head->tglMasuk<<endl;
        tulis_file<<"Tanggal Bayar : "<<tglBayar<<endl;
        tulis_file.close();

        total += head->harga;
        cout<<"Pembayaran Selesai"<<endl;

        hapus = head; 
        head = hapus->next;
        hapus->next = NULL;
        delete hapus;

        onprocess(); //update data onproses ke file setelah hapus
        simpanAndShowOmset(); //update omset ke file setelah di tambah
        return; //untuk keluar dari fungsi 

    } else {
        while(cari->next!=NULL && cari->next->id != x){
            cari = cari->next;
        }

        if(cari->next!=NULL) {
            string filename = "pembayaran/pelanggan"+to_string(cari->next->id)+".txt"; //ubah id int menjadi string terlebih dulu, agar bisa di concat
            ofstream tulis_file(filename);
            tulis_file<<"ID : "<<cari->next->id<<endl;  
            tulis_file<<"Nama : "<<cari->next->nama<<endl;
            tulis_file<<"Berat : "<<cari->next->berat<<endl;
            tulis_file<<"Paket : "<<cari->next->paket<<endl;
            tulis_file<<"Harga : "<<cari->next->harga<<endl;
            tulis_file<<"Tanggal Input : "<<cari->tglMasuk<<endl;
            tulis_file<<"Tanggal Bayar : "<<tglBayar<<endl;
            tulis_file.close();

            total += cari->next->harga;
            cout<<"Pembayaran Selesai"<<endl;

            hapus = cari->next;
            cari->next = hapus->next;
            hapus->next = NULL;
            delete hapus;

            onprocess(); //update data onproses ke file setelah hapus
            simpanAndShowOmset(); //update omset ke file setelah di tambah
        }else {
            cout<<"data tidak diketemukan "<<endl;
        }
    }
}


//menampilkan keseluruhan data yang masuk
void allInput() {
    if(countInput!=0) {
        string baris;
        int idInput = 341;
        ofstream tulisfile("seluruhInput.txt");
        cout<<"\nData Masuk Seluruh Pelanggan"<<endl;
        tulisfile<<"Data Masuk Seluruh Pelanggan"<<endl;
        for(int i=0; i<countInput; i++){
            ifstream bacafile("input/pelanggan"+to_string(idInput)+".txt");
            if(bacafile.is_open()){
                while (getline(bacafile,baris)) {
                    cout<<baris<<endl;
                    tulisfile<<baris<<endl;
                }cout<<endl;
                tulisfile<<endl;
                bacafile.close();
            }
            idInput++;
        }
        tulisfile.close();
    }else {
        cout<<"\nBelum Ada Data Input !! "<<endl;
    }
}
  
//menampilkan keseluruhan data pembayaran
void allPembayaran () {
    string baris;
    int idBayar = 341;
    ofstream tulisfile("seluruhPembayaran.txt");  
    cout<<"\nData Pembayaran Seluruh Pelanggan"<<endl;
    tulisfile<<"Data Pembayaran Seluruh Pelanggan"<<endl;
    for(int i=0; i<countInput; i++){
        ifstream bacafile("pembayaran/pelanggan"+to_string(idBayar)+".txt");
        if(bacafile.is_open()){
            while(getline(bacafile,baris)){
                cout<<baris<<endl;
                tulisfile<<baris<<endl;
            }cout<<endl;
            tulisfile<<endl;
            bacafile.close();
        }
        idBayar++;
    }
}


//untuk mengakses id terakhir dari file, dan menyimpannya
int bacaLastId() {
    ifstream file("lastId.txt");
    int id = 340; // default kalau belum pernah ada file
    if (file.is_open()) {
        file >> id;
        file.close();
    }
    return id;
}
void simpanLastId(int id) {
    ofstream file("lastId.txt");
    file << id;
    file.close();
}



//----------FUNGSI UTAMA-----------

int main() {

    //variabel untuk struct
    int makeId = bacaLastId();
    string nama;
    float  berat;
    string  paketHarga;
    float harga;


    //variabel untuk proses data dibawah
    int pilih, pilPaket,x;
    string inputMenu, baca;
    string dataBaca[100];


    //mengambil data dari onproses.txt jika ada
    ifstream bacafile("onprocess.txt");
    int k = 0;
    if (bacafile.is_open()) {
        kondisiInput = false;
        while(getline(bacafile,baca)){
            dataBaca[k++] = baca;
        }
        bacafile.close();
    }

    int jumlahNode = k/6;
    for(int i = 0; i < jumlahNode; i++){
        int offset = i*6;
        int id = stoi(dataBaca[offset]);
        string nama = dataBaca[offset+1];
        float berat = stof(dataBaca[offset+2]);
        string paket = dataBaca[offset+3];
        int harga = stoi(dataBaca[offset+4]);
        string tglMasuk = dataBaca[offset+5];
        inputPelanggan(id,nama,berat,paket,harga,tglMasuk);
    }


    //pemilihan menu
    do {
        string tglMasuk = ambilTanggalHariIni();
        system("cls");
        menu();
        cout << "Masukkan Pilihan : ";
        cin >> inputMenu;

        //validasi input
        if (!isAngka(inputMenu))
        {
            cout << "input harus berupa angka! silahkan coba lagi ! " << endl;
            system("pause");
            continue;
        }

        pilih = stoi(inputMenu);
        switch (pilih)
        {
        case 1:
            kondisiInput = true;
            cout << "Masukkan nama : ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan berat laundry (kg) : ";
            cin >> berat;
            //validasi input
            while (cin.fail() || berat <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Berat harus lebih dari 0! Masukkan ulang berat laundry: ";
                cin >> berat;
            }

            cout<<"\nPaket Laundry"<<endl;
            cout<<"[1] Cuci Aja"<<endl;
            cout<<"[2] Cuci Lipat"<<endl;
            cout<<"[3] Cuci Aja Express"<<endl;
            cout<<"[4] Cuci Lipat Express"<<endl;

            cout << "Pilih Paket : ";
            cin >> pilPaket;
            while (cin.fail() || pilPaket < 1 || pilPaket > 4) {
                //validasi input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Pilihan tidak valid! Pilih antara 1 sampai 4: ";
                cin >> pilPaket;
            }

            switch (pilPaket) {
            case 1:
                makeId++;
                simpanLastId(makeId);
                harga = berat * 10000.0;
                paketHarga = to_string(pilPaket)+" - 10000/kg";
                inputPelanggan(makeId,nama, berat,paketHarga,harga,tglMasuk);
                break;
            case 2:
                makeId++;
                simpanLastId(makeId);
                harga = berat * 15000.0;
                paketHarga = to_string(pilPaket)+" - 15000/kg";
                inputPelanggan(makeId,nama, berat,paketHarga,harga,tglMasuk);
                break;
            case 3:
                makeId++;
                simpanLastId(makeId);
                harga = berat * 15000.0;
                paketHarga = to_string(pilPaket)+" - 15000/kg";
                inputPelanggan(makeId,nama, berat,paketHarga,harga,tglMasuk);
                break;
            case 4:
                makeId++;
                simpanLastId(makeId);
                harga = berat * 20000.0;
                paketHarga = to_string(pilPaket)+" - 20000/kg";
                inputPelanggan(makeId,nama, berat,paketHarga,harga,tglMasuk);
                break;
            default:
                cout<<"Tidak ada pilihan paket"<<endl;
                break;
            }
            system("pause");
            break;
        case 2:
            onprocess();
            system("pause");
            break;
        case 3:
            onprocess();
            if(cekData){
                cout<<"\nMasukkan ID Pelanggan : ";
                cin>>x;
                //validasi input
                while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Mohon Masukkan Angka! Masukkan ID yang tertera : ";
                cin >>x;
            }
                pembayaran(x);
            }
            system("pause");
            break;
        case 4:
            simpanAndShowOmset();
            system("pause");
            break;
        case 5:
            allInput();
            system("pause");
            break;
        case 6:
            allPembayaran();
            system("pause");
            break;
        case 7:
            cout << "Anda telah Keluar dari Program" << endl;
            system("pause");
            break;
        default:
            cout << "Pilih Menu yang tersedia ! " << endl;
            system("pause");
        }
    } while (pilih != 7);

    // hapus semua node menghindari memory leak
    while (head != NULL)
    {
        hapus = head;
        head = head->next;
        hapus->next = NULL;
        delete hapus;
    }
    cin.get();
    return 0;
}