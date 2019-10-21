// ReinasTest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <math.h>
#include <omp.h>
#include <vector>
#include <chrono>


int n_soluciones = 0;
int const n_reinas = 8;



void comprobador(unsigned long long n);


/*
	18.446.744.073.709.551.615

	11.112.006.825.558.016 // 14

	437.893.890.380.859.375 // 15

	18.446.744.073.709.551.615 // 16 
*/


int main()
{
	
	//std::vector<int8_t> vector = base10toN(18446744073709551615);
	/*
	std::vector<int8_t> vector = base10toN(34);


	for (int i = 0; i < vector.size(); i++) {
		printf("%d ", vector[i]);
	}

	*/

	// /xHost
	// /o3

	
	//Numero de threads
	//omp_set_num_threads(2);

	unsigned long long n_maximo = powf(n_reinas, n_reinas);

	for (int j = 1;j < 5;j++) {

		omp_set_num_threads(j);

		auto start = std::chrono::high_resolution_clock::now();

		#pragma omp parallel for shared(n_reinas)  
		for (unsigned long long i = 1; i < n_maximo; i++)
			comprobador(i);

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;

		std::cout << "Tiempo total: " << elapsed.count() << "s con " << j << " threads.\n";
		

	}
		
	std::cout <<n_reinas <<"-reinas "<< "soluciones totales: "<< n_soluciones/4;
	
	return 0;
}



void comprobador(unsigned long long n)
{
	std::vector<int8_t> vector;

	while (n != 0) {
		int sobrante = (n % n_reinas);
		vector.push_back(sobrante + 1);
		n /= n_reinas;
	}


	int agregar = n_reinas - vector.size();
	for (int i = 0; i < agregar; i++)
		vector.push_back(1);

	for (int i = 0; i < vector.size() - 1; i++) {

		for (int j = i + 1; j < vector.size(); j++) {

			if (vector[i] == vector[j])
				return;

			if (abs((float)(vector[j] - vector[i]) / (float)((j + 1) - (i + 1))) == 1.0)
				return;

		}
	}

	/*
	for (int i = 0; i < vector.size(); i++) {

		for (int j = 0; j < vector.size(); j++) {
			if (vector[i] == j + 1) {
				std::cout << " R ";
			}
			else {
				std::cout << " - ";
			}
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	*/

	n_soluciones++;
}






