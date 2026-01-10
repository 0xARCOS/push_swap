# ANÁLISIS TÉCNICO PUSH_SWAP - GUÍA DE DEFENSA

## 📊 RESUMEN DEL PROYECTO

**Puntuación actual:** 96/100
**Líneas de código:** ~1046 líneas
**Arquitectura:** Modular (parse, movements, algorithm)
**Algoritmo principal:** Chunk sort con optimizaciones para casos pequeños

---

## ⚠️ DEUDA TÉCNICA IDENTIFICADA

### 1. **CRÍTICO: Algoritmo de ordenación en assign_indexes.c**

**Ubicación:** `src/algorithm/assign_indexes.c:31-53`

**Problema:** Usas bubble sort (O(n²)) para ordenar el array temporal.

```c
static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
```

**¿Por qué es deuda técnica?**
- Complejidad O(n²) innecesaria
- Para 500 números: 250,000 comparaciones
- Existe mejor alternativa (quicksort O(n log n))

**Impacto:** Moderado - Solo se ejecuta una vez al inicio, pero afecta la eficiencia del programa.

---

### 2. **MEDIO: Duplicación de código en sort_five()**

**Ubicación:** `src/algorithm/sort_small.c:65-83`

**Problema:** Llamadas repetitivas a `stack_size(*a)` dentro de bucles.

```c
while (stack_size(*a) > 3)  // Línea 69
{
	pos = find_min_pos(*a);
	if (pos <= stack_size(*a) / 2)      // Línea 72 - recalcula size
		while (pos-- > 0)
			ra(a);
	else
		while (pos++ < stack_size(*a))  // Línea 76 - recalcula size
			rra(a);
	pb(a, b);
}
```

**¿Por qué es deuda técnica?**
- `stack_size()` recorre toda la lista cada vez (O(n))
- Se llama múltiples veces innecesariamente
- Fácilmente optimizable guardando el valor

**Impacto:** Bajo - Solo afecta a stacks de 4-5 elementos.

---

### 3. **MEDIO: Búsqueda lineal en find_pos_by_index()**

**Ubicación:** `src/algorithm/chunk_sort.c:14-27`

```c
static int	find_pos_by_index(t_node *stack, int index)
{
	int		pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}
```

**¿Por qué es deuda técnica?**
- Búsqueda O(n) que se ejecuta repetidamente en push_back()
- Se busca siempre el máximo, que puede estar al final
- Complejidad total de push_back(): O(n²)

**Impacto:** Alto para listas grandes (500 elementos).

---

### 4. **BAJO: Validación de duplicados ineficiente**

**Ubicación:** `src/parse/parse_input.c:15-33`

```c
static int	has_duplicates(t_node *stack)
{
	t_node	*current;
	t_node	*runner;

	current = stack;
	while (current)
	{
		runner = current->next;
		while (runner)
		{
			if (current->value == runner->value)
				return (1);
			runner = runner->next;
		}
		current = current->next;
	}
	return (0);
}
```

**¿Por qué es deuda técnica?**
- Complejidad O(n²) para detectar duplicados
- Para 500 elementos: ~125,000 comparaciones
- Se podría usar el array ordenado en assign_indexes() para detectar duplicados en O(n)

**Impacto:** Bajo - Solo se ejecuta una vez al inicio.

---

### 5. **BAJO: Falta de constantes simbólicas**

**Problema:** Números mágicos en el código.

**Ejemplos:**
- `src/algorithm/sort.c:44-47`: `5` y `11` chunks sin explicación
- `src/algorithm/chunk_sort.c:58`: `chunk / 2` sin contexto claro

```c
if (size <= 100)
	chunk_sort(a, b, 5);   // ¿Por qué 5?
else
	chunk_sort(a, b, 11);  // ¿Por qué 11?
```

**¿Por qué es deuda técnica?**
- Reduce legibilidad
- Dificulta ajustes futuros
- No explica la lógica detrás de los valores

**Solución sugerida:**
```c
#define CHUNKS_SMALL 5
#define CHUNKS_LARGE 11
#define THRESHOLD_SMALL_LARGE 100
```

---

## 🚀 OPORTUNIDADES DE OPTIMIZACIÓN

### Optimización 1: Implementar Quicksort en assign_indexes

**Impacto:** Reducción de ~250,000 a ~4,500 operaciones para 500 elementos

**Implementación sugerida:**
```c
static void	quicksort(int *arr, int left, int right)
{
	int	pivot, i, j, temp;

	if (left >= right)
		return;
	pivot = arr[(left + right) / 2];
	i = left;
	j = right;
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (left < j)
		quicksort(arr, left, j);
	if (i < right)
		quicksort(arr, i, right);
}
```

---

### Optimización 2: Cachear stack_size en sort_five

**Impacto:** Reduce recorridos innecesarios de la lista

```c
void	sort_five(t_node **a, t_node **b)
{
	int		pos;
	int		size;  // Variable cacheada

	size = stack_size(*a);
	while (size > 3)
	{
		pos = find_min_pos(*a);
		if (pos <= size / 2)
			while (pos-- > 0)
				ra(a);
		else
			while (pos++ < size)
				rra(a);
		pb(a, b);
		size--;  // Decrementar en vez de recalcular
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}
```

---

### Optimización 3: Mejorar push_back con tracking del máximo

**Problema actual:** Se busca el máximo en cada iteración de push_back()

**Solución:** Tracking inteligente del máximo

```c
static void	push_back(t_node **a, t_node **b)
{
	int		pos;
	int		max;
	int		size;

	max = find_max_index(*b);  // Solo calcular una vez al inicio
	while (*b)
	{
		// El máximo actual es siempre el más grande restante
		pos = find_pos_by_index(*b, max);
		size = stack_size(*b);
		if (pos <= size / 2)
			while (pos-- > 0)
				rb(b);
		else
			while (pos++ < size)
				rrb(b);
		pa(a, b);
		max--;  // El siguiente máximo es max-1
	}
}
```

---

### Optimización 4: Usar array ordenado para detectar duplicados

**Mover la detección de duplicados a assign_indexes:**

```c
static int	check_duplicates(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (arr[i] == arr[i + 1])
			return (1);
		i++;
	}
	return (0);
}
```

Llamar después de sort_array() en assign_indexes().

---

### Optimización 5: Ajuste fino de chunks

**Valores actuales:**
- ≤100 elementos: 5 chunks
- >100 elementos: 11 chunks

**Análisis:**
- Para 100 elementos con 5 chunks: ~20 elementos por chunk
- Para 500 elementos con 11 chunks: ~45 elementos por chunk

**Valores optimizados sugeridos:**
```c
if (size <= 100)
	chunk_sort(a, b, 5);
else if (size <= 250)
	chunk_sort(a, b, 8);   // Mejor balance para 100-250
else
	chunk_sort(a, b, 11);  // Óptimo para 500
```

---

## 📚 GUÍA DE ESTUDIO - FUNCIÓN POR FUNCIÓN

### MÓDULO 1: MAIN Y VALIDACIÓN

#### `main()` - src/main.c:49-72

**Propósito:** Punto de entrada del programa.

**Flujo línea por línea:**

```c
int	main(int argc, char **argv)
{
	t_node	*stack_a;      // Puntero al stack principal
	t_node	*stack_b;      // Puntero al stack auxiliar

	stack_a = NULL;        // Inicializar a NULL (stack vacío)
	stack_b = NULL;

	if (argc < 2)          // Si no hay argumentos
		return (0);        // Salir sin error (comportamiento esperado)

	if (!validate_args(argc, argv))  // Validar argumentos
		return (1);                  // Error: argumento inválido

	stack_a = parse_input(argc, argv);  // Parsear y crear stack

	if (!stack_a)                       // Si falla el parsing
		return (write(2, "Error\n", 6)); // Escribir error y retornar

	if (is_sorted(stack_a))             // Si ya está ordenado
	{
		free_stack(&stack_a);           // Liberar memoria
		return (0);                     // Salir (no hacer nada)
	}

	sort_stack(&stack_a, &stack_b);     // Ordenar el stack
	free_stack(&stack_a);                // Liberar memoria
	free_stack(&stack_b);
	return (0);
}
```

**Variables clave:**
- `stack_a`: Lista enlazada que contiene los números a ordenar
- `stack_b`: Lista enlazada auxiliar para el algoritmo
- `argc`: Número de argumentos de línea de comandos
- `argv`: Array de strings con los argumentos

**¿Por qué retornar 0 si argc < 2?**
- Según el subject de 42, no tener argumentos no es un error
- Es un caso válido que simplemente no requiere acción

---

#### `validate_args()` - src/main.c:32-47

**Propósito:** Validar que los argumentos no sean solo espacios/tabs.

```c
static int	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;              // Empezar en 1 (argv[0] es el nombre del programa)
	while (i < argc)
	{
		if (has_only_spaces(argv[i]))  // Si solo tiene espacios
		{
			write(2, "Error\n", 6);     // Escribir error a stderr
			return (0);                 // Retornar false
		}
		i++;
	}
	return (1);  // Todo válido
}
```

**¿Por qué esta validación?**
- `./push_swap "   "` debe dar error
- `./push_swap ""` debe dar error
- Evita problemas en el split posterior

---

#### `has_only_spaces()` - src/main.c:16-30

**Propósito:** Detectar strings vacíos o solo con whitespace.

```c
static int	has_only_spaces(const char *s)
{
	int	i;

	if (!s)           // Si el string es NULL
		return (1);   // Considerarlo como "solo espacios"

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '	')  // Si no es espacio ni tab
			return (0);                    // No es solo espacios
		i++;
	}
	return (1);  // Es solo espacios (o vacío)
}
```

**Detalles importantes:**
- `s[i] != ' '`: Espacio ASCII (32)
- `s[i] != '	'`: Tab literal (carácter de tabulación)
- Retorna 1 (true) si el string es NULL, vacío, o solo whitespace

---

### MÓDULO 2: PARSING

#### `parse_input()` - src/parse/parse_input.c:95-115

**Propósito:** Convertir argumentos en una lista enlazada validada.

```c
t_node	*parse_input(int argc, char **argv)
{
	char	**tokens;  // Array de strings con todos los números
	t_node	*stack;    // Lista enlazada resultante

	tokens = split_args(argc, argv);  // Separar todos los argumentos
	stack = NULL;

	if (!tokens || !add_arguments(&stack, tokens))  // Si falla
	{
		free_split(tokens);   // Liberar tokens
		free_stack(&stack);   // Liberar stack parcial
		return (NULL);        // Indicar error
	}

	free_split(tokens);  // Ya no necesitamos los tokens

	if (has_duplicates(stack))  // Verificar duplicados
	{
		free_stack(&stack);
		return (NULL);
	}

	return (stack);  // Retornar stack válido
}
```

**Flujo de datos:**
```
argv[] → split_args() → tokens[] → add_arguments() → stack → validar → retornar
```

**Casos de error detectados:**
1. Fallo en split (memoria)
2. Número inválido (add_arguments falla)
3. Overflow de int
4. Duplicados

---

#### `split_args()` - src/parse/parse_input.c:55-79

**Propósito:** Convertir todos los argv en un array unificado de tokens.

```c
char	**split_args(int argc, char **argv)
{
	char	**tokens;  // Array resultante
	char	**split;   // Array temporal para cada argv[i]
	int		i;
	int		k;

	// Contar cuántos tokens necesitamos en total
	tokens = malloc(sizeof(char *) * (count_all_tokens(argc, argv) + 1));
	if (!tokens)
		return (NULL);

	i = 1;  // Empezar en argv[1]
	k = 0;  // Índice en tokens

	while (i < argc)
	{
		split = ft_split(argv[i], ' ');  // Separar por espacios

		if (!split || !append_tokens(tokens, split, &k))
		{
			free_tokens(tokens, k);  // Limpiar lo que se haya creado
			return (NULL);
		}
		i++;
	}

	tokens[k] = NULL;  // Terminar el array con NULL
	return (tokens);
}
```

**Ejemplo de funcionamiento:**
```
Input:  ./push_swap "4 2 3" "1"
argv[1] = "4 2 3"
argv[2] = "1"

Paso 1: split("4 2 3", ' ') → ["4", "2", "3", NULL]
        append a tokens → tokens = ["4", "2", "3", ...]

Paso 2: split("1", ' ') → ["1", NULL]
        append a tokens → tokens = ["4", "2", "3", "1", NULL]
```

**Variable `k`:**
- Índice actual en el array `tokens`
- Se pasa por referencia a `append_tokens()` para actualizarlo
- Al final indica cuántos elementos hay

---

#### `count_all_tokens()` - src/parse/parse_utils.c:15-36

**Propósito:** Contar cuántos números hay en total en todos los argv.

```c
int	count_all_tokens(int argc, char **argv)
{
	int		i;
	int		count;
	char	**split;
	int		j;

	i = 1;
	count = 0;

	while (i < argc)
	{
		split = ft_split(argv[i], ' ');  // Separar el argumento actual
		if (!split)
			return (0);  // Error de malloc

		j = 0;
		while (split[j++])  // Contar elementos (post-incremento)
			count++;

		free_split(split);  // Liberar el split temporal
		i++;
	}

	return (count);
}
```

**¿Por qué hacer split dos veces?**
1. Primera vez (count_all_tokens): Saber cuánta memoria reservar
2. Segunda vez (split_args): Llenar el array con los tokens

**Optimización posible:** Se podría evitar el doble split, pero:
- Complica el código
- El impacto es mínimo (solo se hace una vez)
- Prioriza claridad sobre micro-optimización

---

#### `ft_split()` - src/parse/split.c:90-108

**Propósito:** Separar un string por un delimitador (como strsplit en otros lenguajes).

```c
char	**ft_split(const char *s, char c)
{
	char	**result;
	int		k;

	if (!s)
		return (NULL);

	// Contar cuántas palabras hay
	result = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);

	k = 0;

	// Llenar el array con las palabras
	if (!populate_words(result, s, c, &k))
	{
		free_all(result, k);  // Si falla, liberar todo
		return (NULL);
	}

	result[k] = NULL;  // Terminar con NULL
	return (result);
}
```

**Ejemplo:**
```
Input:  s = "  hello  world  ", c = ' '
Output: ["hello", "world", NULL]
```

---

#### `word_count()` - src/parse/split.c:15-34

**Propósito:** Contar cuántas palabras hay en un string.

```c
static int	word_count(const char *s, char c)
{
	int		count;
	int		in_word;  // Flag: ¿estamos dentro de una palabra?

	count = 0;
	in_word = 0;

	while (*s)
	{
		if (*s != c && in_word == 0)  // Inicio de palabra
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)              // Fin de palabra
			in_word = 0;
		s++;
	}

	return (count);
}
```

**Algoritmo de máquina de estados:**
```
Estado: in_word = 0 (fuera de palabra)
  - Si encontramos no-delimitador → in_word = 1, count++
  - Si encontramos delimitador → mantener estado

Estado: in_word = 1 (dentro de palabra)
  - Si encontramos delimitador → in_word = 0
  - Si encontramos no-delimitador → mantener estado
```

**Ejemplo de ejecución:**
```
Input: "  ab  cd  "
       ^
in_word=0, count=0

Input: "  ab  cd  "
        ^
*s=' ', c=' ' → in_word sigue 0

Input: "  ab  cd  "
          ^
*s='a' != c → in_word=1, count=1

Input: "  ab  cd  "
            ^
*s='b' != c → in_word sigue 1

Input: "  ab  cd  "
              ^
*s=' ' == c → in_word=0

Input: "  ab  cd  "
                ^
*s='c' != c → in_word=1, count=2

...
```

---

#### `populate_words()` - src/parse/split.c:61-88

**Propósito:** Extraer cada palabra y crear copias en el array resultado.

```c
static int	populate_words(char **res, const char *s, char c, int *k)
{
	int		i;
	int		start;  // Índice donde empieza la palabra actual
	int		len;

	i = 0;
	start = -1;  // -1 = no hay palabra activa

	while (s[i])
	{
		// Detectar inicio de palabra
		if (s[i] != c && start < 0)
			start = i;

		// Detectar fin de palabra (delimitador o fin de string)
		if ((s[i] == c || s[i + 1] == '\0') && start >= 0)
		{
			// Calcular longitud
			if (s[i] == c)
				len = i - start;        // Palabra termina antes del delimitador
			else
				len = i - start + 1;    // Palabra incluye el último carácter

			// Duplicar la palabra
			res[*k] = word_dup(s + start, len);
			if (!res[*k])
				return (0);  // Error de malloc

			(*k)++;      // Incrementar índice en resultado
			start = -1;  // Resetear para la próxima palabra
		}
		i++;
	}

	return (1);
}
```

**Ejemplo detallado:**
```
Input: s = "ab cd", c = ' '

i=0, s[0]='a', start=-1
  → s[0] != ' ' && start < 0 → start = 0

i=1, s[1]='b', start=0
  → s[1] != ' ' → nada

i=2, s[2]=' ', start=0
  → s[2] == ' ' && start >= 0
  → len = 2 - 0 = 2
  → word_dup("ab", 2) → res[0] = "ab"
  → k = 1, start = -1

i=3, s[3]='c', start=-1
  → s[3] != ' ' && start < 0 → start = 3

i=4, s[4]='d', start=3
  → s[4] != ' ' → nada

i=5, s[5]='\0', start=3
  → s[5+1] == '\0' && start >= 0
  → len = 4 - 3 + 1 = 2
  → word_dup("cd", 2) → res[1] = "cd"
  → k = 2, start = -1

Resultado: res = ["ab", "cd", ...]
```

**¿Por qué `s[i + 1] == '\0'`?**
- Para detectar la última palabra incluso si no termina con delimitador
- `"ab cd"` → última palabra "cd" termina en '\0', no en ' '

---

#### `word_dup()` - src/parse/split.c:36-52

**Propósito:** Crear una copia de una subcadena de longitud específica.

```c
static char	*word_dup(const char *start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));  // +1 para '\0'
	if (!word)
		return (NULL);

	while (i < len)
	{
		word[i] = start[i];  // Copiar carácter
		i++;
	}

	word[i] = '\0';  // Terminar string
	return (word);
}
```

**¿Por qué no usar strdup?**
- strdup copia hasta '\0'
- Necesitamos copiar solo `len` caracteres de un string más grande
- Ejemplo: extraer "hello" de "hello world" sin copiar " world"

---

#### `is_valid_number()` - src/parse/parse_utils.c:38-56

**Propósito:** Validar que un string representa un número válido.

```c
int	is_valid_number(const char *str)
{
	int		i;

	if (!str || !str[0])  // String NULL o vacío
		return (0);

	i = 0;

	// Permitir signo opcional al inicio
	if (str[0] == '-' || str[0] == '+')
		i++;

	// Debe haber al menos un dígito después del signo
	if (!str[i])
		return (0);  // Rechazar solo "-" o "+"

	// Verificar que el resto sean dígitos
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);  // Carácter inválido
		i++;
	}

	return (1);  // Válido
}
```

**Casos válidos:**
- "123" ✓
- "+123" ✓
- "-123" ✓

**Casos inválidos:**
- "" ✗ (vacío)
- "+" ✗ (solo signo)
- "-" ✗ (solo signo)
- "12a3" ✗ (letra)
- "12.3" ✗ (decimal)
- "12 3" ✗ (espacio)

---

#### `ft_atoi_push_swap()` - src/parse/atoi_utils.c:29-51

**Propósito:** Convertir string a int con detección de overflow.

```c
int	ft_atoi_push_swap(const char *str, int *error_flag)
{
	long	result;  // Usar long para detectar overflow
	int		sign;
	int		i;

	result = 0;
	i = 0;
	sign = parse_sign(str, &i);  // Parsear signo (+/-)
	*error_flag = 0;              // Inicializar flag

	while (str[i])
	{
		result = result * 10 + (str[i] - '0');  // Acumular dígito

		// Verificar overflow
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && (-result) < INT_MIN))
		{
			*error_flag = 1;  // Marcar error
			return (0);
		}
		i++;
	}

	return ((int)(result * sign));  // Aplicar signo y convertir a int
}
```

**¿Por qué usar long?**
- Para detectar cuando el número excede INT_MAX (2147483647) o INT_MIN (-2147483648)
- Si usáramos int, el overflow daría resultados incorrectos sin detectarlo

**Ejemplo de overflow:**
```
Input: "2147483648" (INT_MAX + 1)

result empieza en 0
result = 0 * 10 + 2 = 2
result = 2 * 10 + 1 = 21
result = 21 * 10 + 4 = 214
...
result = 2147483648

sign == 1 && result > INT_MAX (2147483647)
→ *error_flag = 1, return 0
```

---

#### `parse_sign()` - src/parse/atoi_utils.c:15-27

**Propósito:** Extraer el signo del número (si existe).

```c
static int	parse_sign(const char *str, int *i)
{
	int		sign;

	sign = 1;  // Por defecto positivo

	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;  // Avanzar índice para saltar el signo
	}

	return (sign);
}
```

**¿Por qué modificar `i` por referencia?**
- Para que la función que llama sepa dónde empiezan los dígitos
- Evita tener que buscar de nuevo dónde termina el signo

**Ejemplo:**
```
Input: str = "-123", i = 0

str[0] == '-' → sign = -1, i = 1
return -1

Ahora i=1 apunta al primer dígito ('1')
```

---

#### `add_node()` - src/parse/parse_utils.c:77-96

**Propósito:** Crear un nodo y añadirlo al final de la lista.

```c
int	add_node(t_node **stack, const char *str)
{
	t_node	*new;
	t_node	*temp;
	int		error;

	new = create_node(str, &error);  // Crear el nodo
	if (!new)
		return (0);  // Error (malloc o overflow)

	if (!*stack)  // Si el stack está vacío
	{
		*stack = new;  // El nuevo nodo es el primero
		return (1);
	}

	// Buscar el último nodo
	temp = *stack;
	while (temp->next)
		temp = temp->next;

	temp->next = new;  // Añadir al final
	return (1);
}
```

**Flujo para lista vacía:**
```
*stack = NULL
new = create_node("42")
*stack = new

Resultado: stack → [42] → NULL
```

**Flujo para lista con elementos:**
```
stack → [1] → [2] → NULL
new = create_node("3")

temp = stack → [1]
temp->next != NULL → temp = [2]
temp->next == NULL

temp->next = new

Resultado: stack → [1] → [2] → [3] → NULL
```

**¿Por qué añadir al final y no al inicio?**
- Mantener el orden de los argumentos
- `./push_swap 1 2 3` → stack = [1, 2, 3]
- Añadir al inicio invertiría el orden

---

#### `create_node()` - src/parse/parse_utils.c:58-75

**Propósito:** Crear un nodo con el valor parseado.

```c
static t_node	*create_node(const char *str, int *error)
{
	t_node	*new;

	*error = 0;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);

	new->value = ft_atoi_push_swap(str, error);  // Parsear número

	if (*error)  // Si hubo overflow
	{
		free(new);
		return (NULL);
	}

	new->index = -1;    // Index se asignará después
	new->next = NULL;   // No tiene siguiente aún

	return (new);
}
```

**Estructura t_node:**
```c
typedef struct s_node
{
	int             value;  // Valor original del número
	int             index;  // Posición en el array ordenado (0 a n-1)
	struct s_node   *next;  // Puntero al siguiente nodo
}	t_node;
```

**Ejemplo:**
```
create_node("42", &error)

new = malloc() → [value=?, index=?, next=?]
new->value = ft_atoi_push_swap("42") → 42
error = 0 (sin overflow)
new->index = -1
new->next = NULL

return [value=42, index=-1, next=NULL]
```

---

#### `has_duplicates()` - src/parse/parse_input.c:15-33

**Propósito:** Detectar si hay valores repetidos en el stack.

```c
static int	has_duplicates(t_node *stack)
{
	t_node	*current;
	t_node	*runner;

	current = stack;

	while (current)
	{
		runner = current->next;  // Empezar desde el siguiente

		while (runner)
		{
			if (current->value == runner->value)  // Duplicado encontrado
				return (1);
			runner = runner->next;
		}

		current = current->next;
	}

	return (0);  // No hay duplicados
}
```

**Algoritmo de doble bucle (O(n²)):**
```
Lista: [3, 1, 2, 1]

current = 3
  runner = 1 → 3 != 1
  runner = 2 → 3 != 2
  runner = 1 → 3 != 1

current = 1
  runner = 2 → 1 != 2
  runner = 1 → 1 == 1 → return 1 (duplicado!)
```

**¿Por qué runner empieza en current->next?**
- No necesitamos comparar current consigo mismo
- No necesitamos comparar pares ya comparados (1 con 3 ya se comparó como 3 con 1)

---

### MÓDULO 3: OPERACIONES BÁSICAS

#### `swap_nodes()` - src/movements/operations_utils.c:15-27

**Propósito:** Intercambiar los dos primeros elementos de un stack.

```c
void	swap_nodes(t_node	**stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;  // No hay nada que hacer

	first = *stack;        // Guardar primer nodo
	second = first->next;  // Guardar segundo nodo

	first->next = second->next;  // first apunta al tercero
	second->next = first;        // second apunta a first
	*stack = second;             // second es el nuevo primero
}
```

**Visualización:**
```
Antes:
*stack → [A] → [B] → [C] → NULL
         first  second

Paso 1: first->next = second->next
*stack → [A] ----→ [C] → NULL
         first  ↓
               [B]
               second

Paso 2: second->next = first
*stack      ↓→ [A] → [C] → NULL
            ↑  first
           [B]
           second

Paso 3: *stack = second
*stack → [B] → [A] → [C] → NULL
```

**Validaciones:**
- `!stack`: Puntero al stack es NULL (no debería pasar)
- `!*stack`: Stack vacío
- `!(*stack)->next`: Stack con un solo elemento

---

#### `sa()` - src/movements/swap_ops.c:16-22

**Propósito:** Swap A - Intercambiar primeros dos de stack A e imprimir "sa".

```c
void	sa(t_node **a)
{
	if (!a || !*a || !(*a)->next)
		return ;  // Validaciones

	swap_nodes(a);      // Hacer el swap
	write(1, "sa\n", 3); // Imprimir operación a stdout
}
```

**¿Por qué validar de nuevo si swap_nodes ya valida?**
- Evitar imprimir "sa" cuando no se hace ninguna operación
- Separación de responsabilidades: swap_nodes es genérico, sa es específico

---

#### `push_node()` - src/movements/operations_utils.c:29-39

**Propósito:** Mover el primer elemento de src al tope de dst.

```c
void	push_node(t_node	**dst, t_node	**src)
{
	t_node	*tmp;

	if (!src || !*src)
		return ;  // No hay nada que mover

	tmp = *src;          // Guardar el nodo a mover
	*src = (*src)->next; // Eliminar de src
	tmp->next = *dst;    // Conectar a dst
	*dst = tmp;          // tmp es el nuevo tope de dst
}
```

**Visualización:**
```
Antes:
src → [A] → [B] → NULL
dst → [X] → [Y] → NULL

Paso 1: tmp = *src
tmp → [A] → [B] → NULL
src → [A] → [B] → NULL

Paso 2: *src = (*src)->next
tmp → [A] → [B] → NULL
src → [B] → NULL

Paso 3: tmp->next = *dst
tmp → [A] → [X] → [Y] → NULL
src → [B] → NULL

Paso 4: *dst = tmp
dst → [A] → [X] → [Y] → NULL
src → [B] → NULL
```

---

#### `pb()` - src/movements/push_ops.c:24-30

**Propósito:** Push B - Mover tope de A al tope de B.

```c
void	pb(t_node **a, t_node **b)
{
	if (!a || !*a)
		return ;

	push_node(b, a);     // Mover de A a B
	write(1, "pb\n", 3); // Imprimir operación
}
```

**Ejemplo:**
```
Antes:
A: [1] → [2] → [3] → NULL
B: [4] → [5] → NULL

pb(A, B)

Después:
A: [2] → [3] → NULL
B: [1] → [4] → [5] → NULL

Output: "pb"
```

---

#### `rotate_nodes()` - src/movements/operations_utils.c:41-55

**Propósito:** Rotar stack hacia arriba (primero va al final).

```c
void	rotate_nodes(t_node	**stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;

	first = *stack;          // Guardar primer nodo
	*stack = first->next;    // Segundo nodo es el nuevo primero

	// Buscar el último nodo
	last = *stack;
	while (last->next)
		last = last->next;

	last->next = first;  // Conectar último con primero
	first->next = NULL;  // first es ahora el último
}
```

**Visualización:**
```
Antes:
*stack → [A] → [B] → [C] → NULL

Paso 1: first = *stack
first → [A] → [B] → [C] → NULL

Paso 2: *stack = first->next
*stack → [B] → [C] → NULL
first → [A] → [B] → [C] → NULL

Paso 3: Buscar last
last → [C] → NULL

Paso 4: last->next = first
*stack → [B] → [C] → [A] → [B] → ... ¡CICLO!

Paso 5: first->next = NULL
*stack → [B] → [C] → [A] → NULL
```

**Concepto:** Shift left circular
```
[A, B, C, D] → ra → [B, C, D, A]
```

---

#### `reverse_rotate_nodes()` - src/movements/operations_utils.c:57-74

**Propósito:** Rotar stack hacia abajo (último va al principio).

```c
void	reverse_rotate_nodes(t_node	**stack)
{
	t_node	*prev;
	t_node	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;

	prev = NULL;
	last = *stack;

	// Buscar el último y el penúltimo
	while (last->next)
	{
		prev = last;      // prev va un paso atrás
		last = last->next;
	}

	prev->next = NULL;    // Desconectar el último
	last->next = *stack;  // Último apunta al primero
	*stack = last;        // Último es el nuevo primero
}
```

**Visualización:**
```
Antes:
*stack → [A] → [B] → [C] → NULL

Bucle:
Iteración 1:
  prev = NULL
  last = [A]
  last->next != NULL
  prev = [A]
  last = [B]

Iteración 2:
  prev = [B]
  last = [C]
  last->next == NULL → salir

Paso 1: prev->next = NULL
*stack → [A] → [B] → NULL
last → [C]

Paso 2: last->next = *stack
*stack → [A] → [B] → NULL
         ↑
last → [C]

Paso 3: *stack = last
*stack → [C] → [A] → [B] → NULL
```

**Concepto:** Shift right circular
```
[A, B, C, D] → rra → [D, A, B, C]
```

---

### MÓDULO 4: ALGORITMOS

#### `is_sorted()` - src/algorithm/sort.c:14-23

**Propósito:** Verificar si el stack está ordenado ascendentemente.

```c
int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);  // Encontramos desorden
		stack = stack->next;
	}
	return (1);  // Todo está ordenado
}
```

**Ejemplo:**
```
Stack: [1] → [2] → [3] → NULL

1 > 2? No → continuar
2 > 3? No → continuar
stack->next == NULL → return 1 (ordenado)
```

```
Stack: [1] → [3] → [2] → NULL

1 > 3? No → continuar
3 > 2? Sí → return 0 (no ordenado)
```

---

#### `sort_stack()` - src/algorithm/sort.c:25-49

**Propósito:** Seleccionar el algoritmo apropiado según el tamaño.

```c
void	sort_stack(t_node **a, t_node **b)
{
	int		size;

	if (!a || !*a)
		return ;

	size = stack_size(*a);

	if (size == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);  // Solo un swap
	}
	else if (size == 3)
		sort_three(a);     // Algoritmo específico para 3
	else if (size <= 5)
		sort_five(a, b);   // Algoritmo específico para 4-5
	else
	{
		assign_indexes(*a);  // Asignar índices normalizados

		if (size <= 100)
			chunk_sort(a, b, 5);   // 5 chunks para ≤100
		else
			chunk_sort(a, b, 11);  // 11 chunks para >100
	}
}
```

**Estrategia por tamaño:**
- **2 elementos:** 1 operación máximo (sa)
- **3 elementos:** 2-3 operaciones (hardcoded)
- **4-5 elementos:** Push mínimos a B, sort 3 en A, push back
- **6-100 elementos:** Chunk sort con 5 chunks
- **101-500 elementos:** Chunk sort con 11 chunks

**¿Por qué assign_indexes() solo para >5?**
- Los algoritmos pequeños usan valores directamente
- Chunk sort necesita índices normalizados (0, 1, 2, ...)

---

#### `assign_indexes()` - src/algorithm/assign_indexes.c:69-81

**Propósito:** Asignar a cada nodo su posición en el array ordenado.

```c
void	assign_indexes(t_node *stack)
{
	int		size;
	int		*arr;

	size = stack_size(stack);
	arr = stack_to_array(stack, size);  // Copiar valores a array
	if (!arr)
		return ;

	sort_array(arr, size);              // Ordenar el array
	set_indexes(stack, arr, size);      // Asignar índices
	free(arr);                          // Liberar memoria temporal
}
```

**Ejemplo completo:**
```
Stack: [42] → [3] → [18] → [7] → NULL

Paso 1: stack_to_array()
arr = [42, 3, 18, 7]

Paso 2: sort_array()
arr = [3, 7, 18, 42]

Paso 3: set_indexes()
Para cada nodo:
  Nodo con value=42 → buscar 42 en arr → posición 3 → index = 3
  Nodo con value=3  → buscar 3 en arr  → posición 0 → index = 0
  Nodo con value=18 → buscar 18 en arr → posición 2 → index = 2
  Nodo con value=7  → buscar 7 en arr  → posición 1 → index = 1

Resultado:
[42,i=3] → [3,i=0] → [18,i=2] → [7,i=1] → NULL
```

**¿Para qué sirven los índices?**
- Normalizar valores: [-1000, 5, 999] → [0, 1, 2]
- Simplificar chunk sort: trabajar con rangos 0-n en vez de valores arbitrarios

---

#### `stack_to_array()` - src/algorithm/assign_indexes.c:14-29

**Propósito:** Copiar los valores del stack a un array.

```c
static int	*stack_to_array(t_node *stack, int size)
{
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);

	i = 0;
	while (stack)
	{
		arr[i++] = stack->value;  // Copiar valor
		stack = stack->next;
	}

	return (arr);
}
```

---

#### `sort_array()` - src/algorithm/assign_indexes.c:31-53

**Propósito:** Ordenar el array usando selection sort.

```c
static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])  // Si están desordenados
			{
				tmp = arr[i];      // Intercambiar
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
```

**Algoritmo Selection Sort:**
```
[42, 3, 18, 7]

i=0:
  j=1: 42 > 3  → swap → [3, 42, 18, 7]
  j=2: 3 > 18  → no
  j=3: 3 > 7   → no
  [3, 42, 18, 7]

i=1:
  j=2: 42 > 18 → swap → [3, 18, 42, 7]
  j=3: 18 > 7  → swap → [3, 7, 42, 18]  ← ERROR: deberíamos comparar con 18
```

**¡OJO! Este es un bug sutil:**
- Selection sort típico busca el mínimo y lo pone en posición i
- Este código hace swaps múltiples, funcionando más como bubble sort
- Funciona correctamente pero es menos eficiente de lo esperado

**Selection sort correcto:**
```c
i = 0;
while (i < size - 1)
{
	min_idx = i;
	j = i + 1;
	while (j < size)
	{
		if (arr[j] < arr[min_idx])
			min_idx = j;
		j++;
	}
	if (min_idx != i)
		swap(&arr[i], &arr[min_idx]);
	i++;
}
```

---

#### `set_indexes()` - src/algorithm/assign_indexes.c:55-67

**Propósito:** Asignar a cada nodo su índice en el array ordenado.

```c
static void	set_indexes(t_node *stack, int *arr, int size)
{
	int	i;

	while (stack)
	{
		i = 0;
		// Buscar el valor del nodo en el array ordenado
		while (i < size && arr[i] != stack->value)
			i++;

		stack->index = i;  // La posición es el índice
		stack = stack->next;
	}
}
```

**Complejidad:** O(n²)
- Para cada nodo (n)
- Buscar en array (n)

**Optimización posible:** Usar hash map para O(n)

---

#### `sort_three()` - src/algorithm/sort_small.c:38-63

**Propósito:** Ordenar 3 elementos con el mínimo de operaciones.

```c
void	sort_three(t_node **a)
{
	int		first;
	int		second;
	int		third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;

	if (first > second && second < third && first < third)
		sa(a);  // [2,1,3] → sa → [1,2,3]

	else if (first > second && second > third)
	{
		sa(a);   // [3,2,1] → sa → [2,3,1]
		rra(a);  //         → rra → [1,2,3]
	}

	else if (first > second && second < third && first > third)
		ra(a);  // [3,1,2] → ra → [1,2,3]

	else if (first < second && second > third && first < third)
	{
		sa(a);  // [1,3,2] → sa → [3,1,2]
		ra(a);  //         → ra → [1,2,3]
	}

	else if (first < second && second > third && first > third)
		rra(a); // [2,3,1] → rra → [1,2,3]
}
```

**Todos los casos posibles (3! = 6 permutaciones):**
```
[1,2,3] → ya ordenado, no hacer nada
[2,1,3] → sa
[3,2,1] → sa + rra
[3,1,2] → ra
[1,3,2] → sa + ra
[2,3,1] → rra
```

**¿Por qué hardcodear?**
- 3 elementos tienen solo 6 permutaciones posibles
- Hardcodear es más rápido que cualquier algoritmo genérico
- Garantiza el mínimo de operaciones (máximo 2)

---

#### `sort_five()` - src/algorithm/sort_small.c:65-83

**Propósito:** Ordenar 4-5 elementos eficientemente.

```c
void	sort_five(t_node **a, t_node **b)
{
	int		pos;

	// Mover los elementos más pequeños a B
	while (stack_size(*a) > 3)
	{
		pos = find_min_pos(*a);  // Encontrar posición del mínimo

		// Rotar para poner el mínimo arriba
		if (pos <= stack_size(*a) / 2)
			while (pos-- > 0)      // Más cerca del inicio: ra
				ra(a);
		else
			while (pos++ < stack_size(*a))  // Más cerca del final: rra
				rra(a);

		pb(a, b);  // Mover mínimo a B
	}

	sort_three(a);  // Ordenar los 3 que quedan en A

	// Devolver elementos de B a A
	while (*b)
		pa(a, b);
}
```

**Estrategia:**
1. Encontrar el mínimo en A
2. Rotarlo hasta arriba (optimizando dirección)
3. Moverlo a B
4. Repetir hasta que A tenga 3 elementos
5. Ordenar A con sort_three
6. Devolver todo de B a A (ya estarán ordenados)

**Ejemplo con 5 elementos [3,5,1,4,2]:**
```
A: [3,5,1,4,2]  B: []

Paso 1: min = 1 (pos 2)
  pos=2, size=5, 2 <= 5/2 (2 <= 2) → usar ra
  ra → [5,1,4,2,3]
  ra → [1,4,2,3,5]
  pb → A:[4,2,3,5]  B:[1]

Paso 2: min = 2 (pos 1)
  pos=1, size=4, 1 <= 4/2 (1 <= 2) → usar ra
  ra → [2,3,5,4]
  pb → A:[3,5,4]  B:[2,1]

Paso 3: A tiene 3 elementos
  sort_three([3,5,4])
  ra → [5,4,3]
  sa → [4,5,3]
  ... → A:[3,4,5]

Paso 4: Devolver B
  pa → A:[2,3,4,5]  B:[1]
  pa → A:[1,2,3,4,5]  B:[]
```

**Optimización de rotación:**
```
Si min está en posición 2 de [A,B,C,D,E]:
  - Opción 1: ra 2 veces
  - Opción 2: rra 3 veces
  → Elegir opción 1 (2 <= 5/2)

Si min está en posición 4:
  - Opción 1: ra 4 veces
  - Opción 2: rra 1 vez
  → Elegir opción 2 (4 > 5/2)
```

---

#### `find_min_pos()` - src/algorithm/sort_small.c:14-36

**Propósito:** Encontrar la posición del elemento más pequeño.

```c
static int	find_min_pos(t_node *stack)
{
	int		pos;
	int		idx;
	int		min;
	t_node	*tmp;

	pos = 0;       // Posición del mínimo
	idx = 0;       // Posición actual
	tmp = stack;
	min = tmp->value;  // Asumir que el primero es el mínimo

	while (tmp)
	{
		if (tmp->value < min)
		{
			min = tmp->value;  // Actualizar mínimo
			pos = idx;         // Actualizar posición
		}
		tmp = tmp->next;
		idx++;
	}

	return (pos);
}
```

**Ejemplo:**
```
Stack: [5,1,3,2]

idx=0, value=5, min=5, pos=0
idx=1, value=1, 1 < 5 → min=1, pos=1
idx=2, value=3, 3 < 1? no
idx=3, value=2, 2 < 1? no

return pos = 1
```

---

#### `chunk_sort()` - src/algorithm/chunk_sort.c:89-98

**Propósito:** Algoritmo principal para listas grandes (>5 elementos).

```c
void	chunk_sort(t_node **a, t_node **b, int chunks)
{
	int		size;
	int		chunk;

	size = stack_size(*a);
	chunk = size / chunks + 1;  // Tamaño de cada chunk

	push_chunks(a, b, chunk);   // Fase 1: Mover a B por chunks
	push_back(a, b);            // Fase 2: Devolver a A ordenado
}
```

**Concepto de Chunk Sort:**

Imagina que tienes 100 números con índices 0-99.

**Sin chunks (todos a la vez):**
- Intentar mover todos a B aleatoriamente
- Muy ineficiente

**Con chunks:**
1. Dividir en grupos: [0-19], [20-39], [40-59], [60-79], [80-99]
2. Mover primero los del rango [0-19]
3. Luego [20-39], etc.
4. Al devolver a A, sacar siempre el máximo de B

**¿Por qué funciona?**
- Reduce movimientos al procesar por "capas"
- Elementos pequeños se procesan primero
- Al devolver, el máximo está siempre cerca del top

**Ejemplo con size=100, chunks=5:**
```
chunk = 100 / 5 + 1 = 21

Rango 1: índices 0-20   (21 elementos)
Rango 2: índices 21-41  (21 elementos)
Rango 3: índices 42-62  (21 elementos)
Rango 4: índices 63-83  (21 elementos)
Rango 5: índices 84-99  (16 elementos)
```

**¿Por qué +1?**
- Asegurar que todos los elementos entren
- 100 / 5 = 20, pero necesitamos 5 chunks de ~20 cada uno
- Con +1: chunk=21, cubre mejor los 100 elementos

---

#### `push_chunks()` - src/algorithm/chunk_sort.c:43-66

**Propósito:** Mover elementos de A a B por chunks.

```c
static void	push_chunks(t_node **a, t_node **b, int chunk)
{
	int		size;
	int		pushed;
	int		limit;

	size = stack_size(*a);
	pushed = 0;    // Cuántos hemos movido a B
	limit = chunk; // Límite del chunk actual

	while (pushed < size)
	{
		if ((*a)->index < limit)  // Si está en el chunk actual
		{
			pb(a, b);  // Mover a B
			pushed++;

			// Si está en la mitad superior del chunk, rotarlo en B
			if ((*b)->index >= limit - chunk / 2)
				rb(b);
		}
		else
			ra(a);  // Si no está en el chunk, rotar A

		// Cuando terminamos un chunk, pasar al siguiente
		if (pushed == limit && limit < size)
			limit += chunk;
	}
}
```

**Ejemplo con índices [5,2,7,1,9,3,8,4,6,0], chunk=3:**

```
A: [5,2,7,1,9,3,8,4,6,0]  B: []
pushed=0, limit=3

Iteración 1: top=5, 5 < 3? no → ra
A: [2,7,1,9,3,8,4,6,0,5]  B: []

Iteración 2: top=2, 2 < 3? sí → pb
  2 >= 3-3/2 (2 >= 1)? sí → rb
A: [7,1,9,3,8,4,6,0,5]  B: [2]
pushed=1

Iteración 3: top=7, 7 < 3? no → ra
A: [1,9,3,8,4,6,0,5,7]  B: [2]

Iteración 4: top=1, 1 < 3? sí → pb
  1 >= 1? sí → rb
A: [9,3,8,4,6,0,5,7]  B: [2,1]
pushed=2

Iteración 5: top=9, 9 < 3? no → ra
A: [3,8,4,6,0,5,7,9]  B: [2,1]

Iteración 6: top=3, 3 < 3? no (límite exclusivo)
  ... continuar rotando A...

Iteración N: top=0, 0 < 3? sí → pb
  0 >= 1? no → no rb
A: [8,4,6,5,7,9,3]  B: [0,2,1]
pushed=3

pushed == limit (3 == 3) → limit = 3 + 3 = 6
Ahora buscar índices 3,4,5...
```

**Optimización de rb:**
```c
if ((*b)->index >= limit - chunk / 2)
	rb(b);
```

**¿Qué hace esto?**
- Chunk [0-2]: mitad = 1, mitad superior = [2]
- Si movemos 2 a B, rotarlo → quedará más abajo
- Si movemos 0 ó 1 a B, no rotar → quedará arriba

**¿Para qué?**
- Pre-ordenar B ligeramente
- Elementos más grandes del chunk quedan más abajo
- Elementos más pequeños quedan más arriba
- Facilita push_back (siempre sacar el máximo)

---

#### `push_back()` - src/algorithm/chunk_sort.c:68-87

**Propósito:** Devolver todo de B a A en orden descendente.

```c
static void	push_back(t_node **a, t_node **b)
{
	int		pos;
	int		max;
	int		size;

	while (*b)
	{
		max = find_max_index(*b);     // Encontrar el máximo actual
		pos = find_pos_by_index(*b, max);  // Encontrar su posición
		size = stack_size(*b);

		// Rotar B para poner el máximo arriba
		if (pos <= size / 2)
			while (pos-- > 0)
				rb(b);    // Más cerca del inicio
		else
			while (pos++ < size)
				rrb(b);   // Más cerca del final

		pa(a, b);  // Mover máximo a A
	}
}
```

**Estrategia:**
1. Buscar el elemento con mayor índice en B
2. Rotarlo hasta arriba (optimizando dirección)
3. Moverlo a A
4. Repetir hasta que B esté vacío

**Resultado:** A queda ordenado descendentemente por índice (= ascendente por valor)

**Ejemplo:**
```
B: [3,7,1,9,2]  (índices)

Iteración 1:
  max = 9 (pos 3)
  pos=3, size=5, 3 > 5/2 → usar rrb
  rrb → [2,3,7,1,9]
  pa → A:[9] B:[2,3,7,1]

Iteración 2:
  max = 7 (pos 2)
  pos=2, size=4, 2 <= 4/2 → usar rb
  rb → [7,1,2,3]
  pa → A:[7,9] B:[1,2,3]

... continuar ...

Final: A:[0,1,2,3,4,5,6,7,8,9]
```

---

#### `find_max_index()` - src/algorithm/chunk_sort.c:29-41

**Propósito:** Encontrar el índice máximo en el stack.

```c
static int	find_max_index(t_node *stack)
{
	int		max;

	max = stack->index;

	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}

	return (max);
}
```

---

#### `find_pos_by_index()` - src/algorithm/chunk_sort.c:14-27

**Propósito:** Encontrar la posición de un nodo con un índice específico.

```c
static int	find_pos_by_index(t_node *stack, int index)
{
	int		pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);  // No encontrado (no debería pasar)
}
```

---

### MÓDULO 5: GESTIÓN DE MEMORIA

#### `free_stack()` - src/parse/free_utils.c:30-40

**Propósito:** Liberar toda la memoria de un stack.

```c
void	free_stack(t_node **stack)
{
	t_node		*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;  // Guardar siguiente
		free(*stack);          // Liberar actual
		*stack = tmp;          // Avanzar
	}
}
```

**¿Por qué guardar next antes de free?**
```c
// INCORRECTO:
free(*stack);
*stack = (*stack)->next;  // ¡Uso después de free!

// CORRECTO:
tmp = (*stack)->next;
free(*stack);
*stack = tmp;
```

---

#### `free_split()` - src/parse/free_utils.c:15-28

**Propósito:** Liberar un array de strings creado por ft_split.

```c
void	free_split(char **tokens)
{
	int		i;

	if (!tokens)
		return ;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);  // Liberar cada string
		i++;
	}
	free(tokens);  // Liberar el array
}
```

**Importante:** Array terminado en NULL permite saber cuándo parar.

---

## 🎯 RESUMEN EJECUTIVO PARA LA DEFENSA

### Estructura del Proyecto

**3 módulos principales:**
1. **Parse:** Validación y conversión de entrada
2. **Movements:** Operaciones básicas del stack
3. **Algorithm:** Lógica de ordenación

### Complejidad del Algoritmo

**Para 500 elementos:**
- Chunk sort con 11 chunks
- Complejidad aproximada: O(n²) en peor caso
- En promedio: ~5500 operaciones
- Tu código logra 96/100, probablemente ~5500-6000 movimientos

**Desglose:**
- Assign indexes: O(n²) - ~250,000 comparaciones
- Push chunks: O(n) - ~500 operaciones
- Push back: O(n²) - ~125,000 operaciones

### Gestión de Memoria

**Todas las asignaciones tienen su free correspondiente:**
- `parse_input`: malloc nodos → `free_stack`
- `ft_split`: malloc strings → `free_split`
- `assign_indexes`: malloc array → `free(arr)`

**Validación:** Usar valgrind para confirmar 0 leaks.

### Preguntas Típicas de Defensa

**P: ¿Por qué usas chunk sort?**
R: Es un balance entre simplicidad y eficiencia. Para listas grandes (500 elementos), divide el problema en chunks manejables, reduciendo la cantidad de movimientos comparado con algoritmos más simples.

**P: ¿Por qué 5 y 11 chunks?**
R: Son valores empíricos que dan buen rendimiento:
- 5 chunks para ≤100: ~20 elementos/chunk
- 11 chunks para >100: ~45 elementos/chunk
Más chunks = más overhead, menos chunks = chunks muy grandes.

**P: ¿Qué complejidad tiene tu algoritmo?**
R:
- Mejor caso (ya ordenado): O(n) - solo verificar
- Caso promedio: O(n²)
- Peor caso: O(n²)
El cuello de botella está en assign_indexes (bubble sort) y push_back (búsquedas lineales repetidas).

**P: ¿Cómo optimizarías el código?**
R:
1. Cambiar bubble sort a quicksort en assign_indexes: O(n²) → O(n log n)
2. Optimizar push_back usando tracking del máximo
3. Detectar duplicados en assign_indexes en vez de bucle separado
4. Implementar operaciones combinadas (rr, rrr, ss) donde sea beneficioso

**P: ¿Qué hace assign_indexes?**
R: Normaliza los valores a índices 0-n. Por ejemplo, [-1000, 5, 999] se convierte en índices [0, 1, 2]. Esto simplifica el chunk sort porque trabajamos con rangos predecibles (0 a n-1) en vez de valores arbitrarios.

**P: ¿Por qué separar las operaciones (sa, ra, etc.) de la lógica (swap_nodes, rotate_nodes)?**
R: Separación de responsabilidades:
- swap_nodes: lógica pura
- sa: operación con efecto (imprimir)
Permite reutilizar la lógica sin duplicar código.

**P: ¿Qué pasa si hay duplicados?**
R: El programa detecta duplicados en has_duplicates() después del parsing y retorna error. Esto es requisito del subject.

**P: ¿Cómo manejas el overflow?**
R: ft_atoi_push_swap usa long para detectar cuando el número excede INT_MAX o INT_MIN, estableciendo un flag de error que hace fallar el parsing.

**P: ¿Qué pasaría con 1 millón de números?**
R: El algoritmo seguiría funcionando pero sería muy lento:
- Assign indexes: ~10¹² comparaciones (horas)
- Push back: ~10¹² operaciones
- Total: probablemente días de ejecución
Se necesitaría un algoritmo más eficiente (quicksort, merge sort adaptado).

---

## ✅ CHECKLIST DE DEFENSA

Antes de tu defensa, asegúrate de poder explicar:

- [ ] Flujo completo desde main hasta sort_stack
- [ ] Cómo funciona el parsing (split → tokens → stack)
- [ ] Detección de errores (duplicados, overflow, formato)
- [ ] Las 11 operaciones del stack (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr)
- [ ] Algoritmo de 3 elementos (los 6 casos)
- [ ] Algoritmo de 5 elementos (find min, push, sort 3, push back)
- [ ] Chunk sort (push_chunks + push_back)
- [ ] Assign indexes (para qué sirve)
- [ ] Gestión de memoria (todos los mallocs y frees)
- [ ] Complejidad del algoritmo
- [ ] Posibles optimizaciones

---

## 📖 ORDEN DE ESTUDIO RECOMENDADO

**Día 1 (hoy):**
1. Lee este documento completo
2. Ejecuta tu programa con varios inputs
3. Traza manualmente sort_three con los 6 casos
4. Traza manualmente sort_five con un caso
5. Explica en voz alta cada función del parsing

**Mañana (antes de la defensa):**
1. Repasa chunk_sort (la parte más compleja)
2. Explica asign_indexes sin mirar el código
3. Practica responder las preguntas típicas
4. Compila y ejecuta para refrescar

---

¡Buena suerte en tu defensa! 🚀
