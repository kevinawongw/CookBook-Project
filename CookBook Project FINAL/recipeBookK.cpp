#include "recipeBookK.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

//Constructor
RecipeTable::RecipeTable(int recipeTableSize)
{
  tableSize = recipeTableSize;
  recipeTable = new RecipeItem *[tableSize];
  for (int i = 0; i < tableSize; i++)
  {
    recipeTable[i] = NULL;
  }
}

//Destructor
RecipeTable::~RecipeTable()
{
  for (int i = 0; i < tableSize; i++)
  {
    RecipeItem *temp = recipeTable[i];
    while (temp != NULL)
    {
      RecipeItem *a = temp;
      temp = temp->next;
      delete a;
    }
  }
  delete recipeTable;
}

/*
Function: createRecipeNode
Adds a new struct RecipeItem
*/

RecipeItem *RecipeTable::createNode(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType, RecipeItem *next)
{
  RecipeItem *nr = new RecipeItem;
  nr->name = name;
  nr->mainIngredient = mainIngredient;
  nr->ing2 = ing2;
  nr->ing3 = ing3;
  nr->ing4 = ing4;
  nr->cookTime = cookTime;
  nr->difficulty = difficulty;
  nr->numIng = numIng;
  nr->mealType = mealType;
  nr->next = NULL;

  return nr;
}
/*
Function: addRecipe
add recipe into the hash table
*/

void RecipeTable::addRecipeForName(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{

  int index = getHash(name); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }
    else
    {
      recipeTable[index] = ptr;
      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    return;
  }
  return;
}

void RecipeTable::addRecipeForIngredient(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{
  int index = getHash(mainIngredient); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }

    else
    {
      recipeTable[index] = ptr;
      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    return;
  }
  return;
}

void RecipeTable::addRecipeForMeal(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{

  int index = getHash(mealType); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }

    else
    {
      recipeTable[index] = ptr;
      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    return;
  }
  return;
}

void RecipeTable::addRecipeForDiff(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{
  int index = getHashDiff(difficulty);
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp -> next != NULL)
      {
        temp = temp -> next;
      }
      temp -> next = ptr;
    }
    else
    {
      recipeTable[index] = ptr;
      ptr -> next = NULL;
      delete temp;
    }
  }
  else
  {
    return;
  }
  return;
}
/*
Function: isInTable{
  Returns true if the recipe is in the table and false otherwise.
}

*/
bool RecipeTable::isInTable(string name)
{

  RecipeItem *temp = searchName(name);
  if (temp == nullptr)
  {
    return false;
  }
  else
  {
    return true;
  }
}

/*
Function: Skim Book
Prints all of the possible recipes, so the user can quickly see options.
*/

void RecipeTable::skimBook()
{
  int k = 1;
  cout << "Here are all of the recipes in the book: " << endl;
  for (int i = 0; i < tableSize; i++)
  {
    RecipeItem *temp = recipeTable[i];
    while (temp != NULL)
    {
      cout << k << ".) ";
      cout << temp->name << endl;
      temp = temp->next;
      k++;
    }
  }
}

/*
Function: SearchName
Search the hash table for the parameterized name and returns the RecipeItem with the name.
*/

RecipeItem *RecipeTable::searchName(string name)
{

  int index = getHash(name);

  if (recipeTable[index] != nullptr)
  {
    RecipeItem *temp = recipeTable[index];
    while (temp != nullptr)
    {
      if (temp->name == name)
      {
        return temp;
      }
      else
      {
        temp = temp->next;
      }
    }
  }

  return nullptr;
}

/*
Function: printByIngredients
This function will find the ingredient's hash index and print out those recipes with the parameterized ingredient.
*/
void RecipeTable::printByIngredient(string mainIngredient)
{
  int index = getHash(mainIngredient);
  if (recipeTable[index] != NULL)
  {
    cout << "Here are recipes that you can make with " << mainIngredient << ":" << endl;
    RecipeItem *temp = recipeTable[index];
    while (temp != NULL)
    {
      cout << temp->name << endl;
      temp = temp->next;
    }
  }
}

void RecipeTable::printBestMatchDiff(int input)
{
  int total = 100;
  vector<RecipeItem *> vec;
  RecipeItem *add = new RecipeItem;
  int size = 0;
  int huehue = 0;
  int i = getHashDiff(input);


  add = recipeTable[i];
  while (add != nullptr)
  {
    vec.push_back(add);
    add = add->next;
  }

  int count = -1;
  size = vec.size();


  for (int i = 0; i < size - 1; i++)
  {
    count = -1;
    for (int j = 0; j < size - i - 1; j++)
    {
      if ((vec[j + 1]->numIng + vec[j + 1]->difficulty + vec[j + 1]->cookTime) > (vec[j ]->numIng + vec[j ]->difficulty + vec[j ]->cookTime))
      {
        swap(vec[j], vec[j + 1]);
        count = 1;
      }
    }
    if (count == -1)
    {
      break;
    }
  }
  reverse(vec.begin(), vec.end());



  for (int i = 0; i < 5; i++)
  {

    cout << "Best Match #" << i + 1 << endl
         << endl;
    cout << "Recipe Name: " << vec[i]->name << endl;
    cout << "Ingredients: " << endl;
    cout << "1.) " << vec[i]->mainIngredient << endl;
    if (vec[i]->ing2 != "none")
    {
      cout << "2.) " << vec[i]->ing2 << endl;
    }
    if (vec[i]->ing3 != "none")
    {
      cout << "3.) " << vec[i]->ing3 << endl;
    }
    if (vec[i]->ing4 != "none")
    {
      cout << "4.) " << vec[i]->ing4 << endl;
    }
    cout << "Cook Time: " << vec[i]->cookTime << " minutes" << endl;
    cout << "Difficulty: Level " << vec[i]->difficulty << endl;
    cout << "Meal Type: " << vec[i]->mealType << endl
         << endl;
  }
}

void RecipeTable::printBestMatchMeal(string input)
{
  int total = 100;
  vector<RecipeItem *> vec;
  RecipeItem *add = new RecipeItem;
  int size = 0;
  int i = getHash(input);
  add = recipeTable[i];
  while (add != nullptr)
  {
    vec.push_back(add);
    add = add->next;
  }
  int count = -1;
  size = vec.size();
  for (int i = 0; i < size - 1; i++)
  {
    count = -1;
    for (int j = 0; j < size - i - 1; j++)
    {
      if ((vec[j + 1]->numIng + vec[j + 1]->difficulty + vec[j + 1]->cookTime) > (vec[j + 1]->numIng + vec[j + 1]->difficulty + vec[j + 1]->cookTime))
      {
        swap(vec[j], vec[j + 1]);
        count = 1;
      }
    }
    if (count == -1)
    {
      break;
    }
  }
  reverse(vec.begin(), vec.end());

  for (int i = 0; i < 5; i++)
  {

    cout << "Best Match #" << i + 1 << endl
         << endl;
    cout << "Recipe Name: " << vec[i]->name << endl;
    cout << "Ingredients: " << endl;
    cout << "1.) " << vec[i]->mainIngredient << endl;
    if (vec[i]->ing2 != "none")
    {
      cout << "2.) " << vec[i]->ing2 << endl;
    }
    if (vec[i]->ing3 != "none")
    {
      cout << "3.) " << vec[i]->ing3 << endl;
    }
    if (vec[i]->ing4 != "none")
    {
      cout << "4.) " << vec[i]->ing4 << endl;
    }
    cout << "Cook Time: " << vec[i]->cookTime << " minutes" << endl;
    cout << "Difficulty: Level " << vec[i]->difficulty << endl;
    cout << "Meal Type: " << vec[i]->mealType << endl
         << endl;
  }
}

void RecipeTable::printByMeal(string meal)
{
  int index = getHash(meal);
  if (recipeTable[index] != NULL)
  {
    cout << "Here are recipes that you can make for " << meal << ":" << endl;
    RecipeItem *temp = recipeTable[index];
    while (temp != NULL)
    {
      cout << temp->name << endl;
      temp = temp->next;
    }
  }
}

/*
Function: getHash
Finds the index of a certain name/ingredient/difficulty
*/

unsigned int RecipeTable::getHash(string name)
{

  unsigned int hashValue = 5381;
  int length = name.length();
  for (int i = 0; i < length; i++)
  {
    hashValue = ((hashValue << 5) + hashValue) + name[i];
  }
  hashValue %= tableSize;
  return hashValue;
}

unsigned int RecipeTable::getHashDiff(int num)
{
  return (num % tableSize);
}

void RecipeTable::printSearchedRecipe(string name)
{
  RecipeItem *found = searchName(name);
  cout << "Here is how to make " << name << endl;
  cout << "Difficulty: " << found->difficulty << endl;
  cout << "Ingredients: " << endl;
  cout << "1.) " << found->mainIngredient << endl;
  if (found->ing2 != "none")
  {
    cout << "2.) " << found->ing2 << endl;
  }
  if (found->ing3 != "none")
  {
    cout << "3.) " << found->ing3 << endl;
  }
  if (found->ing4 != "none")
  {
    cout << "4.) " << found->ing4 << endl;
  }

  cout << "Cooking Time: " << found->cookTime << endl;
}
