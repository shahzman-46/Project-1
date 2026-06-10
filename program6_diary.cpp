// ============================================================
//  Program 6: Personal Student Diary
//  Concepts: structs, arrays, functions, loops, if-else
//  Bonus: date/time, search by keyword, sort by date
// ============================================================

#include <iostream>
#include <string>
#include <ctime>      // for automatic date & time
#include <algorithm>  // for sort (bonus)
using namespace std;

// ── Max entries ───────────────────────────────────────────
const int MAX_ENTRIES = 20;

// ── Struct for one diary entry ────────────────────────────
struct DiaryEntry
{
    string title;
    string content;
    string createdAt;     // BONUS: auto date/time
    string lastModified;  // BONUS: auto date/time
};

// ── In-memory storage ─────────────────────────────────────
DiaryEntry entries[MAX_ENTRIES];
int        entryCount = 0;

// ── Auth storage (max 10 users) ───────────────────────────
string regUsers[10];
string regPasswords[10];
int    userCount = 0;

// ── Logged-in user ────────────────────────────────────────
string loggedInUser = "";

// ============================================================
//  HELPER: Get current date-time string
// ============================================================
string getCurrentDateTime()
{
    time_t now = time(0);
    string dt  = ctime(&now);
    // remove trailing newline
    if (!dt.empty() && dt[dt.size()-1] == '\n')
        dt.erase(dt.size()-1);
    return dt;
}

// ============================================================
//  AUTH: Register
// ============================================================
void registerUser()
{
    if (userCount >= 10)
    {
        cout << "⚠️  Max users reached!" << endl;
        return;
    }

    cout << "\n--- Register ---" << endl;
    string uname, pass;

    cout << "Choose Username: ";
    cin.ignore();
    getline(cin, uname);

    // Check duplicate
    for (int i = 0; i < userCount; i++)
    {
        if (regUsers[i] == uname)
        {
            cout << "⚠️  Username already exists!" << endl;
            return;
        }
    }

    cout << "Choose Password: ";
    getline(cin, pass);

    regUsers[userCount]     = uname;
    regPasswords[userCount] = pass;
    userCount++;

    cout << "✅ Registered successfully! Please login." << endl;
}

// ============================================================
//  AUTH: Login
// ============================================================
bool loginUser()
{
    cout << "\n--- Login ---" << endl;
    string uname, pass;

    cout << "Username: ";
    cin.ignore();
    getline(cin, uname);

    cout << "Password: ";
    getline(cin, pass);

    for (int i = 0; i < userCount; i++)
    {
        if (regUsers[i] == uname && regPasswords[i] == pass)
        {
            loggedInUser = uname;
            cout << "\n✅ Welcome, " << uname << "!" << endl;
            return true;
        }
    }

    cout << "❌ Invalid username or password!" << endl;
    return false;
}

// ============================================================
//  FUNCTION: Create New Diary Entry
// ============================================================
void createEntry()
{
    if (entryCount >= MAX_ENTRIES)
    {
        cout << "⚠️  Diary full! Max 20 entries allowed." << endl;
        return;
    }

    cout << "\n--- New Entry ---" << endl;

    string title, content;
    cout << "Title   : ";
    cin.ignore();
    getline(cin, title);

    // Validate empty title
    if (title.empty())
    {
        cout << "⚠️  Title cannot be empty!" << endl;
        return;
    }

    cout << "Content : ";
    getline(cin, content);

    entries[entryCount].title        = title;
    entries[entryCount].content      = content;
    entries[entryCount].createdAt    = getCurrentDateTime();
    entries[entryCount].lastModified = entries[entryCount].createdAt;
    entryCount++;

    cout << "✅ Entry saved!" << endl;
}

// ============================================================
//  FUNCTION: View All Entries (short list)
// ============================================================
void viewAllEntries()
{
    if (entryCount == 0)
    {
        cout << "\n📖 No entries yet. Start writing!" << endl;
        return;
    }

    cout << "\n========== ALL DIARY ENTRIES ==========" << endl;
    cout << "Total Entries: " << entryCount             << endl;
    cout << "---------------------------------------"   << endl;

    for (int i = 0; i < entryCount; i++)
    {
        cout << "  [" << (i+1) << "] " << entries[i].title
             << "   (" << entries[i].createdAt << ")" << endl;
    }

    cout << "=======================================" << endl;
}

// ============================================================
//  FUNCTION: Read Full Entry
// ============================================================
void readFullEntry()
{
    viewAllEntries();
    if (entryCount == 0) return;

    cout << "\nEnter Entry Number to Read: ";
    int n; cin >> n;

    if (n < 1 || n > entryCount)
    {
        cout << "⚠️  Invalid entry number!" << endl;
        return;
    }

    int idx = n - 1;
    cout << "\n====================================" << endl;
    cout << "Title     : " << entries[idx].title        << endl;
    cout << "Created   : " << entries[idx].createdAt    << endl;
    cout << "Modified  : " << entries[idx].lastModified << endl;
    cout << "------------------------------------"       << endl;
    cout << entries[idx].content                        << endl;
    cout << "====================================" << endl;
}

// ============================================================
//  FUNCTION: Edit an Entry
// ============================================================
void editEntry()
{
    viewAllEntries();
    if (entryCount == 0) return;

    cout << "\nEnter Entry Number to Edit: ";
    int n; cin >> n;

    if (n < 1 || n > entryCount)
    {
        cout << "⚠️  Invalid entry number!" << endl;
        return;
    }

    int idx = n - 1;

    cout << "New Title (leave blank to keep \"" << entries[idx].title << "\"): ";
    cin.ignore();
    string newTitle;
    getline(cin, newTitle);

    if (!newTitle.empty())
        entries[idx].title = newTitle;

    cout << "New Content: ";
    string newContent;
    getline(cin, newContent);

    if (!newContent.empty())
        entries[idx].content = newContent;

    entries[idx].lastModified = getCurrentDateTime();

    cout << "✅ Entry updated!" << endl;
}

// ============================================================
//  FUNCTION: Delete One Entry
// ============================================================
void deleteOneEntry()
{
    viewAllEntries();
    if (entryCount == 0) return;

    cout << "\nEnter Entry Number to Delete: ";
    int n; cin >> n;

    if (n < 1 || n > entryCount)
    {
        cout << "⚠️  Invalid entry number!" << endl;
        return;
    }

    int idx = n - 1;
    string deletedTitle = entries[idx].title;

    // Shift entries left
    for (int i = idx; i < entryCount - 1; i++)
        entries[i] = entries[i + 1];

    entryCount--;
    cout << "✅ Entry \"" << deletedTitle << "\" deleted!" << endl;
}

// ============================================================
//  FUNCTION: Delete All Entries
// ============================================================
void deleteAllEntries()
{
    if (entryCount == 0)
    {
        cout << "\n⚠️  No entries to delete." << endl;
        return;
    }

    cout << "\nAre you sure? This will delete ALL " << entryCount
         << " entries! (1=Yes / 2=No): ";
    int confirm; cin >> confirm;

    if (confirm == 1)
    {
        entryCount = 0;
        cout << "✅ All entries deleted!" << endl;
    }
    else cout << "Cancelled." << endl;
}

// ============================================================
//  BONUS: Search Entry by Keyword in Title
// ============================================================
void searchByKeyword()
{
    cout << "\nEnter keyword to search: ";
    cin.ignore();
    string keyword;
    getline(cin, keyword);

    bool found = false;
    cout << "\n--- Search Results for \"" << keyword << "\" ---" << endl;

    for (int i = 0; i < entryCount; i++)
    {
        // Check if keyword exists in title
        if (entries[i].title.find(keyword) != string::npos)
        {
            cout << "  [" << (i+1) << "] " << entries[i].title
                 << "  (" << entries[i].createdAt << ")" << endl;
            found = true;
        }
    }

    if (!found) cout << "  No entries found with that keyword." << endl;
}

// ============================================================
//  MAIN MENU (shown after login)
// ============================================================
void mainMenu()
{
    int choice;
    do
    {
        cout << "\n========== DIARY MENU [" << loggedInUser << "] ==========" << endl;
        cout << "  1. Create New Entry"         << endl;
        cout << "  2. View All Entries"         << endl;
        cout << "  3. Read Full Entry"          << endl;
        cout << "  4. Edit an Entry"            << endl;
        cout << "  5. Delete One Entry"         << endl;
        cout << "  6. Delete All Entries"       << endl;
        cout << "  7. Search Entry by Keyword"  << endl;
        cout << "  8. Exit"                     << endl;
        cout << "=======================================" << endl;
        cout << "  Choice (1-8): ";
        cin  >> choice;

        switch (choice)
        {
            case 1: createEntry();      break;
            case 2: viewAllEntries();   break;
            case 3: readFullEntry();    break;
            case 4: editEntry();        break;
            case 5: deleteOneEntry();   break;
            case 6: deleteAllEntries(); break;
            case 7: searchByKeyword();  break;
            case 8: cout << "\n👋 Goodbye, " << loggedInUser << "!" << endl; break;
            default: cout << "\n⚠️  Invalid! Enter 1-8." << endl;
        }
    } while (choice != 8);
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "=================================" << endl;
    cout << "  📓 Personal Student Diary       " << endl;
    cout << "=================================" << endl;

    int authChoice;
    bool loggedIn = false;

    do
    {
        cout << "\n--- Welcome ---"       << endl;
        cout << "  1. Register"          << endl;
        cout << "  2. Login"             << endl;
        cout << "  3. Exit"              << endl;
        cout << "  Choice (1-3): ";
        cin  >> authChoice;

        switch (authChoice)
        {
            case 1: registerUser(); break;
            case 2:
                loggedIn = loginUser();
                if (loggedIn) mainMenu();
                break;
            case 3: cout << "\n👋 Bye!" << endl; break;
            default: cout << "⚠️  Invalid!" << endl;
        }
    } while (authChoice != 3);

    return 0;
}
