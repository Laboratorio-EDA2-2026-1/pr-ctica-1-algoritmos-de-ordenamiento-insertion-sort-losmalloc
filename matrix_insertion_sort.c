/* 
    PRÁCTICA 1
    EQUIPO: LOS MALLOC
    EDA II
    GRUPO 01
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * EJERCICIO:
 * Se quiere definir un programa que, dada una matriz cuadrada con valores enteros,
 * devuelva una permutación de los valores de modo que:
 *
 * 1. Cada renglón esté ordenado de menor a mayor.
 * 2. Todos los elementos del segundo renglón (de arriba hacia abajo)
 *    sean mayores que los del primero, los del tercero mayores que los del segundo, etc.
 *
 * Regla importante:
 * - Cuando se ordenan los elementos de un renglón, por cada elemento de dicho renglón,
 *   se mueven también todos los elementos que se encuentran por debajo en la misma columna.
 *
 * INSTRUCCIONES:
 * - Completa la función sort_matrix() que debe modificar la matriz en su lugar.
 * - Puedes escribir funciones auxiliares si lo deseas.
 * - NO cambies la firma de sort_matrix().
 */

// Función para imprimir la matriz e ir viendo el procedimiento
void print_matrix(int **matrix, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función que va a permitir el intercambio de columnas completas
void cambio_columnas(int **matrix, int n, int a, int b, int ren){
    // n es para el tamaño de la matriz, a y b son las dos columnas a intercambiar
    for (int i = ren; i < n; i++) { // i es para recorrer cada renglón de la matriz
        int key = matrix[i][a]; // key es la variable temporal
        matrix[i][a] = matrix[i][b]; // cambio de valores
        matrix[i][b] = key; // regresamos el valor del temporal
    }
}

// Función para ordenar los renglones siguiendo la regla de mover la columna
void sort_renglones(int **matrix, int n){
    for (int ren = 0; ren < n; ren++){  // recorre cada renglón
       for (int col = 1; col < n; col++){   //empieza en el segundo elemento
            int comp = col - 1;     //compara el elemento anterior
            while (comp >= 0 && matrix[ren][comp] > matrix[ren][comp + 1]){
                cambio_columnas(matrix, n, comp, comp + 1, ren);
                comp--;
            }
       }
        printf("Después de ordenar el renglón %d:\n", ren + 1);
        print_matrix(matrix, n);
    }
}

// Transpone la matriz para después ordenarla de nuevo
void matriz_transpuesta(int **matrix, int n){
    for (int ren = 0; ren < n; ren++){
        for (int col = ren + 1; col < n; col++){ // solo recorrer la parte superior
            int temp = matrix[ren][col];
            matrix[ren][col] = matrix[col][ren];
            matrix[col][ren] = temp;
        }
    }
    printf("Matriz transpuesta\n");
    print_matrix(matrix, n);
}

// Función que compara si hay valores menores en otros renglones
void intercambio(int **matrix, int n){
    for (int ren = 0; ren < n - 1; ren++){  // recorre cada renglón
        int ultimo = matrix[ren][n - 1]; // último del renglón
        int primero = matrix[ren + 1][0];  // primero del siguiente renglón
        if (primero < ultimo){
            // intercambiar
            int temp = matrix[ren][n - 1];
            matrix[ren][n - 1] = matrix[ren + 1][0];
            matrix[ren + 1][0] = temp;
            printf("Matriz con valores intercambiados:\n\n");
            print_matrix(matrix, n);
            sort_renglones(matrix, n);
        }
    }
}
void sort_matrix(int **matrix, int n) {
    // TODO: Implementa aquí el algoritmo.
    // Necesitarás el método de inserción,
    // pero recuerda aplicar la regla de mover toda la columna.
    
    sort_renglones(matrix, n);
    matriz_transpuesta(matrix, n);
    sort_renglones(matrix, n);
    intercambio(matrix, n);
}

int main() {
    int n = 3;
    // Reserva dinámica de la matriz
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Ejemplo de entrada
    int ejemplo[3][3] = {
        {4, 7, 2},
        {9, 5, 6},
        {8, 1, 3}
    };

    // Copiar ejemplo a la matriz dinámica
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ejemplo[i][j];
        }
    }

    printf("Matriz original:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Llamada a la función que deben completar
    sort_matrix(matrix, n);

    printf("\nMatriz ordenada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
