#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include "Reference.h"
#include "Utilities.h"

// Forward declarations
static int get_random_num(int max);
static int get_count_files_in_dir(char *dirpath);
static int get_count_lines_in_file(char *filepath);
static void print_content_from_file(char *filepath);
static void print_line_from_file(char *filepath);
static void print_datetime_formatted();
static void print_fancy_line(char x, int count);

/* Un-commenting the below returns error indicating function already declared */
//char* build_file_path(const char *startpath, int num, char *endpath);
//char* get_num_as_string(int num);

int main(void) {
    print_fancy_line(FANCY_CHAR, WIDTH);

    print_content_from_file(FILEPATH_DEFAULT_PHRASE);
    print_content_from_file(FILEPATH_DEFAULT_NAME);
    print_datetime_formatted();

    print_content_from_file(build_file_path(
        STARTPATH_IMAGE, 
        get_random_num(get_count_files_in_dir(DIRPATH_IMAGES)), 
        EXT_TXT_FILE
        ));
    print_line_from_file(FILEPATH_QUOTES);
    print_fancy_line(FANCY_CHAR, WIDTH);
    return 0;
}


// Gets random number between 0 and max
// Inputs
// max: the max or ceiling within which random number is selected
// Return
// Random number between 0 and input max number
int get_random_num(int max) 
{
    int random_num; 
    srand(time(NULL));  
    random_num = rand() % max; 
    return random_num;
}


// Gets count of files in a directory
// Inputs
// dirpath: directory path
// Return
// Number of files in the directory path
int get_count_files_in_dir(char *dirpath)
{
    int file_count = 0;
    DIR * dirp; 
    struct dirent * entry;

    dirp = opendir(dirpath);
    while ((entry = readdir(dirp)) != NULL) 
        if (entry->d_type == DT_REG)
            file_count++; 
    closedir(dirp);   

    return file_count;
}


// Gets count of lines in a file
// Inputs
// filepath: file path 
// Return
// Number of lines in the file of given file path
int get_count_lines_in_file(char *filepath)
{
    int ch=0;
    int lines=0;

    FILE *fp = fopen(filepath,"r");

    // File does not exist, or something went wrong!
    if (fp == NULL)
        return 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
        }   
      fclose(fp);
      return lines;
}


// Prints content from file
// Inputs
// filepath: file path
void print_content_from_file(char *filepath)
{
    int c;
    FILE *file;
    file = fopen(filepath, "r");
    if (file) {
        printf("\n");
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
        printf("\n");
    }
}


// Prints line from file
// Inputs
// filepath: file path
void print_line_from_file(char *filepath)
{
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL)
        exit(0);

    int num_lines_in_file = get_count_lines_in_file(filepath);
    int random_line = get_random_num(num_lines_in_file);

    int count = 0;

    if (fp != NULL) {
        char line[512]; 
        while (fgets(line, sizeof line, fp) != NULL) {
            if (count == random_line) { 
                printf("\n%s ", line);
                fclose(fp);
            }
            else
                count++;
        }
        fclose(fp);
    }
    
}


// Prints datetime formatted
void print_datetime_formatted()
{
    time_t t ;
    struct tm *tmp ;
    char MY_TIME[WIDTH];
    time( &t );
    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the 
    // values that represent the 
    // corresponding local time.

    tmp = localtime( &t );

    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%x - %I:%M%p", tmp);

    printf("%31s", "");
    printf("%s\n", MY_TIME );
}


// Prints fancy line
// Inputs
// x: character to repeat
// count: number of times to repeat character
void print_fancy_line(char x, int count) {
    int i;
    printf("\n");
    for (i=0; i<count; i++)
        printf("%c", x); 
    printf("\n\n");
}


