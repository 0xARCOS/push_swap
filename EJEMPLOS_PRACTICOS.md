# EJEMPLOS PRÁCTICOS - PUSH_SWAP

## 🧪 CASOS DE PRUEBA PARA PRACTICAR

### Ejemplo 1: Sort Three - Caso [2,1,3]

**Input:**
```bash
./push_swap 2 1 3
```

**Análisis paso a paso:**
```
A: [2,1,3]  B: []

sort_stack() → size = 3 → sort_three()

Valores:
  first = 2
  second = 1
  third = 3

Condición: first > second && second < third && first < third
  2 > 1? Sí
  1 < 3? Sí
  2 < 3? Sí
  → Ejecutar sa

Resultado:
A: [1,2,3]  B: []

Output: sa
```

**Operaciones totales: 1**

---

### Ejemplo 2: Sort Three - Caso [3,2,1]

**Input:**
```bash
./push_swap 3 2 1
```

**Análisis:**
```
A: [3,2,1]  B: []

Condición: first > second && second > third
  3 > 2? Sí
  2 > 1? Sí
  → Ejecutar sa + rra

Paso 1 - sa:
A: [2,3,1]  B: []

Paso 2 - rra:
A: [1,2,3]  B: []

Output:
sa
rra
```

**Operaciones totales: 2**

---

### Ejemplo 3: Sort Five - Paso a paso

**Input:**
```bash
./push_swap 3 5 1 4 2
```

**Traza completa:**

```
ESTADO INICIAL:
A: [3,5,1,4,2]  B: []
size = 5

sort_stack() → size = 5 → sort_five()

─────────────────────────────────────
FASE 1: Mover mínimos a B
─────────────────────────────────────

Iteración 1: size = 5 (> 3)
  find_min_pos([3,5,1,4,2]) → pos = 2 (valor 1)
  pos=2, size=5, 2 <= 5/2? 2 <= 2.5? Sí → usar ra

  ra:  [3,5,1,4,2] → [5,1,4,2,3]
  ra:  [5,1,4,2,3] → [1,4,2,3,5]
  pb:  A:[4,2,3,5]  B:[1]

Iteración 2: size = 4 (> 3)
  find_min_pos([4,2,3,5]) → pos = 1 (valor 2)
  pos=1, size=4, 1 <= 4/2? 1 <= 2? Sí → usar ra

  ra:  [4,2,3,5] → [2,3,5,4]
  pb:  A:[3,5,4]  B:[2,1]

─────────────────────────────────────
FASE 2: Ordenar los 3 que quedan
─────────────────────────────────────

A: [3,5,4]

sort_three([3,5,4]):
  first=3, second=5, third=4
  Condición: first < second && second > third && first < third
    3 < 5? Sí
    5 > 4? Sí
    3 < 4? Sí
    → Ejecutar sa + ra

  sa:  [3,5,4] → [5,3,4]
  ra:  [5,3,4] → [3,4,5]

Estado: A:[3,4,5]  B:[2,1]

─────────────────────────────────────
FASE 3: Devolver de B a A
─────────────────────────────────────

pa:  A:[2,3,4,5]  B:[1]
pa:  A:[1,2,3,4,5]  B:[]

RESULTADO FINAL:
A: [1,2,3,4,5]  B: []

Output:
ra
ra
pb
ra
pb
sa
ra
pa
pa
```

**Operaciones totales: 9**

**Nota:** Los elementos que se mueven a B salen en orden (primero el más pequeño), por eso al devolverlos quedan ordenados.

---

### Ejemplo 4: Chunk Sort - Conceptual

**Input:** 20 números
```bash
./push_swap 15 3 18 7 1 12 19 5 9 14 2 17 6 11 4 16 8 13 10 20
```

**Assign Indexes:**
```
Valores:    [15, 3, 18, 7, 1, 12, 19, 5, 9, 14, 2, 17, 6, 11, 4, 16, 8, 13, 10, 20]
Índices:    [14, 2, 17, 6, 0, 11, 18, 4, 8, 13, 1, 16, 5, 10, 3, 15, 7, 12, 9, 19]
```

**Cálculo de chunks:**
```
size = 20
chunks = 5 (porque size <= 100)
chunk = 20 / 5 + 1 = 5
```

**Rangos de chunks:**
```
Chunk 1: índices [0-4]    → valores: 1, 2, 3, 4, 5
Chunk 2: índices [5-9]    → valores: 6, 7, 8, 9, 10
Chunk 3: índices [10-14]  → valores: 11, 12, 13, 14, 15
Chunk 4: índices [15-19]  → valores: 16, 17, 18, 19, 20
```

**Push Chunks (simplificado):**

```
A: [15,3,18,7,1,12,19,5,9,14,2,17,6,11,4,16,8,13,10,20] (índices: [14,2,17,6,0,11,18,4,8,13,1,16,5,10,3,15,7,12,9,19])
B: []
pushed = 0, limit = 5

Buscar índices < 5 (valores 1,2,3,4,5):

top=15(i=14), 14 < 5? No → ra
top=3(i=2), 2 < 5? Sí → pb
  2 >= 5-5/2 (2 >= 2)? Sí → rb
pushed=1

top=18(i=17), 17 < 5? No → ra
top=7(i=6), 6 < 5? No → ra
top=1(i=0), 0 < 5? Sí → pb
  0 >= 2? No → no rb
pushed=2

... continuar hasta pushed = 5 ...

Cuando pushed == 5:
  limit = 5 + 5 = 10
  Ahora buscar índices 5-9 (valores 6,7,8,9,10)

... repetir para todos los chunks ...

Al final, B contiene todos los elementos semi-ordenados
```

**Push Back:**
```
B contiene todos los elementos
Repetir hasta que B esté vacío:
  1. Encontrar el índice máximo en B
  2. Rotarlo hasta arriba
  3. pa

Los elementos van saliendo en orden 19,18,17,...,1,0
A queda ordenado: [0,1,2,3,...,19]
```

---

## 🔍 CASOS DE ERROR

### Error 1: Duplicados

**Input:**
```bash
./push_swap 1 2 3 2
```

**Traza:**
```
parse_input():
  split_args() → ["1","2","3","2"]
  add_arguments() → stack: [1,2,3,2]
  has_duplicates():
    current=1, runner=[2,3,2] → no duplicado
    current=2, runner=[3,2] → no duplicado
    current=3, runner=[2]
      3 == 2? No
    current=2, runner=[]

¡ESPERA! Error en mi análisis...

Corrección:
    current=1, runner=[2,3,2]
      1 == 2? No
      1 == 3? No
      1 == 2? No
    current=2 (primer 2), runner=[3,2]
      2 == 3? No
      2 == 2? SÍ → return 1

Output: Error
```

---

### Error 2: Overflow

**Input:**
```bash
./push_swap 2147483648
```

**Traza:**
```
ft_atoi_push_swap("2147483648", &error):
  result = 0
  sign = 1

  Loop:
    result = 0*10 + 2 = 2
    result = 2*10 + 1 = 21
    result = 21*10 + 4 = 214
    result = 214*10 + 7 = 2147
    ...
    result = 214748364*10 + 8 = 2147483648

    Check: sign==1 && result > INT_MAX?
           1==1 && 2147483648 > 2147483647?
           Sí → error_flag = 1, return 0

add_node():
  create_node():
    error = 1 → free(new), return NULL
  return 0

parse_input():
  add_arguments() falló → free todo, return NULL

main():
  stack_a == NULL → write "Error\n", return 1

Output: Error
```

---

### Error 3: String vacío

**Input:**
```bash
./push_swap ""
```

**Traza:**
```
validate_args():
  has_only_spaces(""):
    s[0] == '\0'
    while(s[0]) → false, no entra al loop
    return 1 (es solo espacios)

  write "Error\n"
  return 0

main() → return 1

Output: Error
```

---

### Error 4: Solo signo

**Input:**
```bash
./push_swap +
```

**Traza:**
```
is_valid_number("+"):
  str[0] == '+' → i = 1
  str[1] == '\0' → return 0 (no hay dígitos)

add_arguments():
  is_valid_number falló → return 0

parse_input():
  add_arguments falló → free, return NULL

Output: Error
```

---

## 🎯 EJERCICIOS DE PRÁCTICA

### Ejercicio 1: Traza Manual de sort_three

Traza los siguientes casos sin mirar el código:

1. `[1,3,2]` → ¿?
2. `[3,1,2]` → ¿?
3. `[2,3,1]` → ¿?

**Soluciones:**
```
1. [1,3,2]
   first < second && second > third && first < third
   → sa + ra
   sa: [3,1,2]
   ra: [1,2,3]

2. [3,1,2]
   first > second && second < third && first > third
   → ra
   [1,2,3]

3. [2,3,1]
   first < second && second > third && first > third
   → rra
   [1,2,3]
```

---

### Ejercicio 2: Predecir Operaciones

Para cada input, predice cuántas operaciones se ejecutarán:

1. `./push_swap 1 2` → ¿?
2. `./push_swap 2 1` → ¿?
3. `./push_swap 1 2 3 4 5` → ¿?

**Soluciones:**
```
1. Ya ordenado → 0 operaciones

2. size == 2
   (*a)->value > (*a)->next->value? 2 > 1? Sí
   → sa
   1 operación

3. Ya ordenado → 0 operaciones
```

---

### Ejercicio 3: Debugging Mental

¿Qué imprime este programa?

```bash
./push_swap "4 2 3" "1"
```

**Análisis:**
```
argv[1] = "4 2 3"
argv[2] = "1"

split_args():
  ft_split("4 2 3", ' ') → ["4","2","3"]
  ft_split("1", ' ') → ["1"]
  tokens = ["4","2","3","1",NULL]

add_arguments():
  Crear stack: [4,2,3,1]

has_duplicates(): No

is_sorted([4,2,3,1]): No

sort_stack():
  size = 4 → sort_five()

  Fase 1: Mover mínimo (1) a B
    find_min_pos([4,2,3,1]) → pos = 3
    pos=3, size=4, 3 > 4/2? Sí → usar rra
    rra: [1,4,2,3]
    pb: A:[4,2,3] B:[1]

  Fase 2: sort_three([4,2,3])
    first=4, second=2, third=3
    Condición: first > second && second < third && first > third
      4 > 2? Sí
      2 < 3? Sí
      4 > 3? Sí
      → ra
    ra: [2,3,4]

  Fase 3: Devolver B
    pa: A:[1,2,3,4]

Output:
rra
pb
ra
pa
```

**Operaciones totales: 4**

---

## 📊 TABLA DE COMPLEJIDADES

| Función | Complejidad | Explicación |
|---------|-------------|-------------|
| `stack_size()` | O(n) | Recorre toda la lista |
| `is_sorted()` | O(n) | Recorre la lista una vez |
| `has_duplicates()` | O(n²) | Doble bucle anidado |
| `ft_split()` | O(n) | Recorre el string dos veces |
| `sort_array()` | O(n²) | Bubble/selection sort |
| `assign_indexes()` | O(n²) | sort_array + set_indexes |
| `set_indexes()` | O(n²) | Para cada nodo busca en array |
| `find_min_pos()` | O(n) | Recorre la lista una vez |
| `find_max_index()` | O(n) | Recorre la lista una vez |
| `find_pos_by_index()` | O(n) | Recorre la lista una vez |
| `sort_three()` | O(1) | Número fijo de comparaciones |
| `sort_five()` | O(n²) | Llama a stack_size múltiples veces |
| `push_chunks()` | O(n²) | Rotaciones pueden ser O(n) |
| `push_back()` | O(n²) | Para cada elemento busca máximo |
| `chunk_sort()` | O(n²) | push_chunks + push_back |

---

## 💡 TRUCOS PARA LA DEFENSA

### Truco 1: Explicar con Ejemplos Concretos

**Mal:**
"assign_indexes asigna índices normalizados a cada nodo"

**Bien:**
"assign_indexes convierte los valores en índices de 0 a n-1. Por ejemplo, si tengo [42, 3, 18], los convierte en índices [2, 0, 1] porque 3 es el más pequeño (índice 0), 18 es el mediano (índice 1), y 42 es el más grande (índice 2)."

---

### Truco 2: Mencionar Trade-offs

**Cuando te pregunten sobre optimizaciones:**

"Podría cambiar el bubble sort por quicksort en assign_indexes, pasando de O(n²) a O(n log n). Sin embargo, para los tamaños que maneja push_swap (máximo 500 elementos), el beneficio real es limitado porque esta operación solo se ejecuta una vez. Prioricé la simplicidad del código."

---

### Truco 3: Admitir Limitaciones

**Si te preguntan por el rendimiento con millones de números:**

"El algoritmo actual es O(n²), lo que lo haría impracticable para millones de elementos. Para escalar a ese nivel, necesitaría implementar un algoritmo de ordenación más eficiente como merge sort o quicksort, que son O(n log n). Sin embargo, el subject de push_swap está optimizado para hasta 500 elementos, donde chunk sort funciona bien."

---

### Truco 4: Conectar con el Subject

**Recuerda mencionar:**
- "Según el subject, con 500 números una buena puntuación es <5500 movimientos"
- "El subject requiere detectar duplicados y números fuera de rango de int"
- "Las operaciones permitidas son solo las 11 especificadas: sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr"

---

### Truco 5: Demostrar que Entiendes el Por Qué

**Cuando expliques chunk sort:**

"Uso chunk sort porque divide el problema en partes manejables. Si intentara ordenar 500 números de golpe, tendría que hacer muchas rotaciones costosas. Al dividirlo en chunks de ~45 elementos, proceso primero los más pequeños, luego los medianos, y finalmente los más grandes. Esto reduce drásticamente el número de movimientos necesarios."

---

## 🚨 ERRORES COMUNES EN DEFENSAS

### Error 1: No saber qué hace index

❌ "index es un número que guardo en cada nodo"

✅ "index es la posición normalizada del valor en el array ordenado. Me permite trabajar con rangos predecibles (0 a n-1) independientemente de los valores reales. Por ejemplo, si tengo valores [-1000, 5, 999], sus índices serían [0, 1, 2]."

---

### Error 2: Confundir value e index

❌ "Ordeno por index"

✅ "Asigno índices basados en los valores ordenados, luego uso esos índices para chunk sort. Al final, los índices ordenados ascendentemente corresponden a valores ordenados ascendentemente."

---

### Error 3: No saber explicar el límite de chunk

❌ "Uso chunk / 2 porque... no sé"

✅ "En push_chunks, cuando muevo un elemento a B, si su índice está en la mitad superior del chunk actual (>= limit - chunk/2), hago rb. Esto pre-ordena B ligeramente, poniendo elementos más grandes más abajo y elementos más pequeños más arriba, lo que facilita push_back."

---

### Error 4: No saber el propósito de cada fase

❌ "push_chunks mueve cosas a B"

✅ "push_chunks implementa la fase 1 del chunk sort: mueve elementos de A a B procesando por rangos de índices (chunks). Primero mueve elementos con índices 0-chunk, luego chunk-2*chunk, etc. Esto distribuye los elementos en B de forma semi-ordenada."

---

## 📚 PREGUNTAS DE REPASO

### Nivel Básico

1. ¿Qué estructura de datos usas para los stacks?
2. ¿Cuántas operaciones hay en total?
3. ¿Qué hace la operación sa?
4. ¿Qué hace la operación pb?
5. ¿Cómo detectas duplicados?

### Nivel Intermedio

6. ¿Por qué usas assign_indexes?
7. ¿Cómo funciona sort_three?
8. ¿Cuál es la estrategia de sort_five?
9. ¿Qué son los chunks en chunk_sort?
10. ¿Cómo decides entre ra y rra?

### Nivel Avanzado

11. ¿Cuál es la complejidad de tu algoritmo?
12. ¿Dónde está el cuello de botella en rendimiento?
13. ¿Cómo optimizarías assign_indexes?
14. ¿Por qué rb en la mitad superior del chunk?
15. ¿Qué pasaría si cambiaras 5 chunks a 3 chunks?

---

## ✅ RESPUESTAS CORTAS

### Nivel Básico

1. Lista enlazada simple (t_node con value, index, next)
2. 11 operaciones (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr)
3. Intercambia los dos primeros elementos de stack A
4. Mueve el primer elemento de A al tope de B
5. Bucle anidado que compara cada elemento con todos los siguientes

### Nivel Intermedio

6. Para normalizar valores a índices 0 a n-1 y simplificar chunk sort
7. Hardcodea los 6 casos posibles para usar máximo 2 operaciones
8. Mover los 2 mínimos a B, ordenar 3 en A, devolver B a A
9. Rangos de índices que proceso en orden (primero 0-chunk, luego chunk-2*chunk, etc.)
10. Si pos <= size/2 uso ra (más cerca del inicio), sino rra (más cerca del final)

### Nivel Avanzado

11. O(n²) en promedio y peor caso, O(n) en mejor caso (ya ordenado)
12. sort_array() en assign_indexes y búsquedas lineales en push_back
13. Cambiar bubble sort por quicksort (O(n log n))
14. Pre-ordena B poniendo elementos grandes más abajo, facilita encontrar el máximo después
15. Chunks más grandes → menos precisión, más movimientos → peor rendimiento

---

¡Suerte en tu defensa! 🎓
