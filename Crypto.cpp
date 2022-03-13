constexpr auto F_CRYPT = "fichierCrypte.txt";
constexpr auto F_NONCRYPT = "fichierNonCrypte.txt";
constexpr auto IMAGE_PATH = "imageCryptage.bmp";

#include "Crypto.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>


#ifdef _WIN32
#define clearConsole() std::system("cls")
#else
#define clearConsole() std::system("clear")
#endif

void Crypto::AfficherMenu()      //affiche le menu utilisateur et offre des choix
{
	int key = 0;
	std::string stringKey;
	int choix = 0;
	int menu = 0;
	int type = 0;
	int mode = 0;
	int maxkey = 0;
	bool menuLire = true;

	int derniereOperation = 0;  // 1 si la derniere operation executee est un chiffrage, 2 si c'est un dechiffrage

	while (true)
	{
		derniereOperation = 0;
		key = 0;
		choix = 0;
		menuLire = true;

		clearConsole();
		std::cout << " Placer le message avec un cryptage dans fichierCrypte.txt ou le message sans cryptage dans fichierNonCrypte.txt " << std::endl;
		std::cout << "                                                     " << std::endl;
		std::cout << "                                                     " << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "               *         1.Crypter.                 *" << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "               *         2.Decrypter.               *" << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "               *         3.Lire fichier.            *" << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "               *         4.Ecrire fichier.          *" << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "               *         5.Quitter.                 *" << std::endl;
		std::cout << "               **************************************" << std::endl;
		std::cout << "                                                     " << std::endl;
		std::cout << "                   Indiquer votre choix: ";


		while ((!(std::cin >> choix)) || ((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4) && (choix != 5)))
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Choix invalide! Entrer un nouveau choix: ";
		}


		switch (choix)
		{
		case 1:

			std::cout << " 1 - Cryptage Cesar " << std::endl;
			std::cout << " 2 - Cryptage Vigenere" << std::endl;
			std::cout << " 3 - Cryptage dans une image (54 caracteres max.)" << std::endl;
			std::cout << " Votre choix (1, 2 ou 3) : ";
			while ((!(std::cin >> type)) || (((type != 1) && (type != 2) && (type != 3))))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
			}

			if (type == 1)
			{
				std::cout << std::endl << " 1 - Cryptage cesar sur l'ensemble des caracteres ASCII affichables (plus securise)" << std::endl;
				std::cout << " 2 - Cryptage cesar uniquement sur les lettres de l'alphabet (moins securise)" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";
				while ((!(std::cin >> mode)) || (((mode != 1) && (mode != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}

				if (mode == 1)
				{
					maxkey = 94;
				}
				else
				{
					maxkey = 25;
				}

				std::cout << std::endl << "Entrer votre cle de securite (entre 1 et " << maxkey << ") : ";
				while ((!(std::cin >> key)) || ((key < 1) || (key > maxkey)))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Entrer votre cle de securite (entre 1 et " << maxkey << ") : ";
				}
				ChiffrerCesar(key, mode);
			}
			else if (type == 2)  //cryptage vigenere
			{
				std::cout << std::endl << " 1 - Cryptage Vigenere sur l'ensemble des caracteres ASCII affichables (plus securise)" << std::endl;
				std::cout << " 2 - Cryptage Vigenere uniquement sur les lettres de l'alphabet (moins securise)" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";
				while ((!(std::cin >> mode)) || (((mode != 1) && (mode != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}

				if (mode == 1)
				{
					int taille;
					bool valide1 = false;
					bool valide2 = false;

					while ((!(valide1)) || (!(valide2)))
					{
						std::cout << std::endl << "Entrer votre cle de securite (tous les caracteres ASCII affichables sont autorises) : ";
						while ((!(std::cin >> stringKey)))
						{
							std::cin.clear();
							std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
							std::cout << "Choix invalide! Entrer votre cle de securite (tous les caracteres ASCII affichables sont autorises) : ";

						}
						valide1 = true;
						valide2 = true;
						taille = (int)stringKey.length();


						while (((taille) > 0) && (valide2 == true))
						{

							if ((stringKey[taille - 1] < 32) || (stringKey[taille - 1] > 126))
							{
								valide1 = false;
								valide2 = false;
							}
							taille--;
						}

					}
				}
				else
				{
					int taille;
					bool valide1 = false;
					bool valide2 = false;

					while ((!(valide1)) || (!(valide2)))
					{
						std::cout << std::endl << "Entrer votre cle de securite (seuls les caracteres de l'alphabet sont autorises) : ";
						while ((!(std::cin >> stringKey)))
						{
							std::cin.clear();
							std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
							std::cout << "Choix invalide! Entrer votre cle de securite (seuls les caracteres de l'alphabet sont autorises) : ";
						}

						valide1 = true;
						valide2 = true;
						taille = (int)stringKey.length();


						while (((taille) > 0) && (valide2 == true))
						{
							if ((stringKey[taille - 1] < 65) || (stringKey[taille - 1] > 122) || ((stringKey[taille - 1] > 90) && (stringKey[taille - 1] < 97)))
							{
								valide1 = false;
								valide2 = false;
							}
							taille--;
						}

					}
				}

				ChiffrerVigenere(stringKey, mode);
			}
			else           // cryptage dans image
			{
				ChiffrerDansImage();
				menuLire = false;
			}




			derniereOperation = 1;
			break;
		case 2:

			std::cout << " 1 - Decryptage Cesar " << std::endl;
			std::cout << " 2 - Decryptage Vigenere" << std::endl;
			std::cout << " 3 - Decryptage dans une image" << std::endl;
			std::cout << " Votre choix (1, 2 ou 3) : ";
			while ((!(std::cin >> type)) || (((type != 1) && (type != 2) && (type != 3))))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
			}

			if (type == 1)
			{
				std::cout << std::endl << " 1 - Decryptage cesar sur l'ensemble des caracteres ASCII affichables (plus securise)" << std::endl;
				std::cout << " 2 - Decryptage cesar uniquement sur les lettres de l'alphabet (moins securise)" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";
				while ((!(std::cin >> mode)) || (((mode != 1) && (mode != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}

				if (mode == 1)
				{
					maxkey = 94;
				}
				else
				{
					maxkey = 25;
				}

				int frequence;
				std::cout << std::endl << " 1 - Decryptage a partir d'une cle" << std::endl;
				std::cout << " 2 - Decryptage a partir d'une analyse frequentielle (anglais uniquement)" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";
				while ((!(std::cin >> frequence)) || (((frequence != 1) && (frequence != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}


				if (frequence == 1)
				{
					std::cout << std::endl << "Entrer votre cle de securite (entre 1 et " << maxkey << ") : ";
					while ((!(std::cin >> key)) || ((key < 1) || (key > maxkey)))
					{
						std::cin.clear();
						std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
						std::cout << "Choix invalide! Entrer votre cle de securite (entre 1 et " << maxkey << ") : ";
					}
					DechiffrerCesar(key, mode);
				}
				else
				{
					DechiffrerCesar(mode);
					menuLire = false;
				}
			}
			else if (type == 2) //decryptage vigenere
			{

				std::cout << std::endl << " 1 - Decryptage Vigenere sur l'ensemble des caracteres ASCII affichables (plus securise)" << std::endl;
				std::cout << " 2 - Decryptage Vigenere uniquement sur les lettres de l'alphabet (moins securise)" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";
				while ((!(std::cin >> mode)) || (((mode != 1) && (mode != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}

				if (mode == 1)
				{
					int taille;
					bool valide1 = false;
					bool valide2 = false;

					while ((!(valide1)) || (!(valide2)))
					{
						std::cout << std::endl << "Entrer votre cle de securite (tous les caracteres ASCII affichables sont autorises) : ";
						while ((!(std::cin >> stringKey)))
						{
							std::cin.clear();
							std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
							std::cout << "Choix invalide! Entrer votre cle de securite (tous les caracteres ASCII affichables sont autorises) : ";
						}
						valide1 = true;
						valide2 = true;
						taille = (int)stringKey.length();


						while (((taille) > 0) && (valide2 == true))
						{
							if ((stringKey[taille - 1] < 32) || (stringKey[taille - 1] > 126))
							{
								valide1 = false;
								valide2 = false;
							}
							taille--;
						}

					}
				}
				else
				{
					int taille;
					bool valide1 = false;
					bool valide2 = false;

					while ((!(valide1)) || (!(valide2)))
					{
						std::cout << std::endl << "Entrer votre cle de securite (seuls les caracteres de l'alphabet sont autorises) : ";
						while ((!(std::cin >> stringKey)))
						{
							std::cin.clear();
							std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
							std::cout << "Choix invalide! Entrer votre cle de securite (seuls les caracteres de l'alphabet sont autorises) : ";
						}

						valide1 = true;
						valide2 = true;
						taille = (int)stringKey.length();


						while (((taille) > 0) && (valide2 == true))
						{
							if ((stringKey[taille - 1] < 65) || (stringKey[taille - 1] > 122) || ((stringKey[taille - 1] > 90) && (stringKey[taille - 1] < 97)))
							{
								valide1 = false;
								valide2 = false;
							}
							taille--;
						}

					}
				}

				DechiffrerVigenere(stringKey, mode);
			}
			else                    //decryptage dans image
			{
				DechiffrerDansImage();
			}
			derniereOperation = 2;
			break;
		case 3:
			std::cout << " 1 - Lire fichier non crypte " << std::endl;
			std::cout << " 2 - Lire fichier crypte" << std::endl;
			std::cout << " Votre choix (1 ou 2) : ";

			while ((!(std::cin >> choix)) || (((choix != 1) && (choix != 2))))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
			}

			if (choix == 1)
			{
				LireMesssage(2);
			}
			else
			{
				LireMesssage(1);
			}
			menuLire = false;
			break;
		case 4:

			std::cout << std::endl << " L'ecriture supprimera le contenu du fichier" << std::endl;
			std::cout << " Continuer ? (1 pour oui, 2 pour non) : ";

			while ((!(std::cin >> choix)) || (((choix != 1) && (choix != 2))))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
			}

			if (choix == 1)
			{
				std::cout << std::endl << " 1 - Ecrire dans le fichier non crypte " << std::endl;
				std::cout << " 2 - Ecrire dans le fichier crypte" << std::endl;
				std::cout << " Votre choix (1 ou 2) : ";

				while ((!(std::cin >> choix)) || (((choix != 1) && (choix != 2))))
				{
					std::cin.clear();
					std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
					std::cout << "Choix invalide! Votre choix (1 ou 2) : ";
				}

				if (choix == 1)
				{
					EcrireFichier(2);
				}
				else
				{
					EcrireFichier(1);
				}
			}
			menuLire = false;

			break;

		case 5:
			std::cout << "Le programme va desormais se fermer...3" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			std::cout << "...2" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			std::cout << "...1" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			return;
			break;
		}

		if (menuLire)
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Operation reussie ! Voulez vous afficher le nouveau message ? (1 pour oui, 2 pour non) : ";
			while ((!(std::cin >> choix)) || ((choix != 1) && (choix != 2)))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide ! Voulez vous afficher le message ? (1 pour oui, 2 pour non) : ";
			}
			if (choix == 1)
			{
				LireMesssage(derniereOperation);
			}
		}

		choix = 0;
		std::cout << "Retour au menu principal ? (1 pour oui, 2 pour non) : ";
		while ((!(std::cin >> choix)) || ((choix != 1)) && (choix != 2))
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Choix invalide ! Retour au menu principal ? (1 pour oui, 2 pour non) : ";
		}
		if (choix == 2)
		{
			std::cout << "Le programme va desormais se fermer...3" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			std::cout << "...2" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			std::cout << "...1" << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(800));
			return;
		}
	}
}

void Crypto::ChiffrerCesar(int key, int mode)   // Fonction de chiffrement par code Cesar
{

	char c_buffer;
	bool present = false; //presence du caractere dans la liste des caracteres ASCII affichables (entre 32 et 126)

	std::ofstream fichier_crypt(F_CRYPT, std::ofstream::out);                   //ouverture des fichiers
	std::ifstream fichier_nonCrypt(F_NONCRYPT, std::ifstream::in);


	if ((fichier_nonCrypt.is_open()) && (fichier_crypt.is_open()))   //on verifie que les 2 fichiers sont bien ouverts
	{
		fichier_nonCrypt.seekg(0, std::ios_base::beg);      //on se place au debut dans les 2 fichiers
		fichier_crypt.seekp(0, std::ios_base::beg);
		fichier_nonCrypt.get(c_buffer);                    //on recupere le premier caractere du fichier

		if (mode == 1)                                 //mode ASCII
		{
			while (fichier_nonCrypt.eof() == false)    //on verifie si on a atteint la fin du fichier
			{
				int i = 32;
				present = false;
				while ((!present) && (i < 127))          //on recherche la presence du caractere dans les caracteres ASCCI affichables
				{
					if ((int)c_buffer == (i))
					{
						present = true;
					}
					i++;
				}

				if (present)
				{
					if ((((int)c_buffer) + key) > 126)
						//if (((((int)c_buffer) + key) % 127) < 32)                                    //present -> code ceasar classique
					{
						fichier_crypt.put(((((int)c_buffer) + key) % 127) + 32);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else
				{
					fichier_crypt.put(c_buffer);              //non present -> caractere reinsere tel quel
				}

				fichier_nonCrypt.get(c_buffer);               //on lit le caractere suivant dans le fichier
			}
		}
		else                                                 //mode alphabet seulement
		{
			while (fichier_nonCrypt.eof() == false)
			{
				if ((((int)c_buffer) < 91) && (((int)c_buffer) > 64))   //gestion des lettres majuscules
				{

					if ((((int)c_buffer) + key) > 90)
					{
						fichier_crypt.put(64 + ((int)c_buffer) - 90 + key);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else if ((((int)c_buffer) < 123) && (((int)c_buffer) > 96))  //gestion des lettres minuscules
				{
					if ((((int)c_buffer) + key) > 122)
					{
						fichier_crypt.put(96 + ((int)c_buffer) - 122 + key);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else                                  //caractere non pris en charge
				{
					fichier_crypt.put(c_buffer);
				}


				fichier_nonCrypt.get(c_buffer);
			}
		}
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	fichier_nonCrypt.close();
	fichier_crypt.close();
}

void Crypto::ChiffrerVigenere(std::string stringKey, int mode)   
{
	int key;
	char c_buffer;
	int indiceStringKey = 0;
	int tailleStringKey = (int)stringKey.length();
	bool present = false; //presence du caractere dans la liste des caracteres ASCII affichables (entre 32 et 126)

	std::ofstream fichier_crypt(F_CRYPT, std::ofstream::out);                   //ouverture des fichiers
	std::ifstream fichier_nonCrypt(F_NONCRYPT, std::ifstream::in);


	if ((fichier_nonCrypt.is_open()) && (fichier_crypt.is_open()))   //on verifie que les 2 fichiers sont bien ouverts
	{
		fichier_nonCrypt.seekg(0, std::ios_base::beg);      //on se place au debut dans les 2 fichiers
		fichier_crypt.seekp(0, std::ios_base::beg);
		fichier_nonCrypt.get(c_buffer);                    //on recupere le premier caractere du fichier

		if (mode == 1)                                 //mode ASCII
		{
			while (fichier_nonCrypt.eof() == false)    //on verifie si on a atteint la fin du fichier
			{
				if (indiceStringKey >= tailleStringKey)   // quand on atteint la fin de notre cle Vigenere on revient au debut
				{
					indiceStringKey = 0;
				}

				int i = 32;
				present = false;
				while ((!present) && (i < 127))          //on recherche la presence du caractere dans les caracteres ASCCI affichables
				{
					if ((int)c_buffer == (i))
					{
						present = true;
					}
					i++;
				}

				if (present)
				{
					key = (((int)stringKey[indiceStringKey]) - 32);  //32 est l'indice de premier caractere ASCII qu'on prend en charge

					if ((((int)c_buffer) + key) > 126)                 //present -> code ceasar classique				                                  
					{
						fichier_crypt.put(((((int)c_buffer) + key) % 127) + 32);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else
				{
					fichier_crypt.put(c_buffer);              //non present -> caractere reinsere tel quel
				}

				fichier_nonCrypt.get(c_buffer);               //on lit le caractere suivant dans le fichier

				indiceStringKey++;                      //on avance d'un caractere dans la cle Vigenere
			}
		}
		else                                                 //mode alphabet seulement
		{
			while (fichier_nonCrypt.eof() == false)
			{
				if (indiceStringKey >= tailleStringKey)   // quand on atteint la fin de notre cle Vigenere on revient au debut
				{
					indiceStringKey = 0;
				}

				for (int j = 0; j < tailleStringKey; j++)                 //met en minuscule les majuscules dans la cle dans la cle vigenere
				{
					if ((stringKey[j] > 64) && (stringKey[j] < 91))
					{
						stringKey[j] = (((int)stringKey[j]) + 32);
					}
				}

				key = (((int)stringKey[indiceStringKey]) - 97);  //97 est l'indice de premier caractere ASCII qu'on prend en charge

				if ((((int)c_buffer) < 91) && (((int)c_buffer) > 64))   //gestion des lettres majuscules
				{

					if ((((int)c_buffer) + key) > 90)
					{
						fichier_crypt.put(64 + ((int)c_buffer) - 90 + key);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else if ((((int)c_buffer) < 123) && (((int)c_buffer) > 96))  //gestion des lettres minuscules
				{
					if ((((int)c_buffer) + key) > 122)
					{
						fichier_crypt.put(96 + ((int)c_buffer) - 122 + key);
					}
					else
					{
						fichier_crypt.put(((int)c_buffer) + key);
					}
				}
				else                                  //caractere non pris en charge
				{
					fichier_crypt.put(c_buffer);
				}


				fichier_nonCrypt.get(c_buffer);
				indiceStringKey++; //on avance d'un caractere dans la cle Vigenere
			}
		}
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);   

	}

	fichier_nonCrypt.close();
	fichier_crypt.close();
}

void Crypto::ChiffrerDansImage()
{


	std::ifstream  src("sauvegarde.bmp", std::ios::binary);
	std::ofstream  dst(IMAGE_PATH, std::ios::binary);

	dst << src.rdbuf();




	std::ifstream fichier_nonCrypt(F_NONCRYPT, std::ifstream::in);
	fichier_nonCrypt.seekg(0);
	std::fstream image(IMAGE_PATH);
	std::vector<int> msg_binaire;
	int nbBitMsg = 0;

	if ((image.is_open()) && (fichier_nonCrypt.is_open()))
	{

		char c;
		fichier_nonCrypt.get(c);
		int compteur = 0;

		while (!(fichier_nonCrypt.eof()))
		{
			for (int i = 0; i <= 7; i++)        //on transforme le message en binaire
			{
				compteur++;

				if (((int)c) & (1 << (7 - i)))
				{
					msg_binaire.push_back(1);
				}
				else
				{
					msg_binaire.push_back(0);
				}
			}

			fichier_nonCrypt.get(c);
		}
		nbBitMsg = compteur;

		fichier_nonCrypt.close();

		if (nbBitMsg > 431)    // limite de caractere
		{
			std::cout << "Message trop volumineux pour cette methode !" << std::endl << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(1);
		}



		for (int i = 0; i < nbBitMsg; i++)           //on insere le message dans les bits de poids faible de l'image
		{
			image.seekg(54 + (i * 8));
			image.get(c);

			if ((abs((int)c % 2)) != (msg_binaire[i]))
			{
				if (msg_binaire[i] == 0)
				{
					image.seekg(54 + (i * 8));
					image.put(c - 1);
				}
				else
				{
					image.seekg(54 + (i * 8));
					image.put(c + 1);
				}
			}
		}

		for (int i = 1; i < 4; i++)       //on ecrit un marqueur de fin de message
		{
			image.seekg(54 + ((nbBitMsg - 1) * 8) + (i * 8));
			image.put(127);
			image.seekg(54 + ((nbBitMsg - 1) * 8) + (i * 8));
			image.get(c);
		}
		
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	image.close();
	fichier_nonCrypt.close();

	std::cout << std::endl << "Le cryptage est termine !" << std::endl;
	
} 

void Crypto::DechiffrerCesar(int mode)   // dechiffrement grace a une analyse frequentielle
{
	double frequenceReference[26] = {           //Tableau des frequences de chaque caractere dans le langage courant anglais
	0.08167,	//a
	0.01492,	//b
	0.02782,	//c
	0.04253,	//d
	0.12702,	//e
	0.02228,	//f
	0.02015,	//g
	0.06094,	//h
	0.06966,	//i
	0.00153,	//j
	0.00772,	//k
	0.04025,	//l
	0.02406,	//m
	0.06749,	//n
	0.07507,	//o
	0.01929,	//p
	0.00095,	//q
	0.05987,	//r
	0.06327,	//s
	0.09056,	//t
	0.02758,	//u
	0.00978,	//v
	0.02360,	//w
	0.00150,	//x
	0.01974,	//y
	0.00074		//z
	};

	//Tableau de frequence de tous les caracteres pour le resultat d'un dechiffrage - l'indice 0 pour a, 1 pour b, etc... 
	double frequenceFichier[26] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

	// Tableau stockant la somme des ecarts de frequence de chaque lettre (par rapport a la reference) et pour chaque cle - indice 1 pour la somme des ecarts de la cle 1, etc...
	double differenceFrequence[25] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};  


	std::ifstream fichier_crypt(F_CRYPT, std::ifstream::in);       //ouverture fichier crypte
	if (fichier_crypt.is_open())
	{

		int nombreDeCaractere = 0;			//nombre de caractere dans le fichier
		fichier_crypt.get();

		while (fichier_crypt.eof() == false)
		{
			nombreDeCaractere++;
			fichier_crypt.get();
		}

		fichier_crypt.close();

		DechiffrerCesar(1, mode);                             // dechiffrement pour la cle 1

		std::ifstream fichier_nonCrypt(F_NONCRYPT, std::ifstream::in);
		if (fichier_nonCrypt.is_open())
		{
			char c_buffer;                                             //on lit le fichier et on calcul les frequences de chaques lettres pour la cle de 1

			for (int i = 0; i < nombreDeCaractere; i++)
			{
				fichier_nonCrypt.get(c_buffer);

				if (((int)c_buffer >= 65) && ((int)c_buffer <= 90))     // si le caractere est une lettre majuscule
				{
					c_buffer = ((int)c_buffer) + 32;                    //on met la lettre en minuscule
					frequenceFichier[(((int)c_buffer) - 97)]++;           //on ajoute +1 occurence de la lettre dans frequenceFichier
				}
				else if ((((int)c_buffer) >= 97) && (((int)c_buffer) <= 122))          // le caractere est une lettre minuscule
				{
					frequenceFichier[((int)c_buffer) - 97]++;     //on ajoute +1 occurence de la lettre dans frequenceFichier
				}
			}
			for (int j = 0; j < 26; j++)                                           //on parcourt le tableau frequenceFichier
			{
				frequenceFichier[j] /= nombreDeCaractere;                      //on divise le nombre d'occurence par le nombre total de caractere du fichier pour avoir la frequence d'apparition de chaque lettre
				differenceFrequence[0] += abs(frequenceReference[j] - frequenceFichier[j]);   //on calcul la difference pour chaque lettre entre la frequence trouve et celle de reference, puis on fait la somme de toutes les differences
			}                                                                                 

			fichier_crypt.close();

			double indice0;
			for (int i = 1; i < 25; i++)                                 // on boucle pour chaque cles cesar restantes
			{
				indice0 = frequenceFichier[0];
				for (int j = 0; j < 24; j++)                            // on decale les frequences de 1 a chaque fois
				{
					frequenceFichier[j] = frequenceFichier[j + 1];
				}
				frequenceFichier[24] = indice0;

				for (int j = 0; j < 26; j++)                                           //on parcourt le tableau frequenceFichier
				{
					differenceFrequence[i] += abs(frequenceReference[j] - frequenceFichier[j]);   //on calcul la difference pour chaque lettre entre la frequence trouve et celle de reference, puis on fait la somme de toutes les differences
				}
			}
		}
		else
		{
			std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(1);
		}


		bool reussite = false;        //boolean pour savoir si on a reussi a dechiffrer correctement le code
		double seuilFrequence = -1;
		double plusPetiteFrequence = -1;
		int nombreTentative = 0;
		int reponse;
		int key;

		do
		{
			nombreTentative++;
			for (int i = 1; i < 26; i++)   //on cherche l'indice de la plus petite difference de frequence
			{
				if (differenceFrequence[i - 1] > seuilFrequence)
				{
					if (plusPetiteFrequence == -1)
					{
						plusPetiteFrequence = differenceFrequence[i - 1];       //on initialise avec la premiere valeure possible
						key = i;                                             //on sauvegarde l'indice qui correspond a la cle
					}
					else if (differenceFrequence[i - 1] < plusPetiteFrequence)
					{
						plusPetiteFrequence = differenceFrequence[i - 1];
						key = i;
					}

				}

			}
			DechiffrerCesar(key, mode);
			std::cout << std::endl << "Resultat du decryptage : " << std::endl;
			LireMesssage(2);

			std::cout << "Est ce que le message ci dessus est correcte ? (1 pour oui / 2 pour non) : ";
			while ((!(std::cin >> reponse)) && (reponse != 1) && (reponse != 2))
			{
				std::cin.clear();
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Choix invalide! Est ce que le decryptage est correcte ? (1 pour oui / 2 pour non) : ";
			}

			if (reponse == 1)         //le resultat est bon on quitte, sinon on propose le 2eme choix le plus probable et ainsi de suite jusqu'a la fin des possibilites
			{
				reussite = true;
			}
			seuilFrequence = plusPetiteFrequence;
			plusPetiteFrequence = -1;
		} while ((!(reussite)) && (nombreTentative < 25));

		if (reussite)
		{
			std::cout << "Decryptage du message reussi ! La cle etait " << key << " !" << std::endl;
		}
		else
		{
			std::cout << "Aucune des possibilites n'est correcte. Echec de la decryption..." << std::endl << std::flush;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	else
	{
	std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	exit(1);
	}
}

void Crypto::DechiffrerCesar(int key, int mode)     // fonction de dechiffrement par code Cesar avec une cle (mode = 1 : ensemble des caracteres ASCII affichables, mode = 2 uniquement 'a...z' et 'A...Z'
{

	char c_buffer;

	std::ofstream fichier_nonCrypt(F_NONCRYPT, std::ofstream::out);              //ouverture des fichiers
	std::ifstream fichier_crypt(F_CRYPT, std::ifstream::in);

	if ((fichier_nonCrypt.is_open()) && (fichier_crypt.is_open()))
	{
		fichier_crypt.seekg(0, std::ios_base::beg);
		fichier_nonCrypt.seekp(0, std::ios_base::beg);
		fichier_crypt.get(c_buffer);

		if (mode == 1)      //mode 1 (ASCCI affichable) selectionne
		{
			while (fichier_crypt.eof() == false)
			{
				if (((int)c_buffer >= 32) && ((int)c_buffer <= 126))            //caractere pris en charge -> code ceasar classique
				{
					if ((((int)c_buffer) - key) < 32)
					{
						fichier_nonCrypt.put(127 + ((int)c_buffer) - 32 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else                               // caractere non pris en charge -> caractere non pris en charge 
				{
					fichier_nonCrypt.put(c_buffer);
				}

				fichier_crypt.get(c_buffer);
			}
		}
		else   // mode 2 ('a...z' et 'A...Z") selectionne
		{
			while (fichier_crypt.eof() == false)
			{
				if ((((int)c_buffer) < 91) && (((int)c_buffer) > 64))   //gestion des lettres majuscules
				{

					if ((((int)c_buffer) - key) <= 64)
					{
						fichier_nonCrypt.put(90 + ((int)c_buffer) - 64 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else if ((((int)c_buffer) < 123) && (((int)c_buffer) > 96))  //gestion des lettres minuscules
				{
					if ((((int)c_buffer) - key) <= 96)
					{
						fichier_nonCrypt.put(122 + (((int)c_buffer)) - 96 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else                                  //caractere non pris en charge
				{
					fichier_nonCrypt.put(c_buffer);
				}


				fichier_crypt.get(c_buffer);
			}
		}
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}
	fichier_nonCrypt.close();
	fichier_crypt.close();
}

void Crypto::DechiffrerVigenere(std::string stringKey, int mode)
{
	int key;
	int indiceStringKey = 0;
	int tailleStringKey = (int)stringKey.length();

	char c_buffer;

	std::ofstream fichier_nonCrypt(F_NONCRYPT, std::ofstream::out);              //ouverture des fichiers
	std::ifstream fichier_crypt(F_CRYPT, std::ifstream::in);

	if ((fichier_nonCrypt.is_open()) && (fichier_crypt.is_open()))
	{
		fichier_crypt.seekg(0, std::ios_base::beg);
		fichier_nonCrypt.seekp(0, std::ios_base::beg);
		fichier_crypt.get(c_buffer);

		if (mode == 1)      //mode 1 (ASCCI affichable) selectionne
		{
			while (fichier_crypt.eof() == false)
			{
				if (indiceStringKey >= tailleStringKey)   // quand on atteint la fin de notre cle Vigenere on revient au debut
				{
					indiceStringKey = 0;
				}

				if (((int)c_buffer >= 32) && ((int)c_buffer <= 126))            //caractere pris en charge -> code ceasar classique
				{
					key = (((int)stringKey[indiceStringKey]) - 32);  //32 est l'indice de premier caractere ASCII qu'on prend en charge

					if ((((int)c_buffer) - key) < 32)
					{
						fichier_nonCrypt.put(127 + ((int)c_buffer) - 32 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else                               // caractere non pris en charge -> caractere non pris en charge 
				{
					fichier_nonCrypt.put(c_buffer);
				}

				fichier_crypt.get(c_buffer);
				indiceStringKey++;                      //on avance d'un caractere dans la cle Vigenere
			}
		}
		else   // mode 2 ('a...z' et 'A...Z") selectionne
		{
			while (fichier_crypt.eof() == false)
			{
				if (indiceStringKey >= tailleStringKey)   // quand on atteint la fin de notre cle Vigenere on revient au debut
				{
					indiceStringKey = 0;
				}

				for (int j = 0; j < tailleStringKey; j++)                 //met en minuscule les majuscules dans la cle dans la cle vigenere
				{
					if ((stringKey[j] > 64) && (stringKey[j] < 91))
					{
						stringKey[j] = (((int)stringKey[j]) + 32);
					}
				}

				key = (((int)stringKey[indiceStringKey]) - 97);  //97 est l'indice de premier caractere qu'on prend en charge

				if ((((int)c_buffer) < 91) && (((int)c_buffer) > 64))   //gestion des lettres majuscules
				{
					if ((((int)c_buffer) - key) <= 64)
					{
						fichier_nonCrypt.put(90 + ((int)c_buffer) - 64 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else if ((((int)c_buffer) < 123) && (((int)c_buffer) > 96))  //gestion des lettres minuscules
				{
		
					if ((((int)c_buffer) - key) <= 96)
					{
						fichier_nonCrypt.put(122 + (((int)c_buffer)) - 96 - key);
					}
					else
					{
						fichier_nonCrypt.put(((int)c_buffer) - key);
					}
				}
				else                                  //caractere non pris en charge
				{
					fichier_nonCrypt.put(c_buffer);
				}

				fichier_crypt.get(c_buffer);
				indiceStringKey++;      //on avance d'un caractere dans la cle Vigenere
			}
		}
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}
	fichier_nonCrypt.close();
	fichier_crypt.close();
}

void Crypto::DechiffrerDansImage()
{

	std::ofstream fichier_nonCrypt(F_NONCRYPT, std::ofstream::out);
	std::ifstream image(IMAGE_PATH, std::ifstream::in);
	std::vector<char> msg_binaire;
	bool finMessage = false;
	char c;
	int i = 0;

	if ((image.is_open()) && (fichier_nonCrypt.is_open()))
	{
		while ((i < 13651) && (!(finMessage)))          //on recupere les bits de poids faible de l'image 
		{
			image.seekg(54 + (i * 8));
			image.get(c);
			if (c == 127)
			{
				image.seekg(54 + ((i + 1) * 8));
				image.get(c);
				if (c == 127)
				{
					image.seekg(54 + ((i + 1) * 8));
					image.get(c);
					if (c == 127)
					{
						finMessage = true;
					}
				}
			}

			if (!(finMessage))
			{
				image.seekg(54 + (i * 8));
				image.get(c);

				if (abs((((int)c) % 2)) == 1)
				{
					msg_binaire.push_back(1);
					
				}
				else
				{
					msg_binaire.push_back(0);
					
				}
			}
			i++;
		}

		image.close();

		int cpt = 0;
		int table[8];
		int a = 0;
		for (int bit : msg_binaire)
		{
			cpt++;
			
			table[cpt - 1] = bit;
			if (cpt == 8)
			{
				for (int j = 0; j < 8; j++)
				{
					if (table[j] == 1)
					{
						a = ((int) (a + (pow(2, (7 - j)))));
					}
				}
				fichier_nonCrypt.put(a);
				a = 0;
				cpt = 0;
			}
		}
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush; //le fichier n'est pas ouvert
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	if (finMessage)
	{
		std::cout << std::endl << "Decryptage reussi !" << std::endl;
	}
	else
	{
		std::cout << "Erreur decryptage, marqueur de fin non atteint." << std::endl;
	}

	fichier_nonCrypt.close();

}

void Crypto::LireMesssage(int numFichier)
{
	std::ifstream input_file;

	if (numFichier == 1)
	{
		input_file.open(F_CRYPT, std::ifstream::in);
	}
	else if (numFichier == 2)
	{
		input_file.open(F_NONCRYPT, std::ifstream::in);
	}
	else
	{
		std::cout << "Erreur du programme. Fermeture..." << std::endl << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	std::vector<std::string> lines;
	std::string line;

	if (!input_file.is_open()) {
		std::cout << "Impossible d'ouvrir le fichier !" << std::endl << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	std::cout << std::endl;
	for (const auto& i : lines)
		std::cout << i << std::endl;
	std::cout << std::endl;

	input_file.close();
}

void Crypto::EcrireFichier(int numFichier)
{
	std::vector<std::string> lines;
	std::string line;

	std::ofstream fichier;

	std::cout << std::endl << "(terminer l'ecriture en appuyant depuis une nouvelle ligne sur * puis entree) : " << std::endl;
	std::cout << "Texte a ecrire : " << std::endl << std::endl;
	std::cin.ignore();

	std::getline(std::cin, line);            //recupere ce que l'utilisateur ecrit, s'arrete lorsqu'il lit une chaine "*"
	while (line != "*"){
		line += "\n";
		lines.push_back(line);
		std::getline(std::cin, line);
	}
	

	if (numFichier == 1)      //fichier crypte
	{
		fichier.open(F_CRYPT, std::ostream::trunc);      //ouvre et supprime le contenu
	}
	else                     //ficher non crypte
	{
		fichier.open(F_NONCRYPT, std::ofstream::trunc);     //ouvre et supprime le contenu
	}

	if (fichier.is_open())
	{
		for (const auto& i : lines)
		{
			fichier << i;
		}

		std::cout << "Ecriture du fichier reussie !" << std::endl;
	}
	else
	{
		std::cout << "Erreur ouverture fichier" << std::endl << std::flush;
		std::cout << "Fermeture du programme...";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(1);
	}

	fichier.close();

}