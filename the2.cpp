#include "the2.h"
#include <cmath>
// You may write your own helper functions here

void counting_sort_ascending(int arr[], int n, int k, long & numberOfIterations, int temp_digit_list[]){
    int C[k+1];
    int B[n];
    
    for(int i=0; i<=k; i++) { 
        C[i]=0; 
        
    }
    
    for(int j=0; j<n; j++) { 
        C[ temp_digit_list[j]] += 1; numberOfIterations++;
        
    }
    
    for(int i=1; i<=k; i++) { 
        C[i] = C[i] + C[i-1]; numberOfIterations++;
        
    }
    
    for (int j = n-1; j>=0; j--) {
        B[C[ temp_digit_list[j]]-1] = arr[j];
        C[temp_digit_list[j]]-=1;
        numberOfIterations++;
    }
    
    for(int i=0; i<n; i++){ 
        arr[i]=B[i]; numberOfIterations++;
        
    }
}


void counting_sort_descending(int arr[], int n, int k, long & numberOfIterations, int temp_digit_list[]){
    int C[k+1];
    int B[n];
    
    for(int i=0; i<=k; i++) { 
        C[i]=0; 
        
    }
    
    for(int j=0; j<n; j++) { 
        C[ temp_digit_list[j]] += 1; numberOfIterations++;
        
    }
    
    for(int i=k; i>=1; i--) { 
        C[i-1] = C[i-1] + C[i]; numberOfIterations++;
        
    }
    
    for (int j = n-1; j>=0; j--) {
        B[C[ temp_digit_list[j]]-1] = arr[j];
        C[temp_digit_list[j]]-=1;
        numberOfIterations++;
    }
    
    for(int i=0; i<n; i++){ 
        arr[i]=B[i]; numberOfIterations++;
        
    }
}


int num_slicing(int num, int start_digit, int groupSize)
{
    int result=0;
    for(int i=start_digit, j=0; i<start_digit+groupSize; i++,j++){
        int temp = (int)((num / pow(10,i)))%10;
        result+= temp*pow(10,j);
    }
    return result;
}


long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    
    int  i, j;
    int remaining_groups = maxDigitLength%groupSize;
    int strt;
    
    for(strt=0; strt<maxDigitLength-remaining_groups; strt+=groupSize){
        int temp_digit_list[arraySize];
        for(i=0; i<arraySize; i++){
            temp_digit_list[i] = num_slicing(arr[i], strt, groupSize);
        }
        
        if(ascending==1)
            counting_sort_ascending(arr, arraySize, pow(10, groupSize)-1, numberOfIterations, temp_digit_list);
            
        else counting_sort_descending(arr, arraySize, pow(10, groupSize)-1, numberOfIterations, temp_digit_list);

    }
    if (remaining_groups!=0){
        int temp_digit_list[arraySize];
        for(i=0; i<arraySize; i++){
            temp_digit_list[i] = num_slicing(arr[i], strt, remaining_groups);
        }
        
        if(ascending==1)
            counting_sort_ascending(arr, arraySize, pow(10, remaining_groups)-1, numberOfIterations, temp_digit_list);
            
        else counting_sort_descending(arr, arraySize, pow(10, remaining_groups)-1, numberOfIterations, temp_digit_list);

    }
    

    
    return numberOfIterations;
}
