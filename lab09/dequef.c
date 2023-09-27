#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef *df_alloc(long capacity, double factor)
{
   dequef *deque = (dequef *)malloc(sizeof(dequef));
   if (deque != NULL)
   {
      deque->data = (float *)malloc(capacity * sizeof(float));
      if (deque->data != NULL)
      {
         deque->first = 0;
         deque->size = 0;
         deque->cap = capacity;
         deque->mincap = capacity;
         deque->factor = factor;
      }
      else
      {
         // Allocation of data array failed, clean up and return NULL
         free(deque);
         deque = NULL;
      }
   }
   return deque;
}

/**
   Resizes the deque data based on the factor and the capacity.
   nCap is the new capacity the array will hold. Can increase or decrease size.

   On succes returns 1
   On failure returns 0
**/
int df_resize(dequef *D, long nCap)
{
   if (D != NULL)
   {
      float *nData = (float *)malloc(nCap * sizeof(float));

      if (nData != NULL)
      {
         for (long i = 0; i < D->size; i++)
         {
            nData[i] = D->data[(D->first + i) % D->cap];
         }

         D->data = nData;
         D->first = 0;
         D->cap = nData;
         return 1;
      }
   }
   return 0;
}

/**
  Release a dequef and its data.
**/
void df_free(dequef *D)
{
   free(D->data);
   free(D);
}

/**
   The size of the deque.
**/
long df_size(dequef *D)
{
   return D->size;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef *D, float x)
{
   if (D->size == D->cap)
      if (df_resize(D, D->cap * D->factor) == 0)
         return 0;

   D->data[(D->size + D->first) % D->cap] = x;
   D->size++;
   return 1;
}

/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef *D)
{
   if (D->size == 0)
      return 0.0;

   int last_index = (D->first + D->size - 1) % D->cap;
   float ret = D->data[last_index];
   D->size--;

   if (D->size < D->cap / (D->factor * D->factor))
   {
      long nCap = D->cap / D->factor;
      if (nCap < D->mincap)
         nCap = D->mincap;
      df_resize(D, nCap);
   }

   if (D->size == 0)
   {
      D->first = 0;
   }

   return ret;
}

/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef *D, float x)
{
   if (D->size == D->cap)
      if (df_resize(D, D->cap * D->factor) == 0)
         return 0;

   int index = (D->first - 1 + D->cap) % D->cap;

   D->data[index] = x;

   D->first = index;
   D->size++;
   return 1;
}

/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef *D)
{
   if (D->size == 0)
      return 0.0;

   // Calculate the index of the element to be ejected
   int eject_index = D->first;

   // Retrieve the element to be ejected
   float ejected_element = D->data[eject_index];

   // Update the 'first' index and decrement the size of the deque
   D->first = (D->first + 1) % D->cap;
   D->size--;

   // Check if resizing is necessary based on the condition capacity / (factor^2)
   if (D->size < D->cap / (D->factor * D->factor))
   {
      long new_capacity = D->cap / D->factor;
      if (new_capacity < D->mincap)
      {
         new_capacity = D->mincap;
      }
      df_resize(D, new_capacity);
   }

   return ejected_element;
}

/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef *D, long i, float x)
{
   if (i >= 0 && i < D->size)
   {
      long index = (D->first + i) % D->cap;
      D->data[index] = x;
   }
}

/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef *D, long i)
{
   if (i >= 0 && i < D->size)
   {
      long index = (D->first + i) % D->cap;
      return D->data[index];
   }
   return 0.0;
}

/**
   Print the elements of D in a line.
**/
void df_print(dequef *D)
{
   for (long i = 0; i < &D->size; i++)
      printf("%f ", df_get(D, i));
}
