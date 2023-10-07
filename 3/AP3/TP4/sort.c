#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sort.h"

void print_tab(s_data_t tab[], int tab_size)
{
  for(int i=0; i<tab_size; i++){
    print(tab[i]);
  }
  printf("\n");
}


// BUBBLE SORT
void bubble_sort(s_data_t tab[], int tab_size)
{
  for(int i = 0; i<tab_size-1; i++){
    for(int j = 0; j<tab_size-i-1; j++){
      if(tab[j] > tab[j+1]){
        int tmp = tab[j];
        tab[j] = tab[j+1];
        tab[j+1] = tmp;
      }
    }
  }
}


// INSERTION SORT
void insertion_sort(s_data_t tab[], int tab_size)
{
  for(int i = 1; i<tab_size; i++){
    int val = tab[i];
    int j = i-1;
    while(val < tab[j] && j >= 0){
      tab[j+1] = tab[j];
      --j;
    }
    tab[j+1] = val;
  }
}


// SELECTION SORT
void selection_sort(s_data_t tab[], int tab_size)
{
  for(int i = 0; i < tab_size-1; i++){
    int pos = i;
    for(int j = i+1; j < tab_size; j++){
      if(tab[pos] > tab[j]){
        pos = j;
      }
    }
    if(pos != i){
      int tmp = tab[i];
      tab[i] = tab[pos];
      tab[pos] = tmp;
    }
  }
}

void swapDown(s_data_t tab[], int tab_size, int pos){
  if(pos < tab_size/2){
    int posMin;
    int fg = 2*pos + 1;
    int fd = 2*pos + 2;
    if(fd < tab_size){
      if(tab[fg] < tab[fd]){
        posMin = fg;
      }else{
        posMin = fd;
      }
    }else{
      posMin = fg;
    }
    if(tab[posMin] < tab[pos]){
      int tmp = tab[posMin];
      tab[posMin] = tab[pos];
      tab[pos] = tmp;
      swapDown(tab,tab_size,posMin);
    }
  }
}

void arbre2tas(s_data_t tab[], int tab_size){
  for(int i = (tab_size/2)-1; i>0; i--){
    swapDown(tab,tab_size,i);
  }
}

int supprimerMin(s_data_t *tab, int tab_size, int taille){
  int min = tab[0];
  tab[0] = tab[taille-1];
  swapDown(tab,taille,0);
  return min;
}

void heapify(s_data_t tab[], int tab_size, int i){
  int largest = i;
  int left = 2*i + 1;
  int right = 2*i + 2;
  if(left < tab_size && tab[i] < tab[left]){
    largest = left;
  }else if(right <tab_size && tab[largest] < tab[right]){
    largest = right;
  }else if(largest != i){
    int tmp = tab[i];
    tab[i] = tab[largest];
    tab[largest] = tmp;
  }
}

// HEAP SORT
void heap_sort (s_data_t tab[], int tab_size)
{
  for(int i = (tab_size/2)-1; i>1; i--){
    heapify(tab,tab_size,i);
  }
  for(int i = tab_size-1; i>0; i--){
    int tmp = tab[i];
    tab[i] = tab[0];
    tab[0] = tmp;
  }
}

int partager(s_data_t tab[],int deb, int fin){
  int g = deb-1;
  int d = fin+1;
  int pivot = tab[deb];
  while(g < d){
    g++;
    while(tab[g] < pivot){
      g++;
    }
    d--;
    while(tab[d] > pivot){
      d--;
    }
    if(g<d){
      int tmp = tab[d];
      tab[d] = tab[g];
      tab[g] = tmp;
    }
  }
  return d;
}


// QUICK SORT
void quick_sort(s_data_t tab[], int lower, int upper)
{
  if(upper > lower){
    int pivot = partager(tab,lower,upper);
    quick_sort(tab,lower,pivot);
    quick_sort(tab,pivot+1,upper);
  }
}
