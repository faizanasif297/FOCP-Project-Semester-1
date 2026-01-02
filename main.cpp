#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure Definitions
struct Date {
    int date;
    int month;
    int year;
};

struct Ingredient {
    string name;
    int quantity;
    string unit;
    Date expiryDate;
    string category;
};

struct Recipe {
    string dishName;
    string requiredIngredients[10];
    int requiredQuantities[10];
    int ingredientCount;
    string difficulty;
};

// Global Variables
const int MAX_PANTRY = 100;
const int MAX_RECIPES = 50;

Ingredient pantry[MAX_PANTRY];
int pantryCount = 0;

Recipe cookbook[MAX_RECIPES];
int recipeCount = 0;

Date currentDate;

// Function Prototypes
void loadData();
void saveData();
void addIngredient();
void removeIngredient();
void checkExpiry();
void suggestRecipes();
void randomSurprise();
void loadHardcodedRecipes();
void displayMenu();
void initializeTime();
void checkShortage();
void smartRecipePlanner();

// Main Function
int main() {
    srand(time(0));
    loadHardcodedRecipes();
    loadData();
    initializeTime();

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\n--- CURRENT PANTRY ---\n";
            if (pantryCount == 0)
                cout << "Pantry is empty.\n";
            for (int i = 0; i < pantryCount; i++) {
                cout << i + 1 << ". " << pantry[i].name
                     << " (" << pantry[i].quantity << " " << pantry[i].unit << ") "
                     << "Exp: " << pantry[i].expiryDate.date << "/"
                     << pantry[i].expiryDate.month << "/"
                     << pantry[i].expiryDate.year << endl;
            }
            break;
        case 2: addIngredient(); break;
        case 3: removeIngredient(); break;
        case 4: checkExpiry(); break;
        case 5: suggestRecipes(); break;
        case 6: smartRecipePlanner(); break;
        case 7: checkShortage(); break;
        case 8: randomSurprise(); break;
        case 9:
            saveData();
            cout << "Data saved. Exiting program...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    } while (choice != 9);

    return 0;
}

// Display Menu
void displayMenu() {
    cout << "\n====================================\n";
    cout << "*********** PANTRY SYSTEM ***********\n";
    cout << "====================================\n";
    cout << "1. View Pantry\n";
    cout << "2. Add Ingredient\n";
    cout << "3. Remove Ingredient\n";
    cout << "4. Check Expiry Status\n";
    cout << "5. What Can I Cook?\n";
    cout << "6. Smart Recipe Planner\n";
    cout << "7. Check Ingredient Shortage\n";
    cout << "8. Surprise Me\n";
    cout << "9. Save & Exit\n";
    cout << "====================================\n";
    cout << "Enter choice: ";
}

// Time initialization + expiry adjustment
void initializeTime() {
    cout << "\n--- TIME INITIALIZATION ---\n";
    cout << "Enter today's date\n";
    cout << "Date: "; cin >> currentDate.date;
    cout << "Month: "; cin >> currentDate.month;
    cout << "Year: "; cin >> currentDate.year;

    int daysPassed;
    cout << "Enter number of days passed since last use (0 if first run): ";
    cin >> daysPassed;

    currentDate.date += daysPassed;
    while (currentDate.date > 30) {
        currentDate.date -= 30;
        currentDate.month++;
        if (currentDate.month > 12) {
            currentDate.month = 1;
            currentDate.year++;
        }
    }
}

// Add ingredient
void addIngredient() {
    if (pantryCount >= MAX_PANTRY) {
        cout << "Pantry full, cannot add more ingredients.\n";
        return;
    }

    cin.ignore();
    cout << "Item Name: ";
    getline(cin, pantry[pantryCount].name);

    cout << "Quantity: ";
    cin >> pantry[pantryCount].quantity;

    cout << "Unit: ";
    cin >> pantry[pantryCount].unit;

    cin.ignore();
    cout << "Category: ";
    getline(cin, pantry[pantryCount].category);

    int days;
    cout << "Expires in how many days? ";
    cin >> days;

    pantry[pantryCount].expiryDate = currentDate;
    pantry[pantryCount].expiryDate.date += days;
    while (pantry[pantryCount].expiryDate.date > 30) {
        pantry[pantryCount].expiryDate.date -= 30;
        pantry[pantryCount].expiryDate.month++;
        if (pantry[pantryCount].expiryDate.month > 12) {
            pantry[pantryCount].expiryDate.month = 1;
            pantry[pantryCount].expiryDate.year++;
        }
    }

    pantryCount++;
    cout << "Ingredient added successfully.\n";
}

// Expiry checking
void checkExpiry() {
    cout << "\n--- EXPIRY REPORT ---\n";
    for (int i = 0; i < pantryCount; i++) {
        if (pantry[i].expiryDate.year < currentDate.year ||
           (pantry[i].expiryDate.year == currentDate.year &&
            pantry[i].expiryDate.month < currentDate.month) ||
           (pantry[i].expiryDate.year == currentDate.year &&
            pantry[i].expiryDate.month == currentDate.month &&
            pantry[i].expiryDate.date < currentDate.date)) {

            cout << "EXPIRED: " << pantry[i].name << endl;
        }
        else if (pantry[i].expiryDate.year == currentDate.year &&
                 pantry[i].expiryDate.month == currentDate.month &&
                 pantry[i].expiryDate.date - currentDate.date <= 3) {

            cout << "EXPIRING SOON: " << pantry[i].name << endl;
        }
    }
}

// Load hardcoded recipes
void loadHardcodedRecipes() {
    recipeCount = 3;

    cookbook[0].dishName = "Pasta";
    cookbook[0].ingredientCount = 3;
    cookbook[0].requiredIngredients[0] = "Pasta"; cookbook[0].requiredQuantities[0] = 200;
    cookbook[0].requiredIngredients[1] = "Tomato"; cookbook[0].requiredQuantities[1] = 2;
    cookbook[0].requiredIngredients[2] = "Cheese"; cookbook[0].requiredQuantities[2] = 50;
    cookbook[0].difficulty = "Easy";

    cookbook[1].dishName = "Omelette";
    cookbook[1].ingredientCount = 3;
    cookbook[1].requiredIngredients[0] = "Egg"; cookbook[1].requiredQuantities[0] = 2;
    cookbook[1].requiredIngredients[1] = "Milk"; cookbook[1].requiredQuantities[1] = 50;
    cookbook[1].requiredIngredients[2] = "Salt"; cookbook[1].requiredQuantities[2] = 1;
    cookbook[1].difficulty = "Easy";

    cookbook[2].dishName = "Salad";
    cookbook[2].ingredientCount = 2;
    cookbook[2].requiredIngredients[0] = "Lettuce"; cookbook[2].requiredQuantities[0] = 1;
    cookbook[2].requiredIngredients[1] = "Tomato"; cookbook[2].requiredQuantities[1] = 2;
    cookbook[2].difficulty = "Easy";
}

// Save / Load pantry data
void saveData() {
    ofstream fout("pantry.txt");
    fout << pantryCount << endl;
    for (int i = 0; i < pantryCount; i++) {
        fout << pantry[i].name << endl;
        fout << pantry[i].quantity << endl;
        fout << pantry[i].unit << endl;
        fout << pantry[i].category << endl;
        fout << pantry[i].expiryDate.date << " "
             << pantry[i].expiryDate.month << " "
             << pantry[i].expiryDate.year << endl;
    }
    fout.close();
}

void loadData() {
    ifstream fin("pantry.txt");
    if (!fin) return;
    fin >> pantryCount;
    fin.ignore();
    for (int i = 0; i < pantryCount; i++) {
        getline(fin, pantry[i].name);
        fin >> pantry[i].quantity;
        fin >> pantry[i].unit;
        fin.ignore();
        getline(fin, pantry[i].category);
        fin >> pantry[i].expiryDate.date
            >> pantry[i].expiryDate.month
            >> pantry[i].expiryDate.year;
        fin.ignore();
    }
    fin.close();
}

// Remove ingredient
void removeIngredient() {
    if (pantryCount == 0) {
        cout << "Pantry is empty.\n";
        return;
    }
    cout << "Enter ingredient number to remove: ";
    int num;
    cin >> num;
    if (num < 1 || num > pantryCount) {
        cout << "Invalid number.\n";
        return;
    }
    for (int i = num - 1; i < pantryCount - 1; i++)
        pantry[i] = pantry[i + 1];
    pantryCount--;
    cout << "Ingredient removed.\n";
}

// Suggest recipes
void suggestRecipes() {
    cout << "\n--- RECIPES YOU CAN MAKE ---\n";
    for (int r = 0; r < recipeCount; r++) {
        bool canMake = true;
        for (int i = 0; i < cookbook[r].ingredientCount; i++) {
            bool found = false;
            for (int j = 0; j < pantryCount; j++) {
                if (pantry[j].name == cookbook[r].requiredIngredients[i] &&
                    pantry[j].quantity >= cookbook[r].requiredQuantities[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                canMake = false;
                break;
            }
        }
        if (canMake)
            cout << cookbook[r].dishName << endl;
    }
}

// Random recipe
void randomSurprise() {
    int possible[50], count = 0;
    for (int r = 0; r < recipeCount; r++) {
        bool canMake = true;
        for (int i = 0; i < cookbook[r].ingredientCount; i++) {
            bool found = false;
            for (int j = 0; j < pantryCount; j++) {
                if (pantry[j].name == cookbook[r].requiredIngredients[i] &&
                    pantry[j].quantity >= cookbook[r].requiredQuantities[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) { canMake = false; break; }
        }
        if (canMake) possible[count++] = r;
    }
    if (count == 0) cout << "No recipes available.\n";
    else {
        int idx = possible[rand() % count];
        cout << "Try making: " << cookbook[idx].dishName << endl;
    }
}

// Check shortages
void checkShortage() {
    cout << "\n--- INGREDIENT SHORTAGE ---\n";
    for (int r = 0; r < recipeCount; r++) {
        cout << cookbook[r].dishName << ": ";
        bool shortage = false;
        for (int i = 0; i < cookbook[r].ingredientCount; i++) {
            int needed = cookbook[r].requiredQuantities[i];
            for (int j = 0; j < pantryCount; j++)
                if (pantry[j].name == cookbook[r].requiredIngredients[i])
                    needed -= pantry[j].quantity;
            if (needed > 0) {
                cout << cookbook[r].requiredIngredients[i] << " ";
                shortage = true;
            }
        }
        if (!shortage) cout << "All ingredients available";
        cout << endl;
    }
}

// Smart recipe planner
void smartRecipePlanner() {
    int bestRecipe = -1, minMissing = 1000;
    for (int r = 0; r < recipeCount; r++) {
        int missing = 0;
        for (int i = 0; i < cookbook[r].ingredientCount; i++) {
            int needed = cookbook[r].requiredQuantities[i];
            for (int j = 0; j < pantryCount; j++)
                if (pantry[j].name == cookbook[r].requiredIngredients[i])
                    needed -= pantry[j].quantity;
            if (needed > 0) missing += needed;
        }
        if (missing < minMissing) {
            minMissing = missing;
            bestRecipe = r;
        }
    }
    if (bestRecipe == -1) cout << "No recipes available.\n";
    else cout << "Suggested recipe: " << cookbook[bestRecipe].dishName << endl;
}
