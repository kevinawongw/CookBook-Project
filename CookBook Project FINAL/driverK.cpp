#include "recipeBookK.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
// you may include more libraries as needed

using namespace std;

string toLower(string word)
{
  int L = word.length();
  for (int i = 0; i < L; i++)
  {
    word[i] = tolower(word[i]);
  }
  return word;
}

void menu()
{
  cout << "============Main Menu============" << endl;
  cout << "1. Print list of recipe" << endl;
  cout << "2. Search by name of the recipe" << endl;
  cout << "3. Search by ingredient on hand" << endl;
  cout << "4. Search by meal type (breakfast, lunch, dinner)" << endl;
  cout << "5. Print Best Match by Difficulty" << endl;
  cout << "6. Print Best Match by Meal" << endl;
  cout << "7. Add your own recipe" << endl;
  cout << "8. ReadMe :)" << endl;
  cout << "9. Quit" << endl
       << endl;

  cout << "Select a Numerical Option" << endl;
}

int main(int argc, char **argv)
{
  //These are our four hash tables
  RecipeTable byName(100);
  RecipeTable byIngredient(100);
  RecipeTable byMeal(100);
  RecipeTable byDiff(100);
  string line = "";
  string ingredient = "";
  string choice = "";
  string meal = "";
  string name = "";
  string difficulty = "";

  string addName = "";
  string addMain = "";
  string adding2 = "";
  string adding3 = "";
  string adding4 = "";
  string addTime = "";
  string addDiff = "";
  string newRecipeA = "";
  string addMealType = "";
  int newNumIng = 0;
  string answer = "";
  bool b = true;

  bool a = true;

  //Reading in file
  ifstream stream(argv[1]);
  while (getline(stream, line))
  {
    stringstream ss;
    ss << line;
    string section = "";

    getline(ss, section, ',');
    string recipeName = section;
    getline(ss, section, ',');
    string mainIngredient = section;
    getline(ss, section, ',');
    string ing2 = section;
    getline(ss, section, ',');
    string ing3 = section;
    getline(ss, section, ',');
    string ing4 = section;
    getline(ss, section, ',');
    int cookTime = stoi(section);
    getline(ss, section, ',');
    int difficulty = stoi(section);
    getline(ss, section, ',');
    int numIng = stoi(section);
    getline(ss, section, ',');
    string mealType = section;

    byName.addRecipeForName(recipeName, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType);
    byIngredient.addRecipeForIngredient(recipeName, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType);
    byMeal.addRecipeForMeal(recipeName, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType);
    byDiff.addRecipeForDiff(recipeName, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType);
  }
  while (a)
  {
    menu();
    getline(cin, choice);
    switch (stoi(choice))
    {
    //Print List of Recipes
    case 1:
    {
      byMeal.skimBook();
      break;
    }
    //Search a recipe by Name
    case 2:
    {
      cout << "What recipe would you like to make?" << endl;
      getline(cin, name);
      if (byName.isInTable(toLower(name)))
      {
        byName.searchName(toLower(name));
        byName.printSearchedRecipe(toLower(name));
      }
      else
      {
        cout << "There is no recipe for " << name << endl;
      }
      break;
    }
    //Search by Ingredients you have on hand
    case 3:
    {
      cout << "What main ingredient do you have?" << endl;
      getline(cin, ingredient);
      byIngredient.printByIngredient(toLower(ingredient));
      break;
    }
    //Search by Meal Type
    case 4:
    {
      cout << "What meal type would you like (Breakfast/Lunch/Dinner)" << endl;
      getline(cin, meal);
      byMeal.printByMeal(toLower(meal));
      break;
    }
    //Search by Difficulty Level
    case 5:
    {
      cout << "What difficulty level would you like?" << endl;
      getline(cin, difficulty);
      byDiff.printBestMatchDiff(stoi(difficulty));
      break;
    }
    //Print Best Match by Meal
    case 6:
    {
      cout << "What meal are you eating? (Breakfast/Lunch/Dinner)" << endl;
      getline(cin, meal);
      byMeal.printBestMatchMeal(toLower(meal));
      break;
    }
    //Add a recipe
    case 7:
    {
      newNumIng = 1;
      cout << "What is the name of your recipe?" << endl;
      getline(cin, addName);
      if (byName.isInTable(toLower(addName)))
      {
        cout << "There is already a recipe for this in the book!" << endl;
        break;
      }
      else
      {
        cout << "What is the main ingredient? " << endl;
        getline(cin, addMain);
        cout << "Is there another ingredient? (Y/N)" << endl;
        getline(cin, answer);
        if (answer == "Y" || answer == "y")
        {
          newNumIng++;
          cout << "What is ingredient #2?" << endl;
          getline(cin, adding2);
          cout << "Is there another ingredient? (Y/N)" << endl;
          getline(cin, answer);
          if (answer == "Y" || answer == "y")
          {
            newNumIng++;
            cout << "What is ingredient #3?" << endl;
            getline(cin, adding3);
            cout << "Is there another ingredient? (Y/N)" << endl;
            getline(cin, answer);
            if (answer == "Y" || answer == "y")
            {
              newNumIng++;
              cout << "What is ingredient #4?" << endl;
              getline(cin, adding4);
            }
            else if (answer == "N" || answer == "n")
            {
              adding4 = "none";
            }
          }
          else if (answer == "N" || answer == "n")
          {
            adding3 = "none";
            adding4 = "none";
          }
        }
        else if (answer == "N" || answer == "n")
        {
          adding2 = "none";
          adding3 = "none";
          adding4 = "none";
        }
      }
      cout << "How long does this Recipe take to make?" << endl;
      getline(cin, addTime);
      // int addCookingTime=stoi(addTime);
      cout << "How difficult is this recipe?" << endl;
      getline(cin, addDiff);
      // int newDiff=stoi(addDiff);
      cout << "What is the meal type? (Breakfast/Lunch/Dinner)" << endl;
      getline(cin, addMealType);

      byName.addRecipeForName(toLower(addName), toLower(addMain), toLower(adding2), toLower(adding3), toLower(adding4), stoi(addTime), stoi(addDiff), newNumIng, toLower(addMealType));
      byIngredient.addRecipeForIngredient(toLower(addName), toLower(addMain), toLower(adding2), toLower(adding3), toLower(adding4), stoi(addTime), stoi(addDiff), newNumIng, toLower(addMealType));
      byMeal.addRecipeForMeal(toLower(addName), toLower(addMain), toLower(adding2), toLower(adding3), toLower(adding4), stoi(addTime), stoi(addDiff), newNumIng, toLower(addMealType));
      byDiff.addRecipeForDiff(toLower(addName), toLower(addMain), toLower(adding2), toLower(adding3), toLower(adding4), stoi(addTime), stoi(addDiff), newNumIng, toLower(addMealType));

      newRecipeA = "\n" + toLower(addName) + "," + toLower(addMain) + "," + toLower(adding2) + "," + toLower(adding3) + "," + toLower(adding4) + "," + addTime + "," + addDiff + "," + to_string(newNumIng) + "," + toLower(addMealType);
      ofstream outfile;
      outfile.open(argv[1], std::ios::app);
      outfile << newRecipeA;
      outfile.close();

      cout << endl
           << "Successfully added " << addName << " to the recipe book!" << endl;

      break;
    }
    //readmeee (instructions)
    case 8:
    {
      cout << "Hello! Welcome to the B(e)ST Recipe Book!" << endl
           << endl;
      cout << "*Menu option 1 allows you to skim through the book to see all of the possible Recipes you can make!" << endl;
      cout << "*Menu option 3 and 4 allows you to filter recipes that are possible depending on ingredients or meal type!" << endl
           << "Then search the name of the recipe using menu option 2 so see the full recipe!" << endl;
      cout << "*Menu option 5 will show you the -Best Match- meals by difficulty level!" << endl;
      cout << "*Menu option 6 will show you the -Best Match- meals by meal type!" << endl;
      cout << "*Have your own recipe? Add it to the recipe list using Meny option 7!" << endl;

      cout << endl
           << "Happy Cooking!" << endl;
      break;
    }
    //Exit
    case 9:
    {
      cout << "Goodbye!" << endl;
      a = false;
      break;
    }
    }
  }
}
