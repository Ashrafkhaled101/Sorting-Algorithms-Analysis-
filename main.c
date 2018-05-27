/*
    Author : Ashraf khaled
    Date : 11/3/2018
    Content : Implementing Heap , Max Heap and Sort Heap Algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 300000// max length for the random array.


// generating random arrays with random lengths.
// Fisher-Yates shuffle xD
void randomArray(int *arr, int lower, int upper, int size){
    int i;
    for (i = 0; i < size; i++) {
        int num = (rand() + lower) % (upper + 1);
        arr[i] = num;
    }
}

// initialize data storage

typedef struct node {
    int data;
}node;

typedef struct maxHeap {
    int size;
    node *item;
}maxHeap;

// ----------------------------------- SWEETS FIRST! ---------------------------------------------

//macro-functions just to find the parent , left child and right child according to the algorithm .

#define PARENT(i) (i - 1) / 2
#define LCHILD(i) 2 * i + 1
#define RCHILD(i) 2 * i + 2

// Initialize size of heap with ZERO at the start / allocating memory for the items ,
// And return the heap back .

maxHeap initMaxHeap(int size){

    maxHeap hp;
    hp.size = 0;
    hp.item = malloc(size*sizeof(node));

    return hp;
}

// just a stupid-ass SWAP function,
// because we are in 2018 and still C does NOT have a build-in one!
// taking 2 nodes , swap them and BOOM !

void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}



// ----------------------------------- IMPLEMENTING MAX-HEAP! ---------------------------------------------


//  just making sure that the heap property is never violated
//      In case of :
//          - Deleting a record
//          - Creating a Max heap
//          - or Inserting new record
/// O(log(n))
void heapify(maxHeap *hp , int i){
    // check if the record with-in the heap size,
    // compare the left and right childes with their parent node.
    int largest = (LCHILD(i) < (hp->size) && (hp->item[LCHILD(i)].data) > (hp->item[i].data))? LCHILD(i) : i;

    if(RCHILD(i) < (hp->size) && (hp->item[RCHILD(i)].data) > (hp->item[largest].data))
        largest = RCHILD(i);

    // swap if the previous conditions is true.
    // looping recursively
    if(largest!= i){
        swap(&(hp->item[i]),&(hp->item[largest]));
        heapify(hp,largest);
    }

} //EOF HEAPIFY

//  build a Max Heap for given array of given size.
/// O(n)

void buildMaxheap(maxHeap *hp,int *arr, int size){
    //  check if it is the first record to be add => (relocating),
    //  or we are inserting to an exist heap => (reallocating).
    int i;
    for(i=0 ; i < size ; i++){
        if(hp->size){
            hp->item = realloc((hp->item) , ((hp->size) + 1) * sizeof(node));
        }else{
            hp->item = malloc(sizeof(node));
        }

        node n;
        n.data = arr[i];
        hp->item[(hp->size)++] = n;
    }

    //  making sure that heap property is satisfied
    for(i = ((hp->size)-1)/2 ; i>=0 ; i--)
        heapify(hp, i);


} // EOF BUILD-MAX-HEAP

//  The idea is deleting the Root-node then swap it with the last node ,
//  then call heapfiy.

void deleteNode(maxHeap *hp){
    if(hp->size){
        //printf("%d ",hp->item[0].data);
        swap((&hp->item[0]),&(hp->item[--(hp->size)]));
        hp->item = realloc(hp->item, (hp->size)*sizeof(node));
        heapify(hp,0);
    }
} //EOF DELETE-NODE

// total heap size = the array size , so we send the array size to the function to save the (Real) size of the array
// then we loop throw all the nodes
//      - swapping the last node with the Root(the first node) ,
//      - sub the heap size with one (that's why we're saving the real size before sorting to asgine it back in the end)
//      and calling Heapify() "to max heap the "
/// O(nlog(n))
void heapSort(maxHeap *hp,int *arr,int size){
    int i;
    buildMaxheap(hp,arr,size);

    for(i = hp->size - 1; i > 0 ; i-- ){
        swap(&(hp->item[0]),&(hp->item[i]));
        hp->size = hp->size - 1;
        heapify(hp,0);
    }
    hp->size = size;

} // EOF HEAP SORT

// ------------------------------------ Quick Sort ----------------------------------

// generating random pivot and swap it in it's place.
void randPartition(int *arr , int start , int end){

    // generate a random number (pivot)
    int piv = start + rand()%(end-start + 1);
    //swap the pivot as the first element in the array
    int temp = arr[start];
    arr[start] = arr[piv];
    arr[piv] = temp;
}

// rearranging the array around the pivot.
int partition(int *arr, int start, int end){
    // generating a random pivot
    randPartition(arr,start,end);

    int piv = arr[start]; // set the first element as a pivot
    int i = start + 1;  // the start of the array ignoring the pivot.
    int j=0,temp;

    for (j = start+1 ; j<=end ; j++){
        if(arr[j] < piv){
            //swap to put the element on the left-hand side.
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;

        }
    }
    // place the pivot in it's place in the array , sound be (i-1)
    temp = arr[start];
    arr[start] = arr[i-1];
    arr[i-1] = temp;

    return i-1;
}

void quickSort(int *arr , int start , int end){

    if(start<end){
        int pivot = partition(arr,start,end);
        quickSort(arr,start,pivot-1); // sort the left-hand side
        quickSort(arr,pivot+1,end); // sort the right-hand side
    }

}

// ------------------------------------ Merge Sort -------------------------------------


void merge(int *arr, int start, int mid,int end){

    int p = start,q = mid+1;  //stores the starting position of both parts.
    int i,j;
    int temp[end-start+1], k=0;

    for(i = start ; i <= end ; i++){

        if(p > mid)      //checks if first part comes to an end or not, store the remaining elements
            temp[ k++ ] = arr[ q++] ;

        else if ( q > end)   //checks if second part comes to an end or not , store the remaining elements
            temp[ k++ ] = arr[ p++ ];

        else if( arr[ p ] < arr[ q ])   //check which part has smaller element .
            temp[ k++ ] = arr[ p++ ];

        else
            temp[ k++ ] = arr[ q++];
    }
    // finally store the sorted elements in the main array Traa Tran Traaaaaan ...
    for (j=0 ; j< k ; j ++){
        arr[ start++ ] = temp[ j ] ;
    }


}


void mergeSort (int *arr , int low , int high){

    if(low < high){
        int mid = (low + high) / 2 ;

        mergeSort(arr , low , mid); // sort the left-side.
        mergeSort(arr , mid+1 , high); // sort the right-side.

        merge(arr,low,mid,high); // merge both sides.
    }

}

// insertion sort algorithm,
// ----------------------------------- Insertion sort! ---------------------------------------------

void insertionSort(int *arr , int size){

    int i;
    for(i=0 ; i<size ; i++){

        // hold the value and it's position.
        int temp = arr[i];
        int j = i;

        // check whatever the left-side elements are greater than the holden one.
        while(j > 0 && temp < arr[j-1]){
            // move the left-element forward.
            arr[j] = arr[j-1];
            j--;
        }
        // then place the selected element at the
        arr[j] = temp;

    }

}


// selection sort algorithm,
// ----------------------------------- Selection sort! ---------------------------------------------

void selectionSort(int *arr , int size){
    int min,temp,i,j;

    for(i=0 ; i<size-1 ; i++){
        // selecting one element and comparing it with all other right-elements in the array.
        min = i;
        for(j=i+1 ; j<size ; j++){
            if(arr[min] > arr[j]){
                min = j;
            }

        }// EOF INNER-LOOP

        //swap to place the Min-element in his position.
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

    }// EOF OUTER-LOOP


}


// Bubble sort algorithm,
// ----------------------------------- Bubble sort! ---------------------------------------------

void bubbleSort( int *arr, int size ) {
    int temp;
    int k,i;
        // comparing the counted element with all other right-elements = (size - (counted elements) - 1),
        // to ignore all the counted / sorted elements .
    for(k = 0; k< size-1; k++) {
        for(i = 0; i < size-k-1; i++) {
            if(arr[ i ] > arr[ i+1] ) {
            //swap to place the smallest element on the left-hand side.
                temp = arr[ i ];
                arr[ i ] = arr[ i+1 ];
                arr[ i + 1] = temp;
            }
        } // EOF INNER-LOOP
    } // EOF OUTTER-LOOP
}



// display the array.
void display(int *arr , int s){
    int i ;
    for(i = 0; i < s; i++) {
        printf("%d ", arr[i]) ;
    }
}

int main()
{

    double t1, t2;
    int length = 1000;

    for (length = 1000; length <= MAX_LENGTH; ){

        int *arr = malloc(sizeof(int)*length);
        printf("\n\nLength\t: %d\n",length);
        // Bubble Sort
        randomArray(arr,0,length,length);
        t1 = clock();
        bubbleSort(arr,length);
        t2 = clock();
        printf( "Bubble Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);
        // Selection Sort
        randomArray(arr,0,length,length);
        t1 = clock();
        selectionSort(arr,length);
        t2 = clock();
        printf( "Selection Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);
        // Insertion Sort
        randomArray(arr,0,length,length);
        t1 = clock();
        insertionSort(arr,length);
        t2 = clock();
        printf( "Insertion Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);
        // Heap sort
        maxHeap hp;
        randomArray(arr,0,length,length);
        hp = initMaxHeap(length);
        t1 = clock();
        heapSort(&hp,arr,length);
        t2 = clock();
        printf( "Heap Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);
        // Merge sort
        randomArray(arr,0,length,length);
        t1 = clock();
        quickSort(arr,0,length-1);
        t2 = clock();
        printf( "Merge Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);
        // Quick sort
        randomArray(arr,0,length,length);
        t1 = clock();
        quickSort(arr,0,length-1);
        t2 = clock();
        printf( "Quick Sort\t: %.4f  \tsec\\n \n",(t2-t1)/CLK_TCK);


        switch (length){

        case 1000 :
            length = 5000;
            break;
        case 5000 :
            length = 10000;
            break;
        case 10000 :
            length = 50000;
            break;
        case 50000 :
            length = 100000;
            break;
        case 100000 :
            length = 200000;
            break;
        case 200000 :
            length = 300000;
            break;
        case 300000 :
            length = 300001;
            break;
        }
    }
    return 0;
}
