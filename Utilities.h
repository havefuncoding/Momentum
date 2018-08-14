// Builds file path 
// Inputs
// Given the target built file path: "./Images/image_2.txt"
// startpath: "./Images/image_"
// num: "2" (as integer)
// endpath: ".txt" 
// Return
// File path of the target number.
char* build_file_path(char *startpath, int num, char *endpath)
{
    char num_as_string[5];// = get_num_as_string(num);
    sprintf(num_as_string, "%d", num);

//    strcpy(num_as_string, get_num_as_string(num));    

    char *filepath = malloc(strlen(startpath) + 
                            strlen(num_as_string) + 
                            strlen(endpath) + 1); 
    strcpy(filepath, startpath);
    strcat(filepath, num_as_string);
    strcat(filepath, endpath);

    return filepath;
}


// Gets number as string
// Inputs
// num: number to cast into string
// Return
// Number value returns in string form, as char array
char* get_num_as_string(int num)
{
    int digits = 0;
    while(num != 0)
    {   
        num /= 10; 
        ++digits;
    }   

    char *num_as_string = malloc(digits + 1); 
    sprintf(num_as_string, "%d", num);
    return num_as_string;
}
