// ============================================================
//  Program 4: Online Shopping System
//  Concepts: functions, 1D arrays, loops, if-else, switch
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ── User Info ─────────────────────────────────────────────
string userName, userEmail, userCity, custType, payMethod;

// ── 1D Arrays for Products ────────────────────────────────
string productNames[8]  = {"T-Shirt","Jeans","Shoes","Watch",
                            "Handbag","Headphones","Mobile Cover","Perfume"};
double productPrices[8] = {1200, 3500, 5000, 2500, 4200, 3000, 700, 2800};

// ── Cart ──────────────────────────────────────────────────
int cartItem[50];
int cartQty[50];
int cartCount = 0;

// ============================================================
//  FUNCTION 1: Register User
// ============================================================
void registerUser()
{
    cout << "\n========== User Registration ==========" << endl;
    cout << "User Name  : ";
    cin.ignore();
    getline(cin, userName);

    cout << "Email      : ";
    getline(cin, userEmail);

    cout << "City       : ";
    getline(cin, userCity);

    cout << "Customer Type (1=New / 2=Returning): ";
    int t; cin >> t;
    custType = (t == 1) ? "New Customer" : "Returning Customer";

    cout << "\n✅ Registered!" << endl;
}

// ============================================================
//  FUNCTION 2: Display Products
// ============================================================
void displayProducts()
{
    cout << "\n========== PRODUCT LIST ==========" << endl;
    cout << "  No.  Product         Price"         << endl;
    cout << "----------------------------------"   << endl;
    for (int i = 0; i < 8; i++)
        cout << "   " << (i+1) << ".  " << productNames[i]
             << "\t  Rs. " << productPrices[i] << endl;
    cout << "==================================" << endl;
}

// ============================================================
//  FUNCTION 3: Add Products to Cart
// ============================================================
void addToCart()
{
    displayProducts();
    int itemNo, qty;
    char more;

    do
    {
        cout << "\nProduct Number (1-8): ";
        cin  >> itemNo;

        if (itemNo < 1 || itemNo > 8)
        { cout << "⚠️  Invalid!" << endl; continue; }

        cout << "Quantity: ";
        cin  >> qty;

        cartItem[cartCount] = itemNo - 1;
        cartQty[cartCount]  = qty;
        cartCount++;

        cout << "Add more? (y/n): ";
        cin  >> more;
    } while (more == 'y' || more == 'Y');

    cout << "\n✅ Added to cart!" << endl;
}

// ============================================================
//  FUNCTION 4: Calculate Product Total
// ============================================================
double calculateProductTotal()
{
    double total = 0;
    for (int i = 0; i < cartCount; i++)
        total += productPrices[cartItem[i]] * cartQty[i];
    return total;
}

// ============================================================
//  FUNCTION 5: Calculate GST (17%)
// ============================================================
double calculateGST(double productTotal)
{
    return productTotal * 0.17;
}

// ============================================================
//  FUNCTION 6: Calculate Delivery Charges
// ============================================================
double calculateDeliveryCharges()
{
    if (userCity == "Lahore" || userCity == "Karachi" || userCity == "Islamabad")
        return 250;
    return 500;
}

// ============================================================
//  FUNCTION 7: Customer Discount
// ============================================================
double calculateCustomerDiscount(double productTotal)
{
    if (custType == "New Customer")       return productTotal * 0.05;
    else                                  return productTotal * 0.10;
}

// ============================================================
//  FUNCTION 8: Order Value Discount
// ============================================================
double calculateOrderDiscount(double productTotal)
{
    if      (productTotal > 10000) return productTotal * 0.12;
    else if (productTotal >= 5000) return productTotal * 0.05;
    else                           return 0;
}

// ============================================================
//  FUNCTION 9: Payment Charges (2.5% for card)
// ============================================================
double calculatePaymentCharges(double total)
{
    if (payMethod == "Card") return total * 0.025;
    return 0;
}

// ============================================================
//  FUNCTION 10: Display Checkout Bill
// ============================================================
void displayCheckoutBill()
{
    if (cartCount == 0) { cout << "\n⚠️  Cart is empty!" << endl; return; }

    cout << "\nPayment Method (1=Cash on Delivery / 2=Card): ";
    int p; cin >> p;
    payMethod = (p == 2) ? "Card" : "Cash on Delivery";

    double productTotal  = calculateProductTotal();
    double gst           = calculateGST(productTotal);
    double delivery      = calculateDeliveryCharges();
    double custDisc      = calculateCustomerDiscount(productTotal);
    double orderDisc     = calculateOrderDiscount(productTotal);
    double afterDisc     = productTotal + gst + delivery - custDisc - orderDisc;
    double payCharge     = calculatePaymentCharges(afterDisc);
    double finalAmount   = afterDisc + payCharge;

    cout << "\n========== ONLINE SHOPPING BILL ==========" << endl;
    cout << "User Name      : " << userName      << endl;
    cout << "City           : " << userCity      << endl;
    cout << "Customer Type  : " << custType      << endl;
    cout << "Payment Method : " << payMethod     << endl;
    cout << "------------------------------------------"   << endl;
    cout << "Product Total    : Rs. " << productTotal  << endl;
    cout << "GST (17%)        : Rs. " << gst           << endl;
    cout << "Delivery Charges : Rs. " << delivery      << endl;
    cout << "Customer Discount: Rs. " << custDisc      << endl;
    cout << "Order Discount   : Rs. " << orderDisc     << endl;
    cout << "Payment Charges  : Rs. " << payCharge     << endl;
    cout << "------------------------------------------"   << endl;
    cout << "Final Payable    : Rs. " << finalAmount   << endl;
    cout << "Thank You for Shopping :)"               << endl;
    cout << "==========================================" << endl;
}

// ============================================================
//  Display User Details
// ============================================================
void displayUserDetails()
{
    cout << "\n========== User Details ==========" << endl;
    cout << "Name  : " << userName  << endl;
    cout << "Email : " << userEmail << endl;
    cout << "City  : " << userCity  << endl;
    cout << "Type  : " << custType  << endl;
    cout << "==================================" << endl;
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "   🛍️  Online Shopping System            " << endl;
    cout << "========================================" << endl;

    registerUser();

    int choice;
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "  1. View Products"               << endl;
        cout << "  2. Add Product to Cart"         << endl;
        cout << "  3. Calculate Checkout Bill"     << endl;
        cout << "  4. View User Details"           << endl;
        cout << "  5. Exit"                        << endl;
        cout << "================================" << endl;
        cout << "  Choice (1-5): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: displayProducts();     break;
            case 2: addToCart();           break;
            case 3: displayCheckoutBill(); break;
            case 4: displayUserDetails();  break;
            case 5: cout << "\n👋 Goodbye!" << endl; break;
            default: cout << "\n⚠️  Invalid!" << endl;
        }
    } while (choice != 5);

    return 0;
}
