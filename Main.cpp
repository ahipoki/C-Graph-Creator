#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct compareChars{//Compare chars
  bool operator()(const char* a, const char* b) const{
    return strcmp(a, b)<0;
  }
};

void strupper(char* str);
void addVertex(map<char*, int, compareChars>*, int&);
void addEdge(int**&, map<char*, int, compareChars>*);
void deleteVertex(int**&, map<char*, int, compareChars>*, int&);
void deleteEdge(int**&, map<char*, int, compareChars>*);
void getShortestPath(int**, map<char*, int, compareChars>*);
void printGraph(int**, map<char*, int, compareChars>*);
int* dijkstra(int, int, int*&, bool*, int*, map<char*, int, compareChars>*, int**);
char* find(map<char*, int, compareChars>*, int);

int main()
{
  map<char*, int, compareChars>* vertices = new map<char*, int, compareChars>;//New map of vertices
  int nextVertex = 0;//Next vertex
  int** table = new int*[20];//Table
  for (int i = 0; i < 20; i++){
    table[i] = new int[20];
    for (int j = 0; j < 20; j++){
      table[i][j] = -1;//Set everything in the table of vertices to -1
    }
  }
  char input[80];//Input
  bool running = true;//Running
  while (running){//While program is running
    cout<<"Do you want to add a vertex, add an edge, remove a vertex, remove an edge, find the shortest path, print the connections, or quit?"<<endl;//Ask user if they want to add a vertex, add an edge, remove a vertex, remove an edge, find the shortest path, print out the connections, or quit
    cin.getline(input, sizeof(input));//Get their input
    strupper(input);//Make it uppsercase
    if (strcmp(input, "ADD VERTEX") == 0){//If they want to add a vertex
      addVertex(vertices, nextVertex);//Call addVertex
    }
    else if (strcmp(input, "ADD EDGE") == 0){//If they want to add an edge
      addEdge(table, vertices);//Call addEdge
    }
    else if (strcmp(input, "REMOVE VERTEX") == 0){//If they want to remove a vertex
      deleteVertex(table, vertices, nextVertex);//Call deleteVertex
    }
    else if (strcmp(input, "REMOVE EDGE") == 0){//If they want to remove an edge
      deleteEdge(table, vertices);//Call deleteEdge
    }
    else if (strcmp(input, "PATH") == 0){//If they want to find the shortest path
      getShortestPath(table, vertices);//Call getShortestPath
    }
    else if (strcmp(input, "PRINT") == 0){//If they want to print
      printGraph(table, vertices);//Call printGraph
    }
    else if (strcmp(input, "QUIT") == 0){//If they want to quit
      running = false;//Running is now false
    }
    else{//Anything else
      cout<<"That isn't a valid command"<<endl;//That's an invalid command
    }
  }
  delete vertices;//Delete vertices
  for (int i = 0; i < 20; i++){
    delete[] table[i];//Delete the data in the table
  }
  delete[] table;//Delete the table
  return 0;//Return 0
}

void strupper(char* str){//Make input uppercase
  int len = strlen(str);//Length of str
  for (int i = 0; i < len; i++){//Loop through length of str
    str[i] = toupper(str[i]);//Make each char in str uppercase
  }
}

void addVertex(map<char*, int, compareChars>* vertices, int &nextVertex){//Add vertex
  if (nextVertex == 20){//If nextVertex equals 20
    cout<<"There are too many vertices"<<endl;//Tell them there are going to be too many vertices if another one is added
    return;//Return
  }
  char* label = new char();//Vertex label
  cout<<"Input vertex label"<<endl;//Ask the user for a vertex label
  cin.get(label, 81);//Get the user's input
  map<char*, int>::iterator it;//Iterator it with map
  if (vertices->find(label) != vertices->end()){//If the label is already in the list of vertices
    cout<<label<<" already exists"<<endl;//Tell the user it already exists
    return;//Return
  }
  (*vertices)[label] = nextVertex;//Add the label to the list of vertices
  nextVertex = 0;//nextVertex is now 0
  while(find(vertices, nextVertex) != NULL){
    nextVertex++;//Add 1 to nextVertex
  }
  return;//Return
}

void addEdge(int**& table, map<char*, int, compareChars>* vertices){//Add edge
  char vertexOne[80];//Vertex label 1
  char vertexTwo[80];//Vertex label 2
  cout<<"Enter a vertex label"<<endl;//Ask the user for the first vertex label
  cin.getline(vertexOne, sizeof(vertexOne));//Get the user's input
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter another vertex label"<<endl;//Ask the user for the second vertex label
  cin.getline(vertexTwo, sizeof(vertexTwo));//Get the user's input
  cin.clear();
  cin.ignore(999, '\n');
  if (strcmp(vertexOne, vertexTwo) == 0){//If the two vertex labels entered are the same
    cout<<"You need to enter two different vertex labels"<<endl;//Tell the user they need two different vertex labels
    return;//Return
  }
  if (vertices->find(vertexOne) == vertices->end()){//If the first vertex label they entered isn't found in the list of vertices
    cout<<vertexOne<<" does not exist"<<endl;//Tell the user that vertex label does not exist
    return;//Return
  }
  if (vertices->find(vertexTwo) == vertices->end()){//If the second vertex label they entered isn't found in the list of vertices
    cout<<vertexTwo<<" does not exist"<<endl;//Tell the user that vertex label does not exist
    return;//Return
  }
  cout<<"Enter a weight for the edge"<<endl;//Ask the user for a weight for the edge
  int edgeWeight;//Edge's weight
  cin>>edgeWeight;//Get their input
  cin.clear();
  cin.ignore(999, '\n');
  if (edgeWeight <= 0){//If the weight entered is a negative number or 0
    cout<<"The edge's weight must be positive"<<endl;//Tell the user the weight must be a positive number
    return;//Return
  }
  int pointOne = vertices->find(vertexOne)->second;
  int pointTwo = vertices->find(vertexTwo)->second;
  table[pointOne][pointTwo] = edgeWeight;//Add the weight to the edge
  return;//Return
}

void deleteVertex(int**& table, map<char*, int, compareChars>* vertices, int& nextVertex){//Delete vertex
  char label[80];//Vertex label
  cout<<"Enter the vertex label you want to delete"<<endl;//Ask the user for the vertex label they want to remove
  cin.getline(label, sizeof(label));//Get their input
  cin.clear();
  cin.ignore(999, '\n');
  if (vertices->find(label) == vertices->end()){//If the vertex label is not found
    cout<<label<<" does not exist"<<endl;//Tell the user the vertex label does not exist
    return;//Return
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
  cout<<"Enter the second vertex label"<<endl;
  cin.getline(vertexTwo, sizeof(vertexTwo));
  cin.clear();
  cin.ignore(999, '\n');
  if (strcmp(vertexOne, vertexTwo) == 0){
    cout<<"Enter two different vertex labels"<<endl;
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
  int ref1 = vertices->find(vertexOne)->second;
  int ref2 = vertices->find(vertexTwo)->second;
  if (table[ref1][ref2] == -1){
    cout<<"No edge exists between those two labels"<<endl;
    return;
  }
  table[ref1][ref2] = -1;
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

int* dijkstra(int s, int e, int*& distance, bool* visited, int* parent, map<char*, int, compareChars>* vmap, int** table){
  if (s == e){
    return parent;
  }
  int next = -1;
  int low = 5;
  bool finished = true;
  for (int i = 0; i < 20; i++){
    if (table[s][i] != -1 && !visited[i]){
      int newd = distance[s] + table[s][i];
      if (distance[i] == 0 || distance[i] > newd){
        distance[i] = newd;
        parent[i] = s;
      }
      if (distance[i] < low){
        next = i;
        low = distance[i];
      }
      finished = false;
    }
  }
  visited[s] = true;
  if (finished){
    return NULL;
  }
  return dijkstra(next, e, distance, visited, parent, vmap, table);
}

void printGraph(int** table, map<char*, int, compareChars>* vertices){
  cout<<"Connections: "<<endl;
  for (int i = 0; i < 20; i++){
    char* l = find(vertices, i);
    if (l == NULL){
      continue;
    }
    bool first = true;
    cout<<l<<": ";
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
