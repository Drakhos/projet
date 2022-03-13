constexpr auto F_CRYPT = "fichierCrypte.txt";
constexpr auto F_NONCRYPT = "fichierNonCrypte.txt";
constexpr auto IMAGE_PATH = "steno.bmp";

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <limits>
#include "Crypto.h"
#include <vector>
#include <chrono>
#include <thread>





int main()
{

	Crypto programme;
	programme.AfficherMenu();

	return 0;

}



