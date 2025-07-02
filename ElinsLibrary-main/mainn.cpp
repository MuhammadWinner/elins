#include <iostream> // Untuk fungsi input output.
#include <thread>   // Untuk fungsi sleep_for delay eksekusi program.
#include <chrono>   // Digunakan bersama library thread, Untuk fungsi pengaturan waktu dan melakukan delay.
#include <cstdlib>  // Untuk fungsi system() digunakan untuk pembersihan terminal.
#include <ctime>    // Untuk fungsi waktu saat ini time().

using namespace std;

bool isUserRegistered = false, isAccesApp = false, isBorrow = false;

// Deklarasi fungsi
void menuPage(), greeting(), clearTerminal(), back(), registerUser(), loginUser(), about(), bookList(), borrowing(), returnBook(), runProgram(), sleep(string satuanWaktu, int lamanya), greetingAnimate(int seconds);

// Data
struct userData {
    string username;
    string password;
    string loanHistory;
};
userData user[1] = {
    {"username", "password", "loanHistory"}
};
struct listBooks {
    // struct daftar buku
    int numb;
    string judul;
    string namaPenulis;
    int tahunTerbit;
    long long uniqueId;
};
listBooks books[50] = {
    // Daftar 50 buku
    {1, "Pemburu Mimpi", "Haruki Murakami", 2009, 0001},
    {2, "Matahari Terbit", "Ernest Hemingway", 1926, 0002},
    {3, "Cahaya Kecil", "Anthony Doerr",2014, 0003},
    {4, "Lelaki Terbalik" ,"Orhan Pamuk",1999, 0004},
    {5, "Perahu Kertas" ,"Dee Lestari",2008, 0005},
    {6, "Ketika Mas Gagah Pergi" ,"Helvy Tiana Rosa",2012, 0006},
    {7, "Sapiens: Sejarah Manusia" ,"Yuval Noah Harari",2014, 0007},
    {8, "Rantau 1 Muara" ,"Ahmad Fuadi",2009, 0010},
    {9, "1984" ,"George Orwell",1949, 0011},
    {10, "Pergi" ,"Tere Liye",2011, 0012},
    {11, "The Great Gatsby" ,"F.Scott Fitzgerald",1925, 0013},
    {12, "Ayat ayat Cinta" ,"Habiburrahman El Shirazy",2004, 0014},
    {13, "To Kill a Mockingbird" ,"Harper Lee",1960, 0015},
    {14, "Laskar Pelangi" ,"Andrea Hirata",2005, 0016},
    {15, "The Catcher in the Rye" ,"J.D.Salinger",1951, 0017},
    {16, "Gone with the Wind" ,"Margaret Mitchell",1936, 0020},
    {17, "Dilan: Dia adalah Dilanku Tahun 1990" ,"Pidi Baiq",2014, 0021},
    {18, "Brave New World" ,"Aldous Huxley",1932, 0022},
    {19, "Bumi Manusia" ,"Pramoedya Ananta Toer",1980, 0023},
    {20, "The Alchemist" ,"Paulo Coelho",1988, 0024},
    {21, "Norwegian Wood" ,"Haruki Murakami",1987, 0025},
    {22, "Harry Potter and the Philosopher's Stone" ,"J.K.Rowling",1997, 0026},
    {23, "Jane Eyre" ,"Charlotte Brontë",1847, 0027},
    {24, "Kafka on the Shore" ,"Haruki Murakami",2002, 0030},
    {25, "The Lord of the Rings: The Fellowship of the Ring" ,"J.R.R.Tolkien",1954, 0031},
    {26, "Aku Ini Binatang Jalang" ,"Chairil Anwar",1943, 0032},
    {27, "One Hundred Years of Solitude" ,"Gabriel García Márquez",1967, 0033},
    {28, "Matinya Seorang Penyair" ,"Taufiq Ismail",1963, 0034},
    {29, "The Hunger Games" ,"Suzanne Collins",2008, 0035},
    {30, "Kau, Aku, dan Sepucuk Angpau Merah" ,"Tere Liye",2005, 0036},
    {31, "The Road" ,"Cormac McCarthy",2006, 0037},
    {32, "Ayahku Bukan Pembohong" ,"Tere Liye",2006, 0040},
    {33, "The Hitchhiker's Guide to the Galaxy" ,"Douglas Adams",1979, 0041},
    {34, "Pulang" ,"Tere Liye",2008, 0042},
    {35, "Fahrenheit 451" ,"Ray Bradbury",1953, 0043},
    {36, "Lima Sekawan" ,"Enid Blyton",1942, 0044},
    {37, "The Da Vinci Code" ,"Dan Brown",2003, 0045},
    {38, "Negeri 5 Menara" ,"Ahmad Fuadi",2009, 0046},
    {39, "Misteri Gunung Merapi" ,"S.H.Mintardja",1967, 0047},
    {40, "The Girl with the Dragon Tattoo" ,"Stieg Larsson",2005, 0050},
    {41, "Bumi" ,"Tere Liye",2015, 0051},
    {42, "The Color Purple" ,"Alice Walker",1982, 0052},
    {43, "Rumah Kaca" ,"Pramoedya Ananta Toer",1988, 0053},
    {44, "The Hobbit" ,"J.R.R.Tolkien",1937, 0054},
    {45, "Hujan Bulan Juni" ,"Sapardi Djoko Damono",1964, 0055},
    {46, "The Fault in Our Stars" ,"John Green",2012, 0056},
    {47, "Ketika Cinta Bertasbih" ,"Habiburrahman El Shirazy",2004, 0057},
    {48, "Sang Pemimpi" ,"Andrea Hirata",2006, 0060},
    {49, "The Kite Runner" ,"Khaled Hosseini",2003, 0061},
    {50, "Hujan Matahari" ,"Fira Basuki",2005, 0062},
};

// Navigasi & Shortcut(utility)
string thankU(){
    return  R"(
         /$$$$$$$$ /$$                           /$$             /$$     /$$                  /$$
        |__  $$__/| $$                          | $$            |  $$   /$$/                 | $$
           | $$   | $$$$$$$   /$$$$$$  /$$$$$$$ | $$   /$$       \  $$ /$$//$$$$$$  /$$   /$$| $$
           | $$   | $$__  $$ |____  $$| $$__  $$| $$  /$$/        \  $$$$//$$__  $$| $$  | $$| $$
           | $$   | $$  \ $$  /$$$$$$$| $$  \ $$| $$$$$$/          \  $$/| $$  \ $$| $$  | $$|__/
           | $$   | $$  | $$ /$$__  $$| $$  | $$| $$_  $$           | $$ | $$  | $$| $$  | $$    
           | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$ \  $$          | $$ |  $$$$$$/|  $$$$$$/ /$$
           |__/   |__/  |__/ \_______/|__/  |__/|__/  \__/          |__/  \______/  \______/ |__/
    )";
}
void sleep(string satuanWaktu, int lamanya) {
    if (satuanWaktu == "miliseconds") {
        this_thread::sleep_for(chrono::milliseconds(lamanya));
    }else if (satuanWaktu == "seconds") {
        this_thread::sleep_for(chrono::seconds(lamanya));
    }else if (satuanWaktu == "minutes") {
        this_thread::sleep_for(chrono::minutes(lamanya));
    }else if (satuanWaktu == "hours") {
        this_thread::sleep_for(chrono::hours(lamanya));
    } 
}
void countdown(int seconds) {
    cout << endl;
    for (int i = seconds; i > 0; --i) {
        cout << "Tunggu sebentar! Kamu akan diarahkan ke halaman selanjutnya dalam: " << i << " seconds...\r" << flush;
        sleep("seconds", 1);
    }
}
void clearTerminal() {
    // Membersihkan terminal
    #ifdef _WIN32
    system("cls"); // Untuk Windows
    #else
    system("clear"); // Untuk Unix/Linux
    #endif
}
void back() {
    string a;
    do {
        cout << "\nTekan 'x' untuk kembali ke menu" << endl;
        cin >> a;
        if (a == "x") {
            clearTerminal();
            break;
        }
        else {
            cout << "\n*** Input tidak valid. Coba lagi. ***" << endl;
        }
    } while (true);
}
void greeting() {
    greetingAnimate(3);
    cout << thankU();
    cout << "\n             -=== Terimakasih, Selamat beraktivitas kembali! ===-" << endl;
    sleep("miliseconds", 2000);
    clearTerminal();
}
void greetingAnimate(int seconds) {
    string greeting = thankU();

    int greetingLength = greeting.size();
    string spaces(greetingLength, ' ');

    for (int i = seconds; i > 0; --i) {
        cout << greeting;
        sleep("miliseconds", 600);
        clearTerminal();
        sleep("miliseconds", 100);
    }
}

// Register & Login
void registerUser() {
    cout << "Daftar\n";
    cout << "Username: ";
    cin >> user[0].username;
    isUserRegistered = true;
    cout << "Password: ";
    cin >> user[0].password;
    cout << "\nPendaftaran berhasil!\n";
    countdown(2);
    clearTerminal();
}
void loginUser() {
    cout << "Login\n";
    cout << "Masukkan username yang terdaftar: ";
    string username;
    cin >> username;
    cout << "Password: ";
    string password;
    cin >> password;

    if (isUserRegistered && username == user[0].username && password == user[0].password) {
        cout << "\nLogin successful! Welcome, " << user[0].username << "!\n";
        countdown(2);
        clearTerminal();
        menuPage();
    }
    else {
        cout << "\n*** User not found. Please register first. ***\n";
        countdown(2);
        clearTerminal();
    }
}

// Menu
void about() {
    // Menu Tentang Perpustakaan
    clearTerminal();
    cout << "Selamat datang di Elins Library – tempat di mana pengetahuan bersatu dengan kreativitas! Di sini, kami merayakan warisan intelektual yang dibangun oleh tiga pikiran brilian: Luthfi Awaludin Safi, pakar sejarah yang membawa kita ke masa lalu; Kurniawan Arthur Jarnuzi, ilmuwan komputer yang membuka jendela dunia digital; dan Muhammad Winner An Nuur Alam Suskalanggeng, sastrawan yang memberi ruang pada keindahan kata.\n" << endl;
    cout << "Mari temukan keajaiban di setiap halaman buku, jelajahi sumber daya digital yang mutakhir, dan rasakan kehangatan seni yang menyelimuti ruang baca kami.Perpustakaan ini bukan hanya tempat untuk membaca, tapi juga untuk memimpikan, mencipta, dan berkumpul sebagai komunitas pencinta ilmu.\n" << endl;
    cout << "Selamat menikmati petualangan intelektual Anda di Elins Library tempat di mana setiap cerita memiliki peluang untuk merajut kisahnya sendiri.Selamat membaca dan menemukan inspirasi!\n";
    back();
}
void bookList() {
    // Menu Daftar Buku
    clearTerminal();
    cout << "Daftar Buku - Elins Library\n" << endl;
    cout << "No     Judul       Nama Penulis    Tahun" << endl;
    for (int i = 0; i < 50; i++) {
        cout << books[i].numb << ".   " << books[i].judul << "; " << books[i].namaPenulis << "  " << books[i].tahunTerbit << "." << endl;
    }
    back();
}
void borrowing() {
    clearTerminal();
    cout << "Daftar buku yang bisa dipinjam: \n" << endl;
    srand(time(nullptr) + clock());
    int randomNum = rand() % 25;
    int randomNum2 = rand() % 25 + 25;
    int temp = 0;
    for (int i = randomNum; i < randomNum2; i++) {
        cout << books[temp].numb << ". " << books[i].judul << " " << books[i].namaPenulis << " " << books[i].tahunTerbit << " id:" << books[i].uniqueId << "." << endl;
        temp += 1;
    }
    int whatBook;
    do {
        string yesOrNo;
        cout << "\nPilih buku yang mau kamu pinjam(id): ";
        cin >> whatBook;
        if (whatBook >= randomNum && whatBook <= randomNum2) {
            for (int i = randomNum; i < randomNum2; i++) {
                if (books[i].uniqueId == whatBook) {
                    string loanedBook;
                    cout << books[i].judul << " " << books[i].namaPenulis << " " << books[i].tahunTerbit << " id:" << books[i].uniqueId << "." << endl;
                    cout << "Apakah judulnya sudah sesuai?(y/n)";
                    cin >> yesOrNo;
                    if (yesOrNo == "y") {
                        cout << "Terimakasih atas kunjungan anda di perpustakaan kami! Semoga buku yang anda pinjam bermanfaat." << endl;
                        loanedBook = books[i].judul;
                        user[0].loanHistory = loanedBook;
                        isBorrow = true;
                    }
                    else {
                        cout << "Silahkan pilih ulang!" << endl;
                        isBorrow = false;
                    }
                }
            }
        }
        else {
            cout << "Id buku tidak ditemukan, silahkan pilih ulang." << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
    } while (isBorrow == false);
    
    back();
}
void returnBook() {
    if (user[0].loanHistory == "loanHistory") cout << "Kamu belum melakukan peminjaman buku." << endl;
    else {
        cout << "Berikut buku yang pernah kamu pinjam: \n" << endl;
        cout << "Username: " << user[0].username << endl;
        cout << "Judul buku: " << user[0].loanHistory << "\n\n";
        char yOrN;
        cout << "Apakah kamu mau mengembalikan buku tersebut?(y/n): ";
        cin >> yOrN;
        if (yOrN == 'y') {
            cout << "Buku telah berhasil dikembalikan, Terimakasih!" << endl;
        }
        else if (yOrN == 'n') {
            cout << "Mohon perhatikan tanggal pengembalian buku, jika melebihi batas maksimal waktu pengembalian buku akan dikenakan denda, Terimakasih!" << endl;
        }
        else cout << "Masukkan pilihan yang benar(y/n)" << endl;
    }
    back();
}
void menuPage() {
    int pilihan;
    do {
        cout << "  _ __ ___   ___ _ __  _   _ \n"
            " | '_ ` _ \\ / _ \\ '_ \\| | | |\n"
            " | | | | | |  __/ | | | |_| |\n"
            " |_| |_| |_|\\___|_| |_|\\__,_|\n";
        cout << "\nMenu:\n";
        cout << "1. Tentang Perpustakaan\n";
        cout << "2. Daftar Buku\n";
        cout << "3. Peminjaman\n";
        cout << "4. Pengembalian\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
        case 1:
            // Tentang perpustakaan
            about();
            break;
        case 2:
            // Implementasi daftar buku
            bookList();
            break;
        case 3:
            // Implementasi peminjaman
            borrowing();
            break;
        case 4:
            // Implementasi pengembalian
            returnBook();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan layanan perpustakaan kami!" << endl;
            clearTerminal();
            greeting();
            isAccesApp = false;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
            sleep("miliseconds", 2000);
        }
    } while (pilihan != 5);
}

// Main program
void runProgram() {
    //Welcome message
    char welcome;
    do {
        cout << R"(
        ___                            ___      ___                                           
       (   ) .-.                      (   ) .-.(   )                                          
  .--.  | | ( __) ___ .-.     .--.     | | ( __)| |.-.  ___ .-.    .---.  ___ .-.   ___  ___  
 /    \ | | (''")(   )   \  /  _  \    | | (''")| /   \(   )   \  / .-, \(   )   \ (   )(   ) 
|  .-. ;| |  | |  |  .-. . . .' `. ;   | |  | | |  .-. || ' .-. ;(__) ; | | ' .-. ; | |  | |  
|  | | || |  | |  | |  | | | '   | |   | |  | | | |  | ||  / (___) .'`  | |  / (___)| |  | |  
|  |/  || |  | |  | |  | | _\_`.(___)  | |  | | | |  | || |       / .'| | | |       | '  | |  
|  ' _.'| |  | |  | |  | |(   ). '.    | |  | | | |  | || |      | /  | | | |       '  `-' |  
|  .'.-.| |  | |  | |  | | | |  `\ |   | |  | | | '  | || |      ; |  ; | | |        `.__. |  
'  `-' /| |  | |  | |  | | ; '._,' '   | |  | | ' `-' ; | |      ' `-'  | | |        ___ | |  
 `.__.'(___)(___)(___)(___) '.___.'   (___)(___) `.__. (___)     `.__.'_.(___)      (   )' |  
                                                                                     ; `-' '  
                                                                                      .__.'   
)" << endl;
        cout << "Selamat datang di Perpustakaan Elins" << endl;
        cout << "1. Login" << endl;
        cout << "2. Daftar" << endl;
        cout << "3. Keluar" << endl;
        cout << "Silahkan Login terlebih dahulu! jika belum memiliki akun pilih daftar(1/2): ";
        cin >> welcome;

        switch (welcome) {
        case '1':
            // Login page
            clearTerminal();
            loginUser();
            break;
        case '2':
            // Registration page
            clearTerminal();
            registerUser();
            break;
        case '3':
            //Keluar
            exit(0);
        default:
            cout << "Masukan pilihan nomor yang benar (1/2/3)" << endl;
            cin.clear();
            cin.ignore(123, '\n');
            sleep("miliseconds", 2000);
            clearTerminal();
            break;
        }
    } while (isAccesApp == true);
}

int main() {
    isAccesApp = true;
    runProgram();
    return 0;
}
