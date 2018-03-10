#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 15

typedef struct{
	int taille;
	int arbre[MAX];
}Tas;

int estTas(int tab[], int taille){
	if(tab == NULL )
		return 1;
	int i;
	for(i=0; i<(taille/2); i++)
		if(2*i+2< taille){
			if(tab[2*i+1]<tab[i] || tab[2*i+2]<tab[i])
				return 0;
		}		
	return 1; 
}

int fils(Tas T, int indice){
	int indicefg = 2*indice+1;
	int indicefd = 2*indice+2;
	if(indicefg >= T.taille)
		return -1;
	else if(indicefd >= T.taille) 
		return indicefg;
	else if(T.arbre[indicefg] < T.arbre[indicefd])
		return indicefg:
	else
		return indicefd;
}

void change(Tas *T, int indice, int valeur){
	int indicep = (indice-1)/2;
	if(indicep >= 0 && indice < T->taille){
		T->arbre[indice]=valeur;
		if(indice > 0 && T->arbre[indice] < T->arbre[indicep]){
			T->arbre[indice] = T->arbre[indicep];
			change(T, indicep, valeur);
		}
	}
}

int Ajout(Tas *T, int valeur){
	int i;

/* la valeur est déjà présente ? */
	for(i=0; i<T->taille; i++){
		if(T->arbre[i]== valeur)
			return 0;
	}

/* problème avec la taille du tableau ? */
	if(T->taille < MAX){
		change(T, T->taille, valeur);
		T->taille++;
		return 1;
	}

		return 0;
	
}

int ExtraireMin(Tas *T){
	T->arbre[racine] = T->arbre[taille];
	taille = taille -1;
	change(T,T->taille, T->arbre[taille]);
}


int main(){
	int tab[6]={1,5,4,14,13,20};
	int result = estTas(tab,6);
	printf("%d", result);
	return 0;
}