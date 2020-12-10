#ifndef RECIPEBOOK_HPP
#define RECIPEBOOK_HPP

#include <string>
#include <cstring>

using namespace std;

struct RecipeItem
{
  string name;
  string mainIngredient;
  string ing2;
  string ing3;
  string ing4;
  int cookTime;
  int difficulty;
  int numIng;
  string mealType;
  struct RecipeItem *next;
};

class RecipeTable
{
public:
  RecipeTable(int recipeTableSize); //done
  ~RecipeTable();                   //done
  RecipeItem *createNode(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType, RecipeItem *next);
  void addRecipeForName(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType); //done
  bool isInTable(string name);                                                                                                                                 //done
  void skimBook();
  void addRecipeForMeal(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType);       //done
  void addRecipeForDiff(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType);       //done
  void addRecipeForIngredient(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType); //done
  RecipeItem *searchName(string name);
  void printSearchedRecipe(string name);
  void printBestMatch();
  void printByIngredient(string mainIngredient);
  void printByMeal(string meal);
  unsigned int getHash(string name); //done
  unsigned int getHashDiff(int num);
  void printBestMatchDiff(int input);
  void printBestMatchMeal(string input);

private:
  int tableSize;
  RecipeItem **recipeTable;
};

#endif
