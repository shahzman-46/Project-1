// ============================================================
//  Program 3: Grocery Mart Billing System
//  Concepts: functions, 1D arrays, loops, if-else, switch
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ── Customer Info ─────────────────────────────────────────
string custName, custID, custType, payMethod;

// ── 1D Arrays for Grocery Items ───────────────────────────
string itemNames[8]  = {"Rice 1 KG","Sugar 1 KG","Cooking Oil 1L","Milk Pack",
                        "Tea Pack","Flour 5 KG","Eggs Dozen","Detergent"};
double itemPrices[8] = {350, 180, 580, 220, 450, 950, 320, 600};

// ── Cart arrays ───────────────────────────────────────────
int cartItem[50];
int cartQty[50];
int cartCount = 0;

// ── Loyalty ──────────────────────────────────────────────
double loyaltyPoints = 0;

// ============================================================
//  FUNCTION 1: Register Customer
// ============================================================
void registerCustomer()
{
    cout << "\n========== Customer Registration ==========" << endl;
    cout << "Customer Name         : ";
    cin.ignore();
    getline(cin, custName);

    cout << "Customer ID           : ";
    getline(cin, custID);

    cout << "Customer Type (1=Regular / 2=Member): ";
    int t; cin >> t;
    custType = (t == 2) ? "Member" : "Regular";

    cout << "Payment Method (1=Cash / 2=Card): ";
    int p; cin >> p;
    payMethod = (p == 2) ? "Card" : "Cash";

    cout << "\n✅ Registered!" << endl;
}

// ============================================================
//  FUNCTION 2: Display Grocery List
// ============================================================
void displayGroceryList()
{
    cout << "\n========== GROCERY ITEMS ==========" << endl;
    cout << "  No.  Item              Price"         << endl;
    cout << "-----------------------------------"    << endl;
    for (int i = 0; i < 8; i++)
        cout << "   " << (i+1) << ".  " << itemNames[i]
             << "\t  Rs. " << itemPrices[i] << endl;
    cout << "===================================" << endl;
}

// ============================================================
//  FUNCTION 3: Add Items to Cart
// ============================================================
void addItemsToCart()
{
    displayGroceryList();
    int itemNo, qty;
    char more;

    do
    {
        cout << "\nItem Number (1-8): ";
        cin  >> itemNo;

        if (itemNo < 1 || itemNo > 8)
        {
            cout << "⚠️  Invalid item!" << endl;
            continue;
        }

        cout << "Quantity: ";
        cin  >> qty;

        cartItem[cartCount] = itemNo - 1;
        cartQty[cartCount]  = qty;
        cartCount++;

        cout << "Add more? (y/n): ";
        cin  >> more;
    } while (more == 'y' || more == 'Y');

    cout << "\n✅ Items added to cart!" << endl;
}

// ============================================================
//  FUNCTION 4: Calculate Gross Bill
// ============================================================
double calculateGrossBill()
{
    double total = 0;
    for (int i = 0; i < cartCount; i++)
        total += itemPrices[cartItem[i]] * cartQty[i];
    return total;
}

// ============================================================
//  FUNCTION 5: Calculate Sales Tax
// ============================================================
double calculateSalesTax(double grossBill)
{
    double foodTotal    = 0;
    double nonFoodTotal = 0;

    for (int i = 0; i < cartCount; i++)
    {
        double lineTotal = itemPrices[cartItem[i]] * cartQty[i];
        if (cartItem[i] < 7) foodTotal    += lineTotal;  // items 1-7 = food
        else                 nonFoodTotal += lineTotal;  // item 8 = non-food
    }

    return (foodTotal * 0.05) + (nonFoodTotal * 0.10);
}

// ============================================================
//  FUNCTION 6: Membership Discount (7% for members)
// ============================================================
double calculateMembershipDiscount(double grossBill)
{
    if (custType == "Member") return grossBill * 0.07;
    return 0;
}

// ============================================================
//  FUNCTION 7: Bill Amount Discount
// ============================================================
double calculateBillDiscount(double grossBill)
{
    if      (grossBill > 10000) return grossBill * 0.10;
    else if (grossBill >= 5000) return grossBill * 0.05;
    else                        return 0;
}

// ============================================================
//  FUNCTION 8: Card Charges (2%)
// ============================================================
double calculateCardCharges(double total)
{
    if (payMethod == "Card") return total * 0.02;
    return 0;
}

// ============================================================
//  FUNCTION 10: Calculate Loyalty Points
// ============================================================
double calculateLoyaltyPoints(double totalBill)
{
    return totalBill / 100.0;
}

// ============================================================
//  FUNCTION 9: Display Final Bill
// ============================================================
void displayFinalBill()
{
    if (cartCount == 0) { cout << "\n⚠️  Cart is empty!" << endl; return; }

    double gross      = calculateGrossBill();
    double tax        = calculateSalesTax(gross);
    double memDisc    = calculateMembershipDiscount(gross);
    double billDisc   = calculateBillDiscount(gross);
    double afterDisc  = gross + tax - memDisc - billDisc;
    double cardCharge = calculateCardCharges(afterDisc);
    double total      = afterDisc + cardCharge;

    // Loyalty Points
    double newPoints  = calculateLoyaltyPoints(total);
    cout << "\nGenerated Loyalty Points: " << newPoints << endl;
    cout << "Enter Your Existing Loyalty Points (0 if new): ";
    double existingPts; cin >> existingPts;

    double totalPoints = newPoints + existingPts;
    cout << "Loyalty Points after Purchase: " << totalPoints << endl;

    // Redeem option
    cout << "Press 1 to Redeem Points, Press 2 to Continue: ";
    int redeem; cin >> redeem;
    if (redeem == 1) total -= totalPoints;   // 1 point = Rs. 1

    cout << "\n========== GROCERY MART BILL ==========" << endl;
    cout << "Customer Name  : " << custName   << endl;
    cout << "Customer Type  : " << custType   << endl;
    cout << "Payment Method : " << payMethod  << endl;
    cout << "---------------------------------------"   << endl;
    cout << "Gross Bill         : Rs. " << gross      << endl;
    cout << "Sales Tax          : Rs. " << tax        << endl;
    cout << "Membership Discount: Rs. " << memDisc    << endl;
    cout << "Bill Discount      : Rs. " << billDisc   << endl;
    cout << "Card Charges       : Rs. " << cardCharge << endl;
    cout << "---------------------------------------"   << endl;
    cout << "Total Payable Amount: Rs. " << total      << endl;
    cout << "Thank You For Shopping :)"               << endl;
    cout << "=======================================" << endl;
}

// ============================================================
//  FUNCTION: Display Customer Details
// ============================================================
void displayCustomerDetails()
{
    cout << "\n========== Customer Details ==========" << endl;
    cout << "Name    : " << custName  << endl;
    cout << "ID      : " << custID    << endl;
    cout << "Type    : " << custType  << endl;
    cout << "Payment : " << payMethod << endl;
    cout << "======================================" << endl;
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "    🛒 Grocery Mart Billing System       " << endl;
    cout << "========================================" << endl;

    registerCustomer();

    int choice;
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "  1. View Grocery Items"           << endl;
        cout << "  2. Add Items to Cart"            << endl;
        cout << "  3. Calculate Bill"               << endl;
        cout << "  4. View Customer Details"        << endl;
        cout << "  5. Exit"                         << endl;
        cout << "================================"  << endl;
        cout << "  Choice (1-5): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: displayGroceryList();     break;
            case 2: addItemsToCart();         break;
            case 3: displayFinalBill();       break;
            case 4: displayCustomerDetails(); break;
            case 5: cout << "\n👋 Goodbye!" << endl; break;
            default: cout << "\n⚠️  Invalid!" << endl;
        }
    } while (choice != 5);

    return 0;
}
