#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     LOAD_FACTOR 0.65
#define TABLE_SIZE 130

int table_size = TABLE_SIZE;


struct HashNode {

    char word[50];
    char meaning[100];
    char status;
};


struct HashNode *ht;





void ht_display(struct HashNode *ht) {
    for (int i = 0; i < table_size; i++) {
        if (ht[i].status=='T') {

            printf("%d ) %s : %s \n", i, ht[i].word, ht[i].meaning);
        } else {
            printf("%d empty\n", i);

        }
    }
}




int string_hash(const char *str, int size) {
    int count = 31;//'z'-'a'
    int val = 1;
    int hash = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        char c = str[i];
        int x;

        if (c >= 'A' && c <= 'Z' ){
            x = c - 'A';

        }
        else {
            x = c - 'a';

        }
        hash += (val * x) % size;
        val = (val * count) % size;
    }
    return hash;
}

int Dictionary_hash(char *key, int size) {
   return string_hash(key,size);
}

void addTable(char *word,char *meaning, int size,int flag) {


    int hashValue = Dictionary_hash(word, size);
    int index = hashValue % size;
    int i = 0;
    if (ht[index].status == 'F') {
        strcpy(ht[index].word, word);
        strcpy(ht[index].meaning, meaning);
        ht[index].status = 'T';
    }
        //collision happened!!!ya msebtee
    else{
        if (flag == 1)
            {

            for (i = 1; i < size; i++){

                index = (hashValue + i) % size; // linear probing
                if (ht[index].status == 'F'){
                    strcpy(ht[index].word, word);
                    strcpy(ht[index].meaning, meaning);
                    ht[index].status = 'T';
                    break;
                }
            }
        }
        else{
                for (i = 1; i < size; i++)
                    {
                      index = ((hashValue + (i * i)) % size); // quadratic probing
                      if (ht[index].status == 'F'){
                        strcpy(ht[index].word, word);
                        strcpy(ht[index].meaning, meaning);
                        ht[index].status = 'T';
                        break;
                      }
                    }

          }
      }



}
/*
 * rehash the hash table when filled
*/

void rehash(int flag) {
    int new_size = table_size * 2;
    int index;
    int hashValue;
    int x, i, j;

    struct HashNode *new_hash_table = malloc(sizeof(struct HashNode) * new_size);

    for (x = 0; x < new_size; x++) {
        new_hash_table[x].status = 'F';
    }


    for (i = 0; i < table_size; ++i) {
        if (ht[i].status == 'T') {
            hashValue = Dictionary_hash(ht[i].word, new_size);
            index = hashValue % new_size;
            if (new_hash_table[index].status == 'F') {
                strcpy(new_hash_table[index].word, ht[i].word);
                strcpy(new_hash_table[index].meaning, ht[i].meaning);
                new_hash_table[index].status = 'T';
            } else {
                if (flag == 1) {
                    //
                    for (j = 1; j < new_size; j++) {
                        index = (hashValue + j) % new_size; // linear probing
                        if (new_hash_table[index].status == 'F') {
                            strcpy(new_hash_table[index].word, ht[i].word);
                            strcpy(new_hash_table[index].meaning, ht[i].meaning);
                            new_hash_table[index].status = 'T';
                            break;
                        }
                    }
                } else {
                    //
                    for (j = 1; j < new_size; j++) {
                        index = (hashValue + (j * j)) % new_size; // quadratic probing
                        if (new_hash_table[index].status == 'F') {
                            strcpy(new_hash_table[index].word, ht[i].word);
                            strcpy(new_hash_table[index].meaning, ht[i].meaning);
                            new_hash_table[index].status = 'T';
                            break;
                        }
                    }
                }
            }

        }
        ht = new_hash_table;
        table_size = new_size;

    }
}



void printHashTable(struct HashNode *ht){
    for(int i=0;i<=table_size;i++){
    if(ht[i].status=='T'){
    printf("%s : %s\n",ht[i].word,ht[i].meaning);
    }
    }
}

void printHash_inFile(FILE *fptr_out) {
    for (int i = 0; i <= table_size; i++) {
        if (ht[i].status == 'T')
            fprintf(fptr_out, "%s : %s\n",ht[i].word,ht[i].meaning);
    }
    fclose(fptr_out);
}


void Find(char *word, struct HashNode *ht,int flag) {
    int hashValue = string_hash(word, TABLE_SIZE);
    int i = 0;
    int index;


        if (flag == 0) {
            for (i = 0; i <= table_size-1 ; i++) {

                    // linear probing
                    index = (hashValue + i) % table_size;
                    if (strcasecmp(ht[index].word, word) == 0 &&
                        ht[index].status == 'T') {

                        printf("%s:%s\n", ht[index].word, ht[index].meaning);
                        break;
                    } else{
                        printf("The word was not found\n");
                        break;
                }
                }
            }
else
            if (flag==1){
                for (i = 0; i <=table_size-1; i++) {

                // quadratic probing
                index = (hashValue + (i * i)) % table_size;
                if (strcasecmp(ht[index].word, word) == 0 &&
                    ht[index].status == 'T') {

                    printf("%s:%s\n", ht[index].word, ht[index].meaning);
                    break;
                } else
                    printf("The word was not found\n");
                    break;
            }

        }

    }




void Delete(struct HashNode *ht,char *w,int flag) {
    int hashVal = string_hash(w, table_size);
    int index;
    if (flag == 1) {

        for (int i = 0; i <= table_size-1; i++) {
            index = (hashVal + i) % table_size;
            if (strcasecmp((ht[index].word), w) == 0 && ht[index].status == 'T') {
                /*free(ht[index].word);
                free(ht[index].meaning);
                 */
                ht[index].status = 'F';
                printf("DONE!!!");


                break;
            } else {
                printf("not found");
                break;
            }
        }
    } else if (flag == 0) {
        for (int i = 0; i <= table_size-1; i++) {

                index = (hashVal + (i * i)) % table_size;
                if (strcasecmp((ht[index].word), w) == 0 && ht[index].status == 'T') {

                    /*free(ht[index].word);
                    free(ht[index].meaning);
                     */
                    ht[index].status = 'F';
                    printf("DONE!!!");
                    break;

                } else {
                    printf("not found");
                    break;
                }
            }


        }
    }









    float getLoadFactor(int count,int size){
        return (float)count/size;
    }



// Driver Code
    int main() {
    FILE *fptr;
    FILE *fptr_out;
    char line[120];
    int op = 0;
    int i = 0;
    char word[50];
    char meaning[50];
    int count=0;
    int flag=1;



    fptr = fopen("MyDictionary.txt", "r");
    fptr_out = fopen("dictionary_modified.txt", "w");

    if (fptr_out == NULL) {
        printf("Error! opening file");

// Program exits if the file pointer returns NULL.
        exit(1);
    }


    if (fptr == NULL) {
        printf("Error! opening file");

// Program exits if the file pointer returns NULL.
        exit(1);
    }


    ht = (struct HashNode *) malloc(TABLE_SIZE * sizeof(struct HashNode));
    for (i = 0; i < TABLE_SIZE; i++) {
        ht[i].status = 'F';
    }


    while (fgets(line, sizeof(line), fptr)) {
       // strtok(line,". ");
        char *token1 = strtok(line, ":");
        char *token2 = strtok(NULL, "\n");//split the word and save it in token2
        printf("%s:%s\n", token1, token2);



         if (LOAD_FACTOR <= ((float)count / table_size)) {
              rehash(flag);
          }

        addTable(token1, token2, table_size,flag);

        count++;
        //i++;
    }
    printf("%d#########################\n\n\n",count);
    count=0;
    for(i=0;i<table_size; i++)
    {
        if(ht[i].status == 'T')
           {
               printf("%s:%s\n",ht[i].word,ht[i].meaning);
               count++;
           }

    }
    printf("%d#########################\n\n\n",count);

    while (op != -1) {

        printf("please choose an option:\n"
               "1- Search for a word and display its meaning.\n"
               "2- Update the meaning of an existing word.\n"
               "3- Insert a new word from the user with its meaning.\n"
               "4- Print all words in the dictionary with their associated meanings.\n"
               "5- Print the entire hash table including the empty slots.\n"
               "6- Delete a word from the dictionary.\n"
               "7- Print the number of occupied slots, hash table size and the load factor.\n"
               "8- Save all words back in file dictionary_modified.txt.\n"
               "enter -1 to exit!!\n");
        printf("---------------------------------------------------------\n");
        printf(">>>>>choose (1) for linear probing and (0) for quadratic probing<<<<<<");

        scanf("%d",&op);
        switch (op) {

            case 1: printf("please enter the word you're looking for and the technique you wish to use:\n");
                    scanf("%s %d",&word,&flag);
                   Find(word,ht,flag);
                    break;
            case 2: printf("please enter the word and update the meaning: \n and enter the technique you wish to use:\n");
            scanf("%s %s %d",&word,&meaning,&flag);
            Delete(ht,word,flag);
            addTable(word,meaning,TABLE_SIZE,flag);
                break;

            case 3:
                printf("please enter the word and the meaning:\n"
                       "and enter the technique you wish to use:\n ");
                scanf("%s %s",&word,&meaning,&flag);
                addTable(word,meaning,table_size,flag);
                break;
            case 4:
                printHashTable(ht);
                break;


            case 5:
                ht_display(ht);
                break;

            case 6: printf("enter the word you wish to delete: \n"
                           "and enter the technique you wish to use:\n");
            scanf("%s %d",&word,&flag);
            Delete(ht,word,flag);
                break;

            case 7:  printf("number of occupied slots : %d\n"
                            "hash table size :%d\n"
                            "load factor:%f\n",count,TABLE_SIZE,getLoadFactor(count,table_size));
                break;
            case 8:  printHash_inFile(fptr_out);
            printf("go check your file!!\n");
                break;
            case -1:
                exit(0);

            default: printf("not available ");
                break;



        }
    }



    return 0;
}

