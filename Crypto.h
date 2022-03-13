#ifndef DEF_H
#define DEF_H

#include <string>
#include <fstream>


class Crypto {

public:

	void AfficherMenu();          // affiche le menu utilisateur

private:

	
	void ChiffrerCesar(int key, int mode);    // fonction de chiffrement par code Cesar avec une cle
	
	void ChiffrerVigenere(std::string stringKey, int mode); // fonction de chiffrement par code Vigenere

	void ChiffrerDansImage();               // // fonction de chiffrement qui utilise les bits de poids faible d'une image
	
	void DechiffrerCesar(int mode);      // fonction de dechiffrement par code Cesar avec analyse des frequences(mode = 1 : ensemble des caracteres ASCII affichables, mode = 2 uniquement 'a...z' et 'A...Z')

	void DechiffrerCesar(int key, int mode);    // fonction de dechiffrement par code Cesar avec une cle (mode = 1 : ensemble des caracteres ASCII affichables, mode = 2 uniquement 'a...z' et 'A...Z')
	
	void DechiffrerVigenere(std::string key, int mode);// fonction de dechiffrement par code Vigenere

	void DechiffrerDansImage();               // fonction de dechiffrement qui utilise les bits de poids faible d'une image
	
	void LireMesssage(int numFichier);   // Si numFichier = 1 affiche le contenu du fichier crypte, si numFichier = 2 le contenu du fichier non crypte

	void EcrireFichier(int numFichier); // Ecrit  dans un fichier (supprime le contenu preexistant)

};


#endif //DEF_H

//void ChiffrementAES(std::string stringKey); // chiffrement AES 
//void ChiffrementAES(std::string stringKey); // dechiffrement AES 