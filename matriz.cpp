/*
 * matriz.cpp
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


#include "matriz.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////////////
////////////////*   Operações aritméticas  *//////////////////////////
//////////////////////////////////////////////////////////////////////

// Adição: X = A + B
int matriz_add(matriz& X, const matriz& A, const matriz& B)
{
    if (A.linha != B.linha || A.coluna != B.coluna) return 1;

    long n = A.linha * A.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = A.m_ptr[i] + B.m_ptr[i];

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    X.linha = A.linha;
    X.coluna = A.coluna;
    return 0;
}

// Subtração: X = A -B
int matriz_sub(matriz& X, const matriz& A, const matriz& B)
{
    if (A.linha != B.linha || A.coluna != B.coluna) return 1;

    long n = A.linha * A.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = A.m_ptr[i] - B.m_ptr[i];

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    X.linha = A.linha;
    X.coluna = A.coluna;
    return 0;
}

// MUltiplicação: X = A * B
int matriz_mul(matriz& X, const matriz& A, const matriz& B)
{
    if (A.coluna != B.linha) return 1;

    long n = A.linha * B.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)    {
        ptr[i] = 0.0;
        for (long j = 0; j < A.coluna; j++ )
            ptr[i] += A.m_ptr[i / B.coluna * A.coluna + j] * B.m_ptr[j * B.coluna + i % B.coluna];
    }

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    X.linha = A.linha;
    X.coluna = B.coluna;
    return 0;
}

// MUltiplicação por escalar: X = k * B
void matriz_mul(matriz& X, const double& k, const matriz& A)
{
    long n = A.linha * A.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = k * A.m_ptr[i];

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    X.linha = A.linha;
    X.coluna = A.coluna;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////*   Funções   */////////////////////////////
//////////////////////////////////////////////////////////////////////

// Matriz transposta
void matriz_transposta(matriz& X, const matriz& A)
{
    long n = A.linha * A.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = A.m_ptr[( i % A.linha ) * A.coluna + i / A.linha];

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    n = A.linha;
    X.linha = A.coluna;
    X.coluna = n;
}

// Matriz inversa
int matriz_inversa(matriz& X, const matriz& A)
{
    if (A.coluna != A.linha) return 1;

    long n = A.linha * A.coluna;

    double *inv = new double[n];
    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = A.m_ptr[i];    // Copia para 'ptr' o conteúdo de 'A'

    long j = 0;

    for (long i = 0; i < n; i++) {  // 'inv' recebe matriz identidade
        if(i == (j * (A.linha + 1))) {
            inv[i] = 1.0;
            j++;
        }
        else inv[i] = 0.0;
    }

    j = 0;
    double pivo;

    ////////    Escalona a parte inferior
    for (long i = 0; i < A.linha; i++) {
        if (ptr[i * ( A.linha + 1 )] == 0.0) {  // Verifica se o pivo é nulo
            for (j = i + 1; j < A.linha; j++) { // Procura o valor não nulo abaixo do pivo
                if (ptr[i + j * A.linha] != 0.0) {
                    for (long k = 0; k < A.linha; k++) {
                        // Soma a linha do pivo nulo com a linha abaixo
                        ptr[k + i * A.linha] += ptr[k + j * A.linha];
                        inv[k + i * A.linha] += inv[k + j * A.linha];
                    }
                    break;
                }
            }

            if (j == A.linha) { // Se não achar retorna matriz nula
                delete[] ptr;   // a matriz não tem inversa
                delete[] inv;
                return 1;
            }
        }

        for (j = i + 1; j < A.linha; j++) { // Zera os elementos abaixo do pivô
            if (ptr[i + j * A.linha] != 0.0) {  // Ignora se elemento é nulo
                pivo = ptr[i + j * A.linha] / ptr[i * (A.linha + 1)];
                for(long k = 0; k < A.linha; k++) {
                    ptr[k + j * A.linha] -= ptr[k + i * A.linha] * pivo;
                    inv[k + j * A.linha] -= inv[k + i * A.linha] * pivo;
                }
            }
        }
    }

    //////// Escalona a parte superior
    for(long i = A.linha - 1; i >= 0; i--) {
        for(j = i - 1; j >= 0; j--) {   // Zera os elementos abaixo do pivô
            if(ptr[i + j * A.linha] != 0.0) {   // Ignora se elemento é nulo
                pivo = ptr[i + j * A.linha] / ptr[i * (A.linha + 1)];
                for(long k = A.linha - 1; k >= 0; k-- ) {
                    ptr[k + j * A.linha] -= ptr[k + i * A.linha] * pivo;
                    inv[k + j * A.linha] -= inv[k + i * A.linha] * pivo;
                }
            }
        }
    }

    //////// Transformando os elementos da coluna principal de 'ptr' em '1'
    for(long i = 0; i < A.linha; i++) {
        pivo = ptr[i * (A.linha + 1)];
        for(j = 0; j < A.linha; j++) {
            ptr[j + i * A.linha] /= pivo;
            inv[j + i * A.linha] /= pivo;
        }
    }

    delete[] X.m_ptr;
    X.m_ptr = inv;
    X.linha = A.linha;
    X.coluna = A.linha;
    delete[] ptr;

    return 0;
}

// Determinante da matriz (método da triangulação)
double matriz_det(const matriz& A)
{
    double det = 1.0, pivo;

    if (A.coluna != A.linha) return nan("");

    long j = 0;
    long n = A.linha * A.linha;
    double *ptr = new double[n];

    for (int i = 0; i < n; i++ )
        ptr[i] = A.m_ptr[i]; // Copia A para 'ptr'

    for (long i = 0; i < A.linha; i++)  {
        if (ptr[i * (A.linha + 1)] == 0.0) {    // Verifica se o pivo é nulo
            for (j = i + 1; j < A.linha; j++) { // Procura o valor não nulo abaixo do pivo
                if (ptr[i + j * A.linha] != 0.0) {
                    for (long k = i; k < A.linha; k++) // Soma a linha do pivo nulo com a linha abaixo
                        ptr[k + i * A.linha] += ptr[k + j * A.linha];
                    break;
                }
            }
            if (j == A.linha) { // Se não achar o valor não nulo abaixo do pivo, retorna 0
                delete ptr;
                return 0.0;
            }
        }

        for (long j = i + 1; j < A.linha; j++) {    // Zera os elementos abaixo do pivô
            if (ptr[i + j * A.linha] != 0.0 ) { // Ignora se elemento é nulo
                pivo = ptr[i + j * A.linha] / ptr[i * ( A.linha + 1 )];
                for(long k = i; k < A.linha; k++)
                    ptr[k + j * A.linha] -= ptr[k + i * A.linha] * pivo;
            }
        }
    }

    for (long i = 0; i < A.linha; i++)
        det *= ptr[i * (A.linha + 1)]; // Multiplica os elementos da coluna principal

    delete[] ptr;
    return det;
}

//////////////////////////////////////////////////////////////////////
///////////////////////*   Gerar matrizes   */////////////////////////
//////////////////////////////////////////////////////////////////////

// Cria uma matriz nula de 'l' linhas e 'c' colunas
int matriz_nula(matriz& X, long l, long c)
{
    if (l < 1 || c < 1) return 1;

    long n = l * c;

    delete[] X.m_ptr;
    X.m_ptr = new double[n];
    X.linha = l;
    X.coluna = c;

    for (long i = 0; i < n; i++)
        X.m_ptr[i] = 0.0;

    return 0;
}

// Cria uma matriz identidade de ordem  'n'
int matriz_identidade(matriz& X, long n)
{
    if (n < 1) return 1;

    long N = n * n;

    delete[] X.m_ptr;
    X.m_ptr = new double[N];
    X.linha = n;
    X.coluna = n;

    long j = 0;

    for (long i = 0; i < N; i++) {
        if ( i == j * (1 + n)) {
            X.m_ptr[i] = 1.0;
            j++;
        }
        else X.m_ptr[i] = 0.0;
    }

    return 0;
}

//  Converte um vetor em matriz
int matriz_set_vetor(matriz& X, const double* v, long l, long c)
{
    if (l < 1 || c < 1) return 1;

    long n = l * c;

    delete[] X.m_ptr;
    X.m_ptr = new double[n];

    for (long i = 0; i < n; i++)
        X.m_ptr[i] = v[i];

    X.linha = l;
    X.coluna = c;
    return 0;
}

//////////////////////////////////////////////////////////////////////
///////////////////////*   Outras funções   */////////////////////////
//////////////////////////////////////////////////////////////////////

// Cria uma cópia da matriz: X <-- A
void matriz_copiar(matriz& X, const matriz& A)
{
    long n = A.linha * A.coluna;

    double *ptr = new double[n];

    for (long i = 0; i < n; i++)
        ptr[i] = A.m_ptr[i];

    delete[] X.m_ptr;
    X.m_ptr = ptr;
    X.linha = A.linha;
    X.coluna = A.coluna;
}

//  Imprime a matriz
void matriz_imprimir( const matriz& A )
{
    long n = A.linha * A.coluna;
    std::cout.precision(7);
    std::cout << "\n|";
    std::cout.width(13);
    std::cout << std::right << A.m_ptr[0] << " ";

    for (long i = 1; i < n; i++ )   {
        if(i % A.coluna == 0 ) std::cout << "|\n|";
        std::cout.width(13);
        std::cout << std::right << A.m_ptr[i] << " ";
    }

    std::cout << "|";
}

// Verifica se duas matrizes são iguais
bool matriz_eh_igual(const matriz& A, const matriz& B)
{
    if (A.linha != B.linha || A.coluna != B.coluna) return false;

    long n = A.linha * A.coluna;

    for (long i = 0; i < n; i++ )
        if (A.m_ptr[i] != B.m_ptr[i]) return false;

    return true;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

matriz::matriz()
{
    m_ptr = new double;
    *m_ptr = 0.0;
    linha = 1;
    coluna = 1;
}

matriz::~matriz()
{
    delete[] m_ptr;
}

