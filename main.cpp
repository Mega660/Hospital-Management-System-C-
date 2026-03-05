#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// ================= PATIENT CLASS =================
class Patient {
public:
    int id;
    string name;
    int age;
    string gender;

    Patient(int i, string n, int a, string g) {
        id = i;
        name = n;
        age = a;
        gender = g;
    }

    string toFileString() const {
        stringstream ss;
        ss << id << "," << name << "," << age << "," << gender;
        return ss.str();
    }
};

// ================= DOCTOR CLASS =================
class Doctor {
public:
    int id;
    string name;
    string specialty;

    Doctor(int i, string n, string s) {
        id = i;
        name = n;
        specialty = s;
    }

    string toFileString() const {
        stringstream ss;
        ss << id << "," << name << "," << specialty;
        return ss.str();
    }
};

// ================= APPOINTMENT CLASS =================
class Appointment {
public:
    int patientId;
    int doctorId;
    string date;

    Appointment(int p, int d, string dt) {
        patientId = p;
        doctorId = d;
        date = dt;
    }

    string toFileString() const {
        stringstream ss;
        ss << patientId << "," << doctorId << "," << date;
        return ss.str();
    }
};

// ================= FILE FUNCTIONS =================
void savePatients(const vector<Patient>& patients) {
    ofstream file("patients.txt");
    for (const auto& p : patients)
        file << p.toFileString() << endl;
}

void saveDoctors(const vector<Doctor>& doctors) {
    ofstream file("doctors.txt");
    for (const auto& d : doctors)
        file << d.toFileString() << endl;
}

void saveAppointments(const vector<Appointment>& appointments) {
    ofstream file("appointments.txt");
    for (const auto& a : appointments)
        file << a.toFileString() << endl;
}

void loadPatients(vector<Patient>& patients) {
    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, age, gender;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');

        patients.push_back(Patient(stoi(id), name, stoi(age), gender));
    }
}

void loadDoctors(vector<Doctor>& doctors) {
    ifstream file("doctors.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, specialty;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, specialty, ',');

        doctors.push_back(Doctor(stoi(id), name, specialty));
    }
}

void loadAppointments(vector<Appointment>& appointments) {
    ifstream file("appointments.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string pid, did, date;

        getline(ss, pid, ',');
        getline(ss, did, ',');
        getline(ss, date, ',');

        appointments.push_back(Appointment(stoi(pid), stoi(did), date));
    }
}

// ================= MAIN FUNCTION =================
int main() {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    loadPatients(patients);
    loadDoctors(doctors);
    loadAppointments(appointments);

    int choice;

    do {
        cout << "\n==== HOSPITAL MANAGEMENT SYSTEM ====\n";
        cout << "1. Add Patient\n";
        cout << "2. View Patients\n";
        cout << "3. Add Doctor\n";
        cout << "4. View Doctors\n";
        cout << "5. Book Appointment\n";
        cout << "6. View Appointments\n";
        cout << "7. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            int id, age;
            string name, gender;

            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;

            patients.push_back(Patient(id, name, age, gender));
            savePatients(patients);

            cout << "Patient added successfully.\n";
        }

        else if (choice == 2) {
            for (const auto& p : patients) {
                cout << "ID: " << p.id
                     << " | Name: " << p.name
                     << " | Age: " << p.age
                     << " | Gender: " << p.gender << endl;
            }
        }

        else if (choice == 3) {
            int id;
            string name, specialty;

            cout << "Enter Doctor ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Specialty: ";
            cin >> specialty;

            doctors.push_back(Doctor(id, name, specialty));
            saveDoctors(doctors);

            cout << "Doctor added successfully.\n";
        }

        else if (choice == 4) {
            for (const auto& d : doctors) {
                cout << "ID: " << d.id
                     << " | Name: " << d.name
                     << " | Specialty: " << d.specialty << endl;
            }
        }

        else if (choice == 5) {
            int pid, did;
            string date;

            cout << "Enter Patient ID: ";
            cin >> pid;
            cout << "Enter Doctor ID: ";
            cin >> did;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;

            appointments.push_back(Appointment(pid, did, date));
            saveAppointments(appointments);

            cout << "Appointment booked successfully.\n";
        }

        else if (choice == 6) {
            for (const auto& a : appointments) {
                cout << "Patient ID: " << a.patientId
                     << " | Doctor ID: " << a.doctorId
                     << " | Date: " << a.date << endl;
            }
        }

    } while (choice != 7);

    cout << "Exiting system...\n";
    return 0;
}