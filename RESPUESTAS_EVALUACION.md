# Respuestas Evaluación Push_swap

## 1. Flujo completo desde main hasta sort_stack

**Flujo del programa:**

```
main (src/main.c:49)
  ↓
  Validación de argumentos (validate_args)
  ↓
  parse_input (src/parse/parse_input.c:95)
  ↓
  is_sorted - verifica si ya está ordenado (src/algorithm/sort.c:15)
  ↓
  sort_stack (src/algorithm/sort.c:26)
```

**Detalle paso a paso:**

1. **main.c:49-72**:
   - Inicializa stack_a y stack_b a NULL
   - Si argc < 2, termina sin hacer nada
   - Valida que los argumentos no sean solo espacios
   - Llama a `parse_input()` para crear el stack
   - Si el parsing falla, imprime "Error\n" y sale
   - Verifica si el stack ya está ordenado con `is_sorted()`
   - Si ya está ordenado, libera memoria y termina
   - Si no está ordenado, llama a `sort_stack()`
   - Libera ambos stacks al finalizar

2. **sort_stack.c:26-50**:
   - Obtiene el tamaño del stack
   - Si size == 2: hace `sa` si están desordenados
   - Si size == 3: llama a `sort_three()`
   - Si size <= 5: llama a `sort_five()`
   - Si size > 5:
     - Llama a `assign_indexes()` para asignar índices relativos
     - Si size <= 100: usa `chunk_sort()` con 5 chunks
     - Si size > 100: usa `chunk_sort()` con 11 chunks

---

## 2. Cómo funciona el parsing (split → tokens → stack)

**Proceso de parsing en detalle:**

### Fase 1: Validación inicial (main.c:32-47)
```c
validate_args() → verifica que no haya argumentos vacíos o solo espacios
```

### Fase 2: Split de argumentos (parse_input.c:55-79)
```c
split_args(argc, argv)
  ↓
  1. Cuenta total de tokens con count_all_tokens()
  2. Reserva memoria para array de tokens
  3. Para cada argv[i]:
     - Hace ft_split(argv[i], ' ') → separa por espacios
     - Copia cada token individual con ft_strdup()
     - Libera el split temporal
  4. Retorna array de strings (tokens)
```

**Ejemplo:**
```
Entrada: ./push_swap "3 2 1" "5 4"
Tokens: ["3", "2", "1", "5", "4", NULL]
```

### Fase 3: Conversión a stack (parse_input.c:95-115)
```c
parse_input(argc, argv)
  ↓
  1. Obtiene array de tokens
  2. Para cada token:
     - Valida que sea número válido con is_valid_number()
     - Convierte a entero con ft_atoi_push_swap()
     - Crea nodo con malloc() y lo añade al final del stack
  3. Verifica duplicados con has_duplicates()
  4. Si todo OK, retorna el stack
  5. Si hay error, libera todo y retorna NULL
```

**Estructura del nodo:**
```c
typedef struct s_node {
    int value;        // Valor del número
    int index;        // Índice relativo (para chunk_sort)
    struct s_node *next;  // Siguiente nodo
} t_node;
```

---

## 3. Detección de errores (duplicados, overflow, formato)

### Error 1: Formato inválido (parse_utils.c:38-56)
```c
is_valid_number(str)
  - String vacío → ERROR
  - Solo signo sin dígitos ("+", "-") → ERROR
  - Caracteres no numéricos → ERROR
  - Formato válido: [+/-]dígitos
```

**Ejemplos:**
- ✅ Válidos: "42", "-42", "+42", "0"
- ❌ Inválidos: "abc", "4a2", "+", "-", "", "1 2"

### Error 2: Overflow (atoi_utils.c:29-51)
```c
ft_atoi_push_swap(str, *error_flag)
  - Convierte usando tipo long
  - Si resultado > INT_MAX → error_flag = 1
  - Si resultado < INT_MIN → error_flag = 1
  - Límites: [-2147483648, 2147483647]
```

**Implementación:**
```c
if ((sign == 1 && result > INT_MAX) ||
    (sign == -1 && (-result) < INT_MIN))
{
    *error_flag = 1;
    return (0);
}
```

### Error 3: Duplicados (parse_input.c:15-33)
```c
has_duplicates(stack)
  - Usa dos punteros (current y runner)
  - Para cada nodo, compara con todos los siguientes
  - Si encuentra valor repetido → retorna 1
  - Complejidad: O(n²)
```

**Algoritmo:**
```
Para cada elemento i:
  Para cada elemento j > i:
    Si valor[i] == valor[j]:
      return 1 (hay duplicados)
return 0 (no hay duplicados)
```

### Error 4: Argumentos vacíos (main.c:16-30)
```c
has_only_spaces(str)
  - Verifica si el string solo contiene espacios o tabs
  - Si es solo espacios → Error
```

**Todos los errores imprimen:** `"Error\n"` en stderr

---

## 4. Las 11 operaciones del stack

### Operaciones de Swap (intercambio)
```c
sa (swap_ops.c:16-22)
  - Intercambia los 2 primeros elementos de stack a
  - Si a tiene < 2 elementos, no hace nada
  - Imprime: "sa\n"

sb (swap_ops.c:24-30)
  - Intercambia los 2 primeros elementos de stack b
  - Si b tiene < 2 elementos, no hace nada
  - Imprime: "sb\n"

ss (swap_ops.c:32-49)
  - Ejecuta sa y sb simultáneamente
  - Solo imprime si al menos uno tuvo efecto
  - Imprime: "ss\n"
```

**Implementación de swap_nodes:**
```c
void swap_nodes(t_node **stack)
{
    first = *stack;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *stack = second;
}
```

### Operaciones de Push (transferencia)
```c
pa (push_ops.c:16-22)
  - Toma el primer elemento de b
  - Lo pone al inicio de a
  - Si b está vacío, no hace nada
  - Imprime: "pa\n"

pb (push_ops.c:24-30)
  - Toma el primer elemento de a
  - Lo pone al inicio de b
  - Si a está vacío, no hace nada
  - Imprime: "pb\n"
```

**Implementación de push_node:**
```c
void push_node(t_node **dst, t_node **src)
{
    tmp = *src;           // Guarda el primer nodo de src
    *src = (*src)->next;  // Avanza src al siguiente
    tmp->next = *dst;     // Enlaza tmp con dst
    *dst = tmp;           // tmp es ahora el primero de dst
}
```

### Operaciones de Rotate (rotar hacia arriba)
```c
ra (rotate_ops.c:16-22)
  - El primer elemento pasa al final
  - Todos los demás suben una posición
  - Imprime: "ra\n"

rb (rotate_ops.c:24-30)
  - El primer elemento de b pasa al final
  - Imprime: "rb\n"

rr (rotate_ops.c:32-49)
  - Ejecuta ra y rb simultáneamente
  - Imprime: "rr\n"
```

**Implementación de rotate_nodes:**
```c
void rotate_nodes(t_node **stack)
{
    first = *stack;              // Guarda el primero
    *stack = first->next;        // El segundo es ahora el primero
    last = *stack;
    while (last->next)           // Busca el último
        last = last->next;
    last->next = first;          // Enlaza último con first
    first->next = NULL;          // first es ahora el último
}
```

**Ejemplo:**
```
Antes: [1, 2, 3, 4]
ra
Después: [2, 3, 4, 1]
```

### Operaciones de Reverse Rotate (rotar hacia abajo)
```c
rra (reverse_rotate_ops.c:16-22)
  - El último elemento pasa al inicio
  - Todos los demás bajan una posición
  - Imprime: "rra\n"

rrb (reverse_rotate_ops.c:24-30)
  - El último elemento de b pasa al inicio
  - Imprime: "rrb\n"

rrr (reverse_rotate_ops.c:32-49)
  - Ejecuta rra y rrb simultáneamente
  - Imprime: "rrr\n"
```

**Implementación de reverse_rotate_nodes:**
```c
void reverse_rotate_nodes(t_node **stack)
{
    prev = NULL;
    last = *stack;
    while (last->next)           // Busca el último y penúltimo
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;           // Desconecta el último
    last->next = *stack;         // Enlaza último con el primero
    *stack = last;               // last es ahora el primero
}
```

**Ejemplo:**
```
Antes: [1, 2, 3, 4]
rra
Después: [4, 1, 2, 3]
```

---

## 5. Algoritmo de 3 elementos (los 6 casos)

**Función:** `sort_three()` en sort_small.c:39-64

**Los 6 casos posibles:**

```c
Caso 1: [2, 1, 3]  (first > second < third, first < third)
  → sa
  → Resultado: [1, 2, 3]

Caso 2: [3, 2, 1]  (first > second > third)
  → sa + rra
  → Resultado: [1, 2, 3]

Caso 3: [3, 1, 2]  (first > second < third, first > third)
  → ra
  → Resultado: [1, 2, 3]

Caso 4: [2, 3, 1]  (first < second > third, first < third)
  → sa + ra
  → Resultado: [1, 2, 3]

Caso 5: [1, 3, 2]  (first < second > third, first > third)
  → rra
  → Resultado: [1, 2, 3]

Caso 6: [1, 2, 3]  (ya ordenado)
  → No hace nada
```

**Implementación:**
```c
void sort_three(t_node **a)
{
    first = (*a)->value;
    second = (*a)->next->value;
    third = (*a)->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);  // Caso 1
    else if (first > second && second > third)
    {
        sa(a);   // Caso 2
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);   // Caso 3
    else if (first < second && second > third && first < third)
    {
        sa(a);   // Caso 4
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);  // Caso 5
}
```

**Máximo de movimientos:** 2 operaciones

---

## 6. Algoritmo de 5 elementos (find min, push, sort 3, push back)

**Función:** `sort_five()` en sort_small.c:66-84

**Estrategia:**
1. Reducir el problema a 3 elementos
2. Ordenar esos 3 con sort_three()
3. Devolver los elementos previamente extraídos

### Paso 1: Find min y push a b
```c
while (stack_size(*a) > 3)
{
    pos = find_min_pos(*a);  // Encuentra posición del mínimo

    // Si está en la mitad superior, usa rotate
    if (pos <= stack_size(*a) / 2)
        while (pos-- > 0)
            ra(a);

    // Si está en la mitad inferior, usa reverse rotate
    else
        while (pos++ < stack_size(*a))
            rra(a);

    pb(a, b);  // Push el mínimo a b
}
```

**find_min_pos()** (sort_small.c:15-37):
```c
Recorre el stack completo
Guarda la posición del elemento mínimo
Retorna esa posición
```

### Paso 2: Sort three
```c
sort_three(a);  // Ordena los 3 elementos que quedan en a
```

### Paso 3: Push back
```c
while (*b)
    pa(a, b);  // Devuelve todos los elementos de b a a
```

**Resultado final:** Stack ordenado de menor a mayor

**Ejemplo completo:**
```
Inicial:     a=[5, 2, 4, 1, 3]  b=[]

1. Primer mínimo (1):
   ra -> [2, 4, 1, 3, 5]
   ra -> [4, 1, 3, 5, 2]
   ra -> [1, 3, 5, 2, 4]
   pb -> a=[3, 5, 2, 4]  b=[1]

2. Segundo mínimo (2):
   rra -> [4, 3, 5, 2]
   rra -> [2, 4, 3, 5]
   pb -> a=[4, 3, 5]  b=[2, 1]

3. Sort three:
   sort_three([4, 3, 5])
   sa -> [3, 4, 5]
   a=[3, 4, 5]  b=[2, 1]

4. Push back:
   pa -> a=[2, 3, 4, 5]  b=[1]
   pa -> a=[1, 2, 3, 4, 5]  b=[]

Final: [1, 2, 3, 4, 5] ✓
```

**Complejidad:** O(n²) en peor caso, pero n <= 5

---

## 7. Chunk sort (push_chunks + push_back)

**Función principal:** `chunk_sort()` en chunk_sort.c:90-99

**Estrategia:** Divide los elementos en "chunks" (fragmentos) y los procesa por grupos

### Configuración de chunks
```c
void chunk_sort(t_node **a, t_node **b, int chunks)
{
    size = stack_size(*a);
    chunk = size / chunks + 1;  // Tamaño de cada chunk

    push_chunks(a, b, chunk);
    push_back(a, b);
}
```

**Número de chunks según tamaño:**
- Si size <= 100: **5 chunks** → chunk_size ≈ 21
- Si size > 100: **11 chunks** → chunk_size ≈ 10

### Fase 1: push_chunks (chunk_sort.c:44-67)

**Algoritmo:**
```c
static void push_chunks(t_node **a, t_node **b, int chunk)
{
    size = stack_size(*a);
    pushed = 0;
    limit = chunk;  // Límite del primer chunk

    while (pushed < size)
    {
        // Si el elemento del top está en el chunk actual
        if ((*a)->index < limit)
        {
            pb(a, b);  // Push a b
            pushed++;

            // Optimización: rota b si el elemento es grande
            if ((*b)->index >= limit - chunk / 2)
                rb(b);
        }
        else
            ra(a);  // Si no está en el chunk, rota a

        // Cuando completa un chunk, aumenta el límite
        if (pushed == limit && limit < size)
            limit += chunk;
    }
}
```

**¿Por qué rb(b) selectivo?**
- Envía los elementos más grandes del chunk al fondo de b
- Deja los más pequeños arriba
- Facilita el push_back posterior

**Ejemplo con 10 elementos y 2 chunks:**
```
Índices: 0=mínimo, 9=máximo
chunk_size = 5

Stack inicial a (con índices): [7, 2, 8, 0, 5, 3, 9, 1, 4, 6]

Primer chunk (índices 0-4):
  - Busca elementos con index < 5
  - 2 → pb, rb (2 >= 2.5)
  - 7 → ra
  - 0 → pb, no rb (0 < 2.5)
  - ... continúa

Segundo chunk (índices 5-9):
  - limit = 10
  - Procesa los restantes
```

### Fase 2: push_back (chunk_sort.c:69-88)

**Algoritmo:**
```c
static void push_back(t_node **a, t_node **b)
{
    while (*b)
    {
        max = find_max_index(*b);    // Encuentra el índice máximo en b
        pos = find_pos_by_index(*b, max);  // Su posición
        size = stack_size(*b);

        // Mueve el máximo al top
        if (pos <= size / 2)
            while (pos-- > 0)
                rb(b);   // Desde arriba
        else
            while (pos++ < size)
                rrb(b);  // Desde abajo

        pa(a, b);  // Push el máximo a a
    }
}
```

**Estrategia:**
- Siempre saca el elemento más grande de b
- Lo pone en a
- Resultado: a queda ordenado de mayor a menor... ¡pero es correcto!
- En push_swap, el stack está ordenado si value[i] < value[i+1]

**Optimización de rotación:**
- Si el elemento está en la mitad superior: usa rb (rotate)
- Si está en la mitad inferior: usa rrb (reverse rotate)
- Minimiza el número de operaciones

---

## 8. Assign indexes (para qué sirve)

**Función:** `assign_indexes()` en assign_indexes.c:70-82

### ¿Para qué sirve?

**Problema:** Comparar valores absolutos es ineficiente
- Ejemplo: [-2147483648, 0, 2147483647, -1000, 500]

**Solución:** Usar índices relativos (ranking)
- 0 = el más pequeño
- 1 = el segundo más pequeño
- ...
- n-1 = el más grande

**Ventaja:** Simplifica la lógica de chunk_sort
- En vez de: "¿este valor está en el rango [-1000, 500]?"
- Ahora: "¿este índice está en el rango [0, 50]?"

### Algoritmo completo

**Paso 1: stack_to_array (assign_indexes.c:15-30)**
```c
Crea un array con todos los valores del stack
[42, -5, 100, 0, 17] → arr = [42, -5, 100, 0, 17]
```

**Paso 2: sort_array (assign_indexes.c:32-54)**
```c
Ordena el array usando bubble sort
arr = [-5, 0, 17, 42, 100]
```

**Paso 3: set_indexes (assign_indexes.c:56-68)**
```c
Para cada nodo del stack original:
  - Busca su valor en el array ordenado
  - La posición en el array es su índice
  - Asigna ese índice al nodo
```

### Ejemplo completo

```
Stack original:  [42, -5, 100, 0, 17]

1. Copia a array: [42, -5, 100, 0, 17]

2. Ordena array:  [-5, 0, 17, 42, 100]
                   ↑   ↑   ↑   ↑    ↑
                   0   1   2   3    4  (posiciones = índices)

3. Asigna índices:
   42  está en posición 3 → index = 3
   -5  está en posición 0 → index = 0
   100 está en posición 4 → index = 4
   0   está en posición 1 → index = 1
   17  está en posición 2 → index = 2

Stack con índices:
  value: [42,  -5, 100,  0, 17]
  index: [ 3,   0,   4,  1,  2]
```

### Uso en chunk_sort

```c
if ((*a)->index < limit)  // Compara índice, no valor
    pb(a, b);
```

**Ventajas:**
- Comparaciones simples con enteros pequeños
- Facilita la división en chunks
- No importa el rango de valores original

**Complejidad:** O(n²) por el sort_array

---

## 9. Gestión de memoria (todos los mallocs y frees)

### Mallocs (asignaciones)

#### 1. Parsing - Tokens
**Ubicación:** parse_input.c:62
```c
tokens = malloc(sizeof(char *) * (count_all_tokens(argc, argv) + 1));
```
- Reserva array de punteros a strings
- Tamaño: número de tokens + 1 (para NULL final)

#### 2. Parsing - Split temporal
**Ubicación:** split.c:97
```c
result = malloc(sizeof(char *) * (word_count(s, c) + 1));
```
- Usado en ft_split para separar strings
- Se libera inmediatamente después de usar

#### 3. Parsing - Strings individuales
**Ubicación:** split.c:42
```c
word = malloc(sizeof(char) * (len + 1));
```
- Cada token individual (ft_strdup también usa malloc)
- Se libera al final del parsing

#### 4. Stack - Nodos
**Ubicación:** parse_utils.c:63
```c
new = malloc(sizeof(t_node));
```
- Cada elemento del stack
- Contiene: value, index, next

#### 5. Assign indexes - Array temporal
**Ubicación:** assign_indexes.c:20
```c
arr = malloc(sizeof(int) * size);
```
- Array temporal para ordenar
- Se libera al final de assign_indexes

### Frees (liberaciones)

#### 1. Free de tokens/split
**Ubicación:** free_utils.c + parse_input.c
```c
void free_split(char **tokens)
{
    if (!tokens)
        return;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);  // Libera cada string
        i++;
    }
    free(tokens);  // Libera el array
}
```
- Libera strings individuales
- Luego libera el array de punteros

#### 2. Free de stack
**Ubicación:** free_utils.c
```c
void free_stack(t_node **stack)
{
    t_node *tmp;

    if (!stack || !*stack)
        return;
    while (*stack)
    {
        tmp = *stack;
        *stack = (*stack)->next;
        free(tmp);  // Libera cada nodo
    }
    *stack = NULL;
}
```
- Recorre toda la lista enlazada
- Libera cada nodo uno por uno

#### 3. Free del array en assign_indexes
**Ubicación:** assign_indexes.c:81
```c
free(arr);
```
- Libera el array temporal después de asignar índices

### Flujo completo de memoria

```
1. MAIN - Inicialización
   stack_a = NULL;
   stack_b = NULL;

2. PARSING
   tokens = malloc(...)           ← Array de punteros
   para cada token:
     token[i] = malloc(...)       ← String individual

   para cada token:
     new = malloc(sizeof(t_node)) ← Nodo del stack

   free_split(tokens)             → Libera todos los tokens

3. SORTING (si size > 5)
   arr = malloc(...)              ← Array temporal
   assign_indexes(...)
   free(arr)                      → Libera array

4. FIN - main.c:69-70
   free_stack(&stack_a)           → Libera todos los nodos de a
   free_stack(&stack_b)           → Libera todos los nodos de b

5. RETORNO
   return (0);
```

### Casos de error y liberación

```c
// Error en parsing
if (!tokens || !add_arguments(&stack, tokens))
{
    free_split(tokens);    // Libera tokens
    free_stack(&stack);    // Libera stack parcial
    return (NULL);
}

// Error por duplicados
if (has_duplicates(stack))
{
    free_stack(&stack);    // Libera todo el stack
    return (NULL);
}
```

### Verificación con Valgrind

Para verificar que no hay memory leaks:
```bash
valgrind --leak-check=full ./push_swap 3 2 1
```

**Resultado esperado:**
```
All heap blocks were freed -- no leaks are possible
```

---

## 10. Complejidad del algoritmo

### Análisis por casos

#### Caso 1: n = 2
```c
Operaciones: 0 o 1 (sa si desordenado)
Complejidad: O(1)
```

#### Caso 2: n = 3
```c
Operaciones: máximo 2 (sa + ra/rra)
Complejidad: O(1)
```

#### Caso 3: n <= 5
```c
Operaciones por fase:
  - find_min_pos: O(n)
  - rotate hasta min: O(n)
  - pb: O(1)
  - sort_three: O(1)
  - pa back: O(1) × 2

Total: O(n) × 2 iteraciones = O(n)
Movimientos típicos: ~12
```

#### Caso 4: n > 5 (chunk_sort)

**Subfases:**

1. **assign_indexes: O(n²)**
```c
stack_to_array:  O(n)
sort_array:      O(n²)  ← Bubble sort
set_indexes:     O(n²)  ← Para cada nodo, busca en array
Total:           O(n²)
```

2. **push_chunks: O(n × k)**
```c
Para cada elemento (n iteraciones):
  - Verifica índice: O(1)
  - pb o ra: O(1)
  - rb condicional: O(1)

Total operaciones: aproximadamente n × (k rotaciones promedio)
  donde k = número de chunks

Para n=100, chunks=5:  ~500 operaciones
Para n=500, chunks=11: ~5000 operaciones
```

3. **push_back: O(n²)**
```c
Para cada elemento en b (n iteraciones):
  - find_max_index: O(n)
  - find_pos: O(n)
  - rotate hasta max: O(n)
  - pa: O(1)

Total: n × O(n) = O(n²)
```

### Complejidad total

```
Función              Tiempo      Espacio
─────────────────────────────────────────
parse_input          O(n²)       O(n)
assign_indexes       O(n²)       O(n)
chunk_sort           O(n²)       O(1)
  - push_chunks      O(n×k)      O(1)
  - push_back        O(n²)       O(1)
─────────────────────────────────────────
TOTAL                O(n²)       O(n)
```

**Espacio:**
- Stack A: n nodos → O(n)
- Stack B: hasta n nodos → O(n)
- Array temporal: n enteros → O(n)
- **Total: O(n)**

### Número de operaciones

**Benchmarks comunes:**

```
n = 3:      2-3 operaciones
n = 5:      ~12 operaciones
n = 100:    ~700 operaciones (límite: 700 para 5 puntos)
n = 500:    ~5500 operaciones (límite: 5500 para 5 puntos)
```

**Factores que afectan:**
- Distribución inicial de números
- Número de chunks elegido
- Optimización rb en push_chunks

---

## 11. Posibles optimizaciones

### Optimización 1: Mejorar assign_indexes
**Problema actual:** O(n²) por bubble sort

**Solución:**
```c
Usar quicksort o mergesort → O(n log n)
Biblioteca qsort de C:
  qsort(arr, size, sizeof(int), compare_int);
```

**Beneficio:**
- Reduce de O(n²) a O(n log n)
- Especialmente útil para n > 100

### Optimización 2: Ajustar número de chunks dinámicamente
**Implementación actual:**
```c
if (size <= 100) chunks = 5;
else chunks = 11;
```

**Mejora:**
```c
// Fórmula óptima basada en experimentos
chunks = sqrt(size) * 1.4;

// O gradual:
if (size <= 16) chunks = 1;
else if (size <= 100) chunks = 5;
else if (size <= 200) chunks = 8;
else chunks = 11;
```

**Beneficio:**
- Mejor adaptación a diferentes tamaños
- Menos operaciones en tamaños intermedios

### Optimización 3: Pre-ordenar chunks en push_chunks
**Idea:**
- Al hacer pb, decidir si hacer rb basado en más criterios
- Implementar rotación inteligente de ambos stacks

**Ejemplo:**
```c
if ((*a)->index < limit)
{
    pb(a, b);

    // Heurística mejorada
    if (stack_size(*b) > 1 &&
        (*b)->index > (*b)->next->index)
        rb(b);  // Solo si mejora el orden
}
```

### Optimización 4: Usar operaciones dobles
**Problema:** No se usan ss, rr, rrr en el código actual

**Oportunidad:**
```c
// En vez de:
ra(a);
rb(b);

// Usar:
rr(a, b);  // 1 operación en vez de 2
```

**Beneficio:**
- Reduce el contador de operaciones
- Útil cuando ambos stacks necesitan rotar

### Optimización 5: Algoritmo híbrido
**Para n entre 6 y 20:**
- chunk_sort puede ser excesivo
- sort_five es insuficiente

**Solución:**
```c
else if (size <= 20)
    insertion_sort(a, b);  // Nuevo algoritmo
else
    chunk_sort(a, b, chunks);
```

**insertion_sort básico:**
```c
1. pb todos menos 3 a b
2. sort_three en a
3. Para cada elemento en b:
   - Calcula mejor posición en a
   - Rota a hasta esa posición
   - pa
```

### Optimización 6: Calcular costo de rotación
**Para push_back mejorado:**
```c
int calculate_cost(int pos, int size)
{
    if (pos <= size / 2)
        return pos;        // rb × pos
    else
        return size - pos; // rrb × (size - pos)
}

// Elegir elemento con menor costo total
// (costo en b + costo de inserción en a)
```

### Optimización 7: Detectar subsecuencias ordenadas
**Idea:**
- Identificar partes ya ordenadas
- No moverlas innecesariamente

**Ejemplo:**
```
Stack: [5, 1, 2, 3, 4]
  → [1,2,3,4] ya está ordenado
  → Solo mover el 5
```

### Optimización 8: Memoria - Pool de nodos
**Problema:** malloc/free para cada nodo es lento

**Solución:**
```c
// Pre-alocar todos los nodos de una vez
t_node *pool = malloc(sizeof(t_node) * count);

// Usar nodos del pool
new = &pool[index++];

// Free una sola vez al final
free(pool);
```

**Beneficio:**
- Más rápido (menos syscalls)
- Mejor localidad de caché

### Optimización 9: Look-ahead en push_chunks
**Idea:**
- Mirar varios elementos adelante
- Decidir si vale la pena rotar o esperar

**Ejemplo:**
```c
// Si el siguiente también está en el chunk
if (next_is_in_chunk && current_is_not)
    ra(a);  // Espera al siguiente
else if (current_is_in_chunk)
    pb(a, b);
```

### Resumen de impacto

```
Optimización                Mejora         Dificultad
──────────────────────────────────────────────────────
1. Mejor sort               Media          Baja
2. Chunks dinámicos         Baja-Media     Baja
3. Pre-ordenar chunks       Media          Media
4. Operaciones dobles       Baja           Baja
5. Algoritmo híbrido        Alta           Media-Alta
6. Costo de rotación        Alta           Media
7. Subsecuencias            Media-Alta     Alta
8. Pool de nodos            Baja           Media
9. Look-ahead               Media          Alta
──────────────────────────────────────────────────────
```

### Optimización más valiosa
**#6: Calcular costo de rotación**
- Implementación relativamente simple
- Gran impacto en número de operaciones
- Usado en los mejores push_swap

---

## Recursos adicionales

### Comandos útiles para testing

```bash
# Generar números aleatorios
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l

# Verificar con checker
ARG="3 2 1"; ./push_swap $ARG | ./checker $ARG

# Benchmark automatizado
bash tester.sh
```

### Visualizador
- push_swap_visualizer (GitHub)
- push_swap_GUI

### Referencias
- Subject de 42
- Algoritmos de sorting
- Complejidad computacional
