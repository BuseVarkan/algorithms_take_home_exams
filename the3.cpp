#include "the3.h"



int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;

    //your code here
    int my_max = len[i];

    if (i == 0) {
        return len[0];
    }
    
    if(number_of_calls==1){
        for (int j = i - 1; j >= 0; j--){
            int temp1=recursive_sln(j, arr, len, number_of_calls);
            my_max = temp1>my_max ? temp1 : my_max;
        }
        for (int j = i - 1; j >= 0; j--){
            int temp2;
            if ((arr[i][0] == 'I' && arr[j][1] == 'O') || 
                (arr[i][0] == 'O' && arr[j][1] == 'I') || 
                (arr[i][0] == 'S' && arr[j][1] == 'S')){
                    temp2=recursive_sln(j, arr, len, number_of_calls)+len[i];
                    my_max = my_max>temp2 ? my_max : temp2;
                    break;
                }
            
        }
    }
        
    else{
        int temp1;
        int temp2;
        
        for (int j = i - 1; j >= 0; j--){
            if((arr[i][1] == arr[j][1])){
                temp1=recursive_sln(j, arr, len, number_of_calls);
                my_max = temp1>my_max ? temp1 : my_max;
                break;
            }
        }
        for (int j = i - 1; j >= 0; j--){
            
            if((arr[i][0] == 'I' && arr[j][1] == 'O') || 
                 (arr[i][0] == 'O' && arr[j][1] == 'I') || 
                 (arr[i][0] == 'S' && arr[j][1] == 'S')){
                     temp2=recursive_sln(j, arr, len, number_of_calls)+len[i];
                     my_max = my_max>temp2 ? my_max : temp2;
                     break;
                }
        }

    }

    return my_max;
   
}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

    //your code here
    
    if(i==-1)return 0;
    int my_max = memoization_sln(i-1, arr, len, mem);
    if(i==0){
        if(arr[0][1]=='I'){
        mem[0][0]=len[0];
        mem[0][1]+=1;
        mem[0][2]+=1;
    }
    else if(arr[0][1]=='O'){
        mem[0][0]+=1;
        mem[0][1]=len[0];
        mem[0][2]+=1;
    }
    else if(arr[0][1]=='S'){
        mem[0][0]+=1;
        mem[0][1]+=1;
        mem[0][2]=len[0];
    }

    }
    
    else if(i>=1){
        mem[i][0]=mem[i-1][0];
        mem[i][1]=mem[i-1][1];
        mem[i][2]=mem[i-1][2];
        
        if(arr[i][1]=='I'){
            if(arr[i][0]=='I') mem[i][0]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][0]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][0]=len[i]+mem[i-1][2];
        }
        if(arr[i][1]=='O'){
            if(arr[i][0]=='I') mem[i][1]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][1]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][1]=len[i]+mem[i-1][2];
        }
        if(arr[i][1]=='S'){
            if(arr[i][0]=='I') mem[i][2]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][2]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][2]=len[i]+mem[i-1][2];
        }
        if(mem[i-1][0]>mem[i][0]||mem[i-1][1]>mem[i][1]||mem[i-1][2]>mem[i][2]){
            mem[i][0]=mem[i-1][0];
            mem[i][1]=mem[i-1][1];
            mem[i][2]=mem[i-1][2];
        }

    }
    int my_max_0 = mem[i][0];
    int my_max_1 = mem[i][1];
    int my_max_2 = mem[i][2];
    int my_max_tmp, my_max_3;
    
     my_max_tmp = my_max_0>my_max_1 ? my_max_0 : my_max_1;
     my_max_3 = my_max_tmp>my_max_2 ? my_max_tmp : my_max_2;
     my_max = my_max>my_max_3 ? my_max : my_max_3;

    return my_max; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming

    //your code here
    if(arr[0][1]=='I'){
        mem[0][0]=len[0];
        mem[0][1]+=1;
        mem[0][2]+=1;
    }
    else if(arr[0][1]=='O'){
        mem[0][0]+=1;
        mem[0][1]=len[0];
        mem[0][2]+=1;
    }
    else if(arr[0][1]=='S'){
        mem[0][0]+=1;
        mem[0][1]+=1;
        mem[0][2]=len[0];
    }
    
    for(int i=1; i<size; i++){
        mem[i][0]=mem[i-1][0];
        mem[i][1]=mem[i-1][1];
        mem[i][2]=mem[i-1][2];
        
        if(arr[i][1]=='I'){
            if(arr[i][0]=='I') mem[i][0]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][0]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][0]=len[i]+mem[i-1][2];
        }
        if(arr[i][1]=='O'){
            if(arr[i][0]=='I') mem[i][1]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][1]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][1]=len[i]+mem[i-1][2];
        }
        if(arr[i][1]=='S'){
            if(arr[i][0]=='I') mem[i][2]=len[i]+mem[i-1][1];
            if(arr[i][0]=='O') mem[i][2]=len[i]+mem[i-1][0];
            if(arr[i][0]=='S') mem[i][2]=len[i]+mem[i-1][2];
        }
        if(mem[i-1][0]>mem[i][0]||mem[i-1][1]>mem[i][1]||mem[i-1][2]>mem[i][2]){
            mem[i][0]=mem[i-1][0];
            mem[i][1]=mem[i-1][1];
            mem[i][2]=mem[i-1][2];
        }
    }
    
    int my_max_0 = mem[size-1][0];
    int my_max_1 = mem[size-1][1];
    int my_max_2 = mem[size-1][2];
    int my_max_tmp, my_max;
    
     my_max_tmp = my_max_0>my_max_1 ? my_max_0 : my_max_1;
     my_max = my_max_tmp>my_max_2 ? my_max_tmp : my_max_2;
    
    return my_max; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
