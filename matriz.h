/*
 * matriz.h
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


#ifndef MATRIZ_H
#define MATRIZ_H

class matriz
{
    private:
        double *m_ptr;  // Ponteiro para o vetor que contém a matriz
        long linha;     // Número de linhas da matriz
        long coluna;    // Número de colunas da matriz

    public:
        /*   Operações aritméticas  */
        friend int  matriz_add(matriz&, const matriz&, const matriz& );
        friend int  matriz_sub(matriz&, const matriz&, const matriz& );
        friend int  matriz_mul(matriz&, const matriz&, const matriz& );
        friend void matriz_mul(matriz&, const double&, const matriz& );

        /*   Funções   */
        friend void   matriz_transposta(matriz&, const matriz&);
        friend int    matriz_inversa(matriz&, const matriz&);
        friend double matriz_det(const matriz&);

        /*   Gerar matrizes  */
        friend int matriz_nula(matriz&, long, long);
        friend int matriz_identidade(matriz&, long);
        friend int matriz_set_vetor(matriz&, const double*, long, long);

        /*   Outras funções  */
        friend void matriz_copiar(matriz&, const matriz& );
        friend void matriz_imprimir( const matriz& );
        friend bool matriz_eh_igual(const matriz&, const matriz&);

        matriz();
        virtual ~matriz();
};

#endif /* MATRIZ_H */
