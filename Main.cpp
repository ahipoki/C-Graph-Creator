#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct compareChars{
  bool operator()(const char* a, const char* b) const{
    return strcmp(a, b) < 0;
  }
};

void strupper(char* str);
void addVertex(map<char*, int, compareChars>*, int&);
void addEdge(int**&, map<char*, int, compareChars>*);
void deleteVertex(int**&, map<char*, int, compareChars>*, int&);
void deleteEdge(int**&, map<char*, int, compareChars>*, int&);
void getShortestPath(int**, map<char*, int, compareChars>*);
void printGraph(int**, map<char*, int, compareChars>*);
int* dijkstra(int, int, int*&, bool*, int*, map<char*, int, compareChars>*, int**);
char* find(map<char*, int, compareChars>*, int);

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
      cout<<"That isn't a valid command"<<endl;
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

void addVertex(map<char*, int, >* vertices, int& nextVertexIndex){
  if (nextVertexIndex == 20){
    cout<<"There's too many vertices"<<endl;
    return;
  }
  char label[80];
  cout<<"Enter a label for the vertex"<<endl;
  cin.getline(label, sizeof(label));
  cin.clear();
  cin.ignore(999, '\n');
  map<char*, int>::iterator it;
  if (vertices->find(label) != vertices->end()){
    cout<<"There's already a vertex with that label"<<endl;
    return;
  }
  (*vertices)[label] = nextVertexIndex;
  nextVertexIndex = 0;
  while (find(vertices, nextVertexIndex) != NULL){
    nextVertexIndex++;
  }
  cout<<"Vertex added"<<endl;
  return;
}

void addEdge(){
  char* vertexOne[80];
  char* vertexTwo[80];
  cout<<"Enter a vertex label"<<endl;
  cin.getline(vertexOne, sizeof(vertexOne));
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter another vertex label"<<endl;
  cin.getline(vertexTwo, sizeof(vertexTwo));
  cin.clear();
  cin.ignore(999, '\n');
  if (strcmp(vertexOne, vertexTwo) == 0){
    cout<<"You need to enter two different vertex labels"<<endl;
    return;
  }
  if (vertices->find(vertexOne) == vertices->end()){
    cout<<vertexOne<<" does not exist"<<endl;
    return;
  }
  if (vertices->find(vertexTwo) == vertices->end()){
    cout<<vertexTwo<<" does not exist"<<endl;
    return;
  }
  cout<<"Enter a weight for the edge"<<endl;
  int edgeWeight;
  cin>>edgeWeight;
  cin.clear();
  cin.ignore(999, '\n');
  if (edgeWeight <= 0){
    cout<<"The edge's weight must be positive"<<endl;
    return;
  }
  int tempOne = vertices->find(vertexOne)->second;
  int tempTwo = vertices->find(vertexTwo)->second;
  table[tempOne][tempTwo] = edgeWeight;
  return;
}

void deleteVertex(){
  char label[80];
  cout<<"Enter the vertex label you want to delete"<<endl;
  cin.getline(label, sizeof(label));
  cin.clear();
  cin.ignore(999, '\n');
  if (vertices->find(label) == vertices->end()){
    cout<<label<<" does not exist"<<endl;
    return;
  }
}

void deleteEdge(){
  
}

void getShortestPath(){
  
}

void printGraph(){
  
}
