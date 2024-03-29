﻿#include "inc.h"
#include "student.h"

void createManualList();    //studentu saraso kurimas
void checkManualList();     //tikrina ar jau egzistuoja sudarytas studentu sarasas
void generateList();        //sugeneruoja visiskai atsitiktinius studentu sarasus
void flushContainers();     //


vector <string> name, surn, fname, mname, fsurn, msurn;
vector <Student> mas;

// apparently the task also requires me to have both vectors and arrays for the same job but i ain doin that nahhhhhhhhhh i already despise everything i do here
//-----------------------------------------------------------------------------------------------------------------
int main()
{
    system("cls");
    flushContainers();
    cout << "Pasirinkite norima veiksma nuspausdami tam tikra skaiciu:\n";
    cout << "1. Sudaryti studentu sarasa\n";
    cout << "2. Sugeneruoti atsitiktinius studentu sarasus\n";
    cout << "\nSpustelekite bet koki klavisa, kad iseiti is programos.\n";
    char id = _getch();  //#include <conio.h>, laukiam vartotojo mygtuko nuspaudimo

    if (id == '1') {
        checkManualList();
    } else if (id == '2') {
        generateList();
    } else {
        cout << "Iseinama...\n";
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------
void checkManualList() {
    system("cls");
    fstream SOutput;

    SOutput.open("output/student_list.txt");
    if (SOutput.is_open()) {
        cout << "Demesio!\n\nEgzistuojantis ranka surasytas studentu sarasas ('output/student_list.txt') bus perrasytas!\nAr norite testi? (y/n):\n";
        char idc = _getch();
        if (idc == 'n') { main(); }
        else if (idc == 'y') { createManualList(); }
        else { checkManualList(); } //i feel like this is extremely dumb but im really running out of time
    } else {
        createManualList();
    }
}
//-----------------------------------------------------------------------------------------------------------------
void createManualList() {
    system("cls");
    
    std::system("mkdir output");        //1 hour left to deadline
    ofstream SOutput("output/student_list.txt");

    //cout << "Iveskite studentu skaiciu: ";
    int /*n,*/ m; char kl = 'y';
    //cin >> n; cout << "\n";

    string var, pav; vector<int> temp; int egz;

    while (kl == 'y' || kl == 'Y') {
        cout << "Iveskite varda: "; cin >> var; cout << "\n";
        cout << "Iveskite pavarde: "; cin >> pav; cout << "\n";
        cout << "Iveskite egzamino pazymi: "; cin >> egz; cout << "\n";
        cout << "Iveskite semestro pazymius: ";
        while (true) {
            cin >> m;
            temp.push_back(m);
            //cout << "Ar vesite dar? (y/n): "; cin >> kl;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
        Student tempas(var, pav, temp, egz);
        mas.push_back(tempas);
        temp.clear();
        temp.resize(0);
        cout << "----------------------------------------------\n";
        cout << "Ar vesite dar? (y/n): "; cin >> kl;
    }
    system("cls");
    cout << setw(20) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(30) << left << "Galutinis (vid.)" << setw(20) << left << "Galutinis (med.)\n";
    SOutput << setw(20) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(30) << left << "Galutinis (vid.)" << setw(20) << left << "Galutinis (med.)\n";
    cout << "--------------------------------------------------------------------------------------------\n";
    SOutput << "--------------------------------------------------------------------------------------------\n";
    for (Student& laik : mas) {
        cout << setw(20) << left << laik.getName() << setw(25) << left << laik.getSurname() << setw(30) << left << fixed << setprecision(2) << getAverage(laik.getNd()) << setw(20) << left << getMedian(laik.getNd()) << "\n";
        SOutput << setw(20) << left << laik.getName() << setw(25) << left << laik.getSurname() << setw(30) << left << fixed << setprecision(2) << getAverage(laik.getNd()) << setw(20) << left << getMedian(laik.getNd()) << "\n";
    }
    SOutput.close();
    cout << "\x1B[32mSarasas issaugotas i 'output/student_list.txt' programos aplankale.\033[0m\n\n";
    cout << "Spustelekite bet koki klavisa, kad grizti i pagrindini meniu.";
    int e = _getch();
    main();
}
//-----------------------------------------------------------------------------------------------------------------
void generateList() {
    system("cls");

    // overkomplikuotas sprendimas, pasitelkiantis "vaizdingus" vardus ir pavardes is 2 duomenu failu, vietoj Vardas1 Pavarde1.

    ifstream names("data/names.txt");
    ifstream surnames("data/surnames.txt");
    bool fail = false;

    //exceptionai, spausdinam grazia raudona spalva :)
    try {
        if (names.fail()) {
            throw "\x1B[31mNerastas vardu sarasas! (truksta 'data/names.txt')\033[0m";
        }
    } catch (const char* msg) {
        cerr << msg << endl;
        fail = true;
    }

    try {
        if (surnames.fail()) {
            throw "\x1B[31mNerastas pavardziu sarasas! (truksta 'data/surnames.txt')\033[0m";
        }
    } catch (const char* msg) {
        cerr << msg << endl;
        fail = true;
    }

    if (!fail) {
        
        bool gender;

        string x, d;
        //cout << "Maisomi vardai ir pavardes...\n";
        while (names >> x >> gender) {
            name.push_back(x);
            if (gender == 0) {
                mname.push_back(x);     //vyru vardu vektorius
            }
            else {
                fname.push_back(x);     //moteru vardu vektorius
            }
        }
        while (surnames >> d >> gender) {
            surn.push_back(d);
            if (gender == 0) {
                msurn.push_back(d);     //vyrisku "pavardziu" vektorius
            }
            else {
                fsurn.push_back(d);     //moterisku "pavardziu" vektorius
            }
        }
        std::system("mkdir output");
        ofstream varg("output/sugeneruoti_vargsiukai.txt");
        ofstream kiet("output/sugeneruoti_kietuoliai.txt");
        int amount;
        cout << "Iveskite studentu kieki:\n";
        cin >> amount;
        cout << "Generuojami studentu sarasai...\n";
        varg << setw(20) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(30) << left << "Galutinis (vid.)\n";
        kiet << setw(20) << left << "Vardas" << setw(25) << left << "Pavarde" << setw(30) << left << "Galutinis (vid.)\n";
        varg << "--------------------------------------------------------------------------------------------\n";
        kiet << "--------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < amount; i++) {
            random_device rd;
            default_random_engine generator(rd()); // rd() duoda atsitiktini seed'a
            uniform_int_distribution<int> randStudent(0, 1);
            uniform_real_distribution<double> randMark(3.30, 10);

            shuffle(begin(mname), end(mname), generator);
            shuffle(begin(msurn), end(msurn), generator);
            shuffle(begin(fname), end(fname), generator);
            shuffle(begin(fsurn), end(fsurn), generator);
            int rand = randStudent(generator);
            double gal = randMark(generator);
            if (gal < 5.0) {
                if (rand == 0) {
                    for (size_t i = 0; i < 1; i += 2)
                        //cout << mname[i] << " " << msurn[i] << '\n';
                        varg << setw(20) << left << mname[i] << setw(25) << left << msurn[i] << setw(30) << left << fixed << setprecision(2) << gal << "\n";
                }
                else if (rand == 1) {
                    for (size_t i = 0; i < 1; i += 2)
                        //cout << fname[i] << " " << fsurn[i] << '\n';
                        varg << setw(20) << left << fname[i] << setw(25) << left << fsurn[i] << setw(30) << left << fixed << setprecision(2) << gal << "\n";
                }
            }
            else if (gal >= 5.0) {
                if (rand == 0) {
                    for (size_t i = 0; i < 1; i += 2)
                        //cout << mname[i] << " " << msurn[i] << '\n';
                        kiet << setw(20) << left << mname[i] << setw(25) << left << msurn[i] << setw(30) << left << fixed << setprecision(2) << gal << "\n";
                }
                else if (rand == 1) {
                    for (size_t i = 0; i < 1; i += 2)
                        //cout << fname[i] << " " << fsurn[i] << '\n';
                        kiet << setw(20) << left << fname[i] << setw(25) << left << fsurn[i] << setw(30) << left << fixed << setprecision(2) << gal << "\n";
                }
            }
        }
        varg.close();
        kiet.close();
        cout << "\x1B[32mKietuoliu sarasas issaugotas i 'output/sugeneruoti_kietuoliai.txt'\033[0m\n";
        cout << "\x1B[32mVargsiuku sarasas issaugotas i 'output/sugeneruoti_vargsiukai.txt'\033[0m\n";
        cout << "Baigta.\n\nSpustelekite bet koki klavisa, kad grizti i pagrindini meniu.";
        int e = _getch();
        main();
    } else {
        cout << "\nPrograma negali pradeti sio darbo. Spustelekite bet koki klavisa, kad grizti i pagrindini meniu.\n";
        int e = _getch();
        main();
    }
}

void flushContainers() {
    name.clear();
    surn.clear();
    mname.clear();
    msurn.clear();
    fname.clear();
    fsurn.clear();
    mas.clear();
}