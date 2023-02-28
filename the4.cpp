#include "the4.h"

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming

    //your code here
    char temp1[nrow][ncol1]; 
    char temp2[nrow][ncol2];

    for(int i=0; i<=ncol1; i++){
        
        for(int j=0; j<=ncol2; j++){
            
            if(i==0){ 
            
                if(j==0){
                    mem[0][0] = 0;
                    continue;
                }
                
                else{
                    int insertion_counter = 0;
                    
                    for(int k=0; k<nrow; k++){
                        if(arr2[k][j-1] != '-') insertion_counter++;
                    }
                    
                    mem[i][j] = mem[i][j-1] + insertion_counter;
                    continue;
                }
                
            }
        
            
            else{
                
                if(j==0){
                    int deletion_counter = 0;
                    
                    for(int k=0; k<nrow; k++){
                        if(arr1[k][i-1] != '-') deletion_counter++;
                    }
                    
                    mem[i][j] = mem[i-1][j] + deletion_counter;
                    continue;
                }
                
                else{
                    int delet = mem[i-1][j];
                    int inser = mem[i][j-1];
                    int replacement = mem[i-1][j-1];
                    int reorder = mem[i-1][j-1];
                    
                    
                    for(int k = 0; k < nrow; k++){
                        if(arr1[k][i-1] != '-') delet++;
                        if(arr2[k][j-1] != '-') inser++;
                    }
                    
                    for(int k=0; k<nrow; k++){
                        if(arr1[k][i-1]!=arr2[k][j-1]){
                            if(arr1[k][i-1]=='-' || arr2[k][j-1]=='-'){
                                replacement++;
                            }
                            replacement++;
                        }
                    }
                    
                    int delete_plus_insert = delet<inser ? delet:inser;
                    
                    bool similarity_check = true;
                    
                    for(int k=0; k<nrow; k++){
                        temp1[k][i-1] = arr1[k][i-1];
                        temp2[k][j-1] = arr2[k][j-1];
                    }
                    
                    for(int k=0; k<nrow-1; k++){
                        for (int m = 0; m < nrow - k - 1; m++){
                            if (temp1[m][i-1] > temp1[m+1][i-1]){
                                int tm = temp1[m][i-1];
                                temp1[m][i-1] = temp1[m+1][i-1];
                                temp1[m+1][i-1] = tm;
                            }
                            
                        }
              
                    }
                   
              
                    
                    for(int k=0; k<nrow-1; k++){
                        for (int m = 0; m < nrow - k - 1; m++){
                            
                            if (temp2[m][j-1] > temp2[m+1][j-1]){
                                int tm = temp2[m][j-1];
                                temp2[m][j-1] = temp2[m+1][j-1];
                                temp2[m+1][j-1] = tm;
                            }
                        }
                        
                    }
                    

                    
                    for(int k=0; k<nrow; k++){
                        if(temp1[k][i-1] != temp2[k][j-1]){
                            similarity_check = false;
                            break;
                        }
                    }
                    
                    if(similarity_check == true){
                        for(int k=0; k<nrow; k++){
                            if(arr1[k][i-1]!=arr2[k][j-1]){
                                reorder++;
                                
                            }
                        }
                    }
                             
                    int to_compare1;
                    if(similarity_check==false) to_compare1=replacement;
                    else{
                        to_compare1 = replacement<reorder ? replacement:reorder ;
                    }
                    
                    mem[i][j] = to_compare1 < delete_plus_insert ? to_compare1 : delete_plus_insert;
                }
                
            }
    
        
        }
      
    }

    return mem[ncol1][ncol2]; 
}
