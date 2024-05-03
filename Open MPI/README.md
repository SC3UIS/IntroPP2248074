# Implementacion de PostmanSort

El funcionamiento general del algoritmo se basa en dividir el arreglo original en 10 sub arreglos (dependiendo del digito de mayor valor), de tal forma que todos los numeros que empiecen con cierto digito queden agrupados en su respectivo arreglo. Posteriormente estos subarreglos son ordenados con otro algoritmo de ordenamiento, para finalmente concatenarlos y obtener el resultado final.


```
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
```

# Implementaciond de BinarySearch
