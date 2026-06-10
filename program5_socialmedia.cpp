// ============================================================
//  Program 5: Social Media Campaign Management System
//  Concepts: functions, 1D arrays, loops, if-else, switch
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ── Client Info ──────────────────────────────────────────
string clientName, businessName, businessType;
int    campaignDays;

// ── 1D Arrays for Platforms ───────────────────────────────
string platformNames[3]   = {"Instagram", "Facebook", "LinkedIn"};
double platformCharges[3] = {15000, 12000, 20000};

// ── Selected Platform ─────────────────────────────────────
int    selectedPlatform = -1;

// ── Campaign Content ──────────────────────────────────────
int    staticPosts = 0, reelPosts = 0, carouselPosts = 0;
double adBudget    = 0;

// ============================================================
//  FUNCTION 1: Register Client
// ============================================================
void registerClient()
{
    cout << "\n========== Client Registration ==========" << endl;
    cout << "Client Name    : ";
    cin.ignore();
    getline(cin, clientName);

    cout << "Business Name  : ";
    getline(cin, businessName);

    cout << "Business Type:" << endl;
    cout << "  1. Small Business" << endl;
    cout << "  2. Medium Business" << endl;
    cout << "  3. Corporate Business" << endl;
    cout << "  Choice: ";
    int t; cin >> t;

    if      (t == 1) businessType = "Small Business";
    else if (t == 2) businessType = "Medium Business";
    else             businessType = "Corporate Business";

    cout << "Campaign Duration (days): ";
    cin  >> campaignDays;

    cout << "\n✅ Client Registered!" << endl;
}

// ============================================================
//  FUNCTION 2: Display Platforms
// ============================================================
void displayPlatforms()
{
    cout << "\n========== SOCIAL MEDIA PLATFORMS ==========" << endl;
    cout << "  No.  Platform    Base Management Charges"      << endl;
    cout << "--------------------------------------------"   << endl;
    for (int i = 0; i < 3; i++)
        cout << "   " << (i+1) << ".  " << platformNames[i]
             << "\t\tRs. " << platformCharges[i] << endl;
    cout << "============================================" << endl;
}

// ============================================================
//  FUNCTION 3: Select Platform
// ============================================================
void selectPlatform()
{
    displayPlatforms();
    cout << "\nSelect Platform (1-3): ";
    cin  >> selectedPlatform;

    if (selectedPlatform < 1 || selectedPlatform > 3)
    {
        cout << "⚠️  Invalid! Defaulting to Instagram." << endl;
        selectedPlatform = 1;
    }
    else selectedPlatform--;  // convert to 0-based index

    cout << "\n✅ Platform selected: " << platformNames[selectedPlatform] << endl;

    // Ask post details
    cout << "\nNumber of Static Posts   : ";
    cin  >> staticPosts;
    cout << "Number of Reel/Video Posts: ";
    cin  >> reelPosts;
    cout << "Number of Carousel Posts : ";
    cin  >> carouselPosts;

    cout << "Enter Ad Budget (Rs.)    : ";
    cin  >> adBudget;
}

// ============================================================
//  FUNCTION 4: Calculate Post Design Cost
// ============================================================
double calculatePostDesignCost()
{
    return (staticPosts * 1000) + (reelPosts * 2500) + (carouselPosts * 1800);
}

// ============================================================
//  FUNCTION 5: Calculate Ad Handling Fee
// ============================================================
double calculateAdHandlingFee()
{
    if      (adBudget > 100000) return adBudget * 0.10;
    else if (adBudget >= 50000) return adBudget * 0.08;
    else                        return adBudget * 0.05;
}

// ============================================================
//  FUNCTION 6: Extra Duration Charges
// ============================================================
double calculateExtraDurationCharges()
{
    if (campaignDays > 30) return (campaignDays - 30) * 500;
    return 0;
}

// ============================================================
//  FUNCTION 7: Calculate GST (16%)
// ============================================================
double calculateGST(double totalCost)
{
    return totalCost * 0.16;
}

// ============================================================
//  FUNCTION 8: Calculate Discount
// ============================================================
double calculateDiscount(double totalCost)
{
    if      (businessType == "Corporate Business") return totalCost * 0.10;
    else if (businessType == "Medium Business")    return totalCost * 0.08;
    else                                           return totalCost * 0.05;
}

// ============================================================
//  FUNCTION 9: Display Final Campaign Bill
// ============================================================
void displayFinalCampaignBill()
{
    if (selectedPlatform == -1)
    {
        cout << "\n⚠️  Please select a platform first!" << endl;
        return;
    }

    double platformCost   = platformCharges[selectedPlatform];
    double postDesign     = calculatePostDesignCost();
    double adHandling     = calculateAdHandlingFee();
    double extraDuration  = calculateExtraDurationCharges();
    double subTotal       = platformCost + postDesign + adBudget + adHandling + extraDuration;
    double gst            = calculateGST(subTotal);
    double discount       = calculateDiscount(subTotal);
    double finalCost      = subTotal + gst - discount;

    cout << "\n========== SOCIAL MEDIA CAMPAIGN BILL ==========" << endl;
    cout << "Client Name       : " << clientName                  << endl;
    cout << "Business Name     : " << businessName                << endl;
    cout << "Business Type     : " << businessType                << endl;
    cout << "Platform          : " << platformNames[selectedPlatform] << endl;
    cout << "Campaign Duration : " << campaignDays << " Days"     << endl;
    cout << "------------------------------------------------"    << endl;
    cout << "Platform Mgmt Charges : Rs. " << platformCost    << endl;
    cout << "Post Design Cost      : Rs. " << postDesign      << endl;
    cout << "Ad Budget             : Rs. " << adBudget        << endl;
    cout << "Ad Handling Fee       : Rs. " << adHandling      << endl;
    cout << "Extra Duration Charges: Rs. " << extraDuration   << endl;
    cout << "GST (16%)             : Rs. " << gst             << endl;
    cout << "Discount              : Rs. " << discount        << endl;
    cout << "------------------------------------------------"    << endl;
    cout << "Final Campaign Cost   : Rs. " << finalCost       << endl;
    cout << "================================================" << endl;
}

// ============================================================
//  FUNCTION 10: Display Client Details
// ============================================================
void displayClientDetails()
{
    cout << "\n========== Client Details ==========" << endl;
    cout << "Client Name    : " << clientName    << endl;
    cout << "Business Name  : " << businessName  << endl;
    cout << "Business Type  : " << businessType  << endl;
    cout << "Campaign Days  : " << campaignDays  << endl;
    cout << "====================================" << endl;
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "================================================" << endl;
    cout << "  📱 Social Media Campaign Management System     " << endl;
    cout << "================================================" << endl;

    registerClient();

    int choice;
    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "  1. View Platforms"              << endl;
        cout << "  2. Select Campaign Platform"    << endl;
        cout << "  3. Calculate Campaign Cost"     << endl;
        cout << "  4. View Client Details"         << endl;
        cout << "  5. Exit"                        << endl;
        cout << "================================" << endl;
        cout << "  Choice (1-5): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: displayPlatforms();        break;
            case 2: selectPlatform();          break;
            case 3: displayFinalCampaignBill();break;
            case 4: displayClientDetails();    break;
            case 5: cout << "\n👋 Goodbye!" << endl; break;
            default: cout << "\n⚠️  Invalid!" << endl;
        }
    } while (choice != 5);

    return 0;
}
