#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 15

typedef struct noeud{
	int valeur;
	struct noeud *fg;
	struct noeud *fd;
}Noeud, *Arbre;

Arbre allocNoeud(int b){
	Arbre a = malloc(sizeof(Noeud));
	if(a!= NULL){
		a->valeur = b;
		a->fg = NULL;
		a->fd = NULL;
	}
	return a;
}

int construitArbreQuelconque(Arbre *a,int *in){
	int type = *in;
	int val = *(in+1);
	int resG;
	int resD;
	if(type==3){
		*a = allocNoeud(val);
		resG =construitArbreQuelconque(&(*a)->fg, in+2);
		resD=construitArbreQuelconque(&(*a)->fd, in+(2*resG)+2);
		return 1+resG+resD;
	}
	if(type==2){
		*a = allocNoeud(val);
		return 1+ construitArbreQuelconque(&(*a)->fg, in+2);
	}

	if(type == 1){
		*a = allocNoeud(val);
		return 1+ construitArbreQuelconque(&(*a)->fd, in+2);
	}

	else{
		*a = allocNoeud(val);
		return 1;
	}
}

void ecritArbreQuelconque(Arbre a, int *tab, int i){

	if(a == NULL){
		return;
	}
	else if (a->fg == NULL && a->fd != NULL){
		printf("1 %d", a->valeur);
	}
	else if(a->fg != NULL && a->fd == NULL){
		printf(" 2 %d ", a->valeur);
		tab[i] = 2;
	}
	else if(a->fg!=NULL && a->fd!=NULL){
		//printf(" 3 %d",a->valeur);
		tab[i] = 3;
	}
	else if(a->fg==NULL && a->fd==NULL){
		//printf(" 0 %d ",a->valeur);
		tab[i] = 0;
			//i++;
	}
	i++;
	tab[i]= a->valeur;
		//printf("%d\n", i);
	printf("%d %d\n", tab[i], i);
	ecritArbreQuelconque(a->fg, tab, i++);
		//i++;
	printf("je passe à la branche de droite");
	i++;
	ecritArbreQuelconque(a->fd, tab, i++);
}

	/* Si cest HG */
Arbre Recherche(Arbre a, int x){
	if(a==NULL)
		return NULL;
	if(a->valeur==x){
		printf("%d",a->valeur);
		return a;
	}
	if(x<a->valeur)
		return Recherche(a->fg,x);
	else if(x>a->valeur)
		return Recherche(a->fd,x);
	else
		return NULL;
}

int Ajout(Arbre *a, int x){
	if(*a == NULL){
		*a=allocNoeud(x);
		return 0;
	}
	if(x==(*a)->valeur)
		return 0; 
	if(x<(*a)->valeur)
		Ajout(&((*a)->fg),x);
	if(x>(*a)->valeur)
		Ajout(&((*a)->fd),x);
	return 0;
}

int estABR_rec(Arbre a, int *min, int *max){
	if(a==NULL)
		return 1;
	if(min == NULL || max == NULL)
		if(a->valeur > *max || a->valeur < *min)
			return 0;
	return estABR_rec(a->fd, &(a->valeur), max) && estABR_rec(a->fg, min, &(a->valeur)) ;
}

int estABR(Arbre a){
	int min, max;
	if(a==NULL)
		return 1;
	min = a->valeur - 1;
	max = a->valeur + 1;
	return estABR_rec(a, &min, &max);
}

void afficheArbJoli(Arbre a, int niv) {
/* affiche l'arbre a sous la forme d'une arborescence (fg en haut, fd en bas)
Pour appeller le dessin de l'arbre a, taper "afficherArbJoli(a,0);" dans votre main*/
	int i = 0;
	for (i=0; i<niv; i++) {
		printf("| ");
	}
	if (a == NULL)
		printf("NULL\n");
	else {
		printf("%d\n", a->valeur);
		afficheArbJoli(a->fg, 1 + niv);
		afficheArbJoli(a->fd, 1 + niv);
	}
}

void afficheTab(int *tab){
	int i;
	for(i=0; i<14 ; i++){
		printf("%d ", tab[i]);
	}
}

void afficheChemin(Arbre a, int*deb, int idx){
	/*Arbre tmp;
	tmp = a;*/
	if(a!=NULL){
		if(a->fg==NULL && a->fd == NULL){
			int i;
			for(i=0; i<idx; i++){
				printf("%d ",deb[i]);
			}
				printf("%d\n", a->valeur);
		}
		else {
			deb[idx]= a->valeur;
			afficheChemin(a->fg, deb, idx+1);
			afficheChemin(a->fd, deb, idx+1);
		}
	}
}

int main(){
	//FILE *file = fopen("data.txt");
	Arbre a;
	int deb[3];
	//viewTree(a);
	int buffer[MAX]={3,5,2,0,0,-1,1,7,3,9,0,8,0,11};
			//int buffer2[MAX];
	construitArbreQuelconque(&a, buffer);
			//ecritArbreQuelconque(a, buffer2, 0);
	printf("\n");
			//afficheTab(buffer2);
	printf(" valeur du noeud recherché %d\n",(Recherche(a,7)->valeur));
	Ajout(&a, 4);
			//printf("%d",b);
			//afficheArbJoli(a,0);
	//printf(" min %d\n",extraitMin(&a)->valeur);
	//printf(" max %d\n",extraitMax(&a)->valeur);
	//afficheArbJoli(a,7);
	//extrait(&a,7);
	afficheArbJoli(a,7);
	estABR(a);
	//printf("%d",estABR(a));
	afficheChemin(a, deb,0);
	return 0;
}
