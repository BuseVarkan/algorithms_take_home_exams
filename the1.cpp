#include "the1.h"
#include <climits>
//You can add your own helper functions

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int i=1;
    int x,j;
    while (i<size){
        x = arr[i];
        j=i-1;
        //comparison+=1;
        while (j>=0 && ++comparison && arr[j]>x){
        //comparison+=1;
            swap+=1;
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1] = x;
        i=i+1;
    }
}

int * generate_subarrays(int* arr, int K, int size, int how_many){
    int **subparts_list;
	int i=0, j=0, k=0;
	while (i< size)
	{
	    int * temp;
	    j=0;
	   while(j<K)
	   {
       	    temp[j] = arr[i];
            j++;
            i++;
	   }
	   subparts_list[k]=temp;
	}
	return *subparts_list;
}

void counter(int &number_of_calls){
    number_of_calls +=1;
}


void my_swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void heapify(int arr [], int indexes_array [], int size, int i, long& comparison, long& swap)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    // COMPARISON
    
    if (l < size && arr[l]!=INT_MAX && ++comparison &&arr[l] < arr[smallest] ){
        //comparison+=1;
        smallest = l;
    }
 
    // COMPARISON
    if (r < size && arr[r]!=INT_MAX && ++comparison && arr[r] < arr[smallest] ){
        //comparison+=1;
        smallest = r;
    }
 
    // COMPARISON
    if (smallest != i) {
        // SWAP
      // comparison+=1;
    
        my_swap(arr + i, arr + smallest);
    
        my_swap(indexes_array + i, indexes_array + smallest); // To keep track of index changes
        swap+=1;
        heapify(arr, indexes_array, size, smallest, comparison, swap);
    }
    
}
 
void create_heap(int arr [], int indexes_array [], int size, long& comparison, long& swap)
{
    int start = (size / 2) - 1;

    for (int i = start; i >=0; i--) {
        heapify(arr, indexes_array, size, i, comparison, swap);
    }
}

void append_to_output_list(int* output_arr, int num, int & counter){
    output_arr[counter++] = num;
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
    
    int number_of_calls = 1;

	//Your code here
	int array_for_heap[K];
	int indexes_array[K];
	int follow_pointer[K];
	int min_element, index_of_min;
	int output_array[size];
	int counter = 0;
	
	
	if (size<K)
	{
	    insertionSort(arr, comparison, swap, size);
	}
	else
	{
	    int i=0;
	    int how_many = size/K;
	    while(i<size) {
	        
	        number_of_calls += kWayMergeSortWithHeap(arr+i, K, how_many, comparison, swap);
	        i+=how_many;
	    }
	    i=0;
	    while(i<size){
	        array_for_heap[i/how_many] = arr[i];
	        indexes_array[i/how_many] = i;
	        i+=how_many;
	    }
	    
	    for (int i=0; i<K; i++) follow_pointer[i]=0;
	    create_heap(array_for_heap, indexes_array, K, comparison, swap); //Create min heap here
	    for(int k=0; k<size; k++)
	    {
    	    min_element=array_for_heap[0];
    	    
    	    output_array[k] = min_element;
    	    
    	    index_of_min = indexes_array[0];
    	    indexes_array[0]+=1;

    	    if(follow_pointer[(int)(index_of_min/how_many)] < how_many-1) {
    	        array_for_heap[0] = arr[indexes_array[0]];
    	         follow_pointer[(int)(index_of_min/how_many)]+=1;
    	    }
    	    else array_for_heap[0] = INT_MAX;
    	    heapify(array_for_heap, indexes_array, K, 0, comparison, swap);
    	   
	    }
	    for(int k=0; k<size; k++)
	    {
	      arr[k] = output_array[k];
	   }
	}
	return number_of_calls;
}

