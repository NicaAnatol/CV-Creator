#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <conio.h>
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_ENTER   13
#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_ESCAPE  27
#include <windows.h>
char key;
char str[100];
int current_menu_paragraph = 0;
struct MENU {
    char list[50][100];
    int amount_of_paragraph;
    char menu_name[100];
};
struct MENU MAIN_MENU = {
    .list = {"Creare CV", "Lista CV", "Stergere","Cautare"},
    .amount_of_paragraph = 4,
    .menu_name = "CV Menu"
};
struct MENU MENU_A = {
    .list = {},
    .amount_of_paragraph = 0,
    .menu_name = "CV creator"
};
struct MENU MENU_B = {
    .list = {},
    .amount_of_paragraph = 0,
    .menu_name = "Lista"
};
struct MENU MENU_C = {
    .list = {},
    .amount_of_paragraph = 0,
    .menu_name = "Stergere"
};
struct MENU MENU_D = {
    .list = {},
    .amount_of_paragraph = 0,
    .menu_name = "Cautare dupa cuvinte"
};
struct MENU *current_menu = &MAIN_MENU;

void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void print_current_menu (void) {
    system("cls");
    setConsoleColor(FOREGROUND_GREEN);
    printf("\t\t\t%s\n\n", current_menu->menu_name);
    for (int i = 0; i < current_menu->amount_of_paragraph; ++i) {
        if (i == current_menu_paragraph) {
            printf("=> ");
        }
        printf("%s\n", current_menu->list[i]);
    }
   if(current_menu==&MAIN_MENU){
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n-=Pentru a iesi apasati ESC=-\n");
   }
   if(current_menu==&MENU_A){
       int a;
       char nume[100],prenume[100],numele[100];
       FILE *fptr;
       a=0;
       printf("Pentru a continua apasati 1 in caz contar 2:");
       scanf("%d",&a);
       if (a==1){
        printf("Introduceti Numele si Prenumele:");
        scanf("%s %s",&nume,&prenume);
        strcpy(numele,nume);
        strcat(nume,"_");
        strcat(nume,prenume);
        strcat(nume,".txt");
        fptr = fopen(nume, "w");
        fprintf(fptr, "Numele/Prenume  %s  %s\n",numele,prenume);
        strcpy(MENU_B.list[MENU_B.amount_of_paragraph], nume);
        MENU_B.amount_of_paragraph++;
        printf("telefon:");
        scanf("%s",&str);
        fprintf(fptr, "telefon: %s\n",str);
        printf("sex:");
        scanf("%s",&str);
        fprintf(fptr, "sex:  %s\n",str);
        printf("email:");
        scanf("%s",&str);
        fprintf(fptr, "email: %s\n",str);
         printf("data de nastere:");
        scanf("%s",&str);
        fprintf(fptr, "data de nastere:  %s\n",str);
        printf("Abilitati (incheiati cu * separat):");
        fprintf(fptr, "Abilitati: ");
    while (1) {
        scanf("%s",str);
        if (strcmp(str,"*")==0)
            break;
            fprintf(fptr," %s",str);}
        fclose(fptr);
        strcpy(str,"A");
        listFiles(".");
        current_menu = &MAIN_MENU;
        current_menu_paragraph = 0;
        print_current_menu();
       }else if (a ==2) {
        current_menu = &MAIN_MENU;
        current_menu_paragraph = 0;
        print_current_menu();
        return;

    }

}
 if (current_menu == &MENU_B) {
            display_selected_file(MENU_B.list[current_menu_paragraph]);
}
 if (current_menu == &MENU_C) {
            if (key==KEY_ENTER){
                    setConsoleColor(FOREGROUND_RED);
       if (remove(MENU_B.list[current_menu_paragraph]) == 0) {
        printf("Filul %s Sters cu succes\n", MENU_B.list[current_menu_paragraph]);
        listFiles(".");
    } else {
        printf("Imposibil de sters file-ul: %\n", MENU_B.list[current_menu_paragraph]);
    }
}
setConsoleColor(FOREGROUND_GREEN);
}
 if (current_menu == &MENU_D) {
            DIR *dir;
    struct dirent *entry;
    FILE *file;
    char line[100];
    char filename[100];
    dir = opendir(".");
    char cuvant[100];
            printf("Introduceti cuvantul pe care il cautati (pentru a iesi tastati '*'):");

            scanf("%s",cuvant);
            if (strcmp(cuvant,"*")!=0){

 while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *dot = strrchr(entry->d_name, '.');
        if ((dot && strcmp(dot, ".o") != 0)&&(dot && strcmp(dot, ".c") != 0)&&(dot && strcmp(dot, ".exe") != 0)) {
             file = fopen(entry->d_name, "r");
      while (fscanf(file, "%s", line) == 1) {
        if (strcmp(line,cuvant)==0){
                setConsoleColor(FOREGROUND_RED);
            printf("%s\n",entry->d_name);
            break;
    }setConsoleColor(FOREGROUND_GREEN);
    }
    fclose(file);
        }}}}else{
        current_menu = &MAIN_MENU;
        current_menu_paragraph = 0;
        print_current_menu();
        }
    closedir(dir);
}
}

void display_selected_file(const char *filename) {
    FILE *file;
    char line[100];

    file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }
    printf("\nContinutul fisierului '%s':\n", filename);
    while (fgets(line, sizeof(line), file) != NULL) {
        setConsoleColor(FOREGROUND_RED);
        printf("%s", line);
    }
    setConsoleColor(FOREGROUND_GREEN);

    fclose(file);
}
void key_processing(char key) {
    if (key == KEY_DOWN) {
        current_menu_paragraph++;
        if (current_menu_paragraph >= (current_menu->amount_of_paragraph)) {
            current_menu_paragraph = current_menu->amount_of_paragraph - 1;
        }
    }
    void sort_games(struct MENU *menu) {
    int i, j;
    char temp[100];

    for (i = 0; i < menu->amount_of_paragraph - 1; i++) {
        for (j = i + 1; j < menu->amount_of_paragraph; j++) {
            if (strcmp(menu->list[i], menu->list[j]) > 0) {
                strcpy(temp, menu->list[i]);
                strcpy(menu->list[i], menu->list[j]);
                strcpy(menu->list[j], temp);
            }
        }
    }
}


if (key == KEY_ENTER) {
    if (current_menu == &MENU_B) {
        sort_games(&MENU_A);
    }
}

    if (key == KEY_UP) {
        current_menu_paragraph--;
        if (current_menu_paragraph < 0) {
            current_menu_paragraph = 0;
        }
    }

    if (key == KEY_RIGHT) {
        set_current_menu(KEY_RIGHT);
    }

    if (key == KEY_LEFT) {
        set_current_menu(KEY_LEFT);
    }
}

void listFiles(const char *folderPath) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(folderPath);
    if (dir == NULL) {
        perror("Nu s-a putut deschide directorul");
        return;
    }

    MENU_B.amount_of_paragraph=0;
    MENU_C.amount_of_paragraph=0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *dot = strrchr(entry->d_name, '.');
        if ((dot && strcmp(dot, ".o") != 0)&&(dot && strcmp(dot, ".c") != 0)&&(dot && strcmp(dot, ".exe") != 0)) {
            strcpy(MENU_B.list[MENU_B.amount_of_paragraph], entry->d_name);
            MENU_B.amount_of_paragraph++;
            strcpy(MENU_C.list[MENU_C.amount_of_paragraph], entry->d_name);
            MENU_C.amount_of_paragraph++;
        }}
    }
    closedir(dir);
}
void set_current_menu(int key) {
    if (key == KEY_RIGHT){
        if (current_menu == &MAIN_MENU && current_menu_paragraph == 0) {
            current_menu = &MENU_A;
        }

        if (current_menu == &MAIN_MENU && current_menu_paragraph == 1) {
            current_menu = &MENU_B;
        }

        if (current_menu == &MAIN_MENU && current_menu_paragraph == 2) {
            current_menu = &MENU_C;
        }
         if (current_menu == &MAIN_MENU && current_menu_paragraph == 3) {
            current_menu = &MENU_D;
        }
    }

    if (key == KEY_LEFT){
        if (current_menu == &MENU_A || current_menu == &MENU_B || current_menu == &MENU_C || current_menu == &MENU_C) {
            current_menu = &MAIN_MENU;
        }}
    current_menu_paragraph = 0;}
int main() {
    listFiles(".");
    do{
        print_current_menu();
        key = getch();
        key_processing(key);
     }while(key != KEY_ESCAPE);
    return 0;
}
