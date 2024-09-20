#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#define MAXLEN 128
#define SEP ';'

struct movie;
typedef struct movie MOV;

struct movie_head;
typedef struct movie_head MHD;

struct director;
typedef struct director DIR;

struct director_head;
typedef struct director_head DHD;

void clear_screen();
void menu();
MHD *make_movie_head();
DHD *make_director_head();
void sort_director_list(DHD *dph, int direction, MHD *mph, int j);
int swap_director(DHD *dph, DIR *current);
char* find_name(MOV *ARR[], int i);
DIR* find_director(MOV *ARR[], int i);
DIR *find_dir(DHD *dph, int id);
void find_by_dir(MOV *ARR[], DIR *(*func_name)(MOV**, int), int n, DHD *dph);
void find_by_ch(MOV *ARR[], char *(*func_name)(MOV**, int), int n, MHD *mph);
int count_of_lines(char *filename);
void add_director_to_list(char *filename, DHD *dph, char sep);
void add_movie_to_list(char *filename, MHD *mph, char sep, DHD *dph);
void read_to_array(MOV** mov, int n, MHD *head);
void output_movie(MHD *mph, int n);
void output_director(DHD *dph, int n);
void new_gets(char s[], int lim);
void print_head(int n);
void print_tail(int n);
void split_string(char *inputString, char **words, int *wordCount, char delimiter);
DIR *create_director(int id, char *movie_director);
void add_director(DHD *dph, DIR *new_node);
MOV *create_movie(int id_mov, char *movie_name, int id, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3], DHD *dph);
void add_movie(MHD *ph, MOV *new_node, MOV *current_node);
void delete_by_number(DHD *dph, MHD *mph);
void delete_director(DHD *dph, MHD *mph, DIR *current_director);
void delete_movie(MHD *mph, MOV *current_movie);
void edit_Record(MHD *mph, DHD *dph,int n);
void edit_director(DHD *dph, MHD *mph);
void add_Record_to_file(char *filebrand, MHD *mph, char sep, DHD *dph);
int add_Director_to_file(char *filedirector, DHD *dph);
void save_database_changes(char *Record_filename, char *director_filename, MHD *mph, DHD *dph, char sep);


struct movie{
    int id; /* ID of movie */
    char *name; /* Name of movie */
    DIR *director; /* Director of movie */
    int year; /* Year of movie release */
    int duration; /* duration of movie in minutes*/
    float kpr; /* Movie rating on KinoPoisk */
    float plr; /* Movie rating on my opinion */
    int date[3]; /* Day/Month/Year of watch the movie */
    struct movie *prev; /* Link to previous node */
    struct movie *next; /* Link to next node */
};

struct movie_head{
    struct movie *first;
    struct movie *last;
};

struct director{
    int id; /* ID of the director */
    char *name; /* Director name */
    struct director *next; /* Link to previous node */
    struct director *prev; /* Link to next node */
};

struct director_head{
    struct director *first;
    struct director *last;
};

int main(){
    int option, i, flag, flag2=0;
    MHD *mph;
    DHD *dph;
    MOV **ARR = NULL;

    dph=make_director_head();
    mph=make_movie_head();
    add_director_to_list("struct-data2-win.txt",dph,SEP);
    add_movie_to_list("struct-data-win.txt",mph,SEP,dph);

    do{
        puts("| FILE CABINET |\n");
        menu();
        scanf("%i", &option);

        i = count_of_lines("struct-data-win.txt");
        ARR = (MOV**)malloc(i*sizeof(MOV*));
        read_to_array(ARR, i, mph);

        switch(option){
            case 0:{
                puts("\nYour selection is EXIT\n");
                getchar();
                break;
            }
            case 1:{
                puts("\nYour selection is SHOW THE REFERENCE\n");
                puts("----REFERENCE-----");
                puts("This program is a file cabinet. Performs the functions presented in the menu. \nFilms have been selected as the subject area. \nDesignations: name - the name of the film,\n director - the director of the film, year - the year of the film's release, \nduration - the duration of the films in minutes, kpr - rating of the film on kinopoisk,\n plr - rating of the film in my opinion, \ndate - the date of viewing the film.");
                getchar();
                break;
            }
            case 2:{
                puts("\nYour selection is SHOW THE MOVIE DATA\n");
                getchar();
                output_movie(mph,0);
                break;
            }
            case 3:{
                puts("\nYour selection is ADD THE DATA\n");
                add_Record_to_file("struct-data-win.txt", mph, SEP, dph);
                getchar();

                break;
            }
            case 4:{
                puts("\nYour selection is REDACT THE INFORMATION\n");
                edit_Record(mph, dph, i);
                flag2 = 1;
                getchar();
                break;
            }
            case 5:{
                puts("\nYour selection is DELETE THE DATA IN DIRECTOR LIST\n");
                delete_by_number(dph, mph);
                flag2 = 1;
                getchar();
                break;
            }
            case 6:{
                puts("\nYour selection is FIND IN NAME\n");
                getchar();
                find_by_ch(ARR,find_name,i, mph);
                break;
            }
            case 7:{
                puts("\nYour selection is FIND IN DIRECTOR\n");
                getchar();
                find_by_dir(ARR,find_director,i, dph);
                break;
            }
            case 8:{
                puts("\nYour selection is SORT DIRECTOR LIST IN A-Z DIRECION\n");
                getchar();
                sort_director_list(dph, 0, mph, i);
                flag2 = 1;
                break;
            }
            case 9:{
                puts("\nYour selection is SORT DIRECTOR LIST IN Z-A DIRECTION\n");
                getchar();
                sort_director_list(dph,1, mph, i);
                flag2 = 1;
                break;
            }
            case 10:{
                puts("\nYour selection is EDIT NEW DIRECTOR\n");
                getchar();
                edit_director(dph, mph);
                break;
            }
            default:{
                puts("\nIncorrect key");
                getchar();
            }
        }
        puts("\nPress ENTER to continue");
        getchar();
        clear_screen();
    }while(option!=0);
    printf("\nDo you want to save all changes to the file?(Print 1(yes) or 0(no)): ");
    scanf("%d", &flag);
    if (flag == 1){
        if (flag2 == 1){
            save_database_changes("struct-data-win.txt", "struct-data2-win.txt", mph, dph, SEP);
        }else{
            puts("You didn't any changes.");
        }
    }else{
        puts("Changes don't saved. Thank you for use this program! Goodbye!");
    }
    return 0;
}

void clear_screen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE REFERENCE");
    puts("2 - for SHOW THE MOVIE DATA");
    puts("3 - for ADD THE INFORMATION");
    puts("4 - for REDACT THE INFORMATION");
    puts("5 - for DELETE THE DATA IN DIRECTOR LIST");
    puts("6 - for FIND IN NAME");
    puts("7 - for FIND IN DIRECTOR");
    puts("8 - for SORT LIST IN A-Z DIRECION");
    puts("9 - for SORT LIST IN Z-A DIRECTION");
    puts("10 - for EDIT A NEW DIRECTOR OR REDACT");
    printf("Enter the option: ");
}

void save_database_changes(char *Record_filename, char *director_filename, MHD *mph, DHD *dph, char sep) {
    FILE *Record_file = fopen(Record_filename, "w");
    FILE *director_file = fopen(director_filename, "w");
    MOV *current_Record = mph->first;
    DIR *current_director = dph->first;
    if (Record_file == NULL || director_file == NULL) {
        printf("Error opening files for writing.\n");
    }
    do {
        fprintf(Record_file, "%d;%s;%d;%d;%d;%.3f;%.3f;%d;%d;%d\n",
            current_Record->id,  current_Record->name,  current_Record->director->id,
            current_Record->year,  current_Record->duration,  current_Record->kpr,
             current_Record->plr,  current_Record->date[0],  current_Record->date[1],
             current_Record->date[2]);
        current_Record = current_Record->next;
    }while (current_Record != mph->first);
    do {
        fprintf(director_file, "%d%c%s\n", current_director->id, sep, current_director->name);
        current_director = current_director->next;
    }while (current_director != dph->first);
    fclose(Record_file);
    fclose(director_file);
    printf("Changes saved successfully.\n");
}

void add_Record_to_file(char *filebrand, MHD *mph, char sep, DHD *dph){
    int id_mov=1, id, year, duration, date[3];
    float plr, kpr;
    MOV *current;
    char name[100];
    FILE *file = fopen(filebrand, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
    }
    if (mph->last != NULL) {
        id_mov = mph->last->id + 1;
    }
    printf("Enter name of movie: ");
    getchar();
    new_gets(name, MAXLEN);
    /*add a new director to the list or select an existing one*/
    printf("Director ID which are in the database:\n");
    output_director(dph,1);
    printf("Enter -1 to add a new model or select existing director ID: ");
    scanf("%d", &id);
    if(id==-1){
        id = add_Director_to_file("struct-data2-win.txt", dph);
    }
    /*------------------------------------------------------------------*/
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter duration: ");
    scanf("%d", &duration);
    printf("Enter kpr: ");
    scanf("%f", &kpr);
    printf("Enter plr: ");
    scanf("%f", &plr);
    printf("Enter date (3 integers separated by spaces): ");
    scanf("%d %d %d", &date[0], &date[1], &date[2]);
    /*write to file*/
    fprintf(file, "%d;%s;%d;%d;%d;%.3f;%.3f;%d;%d;%d\n", id_mov,  name,  id,  year,  duration,  kpr,  plr, date[0], date[1], date[2]);
    current = create_movie(id_mov, name, id, year, duration, kpr, plr, date, dph);
    add_movie(mph, current, mph->last);
    fclose(file);
    printf("Data added successfully.\n");
}

int add_Director_to_file(char *filedirector, DHD *dph) {
    int id;
    char director[100];
    FILE *file = fopen(filedirector, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
    }
    printf("Enter director name: ");
    scanf("%s", director);

    if (dph->last != NULL) {
        id = dph->last->id + 1;
    } else {
        id = 1;
    }

    fprintf(file, "%d;%s\n", id, director);
    fclose(file);
    printf("Director added successfully.\n");
    return id;
}


void edit_Record(MHD *mph, DHD *dph, int n) {
    char new_movie[100];
    int new_director_id, id_to_edit, edit_line_option=1,record_found = 0;
    MOV *current_Record = mph->first;

    output_movie(mph, 0);
    do{
    printf("Enter the ID of the record you want to edit: ");
    scanf("%d", &id_to_edit);
    getchar();
    if(isalpha(id_to_edit) || id_to_edit < 0 || id_to_edit >= n){
        puts("Incorrect ID, please, try again.");
    }
    }while(isalpha(id_to_edit) || id_to_edit < 0 || id_to_edit >= n);
    if(current_Record != NULL){
    do{
        if (current_Record->id == id_to_edit) {
            record_found = 1;
            puts("Select an option to edit line:");
            puts("1 - Edit movie");
            puts("2 - Edit director");
            puts("3 - Edit year");
            puts("4 - Edit duration");
            puts("5 - Edit kpr");
            puts("6 - Edit plr");
            puts("7 - Edit date");
            puts("8 - Edit all line");
            puts("0 - to exit");
            printf("Enter option: ");
            scanf("%i", &edit_line_option);
            getchar();

            switch (edit_line_option) {
                case 1:
                    printf("Enter new movie: ");
                    fgets(new_movie, 100, stdin);
                    new_movie[strcspn(new_movie, "\n")] = 0;
                    strcpy(current_Record->name, new_movie);
                    break;
                case 2:
                    output_director(dph, 1);
                    printf("Enter new director ID: ");
                    scanf("%d", &new_director_id);
                    getchar();
                    current_Record->director = find_dir(dph, new_director_id);
                    break;
                case 3:
                    printf("Enter new year: ");
                    scanf("%d", &(current_Record->year));
                    getchar();
                    break;
                case 4:
                    printf("Enter new duration: ");
                    scanf("%d", &(current_Record->duration));
                    getchar();
                    break;
                case 5:
                    printf("Enter new kpr: ");
                    scanf("%f", &(current_Record->kpr));
                    getchar();
                    break;
                case 6:
                    printf("Enter new plr: ");
                    scanf("%f", &(current_Record->plr));
                    getchar();
                    break;
                case 7:
                    printf("Enter new date (3 integers separated by spaces): ");
                    scanf("%d %d %d", &(current_Record->date[0]), &(current_Record->date[1]), &(current_Record->date[2]));
                    getchar();
                    break;
                case 8:
                    printf("Enter new movie: ");
                    fgets(new_movie, 100, stdin);
                    new_movie[strcspn(new_movie, "\n")] = 0;
                    strcpy(current_Record->name, new_movie);
                    output_director(dph, 0);
                    printf("Enter new director ID: ");
                    scanf("%d", &new_director_id);
                    getchar();
                    current_Record->director = find_dir(dph, new_director_id);
                    printf("Enter new year: ");
                    scanf("%d", &(current_Record->year));
                    getchar();
                    printf("Enter new duration: ");
                    scanf("%d", &(current_Record->duration));
                    getchar();
                    printf("Enter new kpr: ");
                    scanf("%f", &(current_Record->kpr));
                    getchar();
                    printf("Enter new plr: ");
                    scanf("%f", &(current_Record->plr));
                    getchar();
                    printf("Enter new date (3 integers separated by spaces): ");
                    scanf("%d %d %d", &(current_Record->date[0]), &(current_Record->date[1]), &(current_Record->date[2]));
                    getchar();
                    break;
                case 0:{
                    puts("\nYour selection is EXIT");
                    puts("\nPress Enter\n");
                    break;
                }
                default:
                    puts("Invalid option");
            }
            printf("Record updated successfully.\n");
        }
        current_Record = current_Record->next;
    }while (current_Record != NULL && edit_line_option != 0);

    if (!record_found) {
        printf("Record with ID %d not found.\n", id_to_edit);
    }
    } else{
        perror("List ERROR");
    }
}

void edit_director(DHD *dph, MHD *mph) {
    DIR *current_director = dph->first, *new_node;
    MOV *node;
    int id_to_edit, director_found = 0, flag, flag2, exit, year, duration, date[3];
    float kpr, plr;
    char name[MAXLEN], line[MAXLEN];
    output_director(dph,1);
    do{
    printf("\nYou want to edit a director or add new?(Enter 1(edit) or 2(add)): ");
    scanf("%d", &flag);
    if (flag == 1){
    printf("Enter the ID of the director you want to edit: ");
    scanf("%d", &id_to_edit);
    getchar();
    do{
        if (current_director->id == id_to_edit) {
            director_found = 1;
            printf("Enter new director name: ");
            fgets(current_director->name, 100, stdin);
            current_director->name[strcspn(current_director->name, "\n")] = 0;

            printf("Model updated successfully.\n");
        }
        current_director = current_director->next;
    }while (current_director != dph->first);
    if (!director_found) {
        printf("Model with ID %d not found.\n", id_to_edit);
    }
    exit = 1;
    puts("Edit director succesfull");
    output_director(dph, 1);
    }else if(flag == 2){
        while(strlen(line) <= 3 ){
            printf("\nPrint new name of director: ");
            new_gets(line, MAXLEN);
            new_gets(line, MAXLEN);
        }
        new_node = create_director(dph->last->id+1, line);
        add_director(dph, new_node);
        exit = 1;
        puts("Add new director succesfull");
        output_director(dph, 1);
        printf("\nDo you want to add information to this new director?\n You don't see information if it will have nothing(Yes(1) or No(0)): ");
        scanf("%d", &flag2);
        if (flag2 == 1){
            printf("\nEnter the name: ");
            new_gets(name, MAXLEN);
            new_gets(name, MAXLEN);
            printf("Enter the year: ");
            scanf("%d", &year);
            printf("Enter the duration: ");
            scanf("%d", &duration);
            printf("Enter the kpr: ");
            scanf("%f", &kpr);
            printf("Enter the plr: ");
            scanf("%f", &plr);
            printf("Enter the day of see the movie: ");
            scanf("%d", &date[0]);
            printf("Enter the month of see the movie: ");
            scanf("%d", &date[1]);
            printf("Enter the year of see the movie: ");
            scanf("%d", &date[2]);

            node = create_movie(mph->last->id+1, name, new_node->id, year, duration, kpr, plr, date, dph);
            add_movie(mph, node, mph->last);
            output_movie(mph, 0);
            getchar();
        }else if(flag2 == 0){
            puts("Information didn't add.");
        }else{
            puts("Incorrect number");
        }
    }else{
        puts("Incorrect key, try again");
    }

    }while(exit != 1);
}


MHD *make_movie_head(){
    MHD *ph=NULL; /* Define and init Head */
    ph=(MHD*)malloc(sizeof(MHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}

DHD *make_director_head(){
    DHD *ph=NULL; /* Define and init Head */
    ph=(DHD*)malloc(sizeof(DHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}

void output_director(DHD *dph, int n) {
    DIR *current=dph->first;
    print_head(n);

    do {
        printf("| %2d | %25s |\n", current->id, current->name);
        current = current->next;
    } while (current != dph->first);
}

int swap_director(DHD *dph, DIR *current){
    DIR *temp=current->next;

    current->prev->next = temp;
    temp->next->prev = current;
    current->next = temp->next;
    temp->prev = current->prev;
    temp->next = current;
    current->prev = temp;

    if (dph->first == current) { /* If current was first element of head -> change head pointer to changed element */
        dph->first = temp;
    }
    return 1;
}

void sort_director_list(DHD *dph, int direction, MHD *mph, int j) {
    int swapped, i;
    DIR *current = NULL;
    MOV *current2 = NULL;

    puts("Original list:");
    output_movie(mph, 0);
    if (dph == NULL){
        printf("The list is empty");
    } else {
        do {
            swapped = 0;
            current = dph->first;

            while (current->next != dph->first) {
                if (direction==0 && strcmp(current->name, current->next->name) > 0){
                    swapped = swap_director(dph,current);
                } else if (direction==1 && strcmp(current->name, current->next->name) < 0) {
                    swapped = swap_director(dph,current);
                } else {
                    current = current->next;
                }
            }
        } while (swapped == 1);
    }
    puts("\n");
    if (dph != NULL && mph != NULL){
        current = dph->first;
        print_head(0);
        do{
            current2 = mph->first;
            for(i=0; i < j; i++){
                if(current2->director->name == current->name){
                    printf("| %2d | %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%d |\n", current2->id, current2->name, current2->director->name, current2->year, current2->duration, current2->kpr, current2->plr, current2->date[0], current2->date[1], current2->date[2]);
                }
                current2 = current2->next;
            }
            current = current->next;
        }while(current != dph->first);
        print_tail(0);
    }else{
        perror("List build ERROR!");
    }
    printf("The director list was sorted\n");
}

char* find_name(MOV *ARR[], int i)
{
    return ARR[i]->name;
}
/*-------------------------------------------*/
DIR* find_director(MOV *ARR[], int i)
{
    return ARR[i]->director;
}


/*-------------------------------------------*/
void find_by_dir(MOV *ARR[], DIR *(*func_name)(MOV**, int), int n, DHD *dph)
{
    int i, count=0, id;
    output_director(dph, 1);
    do{
    printf("Enter the id: ");
    scanf("%d", &id);
    if (id < 0){
        puts("Try again! Incorrect number.");
    }
    }while(id < 0);
    for(i=0; i<n; i++)
    {
        if(id == ARR[i]->director->id){
            count++;
            if (count == 1){
            print_head(0);
            }
            printf("| %2d | %25s | %25s | %d | %d | %5.1f | %5.1f | %.2d.%.2d.%.2d |\n",ARR[i]->director->id, ARR[i]->name, ARR[i]->director->name, ARR[i]->year, ARR[i]->duration, ARR[i]->kpr, ARR[i]->plr, ARR[i]->date[0], ARR[i]->date[1], ARR[i]->date[2]);

        }
    }
    if(count==0){
            printf("\nThere is no name that begins with the entered substring\n");
    }else{
        print_tail(0);
    }
    getchar();
}

void find_by_ch(MOV *ARR[], char *(*func_name)(MOV**, int), int n, MHD *mph)
{
    int i, count=0;
    char substring[MAXLEN], *result;
    output_movie(mph, 0);
    do{
    printf("Enter the substring: ");
    new_gets(substring,MAXLEN);
    if (substring == NULL){
        puts("String are emty. Try again!");
    }
    }while(substring == NULL);
    for(i=0; i<n; i++)
    {
        result = strstr(func_name(ARR, i), substring);
        if(result!=NULL)
        {
            count++;
            if(count==1) print_head(0);
            printf("| %2d | %25s | %25s | %d | %d | %5.1f | %5.1f | %.2d.%.2d.%.2d |\n",i , ARR[i]->name, ARR[i]->director->name, ARR[i]->year, ARR[i]->duration, ARR[i]->kpr, ARR[i]->plr, ARR[i]->date[0], ARR[i]->date[1], ARR[i]->date[2]);
        }
    }
    if(count==0) printf("\nThere is no name that begins with the entered substring\n");
}

int count_of_lines(char *filename)
{
    char line[MAXLEN];
    int n=0;

    FILE *file = fopen(filename, "r");

    if (file!=NULL)
    {
        while((fgets(line,MAXLEN,file))!=NULL) n++;
        rewind(file);
    }
    else
    {
        printf("Error opening the file.\n");
    }
    return n;
}

void add_director_to_list(char *filename, DHD *dph, char sep){
    char line[MAXLEN], *words[2];
    int wordCount, i;
    DIR *new_director;
    FILE *file = fopen(filename, "r");
    if (file == NULL) printf("Error opening file.\n");

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);

        if (wordCount == 2){
            int id = atoi(words[0]);
            char *name = words[1];

            new_director = create_director(id, name);
            add_director(dph, new_director);
        }
        else {
                printf("Invalid number of attributes in line: %s\n", line);
        }

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}

void add_movie_to_list(char *filename, MHD *mph, char sep, DHD *dph){
    char line[MAXLEN], *words[10];
    int wordCount, date[3], i;
    MOV *new_movie;
    FILE *file = fopen(filename, "r");
    if (file == NULL) printf("Error opening file.\n");

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);

        if (wordCount == 10){
            int id_mov = atoi(words[0]);
            char *name = words[1];
            int id = atoi(words[2]);
            int year = atoi(words[3]);
            int duration = atoi(words[4]);
            float kpr = atof(words[5]);
            float plr = atof(words[6]);
            date[0] = atoi(words[7]);
            date[1] = atoi(words[8]);
            date[2] = atoi(words[9]);

            new_movie = create_movie(id_mov, name, id, year, duration, kpr, plr, date, dph);
            add_movie(mph, new_movie, mph->last);
        }
        else printf("Invalid number of attributes in line: %s\n", line);

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }

    fclose(file);
}

void read_to_array(MOV** mov, int n, MHD *head){
    MOV *p;
    int i;
    p = (MOV*)malloc(sizeof(MOV));
    if (head != NULL){
        p = head->first;
        for(i = 0; i < n; i++){
            mov[i] = (MOV*)malloc(sizeof(MOV));
            mov[i]->name = p->name;
            mov[i]->director = p->director;
            mov[i]->year = p->year;
            mov[i]->duration = p->duration;
            mov[i]->kpr = p->kpr;
            mov[i]->plr = p->plr;
            mov[i]->date[0] = p->date[0];
            mov[i]->date[1] = p->date[1];
            mov[i]->date[2] = p->date[2];
            mov[i]->next = NULL;
            mov[i]->prev = NULL;
            p = p->next;
        }
    }else{
        perror("List Head ERROR!");
    }
}

void output_movie(MHD *mph, int n) {
    MOV *current;
    current = mph->first;
    print_head(n);
    if(current != NULL){
    do {
        if(current->director!=NULL){
            printf("| %2d | %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%d |\n", current->id, current->name, current->director->name, current->year, current->duration, current->kpr, current->plr, current->date[0], current->date[1], current->date[2]);
            current = current->next;
        }
    }while (current!=mph->first);
    }else{
    perror("List Head ERROR!");
    }
   print_tail(n);
}

void new_gets(char s[], int lim){
    char c;
    int i=0;
    while(((c=getchar())!='\n')&&(i<lim-1))
    {
        s[i]=c;
        i++;
    }
    s[i]='\0';
}

void print_head(int n){
    if(n==0){
        printf("| %2s | %25s | %25s | %4s | %3s | %5s | %5s | %10s |\n","ID","Name","Director","Year","Dur","KPR","PLR","Watchdate");
        printf("+----+---------------------------+---------------------------+------+-----+-------+-------+------------+\n");
    } else {
        printf("| %2s | %25s |\n","ID","Director");
        printf("+----+---------------------------+\n");
    }
}

void print_tail(int n){
    if(n==0){
        printf("+----+---------------------------+---------------------------+------+-----+-------+-------+------------+\n");
    } else {
        printf("+----+---------------------------+\n");
    }
}
void split_string(char *inputString, char **words, int *wordCount, char delimiter) {
    int wordIndex = 0, wordStart=0, wordLength=0, inWord=0, i;

    for (i = 0; i <= strlen(inputString); i++) {
        if ((inputString[i] == delimiter || inputString[i] == '\0')&&(inWord==1)) {
            words[wordIndex] = (char *)malloc(wordLength + 1);
            strncpy(words[wordIndex], inputString + wordStart, wordLength);
            words[wordIndex][wordLength] = '\0';
            wordIndex++;
            inWord = 0;
        } else {
            if (inWord==0) {
                wordStart = i;
                wordLength = 1;
                inWord = 1;
            } else {
                wordLength++;
            }
        }
    }
    *wordCount = wordIndex;
    for (i = 0; i < *wordCount; i++) {
        int len = strlen(words[i]);
        if (words[i][len - 1] == '\r') {
            words[i][len - 1] = '\0';
        }
    }
}

DIR *create_director(int id, char *movie_director){
    DIR *new_director = NULL; /* Pointer to new node */
    char *director = NULL;

    new_director = (DIR*)malloc(sizeof(DIR));
    director = (char*)malloc((strlen(movie_director) + 1) * sizeof(char));

    if (new_director && director){ /* Data is not empty */
        new_director->id = id;
        new_director->name = director;
        memcpy(director, movie_director, strlen(movie_director) + 1);
        new_director->prev = NULL;
        new_director->next = NULL;
        director[strlen(movie_director)] = '\0';
    }
    return new_director; /* return adress of node */
}

void add_director(DHD *dph, DIR *new_node){
    if (dph && new_node) {
        if (dph->first == NULL) { /* Add first node of list */
            dph->first = new_node;
            new_node->prev = new_node;
            new_node->next = new_node;
            dph->last = dph->first->prev;
        } else {
            new_node->prev = dph->first->prev;
            new_node->next = dph->first;
            dph->first->prev->next = new_node;
            dph->first->prev = new_node;
            dph->last = dph->first->prev;
        }
    }
}

MOV *create_movie(int id_mov, char *movie_name, int id, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3], DHD *dph){
    MOV *new_movie = NULL; /* Pointer to new node */
    DIR *movie_director = NULL; /* Pointer to director of movie */
    char *name = NULL;
    new_movie = (MOV*)malloc(sizeof(MOV));
    name = (char*)malloc((strlen(movie_name) + 1) * sizeof(char));
    movie_director = (DIR *)malloc(sizeof(DIR));

    movie_director=find_dir(dph, id);

    if (new_movie && name) { /* Data is not empty */
        new_movie->id = id_mov;
        new_movie->name = name;
        new_movie->director = movie_director;
        new_movie->year = movie_year;
        new_movie->duration = movie_duration;
        new_movie->kpr = movie_kpr;
        new_movie->plr = movie_plr;
        memcpy(name, movie_name, strlen(movie_name) + 1);
        memcpy(new_movie->date, watch_date, sizeof(new_movie->date));
        new_movie->next = NULL;
        new_movie->prev = NULL;
    }

    return new_movie; /* Return adress of node */
}

DIR *find_dir(DHD *dph, int id){
    DIR *current = NULL;
    int flag=0;
    current = dph->first;

    while(current!=NULL && flag==0){
        if(current->id==id){
            flag=1;
        } else current=current->next;
    }
    return current;
}

void add_movie(MHD *ph, MOV *new_node, MOV *current_node){
    if (ph && new_node) {
        if (current_node == NULL) { /* Add first node of list */
            ph->first = new_node;
            ph->last = new_node;
            new_node->prev = NULL;
            new_node->next = NULL;
        } else {
            current_node->next = new_node;
            new_node->prev = current_node;
            new_node->next = ph->first;
            ph->last = new_node;
        }
    }
}

void delete_by_number(DHD *dph, MHD *mph){
    DIR *current=NULL;
    int number=0, flag;
    current=dph->last;
    output_director(dph, 1);
    do{
    printf("\nEnter the id of element that you want to delete (The element number is set from the end of the list): ");
    scanf("%d", &number);
    if(number < 0){
            puts("Incorrect key, try again!");
    }
    }while(number < 0);

    if(current!=NULL){
        while(current->id != number && current!=NULL){
            current = current->prev;
        }

        if(current==NULL) current=dph->first;
        if (current->id == number){
        printf("\nIf you delete the element from directors, all elements with this name will be delete!\n1(Yes) or '0' or another digit(No): ");
        scanf("%d", &flag);
        if(flag == 1){
        delete_director(dph,mph,current);
        mph->last->next = mph->first;
        dph->last->prev->next = dph->first;
        printf("\nThe element from director list was deleted\n");
        output_movie(mph, 0);
        }else{
            puts("Element didn't delete");
        }
        }else{
            puts("\nDidn't search element with this id");
        }

    } else printf("The Director List is empty");
}

void delete_director(DHD *dph, MHD *mph, DIR *current_director) {
    MOV *current_movie = mph->first;
    MOV *next_movie = NULL;
    do {
        next_movie = current_movie->next;
        if (current_movie->director == current_director) {
            delete_movie(mph, current_movie);
        }
        current_movie = next_movie;
    }while (current_movie != mph->last);
        if (!strcmp(current_movie->director->name, current_director->name)) {
            delete_movie(mph, current_movie);
        }
    if (current_director == dph->first) {
        dph->first = current_director->next;
        if (dph->first) {
            dph->first->prev = dph->last;
        } else {
            dph->last = NULL;
        }
    } else if (current_director== dph->last) {
        dph->last = current_director->prev;
        if (dph->last) {
            dph->last->next = dph->first;
        } else {
            dph->first = NULL;
        }
    } else {
        current_director->prev->next = current_director->next;
        current_director->next->prev = current_director->prev;
    }

    current_director->next = NULL;
    current_director->prev = NULL;

    free(current_director);
}

void delete_movie(MHD *mph, MOV *current_movie) {
    if (current_movie == mph->first) { /* If deleted node is the first in the list */
        mph->first = current_movie->next;
                printf("%s", current_movie->name);
        if (mph->first) {
            mph->first->prev = mph->last;
        } else { /* If deleted node is alone in the list */
            mph->last = NULL;
        }
    } else if (current_movie == mph->last) { /* If deleted node is the last in the list */
        mph->last = current_movie->prev;
        printf("%s", current_movie->name);
        if (mph->last) {
            mph->last->next = mph->first;
            mph->first->prev = mph->last;
        } else { /* If deleted node is alone in the list */
            mph->first = NULL;
        }
    } else { /* If deleted node not first or last of the list */
        printf("%s", current_movie->name);
        current_movie->prev->next = current_movie->next;
        current_movie->next->prev = current_movie->prev;
    }
    current_movie->next = NULL;
    current_movie->prev = NULL;
    free(current_movie);
}
