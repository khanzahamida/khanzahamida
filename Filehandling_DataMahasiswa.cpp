#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct tanggal {
    int hari, bulan, tahun;
};

struct nilai {
    float uts, uas, tugas;
};
struct mapel{
    float mtk;
    float bin;
    float big;
    float IPA;
};
struct siswa {
    string nama;
    int umur;
    string jurusan;
    tanggal lahir;
    nilai semester;
    mapel nilai; 
    string NISN;
};


float Totalnilai(nilai semester){
  return (semester.uas*0.4)+(semester.uts*0.35)+(semester.tugas*0.25);
}
float Totalmapel(mapel nilai){
    return(nilai.mtk*0.35)+(nilai.bin*0.2)+(nilai.big*0.2)+(nilai.IPA*0.25);
}

void input(int total,siswa pelajar[]){
     for (int j=0;j<total;j++){
        cout << endl;
        cout<<"======MASUKKAN DATA SISWA======"<<endl;
        cout << "masukkan nama anda: ";
        getline(cin,pelajar[j].nama);
        cout << "masukkan umur anda: ";
        cin>>pelajar[j].umur;
        cin.ignore();
        cout << "masukkan NISN anda: ";
        getline(cin,pelajar[j].NISN);
        cout << "masukkan jurusan anda: ";
        getline(cin,pelajar[j].jurusan);
        cout << "masukkan tanggal lahir anda: ";
        cin>>pelajar[j].lahir.hari;
        cin.ignore();
        cout << "masukkan bulan lahir anda: ";
        cin>>pelajar[j].lahir.bulan;
        cin.ignore();
        cout << "masukkan tahun lahir anda: ";
        cin>>pelajar[j].lahir.tahun;
        cin.ignore();
        cout << "masukkan nilai Matematika: ";
        cin>>pelajar[j].nilai.mtk;
        cin.ignore();
        cout << "masukkan nilai Bahasa Indonesia: ";
        cin>>pelajar[j].nilai.bin;
        cin.ignore();
        cout << "masukkan nilai Bahasa Inggris: ";
        cin>>pelajar[j].nilai.big;
        cin.ignore();
        cout << "masukkan nilai IPA: ";
        cin>>pelajar[j].nilai.IPA;
        cin.ignore();
        cout << "masukkan nilai uts: ";
        cin>>pelajar[j].semester.uts;
        cin.ignore();
        cout << "masukkan nilai uas: ";
        cin>>pelajar[j].semester.uas;
        cin.ignore();
        cout << "masukkan nilai tugas: ";
        cin>>pelajar[j].semester.tugas;
        cin.ignore();

    }
}
void output(int total,siswa pelajar[]){
        for (int j=0;j<total;j++){
        ofstream file ("kanjaa.txt",ios::app);
            cout<< endl;
            file <<"====== DATA SISWA KE-"<<(j+1)<<" ======"<<endl;
            file  << "nama = " << pelajar[j].nama << endl;
            file << "umur = " << pelajar[j].umur << endl;
            file << "NISN = " << pelajar[j].NISN << endl;
            file << "jurusan = " << pelajar[j].jurusan << endl;
            file  << "Tanggal,bulan,lahir "<< "=" << pelajar[j].lahir.hari << "-" << pelajar[j].lahir.bulan << "-" <<pelajar[j].lahir.tahun<<endl;
            file  << "Nilai Matematika = " << pelajar[j].nilai.mtk << endl;
            file << "Nilai Bahasa Indonesia = " << pelajar[j].nilai.bin << endl;
            file << "Nilai Bahasa Inggris = " << pelajar[j].nilai.big << endl;
            file << "Nilai IPA = " << pelajar[j].nilai.IPA << endl;
            file  << "nilai uts: " << pelajar[j].semester.uts << endl;
            file << "nilai uas: " << pelajar[j].semester.uas << endl;
            file << "nilai tugas: " << pelajar[j].semester.tugas << endl;
            file <<"nilai akhir mapel: "<<Totalmapel(pelajar[j].nilai)<<endl;
            file <<"nilai akhir siswa: "<<Totalnilai(pelajar[j].semester)<<endl;
        file.close();
    }
}
void search(){
    string nisn;
    cout << "Masukkan NISN siswa: ";
    cin >> nisn;
    ifstream file("kanjaa.txt");
    bool menemukan = false;
    string baris;
    string header = "";
    while (getline(file, baris)) {
        if (baris.find("======") == 0) {
            header = baris;
        }
        if (baris == "NISN = " + nisn) {
            menemukan = true;
            cout << "Data siswa yang dicari: " << endl;
            cout << header << endl;
            cout << baris << endl;
            while (getline(file, baris)) {
                cout << baris << endl;
                if (baris.find("======") == 0) break;
            }
            break;
        }
        
    }
    if (!menemukan) {
        cout << "siswa dengan nisn :" << nisn << "tidak ditemukan." << endl;
    }
    file.close();
}

void peringkat_siswa(int total,siswa pelajar[])
{
    for (int k=0; k<total-1;k++){
        for (int l=0; l<total-k-1;l++){
            if (Totalmapel(pelajar[l].nilai)<Totalmapel(pelajar[l+1].nilai)){
                siswa tukar = pelajar[l];
                pelajar [l]=pelajar[l+1];
                pelajar [l+1]=tukar;
            }
        }
    } 
    cout<<"======RANGKING SISWA====="  <<endl;
    for(int j = 0; j<total;j++){
        cout<< "RANGKING -->"<<j+1<<endl;
        cout<<"NAMA: "<<pelajar[j].nama<<endl;
        cout<<"NISN: "<<pelajar[j].NISN<<endl;
        cout<<"JURUSAN: "<<pelajar[j].jurusan<<endl;
        cout<<"NILAI AKHIR : "<<Totalmapel(pelajar[j].nilai)<<endl;
        cout<<"======================="<<endl;
    }
}

int main()
{
    ifstream file("kanjaa.txt");
    if(file.peek() == ifstream::traits_type::eof()){
        int total;
        cout << "masukkan jumlah siswa: ";
        cin >> total;
        siswa pelajar[total];
        cin.ignore();
        input(total,pelajar);
        output(total,pelajar);
        peringkat_siswa(total,pelajar);
        cout << "data siswa telah ditambahkan dan disimpan dalam file kanjaa.txt" << endl;
    }
    else{
        string baris;
        while(getline(file,baris)){
            cout<<baris<<endl;
        }
        file.close();
        char pilihan;
        cout <<"apakah anda ingin menambahkan data siswa lagi? (y): ";
        cin >> pilihan;
        if(pilihan == 'y' || pilihan == 'Y'){
            int total;
            cout << "masukkan jumlah siswa: ";
            cin >> total;
            siswa pelajar[total];
            cin.ignore();
            input(total,pelajar);
            output(total,pelajar); 
            peringkat_siswa(total,pelajar);
            cout << "data telah ditambahkan dan disimpan dalam file kanjaa.txt" << endl;

        }
    char opsi2;
    cout << "Apakah anda ingin mencari siswa (s)? ";
    cin >> opsi2;
    if (opsi2 == 's' || opsi2 == 'S') {

         search();
    }
}
    return 0;
}