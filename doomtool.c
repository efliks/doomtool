/*****************************************
  DoomTool

  doomtool.c   FPS computation for Doom

  (C) 2023  M. Feliks
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gitver.h"

void get_token(char* row, char* strtics)
{
    char* p = strtok(row, " ");
    int i = 0;

    while(p != NULL) {
        //printf("%s\n", p);
        p = strtok(NULL, " ");
        i += 1;
        if (i == 4) {
            strcpy(strtics, p);
        }
    }
}

int get_realtics(char* resultfile)
{
    FILE* fp;
    char row[80];
    char strtics[16];
    int realtics;
    int is_found = 0;

    fp = fopen(resultfile, "r");
    if (!fp) {
        return 0;
    }

    while(fgets(row, 80, fp)) {
        if (strncmp(row, "timed ", sizeof ("timed ") - 1) == 0) {
            get_token(row, strtics);
            is_found = 1;
        }
    }
    fclose(fp);

    if (!is_found) {
        return 0;
    }

    realtics = atoi(strtics);
    if (realtics == 0) {
        // probably error
    }

    return realtics;
}

int get_realtics_wrapper(char* resultfile)
{
    int errorcode;

    errorcode = get_realtics(resultfile);
    if (errorcode == 0) {
        printf("I have trouble finding realtics.\n");
    }

    return errorcode;
}

int launch_doom(int argc, char* argv[], char* tempfile)
{
    int i, exitcode;
    char row[80];

    if (argc < 2) {
        return 1;
    }

    strcpy(row, argv[1]);
    for (i = 2; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            break;
        }
        strcat(row, " ");
        strcat(row, argv[i]);
    }
    strcat(row, " > ");
    strcat(row, tempfile);

    exitcode = system(row);

    return exitcode;
}

int launch_doom_wrapper(int argc, char* argv[], char* tempfile)
{
    int errorcode;

    errorcode = launch_doom(argc, argv, tempfile);
    if (errorcode != 0) {
        printf("I cannot run Doom, sorry.\n");
    }

    return errorcode;
}

int create_tempfile(char* tempfile)
{
    unsigned int left, right;
    char buff[13];
    FILE* fp;

    srand((unsigned int)time(NULL));

    left = rand() % 9999;
    right = rand() % 9999;

    sprintf(buff, "%04d", left);
    strcpy(tempfile, buff);
    sprintf(buff, "%04d", right);
    strcat(tempfile, buff);

    strcat(tempfile, ".txt");

    fp = fopen(tempfile, "w");
    if (!fp) {
        printf("I cannot create a temporary file.\n");
        return 1;
    }
    fclose(fp);

    return 0;
}

void destroy_tempfile(char* tempfile)
{
    FILE* fp = fopen(tempfile, "r");

    // check if file exists
    if (fp) {
        fclose(fp);
        remove(tempfile);
    }
}

void compute_fps(int realtics)
{
    double fps;
    char strfps[16], row[80];

    fps = 74960. / (double)realtics;
    sprintf(strfps, "%f", fps);

    strcpy(row, "Your FPS is: ");
    strcat(row, strfps);
    strcat(row, "\n");
    printf(row);
}

int main(int argc, char* argv[])
{
    int exitcode, realtics;
    char tempfile[13];

    printf("** doomtool %s by efliks **\n", GIT_VERSION);

    exitcode = create_tempfile(tempfile);
    if (exitcode == 0) {
        exitcode = launch_doom_wrapper(argc, argv, tempfile);
        if (exitcode == 0) {
            realtics = get_realtics_wrapper(tempfile);
            if (realtics > 0) {
                compute_fps(realtics);
            }
        }
    }

    destroy_tempfile(tempfile);

    return exitcode;
}
