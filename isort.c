#include <stdio.h>
#include <string.h>

#define ARRLENGTH 50 //size of the given array



void shift_element(int* arr, int i); //declaration
void insertion_sort(int* arr , int len);//declaration


int main()
{
    int arr[ARRLENGTH];//declaration of the array
    //filling the array with the input file
    for (int i = 0; i < ARRLENGTH; i++)
    {
        scanf("%d",(arr+i));
    }
    insertion_sort(arr,ARRLENGTH);// sort the array using the insertion method

    //print out the array as required 
    for (int i = 0; i < ARRLENGTH; i++)
    {
        if (i!=ARRLENGTH-1)
        {
            printf("%d,",*(arr+i));
        }
        else
        {
            printf("%d",*(arr+i));
        }
        
    }

    return 0;
}

//shifts the i next elements to the right
void shift_element(int* arr, int i)
{
    int* p_arr = arr;
    for (int j = i; j > 0; j--)
    {//starts overwriting the values from the (p_arr+i)'th spot to the first
        *(p_arr+j) = *(p_arr+j-1);
    }

}

//sorting an array
void insertion_sort(int* arr , int len)
{
    for (int i = 0; i < len-1; i++)
    {   
        //declaring first element as min
        int min = *(arr+i);
        int p_min = i;// stores the spot of min

        for (int j = i+1; j < len; j++)
        {//finding min value in range of j to the array's end
            if (min > *(arr+j))
            {
                min = *(arr+j);
                p_min = j;
            } 
        }
        shift_element(arr+i,p_min-i); //shifts all the elements from i'th spot to the minimum element spot
        *(arr+i) = min; //put the minimum element in i'th spot
    }
}


