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
  map<char*, int, compareChars>* vertices = new map<char*, int, compareChars>;
  int nextVertex = 0;
  int** table = new int*[20];
  for (int i = 0; i < 20; i++){
    table[i] = new int[20];
    for (int j = 0; j < 20; j++){
      table[i][j] = -1;
    }
  }
  char input[80];
  bool running = true;
  while (running){
    cout<<"Do you want to add a vertex, add an edge, remove a vertex, remove an edge, find the shortest path, print out the connections, or quit?"<<endl;
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
  delete vertices;
  for (int i = 0; i < 20; i++){
    delete[] table[i];
  }
  delete[] table;
  return 0;
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = toupper(str[i]);
  }
}

void addVertex(map<char*, int, compareChars>* vertices, int& nextVertex){
  if (nextVertex == 20){
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
  (*vertices)[label] = nextVertex;
  nextVertex = 0;
  while (find(vertices, nextVertex) != NULL){
    nextVertex++;
  }
  cout<<"Vertex added"<<endl;
  return;
}

void addEdge(int**& table, map<char*, int, compareChars>* vertices){
  char vertexOne[80];
  char vertexTwo[80];
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
  int pointOne = vertices->find(vertexOne)->second;
  int pointTwo = vertices->find(vertexTwo)->second;
  table[pointOne][pointTwo] = edgeWeight;
  return;
}

void deleteVertex(int**& table, map<char*, int, compareChars>* vertices, int& nextVertex){
  char label[80];
  cout<<"Enter the vertex label you want to delete"<<endl;
  cin.getline(label, sizeof(label));
  cin.clear();
  cin.ignore(999, '\n');
  if (vertices->find(label) == vertices->end()){
    cout<<label<<" does not exist"<<endl;
    return;
  }
  int point = (*vertices)[label];
  vertices->erase(label);
  for (int i = 0; i < 20; i++){
    table[point][i] = -1;
    table[i][point] = -1;
  }
  nextVertex = point;
  return;
}

void deleteEdge(int**& table, map<char*, int, compareChars>* vertices){
  char vertexOne[80];
  char vertexTwo[80];
  cout<<"Enter the first vertex label"<<endl;
  cin.getline(vertexOne, sizeof(vertexOne));
  cin.clear();
  cin.ignore(999, '\n');
  if (strcmp(vertexOne, vertexTwo) == 0){
    cout<<"Please enter two different vertex labels"<<endl;
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
  int pointOne = vertices->find(vertexOne)->second;
  int pointTwo = vertices->find(vertexTwo)->second;
  if (table[pointOne][pointTwo] == -1){
    cout<<"No edge exists between those two labels"<<endl;
    return;
  }
  table[pointOne][pointTwo] = -1;
  return;
}

void getShortestPath(int** table, map<char*, int, compareChars>* vertices){
  char vertexOne[80];
  char vertexTwo[80];
  cout<<"Enter starting vertex"<<endl;
  cin.getline(vertexOne, sizeof(vertexOne));
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter ending vertex"<<endl;
  cin.getline(vertexTwo, sizeof(vertexTwo));
  cin.clear();
  cin.ignore(999, '\n');
  if (strcmp(vertexOne, vertexTwo) == 0){
    cout<<"The two vertices are the same so the distance between them is 0"<<endl;
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
  int start = vertices->find(vertexOne)->second;
  int end = vertices->find(vertexTwo)->second;
  int* distance = NULL;
  distance = new int[20];
  bool visited[20];
  int parents[20];
  int* parent = dijkstra(start, end, distance, visited, parents, vertices, table);
  if (parent == NULL){
    cout<<"No path between "<<vertexOne<<" and "<<vertexTwo<<" found"<<endl;
    return;
  }
  vector<char*>* path = new vector<char*>();
  int x = end;
  while (x != start){
    path->push_back(find(vertices, x));
    x = parent[x];
  }
  path->push_back(find(vertices, start));
  cout<<"Shortest path is: ";
  bool isFirst = true;
  vector<char*>::reverse_iterator it;
  for (it = path->rbegin(); it != path->rend(); ++it){
    if (!isFirst){
      cout<<"->";
    }
    isFirst = false;
    cout<<*it;
  }
  cout<<endl<<"With length "<<distance[end]<<endl;
  return;
}

int* dijkstra(int start, int end, int*& distance, bool* visited, int* parent, map<char*, int, compareChars>* vertexMap, int** table){
  if (start == end){
    return parent;
  }
  int next = -1;
  int low = 1;
  bool finished = true;
  for (int i = 0; i < 20; i++){
    if (table[s][i] != -1 && !visited[i]){
      int newDistance = distance[s] + table[s][i];
      if (distance[i] == 0 || distance[i] > newDistance){
        distance[i] = newDistance;
        parent[i] = start;
      }
      if (distance[i] < low){
        next = i;
        low = distance[i];
      }
      finished = false;
    }
  }
  visited[start] = true;
  if (finished){
    return NULL;
  }
  return dijkstra(next, end, distance, visited, parent, vertexMap, table);
}

void printGraph(int** table, map<char*, int, compareChars>* vertices){
  cout<<"Connections:"<<endl;
  for (int i = 0; i < 20; i++){
    char* length = find(vertices, i);
    if (length == NULL){
      continue;
    }
    bool first = true;
    cout<<length<<": ";
    for (int j = 0; j < 20; j++){
      if (table[i][j] == -1){
        continue;
      }
      if (!first){
        cout<<", ";
      }
      first = false;
      cout<<find(vertices, j)<<"("<<table[i][j]<<")";
    }
    cout<<endl;
  }
}

char* find(map<char*, int, compareChars>* vertices, int n){
  map<char*, int, compareChars>::iterator it;
  for (it = vertices->begin(); it != vertices->end(); ++it){
    if (it->second == n){
      return it->first;
    }
  }
  return NULL;
}
