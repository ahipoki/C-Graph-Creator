#include <iostream>
#include <cstring>

using namespace std;

void strupper(char* str);
void addVertex();
void addEdge();
void deleteVertex();
void deleteEdge();

int main()
{
  char input[80];
  bool running = true;
  adj[20][20];
  while (running){
    cout<<"Do you want to add a vertex, add an edge, remove a vertex, remove an edge, find the shortest path, or quit?"<<endl;
    cin.getline(input, sizeof(input));
    strupper(input);
    if (strcmp(input, "ADD VERTEX") == 0){
      char label[80];
      cout<<"Enter a label for the vertex"<<endl;
      cin.getline(label, sizeof(label));
      strupper(label);
    }
    else if (strcmp(input, "ADD EDGE") == 0){
      char name1[80];
      char name2[80];
      int weight;
      cout<<"Enter a vertex name"<<endl;
      cin.getline(name1, sizeof(name1));
      strupper(name1);
      cout<<"Enter a second vertex name"<<endl;
      cin.getline(name2, sizeof(name2));
      strupper(name2);
      cout<<"Enter a weight for the edge"<<endl;
      cin>>weight;
      for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
          if (strcmp(name1, adj[i]) == 0){
            if (strcmp(name2, adj[j]) == 0){
              cout<<"Edge added"<<endl;
            }
            cout<<"Vertex not found"<<endl;
          }
          cout<<"Vertex not found"<<endl;
        }
      }
    }
    else if (strcmp(input, "REMOVE VERTEX") == 0){
      char name[80];
      cout<<"Enter a vertex name that you want to remove"<<endl;
      cin.getline(name, sizeof(name));
      strupper(name);
    }
    else if (strcmp(input, "REMOVE EDGE") == 0){
      char name1[80];
      char name2[80];
      cout<<"Enter a vertex name"<<endl;
      cin.getline(name1, sizeof(name1));
      strupper(name1);
      cout<<"Enter a second vertex name"<<endl;
      cin.getline(name2, sizeof(name2));
      strupper(name2);
    }
    else if (strcmp(input, "PATH") == 0){
      char name1[80];
      char name2[80];
      cout<<"Enter a vertex name"<<endl;
      cin.getline(name1, sizeof(name1));
      strupper(name1);
      cout<<"Enter a second vertex name"<<endl;
      cin.getline(name2, sizeof(name2));
      strupper(name2);
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
