#include "the5.h"

/* 
    in the5.h "struct Room" is defined as below:
    
    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/


void DFS(Room* v, vector<int>& path)
{
    if(char(v->content)=='-') v->content = '+';
    if(char(v->content)=='*') return;
    if(!path.empty() && path.back()!=v->id)
                path.push_back(v->id); 
    if(path.empty())path.push_back(v->id);

    int total_size_of_n = (v->neighbors).size();
    vector<Room*> neighbor_list = v->neighbors;
    for (int i = 0; i < total_size_of_n; ++i)
        if (char((v->neighbors)[i]->content)=='-')
            DFS(v->neighbors[i], path);
        else if (char((v->neighbors)[i]->content)=='*')
        {
            path.push_back(v->id);
            break;
        }
        else 
         if(path.back()!=v->id)
                path.push_back(v->id); 
}

void stack_arth(stack<int>& stack, vector<Room*> maze, int& v){
        
        for(int i = 0; i < maze[v]->neighbors.size(); i++)
        {
            if(maze[v]->neighbors[i]->id == stack.top())
            {
                v = maze[v]->neighbors[i]->id;
                break;
            }
        }
        stack.pop();
}

void clear_stack(stack<int>& stack, vector<int>& path){
    while(stack.size() != 0)
    {
        path.push_back(stack.top());
        stack.pop();
    }
}


vector<int> maze_trace(vector<Room*> maze) { 

    vector<int> path;
    
    //your code here
    
    
    // DFS(maze[0], path);
    
    
    int v=0; 
    stack<int> stack;

    while(maze[v]->content != '*'){
        int flag=0;
        int n_counter=0;
        path.push_back(maze[v]->id);
        maze[v]->content = '+';
        while(n_counter<(maze[v]->neighbors).size())
        {
            if(((maze[v]->neighbors)[n_counter])->content != '+')
            {
                flag=1;
                stack.push(maze[v]->id);
                v = maze[v]->neighbors[n_counter]->id;
                break;
            }
            n_counter++;
        }
        if(!flag) stack_arth(stack, maze, v);
        
    }
    stack.push(maze[v]->id);
    clear_stack(stack,path);

    
    // while(i<maze.size())
    // {
    //     if(char(maze[i]->content)=='-') //unvisited
    //     {
    //         path.push_back(maze[i]->id);
    //         maze[i]->content = '+';
            
    //         if(((maze[i]->neighbors)[0])->content == '+')
    //             {
    //                 (maze[i]->neighbors).erase((maze[i]->neighbors).begin());
    //                 int j = ((maze[i]->neighbors)[0])->id;
    //                 i = j;
    //                 continue;
                    
    //             }
    //         else
    //             {

    //                 int j = ((maze[i]->neighbors)[0])->id;
    //                 i = j;
    //                 continue;
    //             }
    //         continue;
    //     }
    //     else if(char(maze[i]->content)=='*') //treasure
    //     {
    //         path.push_back(maze[i++]->id);
    //         break;
    //     }
    //     else if(char(maze[i]->content)=='+') //visited
    //     {
    //         if((maze[i]->neighbors)[0]){
    //             if(((maze[i]->neighbors)[0])->content == '+')
    //             {
    //                 (maze[i]->neighbors).erase((maze[i]->neighbors).begin());
    //                 int j = ((maze[i]->neighbors)[0])->id;
    //                 i = j;
    //                 continue;
                    
    //             }
    //             else
    //             {
    //                 int j = ((maze[i]->neighbors)[0])->id;
    //                 i = j;
    //                 continue;
    //             }
    //         }
    //       break;
            
    //     }
        
    // }

    return path; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
