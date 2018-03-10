#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 40

typedef struct noeud{
	char lettre;
	struct noeud *frd, *frg;
	struct noeud *fils;
}Tnoeud, *Tarbre;

void allocNoeud(Tarbre *a, char l){
	Tarbre tmp;
	if((tmp = malloc(sizeof(Tnoeud))) == NULL){
		fprintf(stderr,"bonsoir, tu fais nawak\n");	
		exit(EXIT_FAILURE);
	}	
	//*a = malloc(sizeof(Tnoeud));
	//if(a!= NULL){
	tmp->lettre = l;
	tmp->frg = NULL;
	tmp->frd = NULL;
	tmp->fils = NULL;

	*a = tmp;
	//}
	
}


int recherche(Tarbre *a, char *mot){
	if((*a)== NULL){
		printf("%c\n", (*a)->lettre);
		return 0;
	}
	if((*a)->lettre == '\0' && *mot == '\0')
		return 1;	
	if(*mot == '\0')
		return 1; 
	if(*mot< (*a)->lettre)
		return recherche(&(*a)->frd, mot);
	else if(*mot> (*a)->lettre)
		return recherche(&(*a)->frg, mot);
	return recherche(&(*a)->fils, mot+1);
}


int Ajout(Tarbre *a, char *mot){
	if((*a)== NULL){
		allocNoeud(a, *mot);
		printf("%c\n", (*a)->lettre);
	}
	if((*a)->lettre == '\0')
		return 0;	
	if(*mot == '\0')
		return 1; 
	if(*mot< (*a)->lettre)
		return Ajout(&(*a)->frd, mot);
	else if(*mot> (*a)->lettre)
		return Ajout(&(*a)->frg, mot);
	return Ajout(&(*a)->fils, mot+1);
}

int nombreMot(Tarbre a){
	if(a == NULL)
		return 0;
	if(a->lettre == '\0')
		return 1;

	return nombreMot(a->fils) + nombreMot(a->frg) + nombreMot(a->frd);
	

}


void afficheChemin(Tarbre a, char *deb, int idx){
/* Quand tout est null, on affiche avec une boucle for */
	if(a!=NULL){
		if(a->fils==NULL && a->frg==NULL && a->frd == NULL){
			int i;
			for(i=0; i<idx; i++){
				printf("%c",deb[i]);
			}
				printf("\n");
		}

		else {
			if(a->frd!=NULL){
				afficheChemin(a->frd, deb, idx);
				deb[idx]= a->lettre;
			}

			deb[idx]= a->lettre;
			afficheChemin(a->fils, deb, idx+1);	
			
			if(a->frg!=NULL){
				afficheChemin(a->frg, deb, idx);
				deb[idx]= a->lettre;
			}
			
		}
	}
}

int main(){
	Tarbre a = NULL;
	//afficheArbJoli(a,7);
	char deb[15];
	//char* tab[MAX]= {"le","bu","la","les","de","des","dune","un", "ses");
	Ajout(&a, "bonjour");
	Ajout(&a, "bonsoir");
	Ajout(&a, "hello");
	Ajout(&a, "gateau");
	Ajout(&a, "arret");
	Ajout(&a, "dauphin");
	Ajout(&a, "zorro");
	Ajout(&a, "aller");
	Ajout(&a, "carrefour");
	//int result  = recherche(&a, "hello");
	//printf("%d\n", result);
	//int nb = nombreMot(a);
	//printf("%d\n", nb);
	afficheChemin(a, deb, 0);
	return 0;
}
