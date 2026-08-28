#include <ncurses.h>
#include <stdio.h>
#include "history.h"
#include <time.h>
#include <stdlib.h>

double race_times[MAX_RACES];
char race_dates[MAX_RACES][11];
char race_hours[MAX_RACES][6];
int race_count = 0;

void save_race_time(double race_time)
{
    time_t agora = time(NULL);
    struct tm *data_hora = localtime(&agora);
    
    if (race_count < MAX_RACES)
    {
        race_times[race_count] = race_time;

        strftime(race_dates[race_count], 11, "%d/%m/%Y", data_hora);
        strftime(race_hours[race_count], 6, "%H:%M", data_hora);

        race_count++;
    }

    FILE *ficheiro = fopen("historico.txt", "a");
    // "a" -> append

    if (ficheiro != NULL)
    {
        fprintf(ficheiro, "%02d/%02d/%04d;%02d:%02d;%.2f\n",
                data_hora->tm_mday,
                data_hora->tm_mon + 1,
                data_hora->tm_year + 1900,
                data_hora->tm_hour,
                data_hora->tm_min,
                race_time);
        
        fclose(ficheiro);
    }
}

void draw_history(void)
{
    clear();
    
    mvprintw(2, 10, "HISTÓRICO DE CORRIDAS");

    draw_history_recursive(0);

    refresh();
}

void draw_history_recursive(int indice)
{
    if (indice >= race_count)
    {
        return;
    }    
    mvprintw(4 + indice, 10, 
            "Corrida %d | %s | %s | %.2f s",
            indice + 1,
            race_dates[indice],
            race_hours[indice],
            race_times[indice] / 1000.0);

    draw_history_recursive(indice + 1);
}

void load_history()
{
    FILE *ficheiro = fopen("historico.txt", "r");
    // "r" -> abre o ficheiro para leitura

    if (ficheiro == NULL)
    {
        return;
    }

    char tempo_texto[30];

    while (race_count < MAX_RACES &&
            fscanf(ficheiro, "%10[^;];%5[^;];%29[^\n]",
                race_dates[race_count],
                race_hours[race_count],
                tempo_texto) == 3)
            // fscanf -> lê valores de ficheiro
    {
        for (int i = 0; tempo_texto[i] != '\0'; i++)
        {
            if (tempo_texto[i] == ',')
            {
                tempo_texto[i] = '.';
            }
        }
        race_times[race_count] = atof(tempo_texto);

        race_count++;
    }

    fclose(ficheiro);
}
