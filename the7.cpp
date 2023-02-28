#include "the7.h"

// Implement your solution after this line

int find_minimum(int distance[], bool mark[], int n)
{
    int minimum=INT_MAX;
    int indexx;
              
    for(int k=0;k<n;k++) 
    {
        if(mark[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            indexx=k;
        }
    }
    return indexx;
}

int** create_input_matrix(int n, std::vector<Road> roads){
    int** input_matrix = new int*[n];
    int M = roads.size();
    int first_index;
    int second_index;
    int costt;
    
    
    for (int i = 0; i < n; ++i){
        input_matrix[i] = new int[n];
    }
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
        input_matrix[i][j]=0;
    }
    
    for(int i=0; i<M; i++){
        first_index = (roads[i]).buildings.first;
        second_index = (roads[i]).buildings.second;
        costt = (roads[i]).time;
        input_matrix[first_index][second_index] = costt;
        input_matrix[second_index][first_index] = costt;
    }
    return input_matrix;
}


int* find_shortest_path(int s, int d, int n, std::vector<Road> roads, int** input_matrix, int parent[]){
    
    bool mark[n];
    int* distance = new int[n];
     
    for(int k = 0; k<n; k++)
    {
        distance[k] = INT_MAX;
        mark[k] = false;    
    }
    
    distance[s] = 0;       
    parent[s]=s;
    
    for(int k = 0; k<n; k++)                           
    {
        int m=find_minimum(distance,mark, n); 
        mark[m]=true;
        for(int k = 0; k<n; k++)                  
        {
            if(!mark[k] && input_matrix[m][k] && distance[m]!=INT_MAX && distance[m]+input_matrix[m][k]<distance[k]){
                parent[k]  = m;
                distance[k]=distance[m]+input_matrix[m][k];
            }
                
        }
    }
    return distance;
}


void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    // You can change these variables. These are here for demo only.
   int paths[n];
    int pathx[n];
    int pathy[n];
    std::vector<int> path;
    std::vector<int> path_reversed;
    //int cost = INT_MAX;
    
    int** input_matrix = create_input_matrix(n, roads);
    int* distances_from_s = find_shortest_path(s, d, n,roads,input_matrix,paths);
    int* distances_from_x =find_shortest_path(x, d, n,roads,input_matrix,pathx);
    int* distances_from_y = find_shortest_path(y, d, n,roads,input_matrix,pathy);
    
    int from_s_to_d = distances_from_s[d];
    int from_s_to_x = distances_from_s[x];
    int from_s_to_y = distances_from_s[y];
    
    int from_x_to_d = distances_from_x[d];
    int from_x_to_y = distances_from_x[y];
    
    int from_y_to_d = distances_from_y[d];
    int from_y_to_x = distances_from_y[x];
    
    int s_x_y_d = from_s_to_x+from_x_to_y+from_y_to_d ;
    int s_y_x_d = from_s_to_y+from_y_to_x+from_x_to_d ;
    int s_x_d = from_s_to_x+from_x_to_d ;
    int s_y_d = from_s_to_y+from_y_to_d ;

            // BOTH
        if(s_x_y_d<=l || s_y_x_d<=l){
            if(s_x_y_d==s_y_x_d && s_x_y_d<=l && s_x_y_d >=0){
                 std::cout<<"YES BOTH " <<s_x_y_d<<"MINUTES";
                 int curr = d;
                 while(curr!=y){
                     path.push_back(curr);
                     curr = pathy[curr];
                    }
                while(curr!=x){
                    path.push_back(curr);
                    curr=pathx[curr];
                }
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
             
            }
            else if(s_x_y_d<=l && s_x_y_d >=0 &&s_x_y_d<s_y_x_d){ 
                std::cout<<"YES BOTH " <<s_x_y_d<<"MINUTES"; 
                int curr = d;
                 while(curr!=y){
                     path.push_back(curr);
                     curr = pathy[curr];
                    }
                while(curr!=x){
                    path.push_back(curr);
                    curr=pathx[curr];
                }
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
            }
            else if(s_y_x_d<=l && s_y_x_d >=0) {
                std::cout<<"YES BOTH " <<s_y_x_d<<"MINUTES";
                int curr = d;
                while(curr!=x){
                    path.push_back(curr);
                    curr=pathx[curr];
                }
                 while(curr!=y){
                     path.push_back(curr);
                     curr = pathy[curr];
                    }
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
            }
        }
        
        //ONLY ONE
        if(s_x_y_d>l && s_y_x_d>l){
            if(s_x_d<=l && s_x_d >=0 && s_x_d<=s_y_d){ 
            std::cout<<"YES PRINTER " <<s_x_d<<"MINUTES";
            int curr = d;
                while(curr!=x){
                    path.push_back(curr);
                    curr=pathx[curr];
                }
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
            }
            else if(s_y_d<=l && s_y_d >=0) {
                std::cout<<"YES DORM " <<s_y_d<<"MINUTES";
                int curr = d;
                while(curr!=y){
                    path.push_back(curr);
                    curr=pathy[curr];
                }
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
            }
        }
        
        // NONE
        if(s_x_y_d>l && s_y_x_d>l && s_x_d>l && s_y_d>l){
            if(from_s_to_d<=l && from_s_to_d>0){
                std::cout<<"YES DIRECTLY " <<from_s_to_d<<"MINUTES";
                int curr = d;
                 while(curr!=s){
                    path.push_back(curr);
                    curr=paths[curr];
                }
                path.push_back(s);
            }
        }
        
        // IMPOSSIBLE
        if(s_x_y_d>l && s_y_x_d>l && s_x_d>l && s_y_d>l && from_s_to_d>l){
            std::cout<<"IMPOSSIBLE";
        }
    
    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());
    for(int i=path.size()-1; i>=0 ;i--){
        path_reversed.push_back(path[i]);
    }
    std::cout<<std::endl;
    if(printPath==1) PrintRange(path_reversed.begin(), path_reversed.end());
    
}
