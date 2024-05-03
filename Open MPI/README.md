# Implementacion de PostmanSort

El funcionamiento general del algoritmo se basa en dividir el arreglo original en 10 sub arreglos (dependiendo del digito de mayor valor), de tal forma que todos los numeros que empiecen con cierto digito queden agrupados en su respectivo arreglo. Posteriormente estos subarreglos son ordenados con otro algoritmo de ordenamiento, para finalmente concatenarlos y obtener el resultado final. A continuacion se explica el codigo:

**1)**  Se define la longitud del arreglo aleatorio y la funcion que se usara para ordenar cada uno de los "buckets"
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
**2)**   Se declara la funcion principal, algunas constantes y se crea el arreglo de longitud len
```
int main()
{
    int t1, t2, k, t, n = 1;
    double start = omp_get_wtime();

    printf("The length of the array is: %d\n", len);

    count = len;
    for (i = 0; i < count; i++) {
        array[i] = rand() % len;
        array1[i] = array[i];            
    }
```

**3)**  Se halla el numero con mayor cantidad de digitos y se computa el valor $n = 10^{maxdigits-1}$, con el fin de tomar unicamente el digito de mayor valor.

```
for (i = 0; i < count; i++) {
        t = array[i];
        while(t > 0) {
            c++;
            t = t / 10;
        }
        if (maxdigits < c)
            maxdigits = c;
        c = 0;
    }

    printf("Checkpoint 1\n");

    while(--maxdigits)
        n = n * 10;
```

**4)**  Se inicializa la longitud de los "buckets" como 0 y se asignan los elementos del arreglo original a los 10 subarreglos, asegurando que cada proceso tiene su propio valor de k privado.

```
for (i = 0; i < 10; i++)
        bucket_count[i] = 0;
    
    #pragma omp parallel for private(k)
    for (i = 0; i < count; i++) {
        k = array[i] / n;
        #pragma omp critical
        {
            bucket[k][bucket_count[k]] = array[i];
            bucket_count[k]++;
        }
    }
```


**5)**  Paraleliza la ejecucion del bucle para ordenar los 10 sub-arreglos, rearregla la lista ya ordenada e imprime el tiempo.

```
#pragma omp parallel for
    for (i = 0; i < 10; i++) {
        sort_bucket(bucket[i], bucket_count[i]);
    }

    k = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < bucket_count[i]; j++) {
            array[k] = bucket[i][j];
            k++;
        }
    }

    double end = omp_get_wtime();
    printf("Time taken: %f\n", end - start);
```

El tiempo de ejecucion para un arreglo de 100,000 elementos sin paralelizar fue de 4.42 sgs, mientras que paralelizando fue de 0.56 sgs aproximadamente.

# Implementaciond de BinarySearch
