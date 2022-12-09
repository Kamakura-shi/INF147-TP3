#include "mod_quiz_3_2.h"

t_file_dynamique_image* t_file_dynamique_image_initialiser(t_image* image_ptr)
{
	
	/* On alloue la memoire dynamiquement */
	t_file_dynamique_image* file_image_ptr = (t_file_dynamique_image*)malloc(sizeof(t_file_dynamique_image));

	/* En cas d'echec : */
	if (file_image_ptr == NULL)
	{
		
		/* Le message suivant est affich� */
		printf(" t_file_dynamique_image_initialiser -> Erreur d'allocation de memoire\n");
		
		/* On retourne le pointeur nul */
		return NULL;
	
	}
	else
	{
		file_image_ptr->tete = t_noeud_image_initialiser(image_ptr);
	}
	
	/* Si le pointeur d'image est le pointeur nul : */
	if (image_ptr == NULL)
	{
		
		/* On initialise la tete de la pile egale a ce dernier */
		file_image_ptr->tete = t_noeud_image_initialiser(image_ptr);
		
		/* On fixe la taille a zero */
		file_image_ptr->taille = 0;
	
	}
	else
	{
		
		/* On initialise un n�ud a partir du pointeur d'image */
		file_image_ptr->tete = t_noeud_image_initialiser(image_ptr);

		if (file_image_ptr->tete == NULL)
		{
			
			/* On libere la memoire allouee pour la pile */
			free(file_image_ptr);
			
			/* On quitte la fonction en retournant le pointeur nul */
			return NULL;
		
		}
		/* Si l'initialisation fonctionne : */
		else
		{
			
			/* On fixe la taille a 1 */
			file_image_ptr->taille = 1;
			
			/* On retourne la pile */
			return file_image_ptr;
		
		}
	}

}

unsigned char t_file_dynamique_image_est_vide(t_file_dynamique_image* file_image_ptr)
{
	if (file_image_ptr->taille == 0)
	{
		return VRAI;
	}
	else
	{
		return FAUX;
	}

}

unsigned char t_file_dynamique_image_enfiler(t_file_dynamique_image* file_image_ptr, t_image* image_ptr)
{
	unsigned char est_succes = EXIT_SUCCESS;

	/* En cas d'�chec : */
	if (file_image_ptr == NULL)
	{
		/* On retourne un indicateur d'�chec (c.-�-d. EXIT_FAILURE) */
		est_succes = EXIT_FAILURE;
	}

	/* Initialiser un noeud */
	t_noeud_image* noeud_image_ptr = t_noeud_image_initialiser(image_ptr);

	/* En cas d'�chec : */
	if (noeud_image_ptr == NULL)
	{
		/* On retourne un indicateur d'echec (c.-a-d. EXIT_FAILURE) */
		est_succes = EXIT_FAILURE;
	}

	/* Ajouter le noeud */
	for (unsigned int i = 0; i < file_image_ptr->taille - 1; i++)
	{
		if (file_image_ptr->taille == 0)
		{
			/* On remplace la tete par le nouveau noeud */
			file_image_ptr->tete = noeud_image_ptr;
		}
		else
		{

			/* On remplace la tete par le nouveau noeud */
			file_image_ptr->tete->prochain = noeud_image_ptr;
			
			/* On relie le nouveau noeud � l'ancienne tete */
			file_image_ptr->tete = noeud_image_ptr;
		
		}
	}

	/* On incremente la taille de la file */
	file_image_ptr->taille++;

	return est_succes;
}

t_image* t_file_dynamique_image_defiler(t_file_dynamique_image* file_image_ptr)
{
	/* Si la file est vide, on affiche le message suivant et on retourne le pointeur nul : */
	if (t_file_dynamique_image_est_vide(file_image_ptr))
	{

		/* on affiche le message suivant */
		printf("t_file_dynamique_image_defiler > ERREUR > La file est vide");

		/* On retourne le pointeur nul */
		return NULL;

	}
	else
	{

		/* On remplace la tete par le prochain noeud */
		t_noeud_image* noeud_suivant_ptr = file_image_ptr->tete->prochain;

		/* retourner la r�f�rence vers l'image encapsul�e par celle-ci */
		t_noeud_image* noeud_supprimer = file_image_ptr->tete;

		/* On libere la memoire allouee pour le noeud depile (i.e. l'ancienne tete) */
		t_noeud_image_detruire(file_image_ptr->tete);

		file_image_ptr->tete = noeud_suivant_ptr;

		/* On decremente la taille de la pile */
		file_image_ptr->taille--;

		return noeud_supprimer->image;

	}

}