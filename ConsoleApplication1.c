
#include <iostream>
#include <stdio.h>
#include <string.h>

char str[80];
int len_str = 0;
int* first_letters;
int* len_words;
int* is_used;
bool* is_unique;

void dynamic_array_alloc(int** mas, int n)
{
   *mas = (int*)malloc(n * sizeof(int));
   
    if (!(*mas)) {
        printf("Error with memory");

    }
}

void dynamic_array_alloc(bool** mas, int n)
{
    *mas = (bool*)malloc(n * sizeof(bool));

    if (!(*mas)) {
        printf("Error with memory");

    }
}

int *first_letters_arr()
{
    int j = 0;
    for (int i = 0; i < len_str; i++) {
        if (i == 0 || str[i - 1] == ' ') {
            first_letters[j] = i;
            j++;
        }
    }
    return first_letters;
}

int* len_words_arr(int amount)
{
    for (int i = 0; i < amount - 1; i++) {
        len_words[i] = first_letters[i + 1] - first_letters[i] - 1;
    }
    len_words[amount - 1] = len_str - first_letters[amount - 1];
    return len_words;
}


void our_words( int amount)
{
    int cur_max_len = 0;
    int index_max = -1;
    printf("The biggest unique word is: "); 
    while (true) {
        for (int i = 0; i < amount; i++) {
            if (len_words[i] > cur_max_len&& is_used[i] == 0) {
                cur_max_len = len_words[i];
                index_max = i;
            }
        }
        if (index_max == -1) {
            printf("Don't have words with unique letters!");
            break;
        }

        if (is_unique[index_max]) {
            for (int j = first_letters[index_max]; j < first_letters[index_max] + len_words[index_max]; j++)
                printf("%c", str[j]);
            break;
        }
        else {
            is_used[index_max] = 1;
            cur_max_len = 0;
            index_max = -1;
        }

    }
}



int main()
{
    printf("Write:");
    int amount_of_words = 0;


    fgets(str, 80, stdin);


    if (str[1] == 0) {
        printf("Bad input!");
        return 0;
    }

    while (str[len_str] != 0) {
        if (str[len_str] == ' ')
            amount_of_words++;
        len_str++;
    }

    if (amount_of_words == len_str - 1) {
        printf("Bad input!");
        return 0;
    }

    len_str--;
    amount_of_words++;

    dynamic_array_alloc(&first_letters, amount_of_words);
    dynamic_array_alloc(&len_words, amount_of_words);
    dynamic_array_alloc(&is_used, amount_of_words);
    dynamic_array_alloc(&is_unique, amount_of_words);

  
    
    for (int i = 0; i < amount_of_words; i++)
        is_used[i] = 0;

    first_letters_arr();
    len_words_arr(amount_of_words);
   

    bool flag = true;
    for (int i = 0; i < amount_of_words; i++) {
        flag = true;
        for (int j = first_letters[i]; j < first_letters[i] + len_words[i]; j++) {
            for (int k = j + 1; k < first_letters[i] + len_words[i]; k++) {
                if (str[j] == str[k]) {
                    flag = false;
                    break;
                }
            }
        }
        if (!flag)
            is_unique[i] = false;
        else
            is_unique[i] = true;
    }


    our_words(amount_of_words);

    free(first_letters);
    free(len_words);
    free(is_used);
    free(is_unique);



}

