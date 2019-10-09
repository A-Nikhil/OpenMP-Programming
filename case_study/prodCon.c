#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

void performTokenizer(char str[]) {
    // printf("%s", str);
    char newString[10][50];
    int i = 0, j, k;
    for (j = 0; j <= strlen(str); j++) {
        if (str[j] == ' ' || str[j] == '\0') {
            newString[i][k] = '\0';
            i++;
            k = 0;
        } else {
            newString[i][k] = str[j];
            k++;
        }
    }
    // printf("%d \n", i);

    int counter;
    for (counter = 0; counter < i; counter++) {
        printf("%s\n", newString[counter]);
    }
}

int main() {

    FILE *handle;
    handle = fopen("myFile.txt", "a+");
    
    char sentences[5][50] = {
        "Hello World\n",
        "Hello, Nikhil\n",
        "How are you?\n",
        "I'm good. Wbu?\n",
        "I'm good too\n"
    };

    int threadNum = 0, i = 0;
    char dataRead[50];
    omp_set_num_threads(2); // 0 - producer, 1 - consumer
    int x;
    #pragma omp parallel shared(handle, i)
    {
        for (x = 0; x<12; x++) {
            threadNum = omp_get_thread_num();
            // printf("%d", threadNum);
            if (threadNum % 2 ==  0)
            {
                // producer
                fputs(sentences[((i+1)%5)], handle);
                printf("Written Line : %s\n", sentences[((i+1)%5)]);
                i++;
            } 
            else 
            {
                // consumer
                fgets(dataRead, 50, handle);
                // fscanf(handle, "%[^\n]", dataRead);
                printf("Tokenizing \n");
                performTokenizer(dataRead);
                // printf("\n\n");
            }
        }
        
    }
    fclose(handle);

}