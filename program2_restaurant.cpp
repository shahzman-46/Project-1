// ============================================================
//  Program 2: Restaurant Billing Management System
//  Concepts: functions, 1D arrays, loops, if-else, switch
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ── Customer Info ─────────────────────────────────────────
string custName, custContact, orderType;
int    numPersons;

// ── 1D Arrays for Menu ────────────────────────────────────
string itemNames[8] = {"Chicken Burger","Zinger Burger","Pizza Small","Pizza Large",
                       "Chicken Biryani","BBQ Platter","Fries","Cold Drink"};
double itemPrices[8] = {450, 550, 900, 1800, 350, 1200, 250, 120};

// ── Cart arrays ───────────────────────────────────────────
int   orderedItem[50];
int   orderedQty[50];
int   orderCount = 0;

// ============================================================
//  FUNCTION 1: Register Customer
// ============================================================
void registerCustomer()
{
    cout << "\n========== Customer Registration ==========" << endl;
    cout << "Customer Name    : ";
    cin.ignore();
    getline(cin, custName);

    cout << "Contact Number   : ";
    getline(cin, custContact);

    cout << "Order Type (1=Dine-in / 2=Takeaway): ";
    int t; cin >> t;
    orderType = (t == 1) ? "Dine-in" : "Takeaway";

    cout << "Number of Persons: ";
    cin >> numPersons;

    cout << "\n✅ Customer Registered!" << endl;
}

// ============================================================
//  FUNCTION 2: Display Food Menu
// ============================================================
void displayFoodMenu()
{
    cout << "\n========== FOOD MENU ==========" << endl;
    cout << "  No.  Item                  Price"  << endl;
    cout << "--------------------------------"    << endl;
    for (int i = 0; i < 8; i++)
        cout << "   " << (i+1) << ".  " << itemNames[i]
             << "\t\tRs. " << itemPrices[i] << endl;
    cout << "================================" << endl;
}

// ============================================================
//  FUNCTION 3: Place Order
// ============================================================
void placeOrder()
{
    displayFoodMenu();
    int itemNo, qty;
    char more;

    do
    {
        cout << "\nEnter Item Number (1-8): ";
        cin  >> itemNo;

        if (itemNo < 1 || itemNo > 8)
        {
            cout << "⚠️  Invalid item! Try again." << endl;
            continue;
        }

        cout << "Enter Quantity: ";
        cin  >> qty;

        orderedItem[orderCount] = itemNo - 1;
        orderedQty[orderCount]  = qty;
        orderCount++;

        cout << "Add more items? (y/n): ";
        cin  >> more;

    } while (more == 'y' || more == 'Y');

    cout << "\n✅ Order placed!" << endl;
}

// ============================================================
//  FUNCTION 4: Calculate Food Bill
// ============================================================
double calculateFoodBill()
{
    double total = 0;
    for (int i = 0; i < orderCount; i++)
        total += itemPrices[orderedItem[i]] * orderedQty[i];
    return total;
}

// ============================================================
//  FUNCTION 5: Calculate Service Charges
// ============================================================
double calculateServiceCharges(double foodBill)
{
    if (orderType == "Dine-in") return foodBill * 0.10;
    else                        return foodBill * 0.05;
}

// ============================================================
//  FUNCTION 6: Calculate GST (16%)
// ============================================================
double calculateGST(double foodBill)
{
    return foodBill * 0.16;
}

// ============================================================
//  FUNCTION 7: Calculate Discount
// ============================================================
double calculateDiscount(double foodBill)
{
    if      (foodBill > 10000) return foodBill * 0.15;
    else if (foodBill >= 5001) return foodBill * 0.10;
    else if (foodBill >= 3000) return foodBill * 0.05;
    else                       return 0;
}

// ============================================================
//  FUNCTION 9: Free Delivery if bill > 5000
// ============================================================
string checkFreeDelivery(double total)
{
    if (total > 5000) return "YES (Free Delivery Applied!)";
    else              return "NO";
}

// ============================================================
//  FUNCTION 8: Display Final Bill
// ============================================================
void displayFinalBill()
{
    if (orderCount == 0)
    {
        cout << "\n⚠️  No order placed yet!" << endl;
        return;
    }

    double foodBill     = calculateFoodBill();
    double service      = calculateServiceCharges(foodBill);
    double gst          = calculateGST(foodBill);
    double discount     = calculateDiscount(foodBill);
    double total        = foodBill + service + gst - discount;

    cout << "\n========== RESTAURANT BILL ==========" << endl;
    cout << "Customer Name  : " << custName           << endl;
    cout << "Order Type     : " << orderType          << endl;
    cout << "Persons        : " << numPersons         << endl;
    cout << "-------------------------------------"    << endl;

    // Show ordered items
    for (int i = 0; i < orderCount; i++)
        cout << "  " << itemNames[orderedItem[i]]
             << " x" << orderedQty[i]
             << "  = Rs. " << itemPrices[orderedItem[i]] * orderedQty[i] << endl;

    cout << "-------------------------------------"    << endl;
    cout << "Food Bill       : Rs. " << foodBill      << endl;
    cout << "Service Charges : Rs. " << service       << endl;
    cout << "GST (16%)       : Rs. " << gst           << endl;
    cout << "Discount        : Rs. " << discount      << endl;
    cout << "Free Delivery   : "     << checkFreeDelivery(total) << endl;
    cout << "-------------------------------------"    << endl;
    cout << "Total Payable   : Rs. " << total         << endl;
    cout << "Enjoy Your Meal :)"                      << endl;
    cout << "=====================================" << endl;
}

// ============================================================
//  FUNCTION 10: Display Customer Details
// ============================================================
void displayCustomerDetails()
{
    cout << "\n========== Customer Details ==========" << endl;
    cout << "Name     : " << custName    << endl;
    cout << "Contact  : " << custContact << endl;
    cout << "Order    : " << orderType   << endl;
    cout << "Persons  : " << numPersons  << endl;
    cout << "======================================" << endl;
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "  🍔 Restaurant Billing Management System" << endl;
    cout << "========================================" << endl;

    registerCustomer();

    int choice;
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "  1. View Food Menu"               << endl;
        cout << "  2. Place Order"                  << endl;
        cout << "  3. Calculate Bill"               << endl;
        cout << "  4. View Customer Details"        << endl;
        cout << "  5. Exit"                         << endl;
        cout << "================================"  << endl;
        cout << "  Choice (1-5): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: displayFoodMenu();        break;
            case 2: placeOrder();             break;
            case 3: displayFinalBill();       break;
            case 4: displayCustomerDetails(); break;
            case 5: cout << "\n👋 Thank You!" << endl; break;
            default: cout << "\n⚠️  Invalid!" << endl;
        }
    } while (choice != 5);

    return 0;
}
