#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define Couleur_J1 "\e[45m"
#define Couleur_J2 "\e[42m"


GameState state = {.map = NULL, .size = 0};
void create_empty_game_state(GameState* state, int size) {
    // On vérifie la taille
    if (state == NULL || size <= 0) {
        fprintf(stderr, "Erreur : paramètres invalides\n");
        return;
    }
    // On initialise le terrain
    state->size = size;
    // On alloue(heap) la mémoire mémoire pour le tableau map (taille size * size), on réalise tout le jeu en une liste longue au lieu d'un tableau
    state->map = (Color*)malloc(size * size * sizeof(Color));
    if (state->map == NULL) {
        fprintf(stderr, "Erreur : allocation de mémoire échouée\n");
        state->size = 0; // Met à jour la taille pour indiquer une erreur
        return;
    }
    // On initialise les cases à EMPTY
    for (int i = 0; i < size * size; i++) {
        state->map[i] = EMPTY;
    }
}

void set_map_value (GameState* state, int x, int y, Color value){
	int size = state->size;
	state->map[x * size + y] = value;
}



Color get_map_value (GameState* state, int x, int y){
	if (state -> map == NULL || x > state -> size || y > state -> size || x < 0 || y < 0)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", state -> map, state -> size, x, y);
		return ERROR;
	}
	return state -> map[y * state -> size + x];
}
void fill_map(GameState* map){
	int size = map->size;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			int couleur= rand()%7 + 3;
			map->map[i * size+j] =couleur;
		}
	}
	map->map[0 * size+(size-1)] = PLAYER_1;
	map->map[(size-1) * size+0] = PLAYER_2;

}
int GR911_letterToNum(char Cellule){	
			if ('R' == Cellule){
				return 3;
			}
			if ('G' == Cellule){
				return 4;
			}
			if ('B' == Cellule){
				return 5;
			}
			if ('Y' == Cellule){
				return 6;
			}
			if ('M' == Cellule){
				return 7;
			}
			if ('C' == Cellule){
				return 8;
			}
			if ('W' == Cellule){
				return 9;
			}
		
	
}
void GR911_affichage(GameState* state){
	int size = state->size;
	for (int i = 0;i < size; i++){
		for ( int j = 0; j < size; j++){
			int Cellule=state->map[i * size + j];
			if (1 == Cellule){
				printf("%s ", Couleur_J1"v"ANSI_COLOR_RESET);
			}
			if (2 == Cellule){
				printf("%s ", Couleur_J2"^"ANSI_COLOR_RESET);
			}
			if (3 == Cellule){
				printf("%s ",ANSI_COLOR_RED "R" ANSI_COLOR_RESET);
			}
			if (4 == Cellule){
				printf("%s ",ANSI_COLOR_GREEN "G" ANSI_COLOR_RESET);
			}
			if (5 == Cellule){
				printf("%s ",ANSI_COLOR_BLUE "B" ANSI_COLOR_RESET);
			}
			if (6 == Cellule){
				printf("%s ",ANSI_COLOR_YELLOW "Y" ANSI_COLOR_RESET);
			}
			if (7 == Cellule){
				printf("%s ",ANSI_COLOR_MAGENTA "M" ANSI_COLOR_RESET);
			}
			if (8 == Cellule){
				printf("%s ",ANSI_COLOR_CYAN "C" ANSI_COLOR_RESET);
			}
			if (9 == Cellule){
				printf("%s ","W");
			}
		}
		printf("\n");
	}
}
int GR911_adjacent(GameState* state,int x , int y , int player){
	int size = state->size;
	 int dx[] = {-1, 1, 0, 0}; 
    int dy[] = {0, 0, -1, 1}; 

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
            if (state->map[nx * size + ny] == player) {
                return 1;
            }
        }
    }

    // Aucune case adjacente n'appartient au joueur
    return 0;
}

void GR911_updateWorld(GameState* state,char Playeed,int Player ){
	int PlayedNum = GR911_letterToNum(Playeed);

	int size = state->size;
	int ch = 1;
	while (ch ==1)
	{ 	
		ch = 0;
		for (int i = 0;i < size; i++){
		for ( int j = 0; j < size; j++){

			if(state->map[i * size+j] ==PlayedNum){
				if(GR911_adjacent(state , i, j,Player)){
					state->map[i * size+j] = Player;
					ch = 1;

				}
				
			}

		}
		
		}
	}

}
int GR911_finDuJeu(GameState* state,int Player){
	int sc = 0;
	
	int size = state->size;
	for (int i = 0;i < size; i++){
		for ( int j = 0; j < size; j++){


			if(state->map[i * size+j] ==1){
				sc = sc + 1;
			
		}
		
	}

	if(sc > (size*size/2)){
		return 1;
	}
	}
	return 0;
}


int main(int argc, char** argv){
	srand( time( NULL ) );
	GameState state;
    // Taille du terrain
    int size = 30;
    // Initialisation
    create_empty_game_state(&state, size);
    // Vérification si l'initialisation a réussi
	fill_map(&state);
    if (state.map != NULL) {
        // Affichage du terrain
       // for (int i = 0; i < size; i++) {
       //     for (int j = 0; j < size; j++) {
        //        printf("%c ", state.map[i * size + j]); // Affiche la valeur de chaque case
        //    }
        //    printf("\n");

		GR911_affichage(&state);
        
	
        // Libération de la mémoire
        free(state.map);

	
    } else {
        printf("Erreur lors de l'initialisation du terrain.\n");
    }

	


    return 0;
}

