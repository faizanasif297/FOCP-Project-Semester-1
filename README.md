# Smart Pantry Management System

**FOCP Project – Semester 1**  

**Project Members:**  
1. Muhammad Faizan Asif (551256)  
2. Salman Javed (546596)  

---

## Project Overview
The Smart Pantry Management System is a **C++ console application** designed to help users manage food inventory, track expiration dates, and plan meals efficiently. Users can:

- View pantry items with details  
- Add or remove ingredients  
- Receive recipe suggestions based on available stock  
- Get random recipe recommendations  
- Monitor soon-to-expire or expired items  

The system uses **arrays, structs, and functions** to handle data and **text files** for persistent storage.

---

## Features

### Pantry Management
- **View Pantry:** Shows all ingredients with quantity, unit, category, and expiry date.  
- **Add Ingredient:** Add a new item with quantity, unit, category, and expiry in days.  
- **Remove Ingredient:** Remove items by selecting them from the list.

### Recipe Management
- **What Can I Cook?:** Lists recipes that can be prepared with available ingredients.  
- **Random Surprise:** Suggests a random recipe to cook.  
- **Smart Recipe Planner:** Suggests recipes with the fewest missing ingredients.  
- **Check Ingredient Shortage:** Shows missing quantities for each recipe.

### Expiry Tracking
- Alerts users about expired items or items expiring in ≤3 days.

### Data Persistence
- Saves pantry data to `pantry.txt` on exit.  
- Loads data from `pantry.txt` at program start.

---

## How to Use

### Time Initialization
At first run, the program prompts you to enter:

- Current **day, month, year**  
- Number of **days passed since last run** (0 if first use)

### Main Menu

SMART PANTRY MANAGER v1.0  
[1] View My Pantry  
[2] Add New Item  
[3] Remove Item  
[4] What Can I Cook? (Recipe Finder)  
[5] Surprise Me! (Random Choice)  
[6] Save & Exit  
Enter your choice:  
### Viewing Pantry  
- Displays all pantry items with details.  
- If pantry is empty, prints:
Pantry is empty

### Adding Ingredients
- Enter Name, Quantity, Unit, Category, and Expiry (in days).  
- Prints confirmation:
Ingredient added successfully

### Removing Ingredients
- Enter the number of the ingredient to remove.  
- Pantry automatically shifts remaining items.  
- If not found, prints:
Item not found

### Recipe Suggestions
- Lists recipes that can be cooked based on available ingredients.  
- Shows recipe name, difficulty, and ingredient status.  

Example:
--- MATCHING RECIPES FOUND ---
Cheese Omelette (Difficulty: Easy)
You have: Eggs (6), Cheese (200g)
Status: Ready to cook!

### Random Recipe
- Picks a random recipe you can make from available ingredients.

### Expiry Check
- Displays:
EXPIRED: Milk
EXPIRING SOON: Cheese

### Save & Exit
- Saves pantry data to `pantry.txt`  
- Prints:
Data saved. Exiting...

---

## Data Structures

### Date
```cpp
struct Date {
    int day;
    int month;
    int year;
};
```
### Ingredient
```cpp
struct Ingredient {
    string name;
    int quantity;
    string unit;
    Date expiryDate;
    string category;
};
```
### Recipe
```cpp
struct Recipe {
    string dishName;
    string requiredIngredients[10];
    int requiredQuantities[10];
    int ingredientCount;
    string difficulty;
};
```
### Global Arrays:  
Ingredient pantry[100]; // Up to 100 ingredients  
Recipe cookbook[50];    // Up to 50 recipes

