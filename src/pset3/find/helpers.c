/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"


/**
 * Nick Sifniotis
 * 29 December 2015
 * 
 * Helper function for search()
 * Implementation of a recursive binary search.
 * Returns true if value exists between values[start] and values[end]
 */
bool bin_search_recurser(int start, int end, int values[], int value)
{
    if (start == end)
        return (value == values[start]);
    if (start == (end - 1))
        return (value == values[start] || value == values[end]);
        
    int midpoint = (start + end) / 2;
    if (value < values[midpoint])
        return bin_search_recurser(start, midpoint, values, value);
    else if (value == values[midpoint])
        return true;
    else if (value > values[midpoint])
        return bin_search_recurser(midpoint, end, values, value);
    else
        return false;           // this line will never be executed.
}


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
        return false;
        
    return bin_search_recurser(0, n - 1, values, value);
}


/**
 * Nick Sifniotis
 * 29 December 2015
 * 
 * Swaps elements a and b in the array values[]
 */
void swap_values(int values[], int a, int b)
{
    int holding = values[a];
    values[a] = values[b];
    values[b] = holding;
}


/**
 * Nick Sifniotis
 * 29 December 2015
 * 
 * Helper function for sort()
 * Implements a recursive merge sort.
 */
void merge_sort_recurser(int values[], int start, int end)
{
    if (start == end)
        return;
        
    if (start == (end - 1))
    {
        if (values[start] > values[end])
            swap_values(values, start, end);
        return;
    }
    
    int midpoint = (start + end) / 2;
    merge_sort_recurser(values, start, midpoint);
    merge_sort_recurser(values, midpoint, end);
    
    int array_size = 1 + end - start;
    int *temp = malloc(array_size * sizeof(int));
    int counter = 0;
    int start_pos = start;
    int end_pos = midpoint;
    while (start_pos < midpoint || end_pos < (end + 1))
    {
        if (start_pos >= midpoint)
        {
            temp[counter] = values[end_pos];
            end_pos++;
        }
        else if (end_pos > end)
        {
            temp[counter] = values[start_pos];
            start_pos++;
        }
        else
        {
            if (values[start_pos] > values[end_pos])
            {
                temp[counter] = values[end_pos];
                end_pos++;
            }
            else
            {
                temp[counter] = values[start_pos];
                start_pos++;
            }
        }
        counter++;
    }
    
    for (int i = 0; i < array_size; i ++)
        values[i + start] = temp[i];
        
    free(temp);
    return;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if (n < 2)
        return;
    
    merge_sort_recurser(values, 0, n - 1);
    
    /*for (int i = 1; i < n; i ++)
    {
        if (values[i] < values[i - 1])
        {
            int temp_counter = i;
            while (values[temp_counter] < values[temp_counter - 1] && temp_counter > 0)
            {
                int holding = values[temp_counter];
                values[temp_counter] = values[temp_counter - 1];
                values[temp_counter - 1] = holding;
                
                temp_counter--;
            }
        }
    }*/
}
