// ============================================================
//  Program 1: LESCO Electricity Bill Management System
//  Concepts: functions, arrays, loops, if-else, switch
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ── Global Customer Info ──────────────────────────────────
string customerName, customerID, customerType;
int    metersInstalled;

// ── Slab Rates stored in 1D Array ─────────────────────────
double slabRates[8] = {12.21, 14.53, 31.51, 38.41, 41.62, 43.04, 44.18, 49.10};

// ============================================================
//  FUNCTION 1: Register Customer
// ============================================================
void registerCustomer()
{
    cout << "\n========== Customer Registration ==========" << endl;

    cout << "Enter Customer Name    : ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter Customer ID      : ";
    getline(cin, customerID);

    cout << "Customer Type (1=Household / 2=Commercial): ";
    int type; cin >> type;
    customerType = (type == 1) ? "Household" : "Commercial";

    cout << "Number of Meters (1=First / 2=Second): ";
    cin >> metersInstalled;

    cout << "\n✅ Customer Registered Successfully!" << endl;
}

// ============================================================
//  FUNCTION 3: Calculate Electricity Consumption Charges
// ============================================================
double calculateConsumptionCharges(int units)
{
    double charges = 0;

    if      (units <= 100) charges = units * slabRates[0];
    else if (units <= 200) charges = 100*slabRates[0] + (units-100)*slabRates[1];
    else if (units <= 300) charges = 100*slabRates[0] + 100*slabRates[1] + (units-200)*slabRates[2];
    else if (units <= 400) charges = 100*slabRates[0] + 100*slabRates[1] + 100*slabRates[2] + (units-300)*slabRates[3];
    else if (units <= 500) charges = 100*slabRates[0] + 100*slabRates[1] + 100*slabRates[2] + 100*slabRates[3] + (units-400)*slabRates[4];
    else if (units <= 600) charges = 100*slabRates[0] + 100*slabRates[1] + 100*slabRates[2] + 100*slabRates[3] + 100*slabRates[4] + (units-500)*slabRates[5];
    else if (units <= 700) charges = 100*slabRates[0] + 100*slabRates[1] + 100*slabRates[2] + 100*slabRates[3] + 100*slabRates[4] + 100*slabRates[5] + (units-600)*slabRates[6];
    else                   charges = 100*slabRates[0] + 100*slabRates[1] + 100*slabRates[2] + 100*slabRates[3] + 100*slabRates[4] + 100*slabRates[5] + 100*slabRates[6] + (units-700)*slabRates[7];

    return charges;
}

// ============================================================
//  FUNCTION 7: Calculate Fixed Charges
// ============================================================
double calculateFixedCharges(int units)
{
    if      (units <= 300) return 0;
    else if (units <= 400) return 200;
    else if (units <= 500) return 400;
    else if (units <= 600) return 600;
    else if (units <= 700) return 800;
    else                   return 1000;
}

// ============================================================
//  FUNCTION 4: Calculate GST (18%)
// ============================================================
double calculateGST(double totalBill)
{
    return totalBill * 0.18;
}

// ============================================================
//  FUNCTION 5: Calculate Income Tax
// ============================================================
double calculateIncomeTax(double totalBill)
{
    if (customerType == "Household") return totalBill * 0.10;
    else                             return totalBill * 0.15;
}

// ============================================================
//  FUNCTION 6: Calculate Electricity Duty (1.5%)
// ============================================================
double calculateElectricityDuty(double consumptionCharges)
{
    return consumptionCharges * 0.015;
}

// ============================================================
//  FUNCTION 9: Display Final Bill
// ============================================================
void displayFinalBill()
{
    int units;
    cout << "\nEnter Units Consumed: ";
    cin  >> units;

    double consumption = calculateConsumptionCharges(units);
    double duty        = calculateElectricityDuty(consumption);
    double fixed       = calculateFixedCharges(units);
    double meterRent   = 250;
    double tvFee       = 35;

    double subTotal    = consumption + duty + fixed + meterRent + tvFee;
    double gst         = calculateGST(subTotal);
    double incomeTax   = calculateIncomeTax(subTotal);
    double totalBill   = subTotal + gst + incomeTax;

    cout << "\n========== LESCO ELECTRICITY BILL ==========" << endl;
    cout << "Customer Name    : " << customerName   << endl;
    cout << "Customer ID      : " << customerID     << endl;
    cout << "Customer Type    : " << customerType   << endl;
    cout << "Units Consumed   : " << units          << endl;
    cout << "--------------------------------------------"   << endl;
    cout << "Consumption Charges : Rs. " << consumption << endl;
    cout << "Electricity Duty    : Rs. " << duty        << endl;
    cout << "Fixed Charges       : Rs. " << fixed       << endl;
    cout << "Meter Rent          : Rs. " << meterRent   << endl;
    cout << "TV Fee              : Rs. " << tvFee       << endl;
    cout << "GST (18%)           : Rs. " << gst         << endl;
    cout << "Income Tax          : Rs. " << incomeTax   << endl;
    cout << "--------------------------------------------"   << endl;
    cout << "Total Payable Bill  : Rs. " << totalBill   << endl;
    cout << "============================================"   << endl;
}

// ============================================================
//  FUNCTION 8: New Connection Charges
// ============================================================
void applyNewConnection()
{
    cout << "\n========== New Connection Charges ==========" << endl;

    double meterCost  = 5000;
    double meterCable = 3000;
    double security   = 2000;
    double additional = 0;
    double newConn    = 0;

    if (customerType == "Household")
        additional = (metersInstalled == 1) ? 2500 : 5000;
    else
        additional = (metersInstalled == 1) ? 35000 : 70000;

    int properConn;
    cout << "Apply for proper new connection? (1=Yes / 2=No): ";
    cin  >> properConn;
    if (properConn == 1) newConn = 250000;

    double total = meterCost + meterCable + security + additional + newConn;

    cout << "Meter Cost           : Rs. " << meterCost  << endl;
    cout << "Meter Cable Cost     : Rs. " << meterCable << endl;
    cout << "Security Cost        : Rs. " << security   << endl;
    cout << "Additional Charges   : Rs. " << additional << endl;
    cout << "New Connection Cost  : Rs. " << newConn    << endl;
    cout << "--------------------------------------------"  << endl;
    cout << "Total Connection Cost: Rs. " << total       << endl;
    cout << "============================================"  << endl;
}

// ============================================================
//  FUNCTION 10: Display Customer Details
// ============================================================
void displayCustomerDetails()
{
    cout << "\n========== Customer Details ==========" << endl;
    cout << "Name             : " << customerName     << endl;
    cout << "Customer ID      : " << customerID       << endl;
    cout << "Customer Type    : " << customerType     << endl;
    cout << "Meters Installed : " << metersInstalled  << endl;
    cout << "======================================" << endl;
}

// ============================================================
//  FUNCTION 2: Display Menu
// ============================================================
void displayMenu()
{
    int choice;
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "  1. Calculate Monthly Bill"        << endl;
        cout << "  2. Apply for New Connection"      << endl;
        cout << "  3. View Customer Details"         << endl;
        cout << "  4. Exit Program"                  << endl;
        cout << "================================"   << endl;
        cout << "  Enter Choice (1-4): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: displayFinalBill();       break;
            case 2: applyNewConnection();     break;
            case 3: displayCustomerDetails(); break;
            case 4: cout << "\n👋 Goodbye!" << endl; break;
            default: cout << "\n⚠️  Invalid choice! Enter 1-4." << endl;
        }
    } while (choice != 4);
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "==========================================" << endl;
    cout << "  ⚡ LESCO Electricity Management System   " << endl;
    cout << "==========================================" << endl;

    registerCustomer();
    displayMenu();

    return 0;
}
