#include <iostream>
#include <cstring>

using namespace std;

void strupper(char* str);
void addVertex();
void addEdge();
void deleteVertex();
void deleteEdge();
void getShortestPath();
void printGraph();

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
      addVertex(vertices, nextVertexIndex);
    }
    else if (strcmp(input, "ADD EDGE") == 0){
      addEdge(table, vertices);
    }
    else if (strcmp(input, "REMOVE VERTEX") == 0){
      deleteVertex(table, vertices, nextVertexIndex);
    }
    else if (strcmp(input, "REMOVE EDGE") == 0){
      deleteEdge(table, vertices);
    }
    else if (strcmp(input, "PATH") == 0){
      getShortestPath(table, vertices);
    }
    else if (strcmp(input, "PRINT") == 0){
      printGraph(table, vertices);
    }
    else if (strcmp(input, "QUIT") == 0){
      running = false;
    }
    else{
      cout<<"Input not valid"<<endl;
    }
  }
  return 0;
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = toupper(str[i]);
  }
}
