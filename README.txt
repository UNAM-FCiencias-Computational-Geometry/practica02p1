Geometría Computacional
Práctica 02 Parte 1 Barrido de línea
Autor: Gaspar Bautista Miguel Angel
Número de cuenta: 30613413-5

No se agregaron estructuras adicionales para esta práctica, se implemento el algoritmo de barrido de 
linea pero utilizando "fuerza bruta", este algoritmo, como sabemos tiene el tiempo de ejecución de 
O(n^2). Lo que hace este algoritmo es probar todos contra todos, nos tomamos dos apuntadores a la cabeza
de la lista y checamos que tmp1 sea distinto de NULL dentro de un while, dentro un while anidado ponemos
como condición que tmp2 sea distinto de NULL, entonces vamos iterando sobre tmp2 y checamos que la interseccion
sea distinta de NULL, si es así metemos el punto resultante en la lista que despues devolveremos.
hasta que tmp2 sea NULL vamos a mover a tmp1 y vamos a comparar nuevamente con todos las aristas.

Finalmente vamos a devolver la lista de puntos que estan en la intersección
