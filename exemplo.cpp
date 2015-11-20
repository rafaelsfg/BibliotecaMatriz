/*
 * exemplo.cpp
 *
 * Copyright 2014 Rafael Andrade <rafaelsandrade@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "matriz.cpp"
#include <cstdio>

int main(int argc, char **argv)
{
    matriz A, B, C;

    // Declara os vetores de números
    double v1[4] = { 2.0, 1.0,
                     0.5, -3.0 };

    double v2[2] = { 3.0, 4.0 };

    // Cria as matrizes A e B
    matriz_set_vetor(A, v1, 2, 2);
    matriz_set_vetor(B, v2, 2, 1);

    // Imprime as matrizes A e B
    printf("\nMatriz A:");
    matriz_imprimir(A);

    printf("\n\nMatriz B:");
    matriz_imprimir(B);

    // Calcula a inversa da matriz A
    if(matriz_inversa(C, A))
        std::cout<< "\nnão tem inversa\n";

    // Imprime a matriz inversa de A
    std::cout << "\n\nInversa de A:";
    matriz_imprimir(C);

    // Calcula C = A * B
    matriz_mul(C, A, B);

    // Imprime a matriz A * B
    std::cout << "\n\nMatriz A * B:";
    matriz_imprimir(C);

    return 0;
}

