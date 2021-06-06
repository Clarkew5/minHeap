#include "heap.h"

Heap* create_heap(){
    //creates the heap
    Heap *h = malloc(sizeof(Heap));
    if (h == NULL) exit(-1);
    
    //creates the head of the heap
    h->head = malloc(sizeof(Heap_Level));
    if (h->head == NULL) exit(-1);
    h->head->level = 1;
    h->head->data_array = calloc(1, sizeof(int));
    if (h->head->data_array == NULL) exit(-1);
    h->head->next_level = NULL;
    h->head->prev_level = NULL;
    
    //sets heap data
    h->insert_level = h->head;
    h->insert_index = 0;   

    return h;
}

int delete_heap(Heap *h){
    //deletes heap h and all data within it
    Heap_Level *p = h->head->next_level;
    free(h->head->data_array);
    free(h->head);
    if(p != NULL){
        while (p->next_level != NULL){
            free(p->data_array);
            p = p->next_level;
            free(p->prev_level);
        }
        free(p->data_array);
        free(p);
    }
    free(h);
    return 0;
}

int swap(Heap_Level *al, int ai, Heap_Level *bl, int bi){
    //swaps two nodes in the heap
    int temp = al->data_array[ai];
    al->data_array[ai] = bl->data_array[bi];
    bl->data_array[bi] = temp;
    return 0;
}

int up_heap(Heap *h){
    Heap_Level *c_l = h->insert_level; //child level
    int c_i = h->insert_index; //child index
    Heap_Level *p_l = h->insert_level->prev_level; //parent level
    int p_i = c_i/2; //parent index
    while (p_l != NULL ){
        if(c_l->data_array[c_i] <= p_l->data_array[p_i]){
            swap(c_l, c_i, p_l, p_i);
            c_l = p_l;
            c_i = p_i;            
            p_l = p_l->prev_level;
            p_i = c_i/2;
        }
        else break;
    }
    return 0;
}

int add(Heap *h, int data){
    //adds the integer data into heap h
    h->insert_level->data_array[h->insert_index] = data;
    up_heap(h);

    int sizeof_array = (int)pow(2, h->insert_level->level-1);
    if (h->insert_index+1 < sizeof_array){
        //if the leaf layer is not full
        h->insert_index++;    
    }
    else{
        //if the leaf layer is full and a new one needs to be added
        h->insert_level->next_level = malloc(sizeof(Heap_Level));
        if (h->insert_level->next_level == NULL) exit(-1);
        h->insert_level->next_level->level = h->insert_level->level+1;
        h->insert_level->next_level->prev_level = h->insert_level;
        h->insert_level = h->insert_level->next_level; 
        int sizeof_array = (int)pow(2, h->insert_level->level-1);       
        h->insert_level->data_array = calloc(sizeof_array, sizeof(int));
        h->insert_level->next_level = NULL;
        
        h->insert_index = 0;        
    }
    return 0;
}

int down_heap(Heap *h){
    Heap_Level *p_l = h->head; //parent level
    int p_i = 0; //parent index
    Heap_Level *c_l = h->head->next_level; //child level
    int lc_i = p_i*2; //left child index
    int rc_i = lc_i+1; //right child index
    
    while (c_l != NULL 
        && c_l->data_array[lc_i] != 0 && c_l->data_array[rc_i] != 0){
        
        if (p_l->data_array[p_i] >= c_l->data_array[lc_i]
         && c_l->data_array[rc_i] >= c_l->data_array[lc_i]){
            
            swap(p_l, p_i, c_l, lc_i);
            p_i = lc_i;
        }
        else if (p_l->data_array[p_i] >= c_l->data_array[rc_i] 
              && c_l->data_array[lc_i] >= c_l->data_array[rc_i]){

            swap(p_l, p_i, c_l, rc_i);
            p_i = rc_i;
        }
        p_l = c_l;
        c_l = c_l->next_level;
        lc_i = p_i*2;
        rc_i = lc_i+1;    
    }
    return 0;
}

int pop(Heap *h){
    //pops the head of the heap h
    int head_data = h->head->data_array[0];

    if (h->insert_index-1 >= 0){
        //if the leaf layer is not empty 
        h->insert_index--;
    }
    else{
        //if the leaf layer is empty and needs to be removed
        h->insert_level = h->insert_level->prev_level;
        free(h->insert_level->next_level->data_array);
        free(h->insert_level->next_level);
        h->insert_level->next_level = NULL;

        h->insert_index = (int)(pow(2, h->insert_level->level-1)-1);      
    }

    h->head->data_array[0] = h->insert_level->data_array[h->insert_index];
    h->insert_level->data_array[h->insert_index] = 0;
    down_heap(h);

    return head_data;
}



int print_heap(Heap *h){
    //prints inputed heap
    Heap_Level *p = h->head;   
    while(p != NULL){
        printf("level: %d\n", p->level);        
        int sizeof_data_array = pow(2, p->level-1);
        for(int i = 0; i < sizeof_data_array; i++){
            printf("%d ", *(p->data_array+i));
        }
        printf("\n");
        p = p->next_level;
    }
    return 0;
}

