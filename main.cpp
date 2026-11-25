#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 100;
const int ROUTES = 5;

string names[MAX], destinations[MAX];
int counts[MAX], passengerCount = 0;
double fares[MAX], stats[ROUTES][2] = {};

string routes[ROUTES] = {
    "Bacolod - Silay",
    "Bacolod - Talisay",
    "Bacolod - Murcia",
    "Bacolod - Bago",
    "Bacolod - Cadiz"
};

int findRoute(string destination) {
    for (int i = 0; i < ROUTES; i++)
        if (routes[i] == destination)
            return i;
    return -1;
}

void showRoutes() {
    cout << "\nAvailable Routes:\n";
    for (int i = 0; i < ROUTES; i++)
        cout << i + 1 << ". " << routes[i] << endl;
}

int searchPassenger() {
    if (passengerCount == 0) {
        cout << "\nNo records available.\n";
        return -1;
    }

    string name;
    cin.ignore(10000, '\n');
    cout << "\nEnter passenger name: ";
    getline(cin, name);

    for (int i = 0; i < passengerCount; i++) {
        if (names[i] == name) {
            cout << "\nPassenger: " << names[i];
            cout << "\nDestination: " << destinations[i];
            cout << "\nPassenger count: " << counts[i];
            cout << "\nFare: PHP " << fixed << setprecision(2) << fares[i];
            cout << "\nTotal: PHP " << fares[i] * counts[i] << endl;
            return i;
        }
    }

    cout << "\nPassenger not found.\n";
    return -1;
}

void addPassenger() {
    if (passengerCount >= MAX) {
        cout << "\nStorage is full.\n";
        return;
    }

    cin.ignore(10000, '\n');
    cout << "\nEnter passenger name: ";
    getline(cin, names[passengerCount]);

    showRoutes();

    int route;
    cout << "Choose destination: ";
    cin >> route;

    if (route < 1 || route > ROUTES) {
        cout << "Invalid route.\n";
        return;
    }

    cout << "Number of passengers: ";
    cin >> counts[passengerCount];
    cout << "Fare per passenger: ";
    cin >> fares[passengerCount];

    if (counts[passengerCount] <= 0 || fares[passengerCount] < 0) {
        cout << "Invalid input.\n";
        return;
    }

    destinations[passengerCount] = routes[route - 1];

    double total = counts[passengerCount] * fares[passengerCount];
    stats[route - 1][0] += counts[passengerCount];
    stats[route - 1][1] += total;

    cout << fixed << setprecision(2);
    cout << "\nBooking added successfully!";
    cout << "\nTotal fare: PHP " << total << endl;
    passengerCount++;
}

void viewPassengers() {
    if (passengerCount == 0) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n========== PASSENGER RECORDS ==========\n";
    for (int i = 0; i < passengerCount; i++) {
        cout << "\nRecord " << i + 1;
        cout << "\nName: " << names[i];
        cout << "\nDestination: " << destinations[i];
        cout << "\nPassengers: " << counts[i];
        cout << "\nFare: PHP " << fixed << setprecision(2) << fares[i];
        cout << "\nTotal: PHP " << fares[i] * counts[i] << endl;
    }
}

void updatePassenger() {
    int i = searchPassenger();
    if (i == -1)
        return;

    int oldRoute = findRoute(destinations[i]);
    stats[oldRoute][0] -= counts[i];
    stats[oldRoute][1] -= counts[i] * fares[i];

    showRoutes();

    int route, newCount;
    double newFare;

    cout << "New destination: ";
    cin >> route;
    cout << "New passenger count: ";
    cin >> newCount;
    cout << "New fare: ";
    cin >> newFare;

    if (route < 1 || route > ROUTES || newCount <= 0 || newFare < 0) {
        cout << "Invalid input. Update cancelled.\n";
        stats[oldRoute][0] += counts[i];
        stats[oldRoute][1] += counts[i] * fares[i];
        return;
    }

    destinations[i] = routes[route - 1];
    counts[i] = newCount;
    fares[i] = newFare;

    stats[route - 1][0] += newCount;
    stats[route - 1][1] += newCount * newFare;

    cout << "\nRecord updated successfully!\n";
}

void deletePassenger() {
    int i = searchPassenger();
    if (i == -1)
        return;

    int route = findRoute(destinations[i]);
    stats[route][0] -= counts[i];
    stats[route][1] -= counts[i] * fares[i];

    for (int j = i; j < passengerCount - 1; j++) {
        names[j] = names[j + 1];
        destinations[j] = destinations[j + 1];
        counts[j] = counts[j + 1];
        fares[j] = fares[j + 1];
    }

    passengerCount--;
    cout << "\nRecord deleted successfully!\n";
}

void displaySummary() {
    int totalPassengers = 0;
    double totalRevenue = 0;

    cout << "\n========== TRANSPORT SUMMARY ==========\n";
    for (int i = 0; i < ROUTES; i++) {
        cout << "\nRoute: " << routes[i];
        cout << "\nPassengers: " << stats[i][0];
        cout << "\nRevenue: PHP " << fixed << setprecision(2) << stats[i][1] << endl;

        totalPassengers += stats[i][0];
        totalRevenue += stats[i][1];
    }

    cout << "\nTotal passengers: " << totalPassengers;
    cout << "\nTotal revenue: PHP " << fixed << setprecision(2) << totalRevenue;
    cout << "\nBooking records: " << passengerCount << endl;
}

int main() {
    int choice;

    do {
        cout << "\n====================================";
        cout << "\n PASSENGER TRANSPORTATION SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Passenger";
        cout << "\n2. View Passengers";
        cout << "\n3. Search Passenger";
        cout << "\n4. Update Passenger";
        cout << "\n5. Delete Passenger";
        cout << "\n6. Display Summary";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";

        cin >> choice;

        switch (choice) {
            case 1: addPassenger(); break;
            case 2: viewPassengers(); break;
            case 3: searchPassenger(); break;
            case 4: updatePassenger(); break;
            case 5: deletePassenger(); break;
            case 6: displaySummary(); break;
            case 7: cout << "\nThank you for using the system!\n"; break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
