# Implementacion de PostmanSort

El funcionamiento general del algoritmo se basa en dividir el arreglo original en 10 sub arreglos (dependiendo del digito de mayor valor), de tal forma que todos los numeros que empiecen con cierto digito queden agrupados en su respectivo arreglo. Posteriormente estos subarreglos son ordenados con otro algoritmo de ordenamiento, para finalmente concatenarlos y obtener el resultado final. A continuacion se explica el codigo:

1)  Se define la longitud del arreglo aleatorio y la funcion que se usara para ordenar cada uno de los "buckets"
```
#define len 100000

int array[len], array1[len];
int i, j, temp, max, count, maxdigits = 0, c = 0;
int bucket[10][len], bucket_count[10];

void sort_bucket(int bucket[], int bucket_count) {
    int i, j, temp;
    for (i = 0; i < bucket_count; i++) {
        for (j = i + 1; j < bucket_count; j++) {
            if (bucket[i] > bucket[j]) {
                temp = bucket[i];
                bucket[i] = bucket[j];
                bucket[j] = temp;
            }
        }
    }
}
```

# Implementaciond de BinarySearch
