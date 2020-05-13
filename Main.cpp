#include <iostream>
#include <cstring>

using namespace std;

void strupper(char* str);

int main()
{
  char input[80];
  bool running = true;
  while (running){
    cout<<"Do you want to add a vertex, add an edge, remove a vertex, remove an edge, find the shortest path, or quit?"<<endl;
    cin.getline(input, sizeof(input));
    strupper(input);
    if (strcmp(input, "ADD VERTEX") == 0){
      cout<<"Added a vertex"<<endl;
    }
    else if (strcmp(input, "ADD EDGE") == 0){
      cout<<"Added an edge"<<endl;
    }
    else if (strcmp(input, "REMOVE VERTEX") == 0){
      cout<<"Removed a vertex"<<endl;
    }
    else if (strcmp(input, "REMOVE EDGE") == 0){
      cout<<"Removed an edge"<<endl;
    }
    else if (strcmp(input, "PATH") == 0){
      cout<<"Shortest Path"<<endl;
    }
    else if (strcmp(input, "QUIT") == 0){
      running = false;
    }
  }
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = toupper(str[i]);
  }
}
