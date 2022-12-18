#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>


#include "TextTable.h"
#include "gotoxy.h"

using namespace std;

struct dll
{
    string file_name; // file name image
    string gambar; // gambar di representasikan dengan matriks
    int width; // dimensi x gambar
    int height; // dimensi y gambar
    int size; // datanya
    time_t waktu; // date add image
    dll *next; // menunjuk node selanjutnya
    dll *prev; // menunjuk node sebelumnya
};

dll *head = NULL;
dll *tail = NULL;
//cari jumlah data
int totalData(){
    int hasil=0;
    dll * bantu = tail;
    do{
        hasil++;
        bantu = bantu->prev;
    }while (bantu != tail);
    return hasil;
}

int cekFileName(string file_name){
    int hasil=0;
    if(head==NULL){
        hasil=0;    
    }else{
        dll * bantu = tail;
        do{
            if(bantu->file_name==file_name){
                hasil=1;
            }
            bantu = bantu->prev;
        }while (bantu != tail);  
    }

    return hasil;
}

//pembuatan gambar dengan array 2d
string gambar(int width,int height){
    int gambar[width][height];

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            gambar[i][j]= (0 + (rand() % 2));
        }
    }
    string hasil;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            hasil.append(to_string(gambar[i][j]));
        }
        hasil.append("\n");
    }
    return hasil;
}
// insert depan
void add() {
    dll *baru;
    baru = new dll;
    string file_name;
    do{
        cout << "input file name : "; getline(cin >> ws, file_name); // input file name
        if(cekFileName(file_name)==1){
            cout << "nama sudah ada\n";
        }else{
            baru->file_name=file_name;
        }
    }while(cekFileName(file_name)==1);

    cout << "input size : "; cin >> baru->size; // input size
    cout << "input width : "; cin >> baru->width; // input size
    cout << "input height : "; cin >> baru->height; // input size
    baru->gambar = gambar(baru->width,baru->height); // generate gambar
    baru->waktu = time(0); // input waktu sekarang
    
    baru->next = NULL;
    baru->prev = NULL;

   if(head == NULL) {
        head = baru;
        tail = baru;
        baru->next = tail;
        baru->prev = head;
   } else {
        baru->next = head;
        head->prev = baru;
        head = baru;
        head->prev = tail;
        tail->next = head;
   }
   cout<<"Data masuk\n";
   getch();
   system("cls");
}

// delete depan
void delete_depan(){
    dll *hapus;
    hapus = head;
    if(head == NULL){
        cout << "Data masih kosong" << endl;
    }else if (head == tail){
        delete head;
        head = NULL;
        tail = NULL;
    }else {
        hapus = head;
        head = head->next;
        delete hapus;
        tail->next = head;
        head->prev = tail;
    }
    cout << "Data Terhapus" << endl;
}

// delete belakang
void delete_belakang(){
    dll *hapus;
    hapus = tail;
    if(head == NULL){
        cout << "Data masih kosong" << endl;
    }else if(head == tail){
        delete tail;
        head = NULL;
        tail = NULL;
    }else {
        hapus = tail;
        tail = tail->prev;
        delete hapus;
        tail->next = head;
        head->prev = tail;
    }
    cout << "Data Terhapus" << endl;
}
void delete_tengah(string datacari) {
    dll *hapus, *bantu;
    
    if(head == NULL){
        cout << "Data Masih Kosong" << endl;
    }else{

        bantu = head;
        do {
            if (datacari == bantu->file_name){
                if (head == tail){
                    delete head;
                    head = NULL;
                    tail = NULL;
                    break;
                    
                } else if (bantu == head){
                    delete_depan();
                    break;
                
                } else if(bantu == tail) {
                    delete_belakang();
                    break;

                } else {
                    hapus = bantu;
                    bantu->prev->next = bantu->next;
                    bantu->next->prev = bantu->prev;
                    delete hapus;
                    break;
                }
                cout << "Data berhasil tehapus";
            } 
            bantu = bantu->next;
        } while(bantu != head);
    }

    cout << "\n\nPress any key to continue...";
    getch();
}
// tampil rincian
void tampilrincian() {
    dll * bantu = head;
    if(head == NULL){
        cout << "data kosong";
        getch();
    }
    else
    {
        int pilih=0;
        do{
            if(head == NULL){
                cout << "data kosong";
                getch();
                pilih=0;
            }
            else{
                int x=20,y=1;
                
                for(int i =0;i < (bantu->width * bantu->height) +bantu->height;i++){
                    if(bantu->gambar[i]!='\n'){
                        gotoxy(x++,y);cout << bantu->gambar[i] <<"\n";
                    }else{
                        y++;
                        x=20;
                    }
                }
                cout << "\nRincian\n";
                cout << "File name : "<<bantu->file_name <<"\n";
                cout << "Size : "<<bantu->size <<" KB \n";
                cout << "Dimensi : "  << bantu->width <<"x" << bantu->height <<"\n\n";
            
                cout << "1. Next\n";
                cout << "2. prev\n";
                cout << "3. Delete\n";
                cout << "0. exit\n";
                cin >> pilih;
                if(pilih == 1 ){
                    bantu = bantu->next;
                }
                else if(pilih == 2){
                    bantu = bantu->prev;
                }
                else if(pilih == 3){
                    delete_tengah(bantu->file_name);
                    bantu = bantu->next;
                }
                else{
                    cout << "pilihan salah";
                }
            }
           system("cls");
        }
        while (pilih!=0);
    }

    
}
void tampilsemua(){
    dll * bantu = head;
    if(head == NULL){
        cout << "data kosong";
    }
    else
    {
        TextTable t( '-', '|', '+' );
        t.add("File Name");t.add("Waktu Dibuat"); t.add("size"); t.add("Width");t.add("Height");t.endOfRow();
        do{
            string waktu = ctime(&bantu->waktu);
            waktu.erase(prev(waktu.end()));
            
            t.add(bantu->file_name);
            t.add(waktu);
            t.add(to_string(bantu->size) + " KB");
            t.add(to_string(bantu->width));
            t.add(to_string(bantu->height));
            
            t.endOfRow();
            
            bantu = bantu ->next;
        }
        while (bantu != head);
        t.setAlignment( totalData(), TextTable::Alignment::LEFT );
        cout << t;
    }
    
}


//cari data(cek dulu)
void cari_data(){
    dll *bantu;
    if(head == NULL) {
        cout << "Sorry data kosong";
    } else {
        string datacari;
        bantu = head;
        int flag=0;
        cout << "input cari apa : "; getline(cin >> ws, datacari);
        do {
            if(datacari == bantu->file_name) {
                flag=1;
            }
            bantu = bantu->next;
        } while(bantu != head);
        if(flag==1) {
            cout << "Data ketemu";
        }else {
            cout << "Data tidak ketemu";
        }
    }

    cout << "\n\nPress any key to continue...";
    getch();
}



//buat sorting ukuran
void sorting_ukuran(){
    dll* bantu2 = head->next;
    cout << " 1. ASCENDING or 2. DESCENDING?\n";
    int pilih; cin >> pilih;
    while (bantu2 != tail->next)
    {
        dll* bantu=head;

        while (bantu != bantu2)
        {
            if(pilih==1){
                if (bantu2->size < bantu->size)
                {
                    swap(bantu2->size, bantu->size);
                    swap(bantu2->waktu, bantu->waktu);
                    swap(bantu2->file_name, bantu->file_name);
                    swap(bantu2->width, bantu->width);
                    swap(bantu2->height, bantu->height);
                    swap(bantu2->gambar, bantu->gambar);
                    
                }
            }
            else if(pilih==2){
                if (bantu2->size < bantu->size)
                {
                    swap(bantu2->size, bantu->size);
                    swap(bantu2->waktu, bantu->waktu);
                    swap(bantu2->file_name, bantu->file_name);
                    swap(bantu2->width, bantu->width);
                    swap(bantu2->height, bantu->height);
                    swap(bantu2->gambar, bantu->gambar);
                    
                }
            }
            else{
                cout << "pilihan salah";
            }
            
            bantu=bantu->next;
        }
        bantu2 = bantu2->next;
    }
}

//buat sorting waktu
void sorting_waktu(){
    dll* bantu2 = head->next;
    cout << " 1. ASCENDING or 2. DESCENDING?\n";
    int pilih; cin >> pilih;
    while (bantu2 != tail->next)
    {
        dll* bantu=head;

        while (bantu != bantu2)
        {
            if(pilih==1){
                if (bantu2->waktu < bantu->waktu)
            {
                swap(bantu2->size, bantu->size);
                swap(bantu2->waktu, bantu->waktu);
                swap(bantu2->file_name, bantu->file_name);
                swap(bantu2->width, bantu->width);
                swap(bantu2->height, bantu->height);
                swap(bantu2->gambar, bantu->gambar);
            }
            }
            else if(pilih==2){
                if (bantu2->waktu > bantu->waktu)
            {
                swap(bantu2->size, bantu->size);
                swap(bantu2->waktu, bantu->waktu);
                swap(bantu2->file_name, bantu->file_name);
                swap(bantu2->width, bantu->width);
                swap(bantu2->height, bantu->height);
                swap(bantu2->gambar, bantu->gambar);
            }
            }
            else{
                cout << "pilihan salah";
            }
            
            bantu=bantu->next;
        }
        bantu2 = bantu2->next;
    }
}

void sorting_nama() {
    dll* bantu2 = head->next;
    cout << " 1. ASCENDING or 2. DESCENDING?\n";
    int pilih; cin >> pilih;
    while (bantu2 != tail->next)
    {
        dll* bantu=head;

        while (bantu != bantu2)
        {
            if(pilih==1){
                if (bantu2->file_name < bantu->file_name)
                {
                    swap(bantu2->size, bantu->size);
                    swap(bantu2->waktu, bantu->waktu);
                    swap(bantu2->file_name, bantu->file_name);
                    swap(bantu2->width, bantu->width);
                    swap(bantu2->height, bantu->height);
                    swap(bantu2->gambar, bantu->gambar);
                }
            }
            else if(pilih==2){
                if (bantu2->file_name > bantu->file_name)
                {
                    swap(bantu2->size, bantu->size);
                    swap(bantu2->waktu, bantu->waktu);
                    swap(bantu2->file_name, bantu->file_name);
                    swap(bantu2->width, bantu->width);
                    swap(bantu2->height, bantu->height);
                    swap(bantu2->gambar, bantu->gambar);
                }
            }
            else{
                cout << "Pilihan salah";
            }
            
            bantu=bantu->next;
        }
        bantu2 = bantu2->next;
    }
}


int main() {
    int pilih;
    do {
        system("cls");
        transisi();
        cout << "\n============================================" << endl;
        cout << "=      DOUBLE LINKED LIST GALERI FOTO      =" << endl;
        cout << "============================================" << endl;
        cout << "= 1. Tambah data                           =" << endl;
        cout << "= 2. Urutkan berdasarkan ukuran            =" << endl;
        cout << "= 3. Urutkan berdasarkan waktu             =" << endl;
        cout << "= 4. Urutkan berdasarkan nama              =" << endl;
        cout << "= 5. Hapus Data                            =" << endl;
        cout << "= 6. Cari Data                             =" << endl;
        cout << "= 7. Tampil Data Rincian                   =" << endl;
        cout << "= 8. Tampil Seluruh Data                   =" << endl;
        cout << "= 0. Selesai                               =" << endl;
        cout << "============================================" << endl;
        cout << "\nPilihan Anda [1-10] : "; cin >> pilih;
        system("cls");
        if(pilih == 1){ 
            add();
        }
        if (pilih == 2){
            sorting_ukuran();
        }
        if (pilih == 3){
            sorting_waktu();
        }
        if (pilih == 4){
            sorting_nama();
        }
        if(pilih == 5){
            string datacari;
            cout << "PILIH DATA UNTUK DIHAPUS\n\n";
            tampilsemua();
            cout << "\n\nInput nama file : "; getline(cin >> ws, datacari);
            delete_tengah(datacari);
        }
        if(pilih == 6){
            cari_data();
        }

        if(pilih == 7){
            tampilrincian();
        }

        if(pilih == 8){
            tampilsemua();
            cout << "\n\nPress any key to continue...";
            getch();
        }

    } while(pilih != 0);

    return 0;
}