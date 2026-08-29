#include <ncurses.h>
#include <stdio.h>
#include "history.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

double race_times[MAX_RACES];
char race_dates[MAX_RACES][11];
char race_hours[MAX_RACES][6];
int race_count = 0;
int indice_melhor = 0;
int indice_pior = 0;

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

    if (race_count > 0)
    {
        double melhor_tempo = race_times[0];
        double pior_tempo = race_times[0];
        
        indice_melhor = 0;
        indice_pior = 0;

        for (int i = 1; i < race_count; i++)
        {
            if (race_times[i] < melhor_tempo)
            {
                melhor_tempo = race_times[i];
                indice_melhor = i;
            }

            if (race_times[i] > pior_tempo)
            {
                pior_tempo = race_times[i];
                indice_pior = i;
            }
        }
    draw_history_recursive(0);

    attron(COLOR_PAIR(4));
    mvprintw(16, 10, "Melhor tempo: %.2f s", melhor_tempo / 1000.0);
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(3));
    mvprintw(17, 10, "Tempo mais lento: %.2f s", pior_tempo / 1000.0);
    attroff(COLOR_PAIR(3));
    }

    refresh();
}

void draw_history_recursive(int indice)
{
    if (indice >= race_count)
    {
        return;
    }    

    if (race_count > 1 && indice == indice_melhor)
    {
        attron(COLOR_PAIR(4));
    }
    else if (race_count > 1 && indice == indice_pior)
    {
        attron(COLOR_PAIR(3));
    }
    else
    {
        attron(COLOR_PAIR(2));
    }

    mvprintw(4 + indice, 10, 
            "Corrida %d | %s | %s | %.2f s",
            indice + 1,
            race_dates[indice],
            race_hours[indice],
            race_times[indice] / 1000.0);

    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));

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

    while (1)
    {
        char data[11];
        char hora[6];

        if (fscanf(ficheiro, " %10[^;];%5[^;];%29[^\n]",
            // fscanf -> lê valores de ficheiro
            data,
            hora,
            tempo_texto) != 3)
        {
            break;
        }

        double tempo = atof(tempo_texto);

        if (race_count < MAX_RACES)
        {
            /* Ainda há espaço no histórico */
            snprintf(race_dates[race_count], 11, "%s", data);
            snprintf(race_hours[race_count], 6, "%s", hora);
            race_times[race_count] = tempo;

            race_count++;
        }
        else
        {
            /* Deslocar as corridas para manter apenas as 10 últimas */
            for (int i = 0; i < MAX_RACES - 1; i++)
            {
                strcpy(race_dates[i], race_dates[i + 1]);
                strcpy(race_hours[i], race_hours[i + 1]);
                race_times[i] = race_times[i + 1];
            }

            /* Guardar a nova corrida na última posição */
            strcpy(race_dates[MAX_RACES - 1], data);
            strcpy(race_hours[MAX_RACES - 1], hora);
            race_times[MAX_RACES - 1] = tempo;
        }
    }

    fclose(ficheiro);
}
