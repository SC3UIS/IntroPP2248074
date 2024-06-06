# Parcial 1

Autor: Edward Andres Sandoval Pineda 2248074

## BinarySearch
Por otro lado, el binary search es una técnica de búsqueda eficiente que divide repetidamente una lista en dos mitades, comparando el elemento buscado con el valor medio. En su implementación paralela, se asignan distintos subconjuntos de datos a múltiples procesadores, los cuales realizan la búsqueda simultáneamente. Cada procesador ejecuta una búsqueda binaria en su subconjunto, reduciendo significativamente el tiempo total de búsqueda. Los resultados de cada búsqueda paralela se combinan al final para proporcionar el resultado final de la búsqueda. Este enfoque paralelo se destaca en la búsqueda en listas extensas, distribuyendo eficazmente la carga de trabajo entre múltiples recursos computacionales.

La salida del programa implementado se encuentra en: Binary_Search_MPI_result.txt

## PostmanSort
El Postman Sort es un algoritmo de ordenamiento que se inspira en la eficiencia de los carteros al entregar correo. En la versión paralela de este algoritmo, se asignan diferentes subconjuntos de datos a diferentes procesadores, quienes los organizan utilizando un método de ordenamiento eficiente, como quicksort o mergesort. Después, los resultados se fusionan para obtener la lista completa ordenada, acelerando el proceso de clasificación.

La salida del programa se encuentra en: Postman_Search_MPI_result.txt