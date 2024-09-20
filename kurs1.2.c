#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 1000

/*Line entry function*/
void new_gets(char s[], int lim)
{
    char c;
    int i;

    i=0;
    while(((c=getchar())!='\n')&&(i<lim-1))
    {
        s[i]=c;
        i++;
    }
    s[i]='\0';
}

/*Is it a separator*/
int isDelimiter(char c, char delimiters[], int numDelimiters)
{
    int i = 0, flag = 1;
    while (i < numDelimiters && flag != 0){
        if (c == delimiters[i]){
            flag = 0;
        }
        i++;
    }
    return (flag == 0);
}

/*Output of the file contents*/
void cat(const char* filename)
{
    int ch;
    FILE *file = fopen(filename, "r");
    while (!feof(file) && !ferror(file))
    {
        ch = getc(file);
        if (ch != EOF)
        {
            putchar(ch);
        }
    }
    putchar('\n');
    fclose(file);
}

/*Is there a keyword in the string*/
int isInString(char *string, char *word){
    int i,check=0,k=0;
    for (i=0;i<strlen(string)&&check==0;i++){
        if (toupper(string[i])==toupper(word[k])){
            k++;
        }
        else{k=0;}
        if (k==strlen(word) && !isalpha(string[i+1]) && !isalpha(string[i-strlen(word)])){
            check=1;
        }
    }
    return check;
}

/*Obrabotka stroki*/
void Result_text(const char *NewFile,char *string, char w1[MAXLEN], char w2[MAXLEN], char w3[MAXLEN], char *separators){

    FILE *res_file = fopen(NewFile, "a");
    int i, max = -1000, count = 0, max_index, index = 0;
    char stroka[MAXLEN] = {'\0'};

    if (isInString(string, w1) || isInString(string, w2) || isInString(string, w3)){
        for (i = 0; i < strlen(string); i ++){/*»щем самое длинное слово*/
            if (isDelimiter(string[i], separators, strlen(separators))){/*явл€етс€ ли разделителем*/
                if (count > max){
                    max = count;
                    max_index = i - count;
                }
                count = 0;
            }else if (i == strlen(string) - 1){
                if (count + 1 > max){
                    max = count + 1;
                    max_index = i - count;
                }
            } else {
                count ++;
            }
        }

        for (i = 0; i < strlen(string); ){
            if (i != max_index){
                stroka[index] = string[i];
                index ++;
                i ++;
            }else{
                if (i + max != strlen(string) - 1){
                    i = i + max + 1;
                }else{
                    i = i + max;
                }
            }

        }
        fprintf(res_file, stroka);
        fprintf(res_file, "\n");
    }else{
        fprintf(res_file, string);
        fprintf(res_file, "\n");
    }
    fclose(res_file);
}

void Clear_file(const char *filename){
    FILE *file = fopen(filename, "w");

    fclose(file);
}
int main(){
    char separators[MAXLEN], string[MAXLEN];
    const char *NewFile = "res_text.txt";
    char w1[MAXLEN],w2[MAXLEN],w3[MAXLEN];
    int number_keywords = 0, flag1 = 0, flag2 = 0, flag3 = 0;/* number_keywords - количество ключевых слов, которые уже нашли в тексте*/

    printf("Enter three keywords, a line of delimiters and text.\n");
    printf("The program will output the converted text, in which the longest word in the line where the keyword is is deleted.\n");
    printf("Enter the first keyword: ");
    new_gets(w1, MAXLEN);
    printf("Enter the second keyword: ");
    new_gets(w2, MAXLEN);
    printf("Enter the third keyword: ");
    new_gets(w3, MAXLEN);

    printf("Enter the delimiters: ");
    new_gets(separators, MAXLEN);

    printf("Enter the text : \n");
    do {
        new_gets(string, MAXLEN);
        if (isInString(string,w1) && flag1 == 0){
            number_keywords ++;
            flag1 = 1;
        }
        if (isInString(string,w2) && flag2 == 0){
            number_keywords ++;
            flag2 = 1;
        }
        if (isInString(string,w3) && flag3 == 0){
            number_keywords ++;
            flag3 = 1;
        }
        Result_text(NewFile, string, w1, w2, w3, separators);
    }while (number_keywords != 3);

    printf("-------------\n");
    printf("Result text: \n");
    cat("res_text.txt");
    printf("-------------\n");

    Clear_file("res_text.txt");

    /* ”даление файла*/
    printf ("Delete file: ");
   if (-1 == remove ("res_text.txt"))
      printf ("Error\n");
   else{
      printf ("Success\n");
   }
    return 0;
}
