#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
  int valeur;
  struct noeud *fg;
  struct noeud *fd;
} Noeud, *Arbre;

Arbre alloueNoeud(int val) {
  Arbre new = (Arbre) malloc(sizeof(Noeud));
  if (new != NULL) {
    new->valeur = val;
    new->fg = NULL;
    new->fd = NULL;
  }
  return new;
}

int rec_dot_export(Arbre a, int nodeID, FILE *dot_file) {
  int val, res_fg=0, res_fd=0;
  if (a != NULL) {
    val = a->valeur;
    fprintf(dot_file, "\tn%d [label=\"<gauche> | <valeur> %d | <droit>\"];\n", nodeID, val);
  }
  if (a->fg != NULL) {
    fprintf(dot_file, "\tn%d:gauche:c -> n%d:valeur;\n", nodeID, nodeID+1);
    res_fg = rec_dot_export(a->fg, nodeID+1, dot_file);
  }
  if (a->fd != NULL) {
    fprintf(dot_file, "\tn%d:droit:c -> n%d:valeur;\n", nodeID, nodeID+res_fg+1);
    res_fd = rec_dot_export(a->fd, nodeID+res_fg+1, dot_file);
  }
  return res_fg+res_fd+1;
}

void dot_export(Arbre a, FILE *dot_file) {
  fprintf(dot_file, "digraph arbre {\n");
  fprintf(dot_file, "\tnode [shape=record,height=.1]\n");
  fprintf(dot_file, "\tedge [tailclip=false,arrowtail=dot,dir=both]\n");
  rec_dot_export(a, 0, dot_file);
  fprintf(dot_file, "}\n");
}

void free_arbre(Arbre a) {
  if (a != NULL) {
    free_arbre(a->fg);
    free_arbre(a->fd);
    free(a);
  }
}

int main(int argc, char *argv[]) {
  Arbre a = NULL;
  FILE *out;

  a = alloueNoeud(1);
  a->fg = alloueNoeud(2);
  a->fd = alloueNoeud(3);
  a->fd->fg = alloueNoeud(4);

  if(argc == 1){
    out=stdout;
    fprintf(stderr,"stdout output\n");
  }
  else if((out=fopen(argv[1],"w"))==NULL){
    fprintf(stderr,"problem opening %s\n",argv[2]);
    exit(1);
  }

  dot_export(a, out);

  if (argc > 1) fclose(out);
  free_arbre(a);
  return 0;
}
