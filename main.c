#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct BSTnode {
    char word[128];
    char meaning[256];
    struct BSTnode *left, *right;
    int count;

};



void Find(struct BSTnode *temp,char *word){

    int flag=0;
    int result = 0;
    while (temp) {
        result = strcasecmp(word,temp->word);
        if (result == 0) {
            printf("Word   : %s\t", word);
            printf("Meaning: %s\n", temp->meaning);
            flag = 1;
            break;
        }
        temp = (result < 0) ? temp->left : temp->right;
    }
    if (!flag)
        printf("Search Element not found in Binary Search Tree\n");

}



struct BSTnode *addtree(struct BSTnode *p, char *w, char *m) {
    int result = 0;

    if (p == NULL) {
        p = (struct BSTnode *) malloc(sizeof(struct BSTnode));
        //error
        strcpy(p->word, w);
        strcpy(p->meaning, m);
        p->count = 1;
        p->left = p->right = NULL;
        printf("%s : %s\n", p->word, p->meaning);
        return p;
    }
    if ((result = strcasecmp(w, p->word)) == 0) {
        p->count++;
    } else if (result < 0) {
        p->left = addtree(p->left, w, m);
    } else {
        p->right = addtree(p->right, w, m);

    }

    return p;
}

void printTreeAlphabtically(struct BSTnode *pTnode) {
    if (pTnode){
        printTreeAlphabtically(pTnode->left);
        printf("%s : %s\n",pTnode->word,pTnode->meaning);
        printTreeAlphabtically(pTnode->right);
    }
}
struct BSTnode *FindMin(struct BSTnode *T){
    if(T!=NULL)
        while(T->left!=NULL)
            T=T->left;
    return T;

}

struct BSTnode *DeleteNode(char *w,struct BSTnode *T) {
    struct BSTnode *Tmp = NULL;
    int result = 0;
    if (T == NULL) {
        printf("tree is not present!!");
        exit(0);
    } else if ((result = strcasecmp(w, T->word) < 0))
        T->left = DeleteNode(w, T->left);
    else if ((result = strcasecmp(w, T->word)) > 0)
        T->right = DeleteNode(w, T->right);
    else { /*element found*/
        if (T->right && T->left) {
            Tmp = FindMin(T->right);
            strcpy(T->word, Tmp->word);
            strcpy(T->meaning, Tmp->meaning);
            T->right = DeleteNode(T->word, T->right);

        } else {
            Tmp = T;
            if (T->left == NULL)
                T = T->right;
            else if (T->right == NULL)
                T = T->left;

            free(Tmp);
        }
    }




    return T;
}


void PrintBasedOnTheCharacter(struct BSTnode *T,char c) {

    if (T) {
        PrintBasedOnTheCharacter(T->left, c);


        if ((T->word)[0] == c) {
            printf("%s : %s\n", T->word, T->meaning);
        }

        PrintBasedOnTheCharacter(T->right, c);
    }
}

struct BSTnode *DeleteBasedOnCharacter(struct BSTnode *T,char c){

    if(T){
        T->left=DeleteBasedOnCharacter(T->left,c);
        T->right=  DeleteBasedOnCharacter(T->right,c);
        if ((T->word)[0] == c) {
            T=DeleteNode(T->word,T);
        }


    }
    return T;

}

void printTreeAlphabticallyInFILE(struct BSTnode *pTnode,FILE *fptr) {
    if (pTnode){
        printTreeAlphabticallyInFILE(pTnode->left,fptr);
        fprintf(fptr,"%s : %s\n",pTnode->word,pTnode->meaning);
        printTreeAlphabticallyInFILE(pTnode->right,fptr);
    }
}








int main() {
    FILE *fptr;
    char line[120];
    char word[20];
    char newWord[20], newMeaning[20];
    char m[100], w[20];
    char w1[128];
    char c_print;
    char c_delete;

    fptr = fopen("MyDictionary.txt", "r+");

    if (fptr == NULL) {
        printf("Error! opening file");

// Program exits if the file pointer returns NULL.
        exit(1);
    }
    struct BSTnode *T = NULL;
    while (fgets(line, sizeof(line), fptr)) {
        strtok(line, ". ");//split the number
        char *token2 = strtok(NULL, ":");//split the word and save it in token2
        while (token2[0] == ' ')token2++; //in case there was any spaces
        char *token3 = strtok(NULL, " \n");//split the meaning of the word
        while (token3[0] == ' ')token3++; // sometimes the meaning is more than one word
        T = addtree(T,token2, token3); //insert the meaning and the word inside the tree

    }
    int ch = 0;

while (ch!=-1) { // loop for the program to continue working
    printf("---------------------------------------------------\n");
    printf("1-Search\n2-Insert\n3-Update the meaning of any word\n4-Delete\n5-print in-order\n6-print words with the same character\n7-delete words with the same character.\n8-save back in file.\n");
    printf("enter -1 to exit\n");
    printf("choose one of those options:\n"); // choose from the menu
    scanf("%d", &ch);
    switch (ch) {


        case 1:
            printf("Enter the word you're looking for:\n"); // search option
            scanf("%s", word);
            char *search = strtok(word, "\n");// remove the space so the compiler reads the word properly
            Find(T, search);//call find function
            break;
        case 2:
            printf("Enter the word and the meaning you want to add:");//insert option

            scanf("%s", newWord);
            scanf("%s", newMeaning);
            T = addtree(T, newWord, newMeaning);
            break;
        case 3:

            printf("enter the word and update the meaning:"); // updating option by deleting the chosen node and inserting another one by the user
            scanf("%s", w);
            scanf("%s", m);
            T = DeleteNode(w, T);
            T = addtree(T, w, m);

            printTreeAlphabtically(T);
            break;

        case 4:
            printf("enter a word to delete:");//deleting option
            scanf("%s", w1);
            char *delete = strtok(w1, "\n");//remove the space so the compiler reads the word properly
            T = DeleteNode(delete, T);
            printTreeAlphabtically(T);
            break;

        case 5:
            printTreeAlphabtically(T);// printing Alphabetically option
            break;

        case 6:
            printf("enter the character:");//printing words with the same character option
            scanf("%s", &c_print);
            PrintBasedOnTheCharacter(T, c_print);
            break;

        case 7:
            printf("enter the character:");//deleting words with the same character option
            scanf("%s", &c_delete);
            T = DeleteBasedOnCharacter(T, c_delete);
            printTreeAlphabtically(T);
            break;

            case 8:
                printTreeAlphabticallyInFILE(T,fptr);//saving back in file option
                printf("check your file!!");
                break;


        default:
            printf("not available!!");
            break;

    }
}

    fclose(fptr);// close file










    /* printf("Enter the word you're looking for:\n");
     scanf("%s", word);
     char *search = strtok(word, "\n");
     Find(T, search);
     printTreeAlphaptically(T);
     printf("Enter the word and the meaning you want to add:");

     scanf("%s", newWord);
     scanf("%s", newMeaning);
     T = addtree(T, newWord, newMeaning);
     printTreeAlphaptically(T);



     printf("enter the word and update the meaning:");
     scanf("%s", w);
     scanf("%s", m);

     printf("the updated meaning of %s is : %s ", w, m);
     printTreeAlphaptically(T);

     printf("enter a word to delete:");
     scanf("%s",w);
     T=DeleteNode(w1,T);
     printTreeAlphaptically(T);
     */
    /* printf("enter the character:");
     scanf("%s",&c_print);
     PrintBasedOnTheCharacter(T,c_print);

     printf("enter the character:");
     scanf("%s",&c_delete);
     T=DeleteBasedOnCharacter(T,c_delete);
     printTreeAlphaptically(T);

*/


    return 0;
}
