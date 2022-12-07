#ifndef MENUCONTROL_H
#define MENUCONTROL_H

#include <string>
#include <vector>
using namespace std;

class MenuControl {
  private:
    vector<string> games;
    int curr, numGames;
    void next();
    void displayGames();
    
  public:
    MenuControl(const string listGames[], int size);
    int loop();
    int getNumGames();


};

#endif