# 📋 RESUMEN EJECUTIVO - DEFENSA PUSH_SWAP

## ⏱️ RESUMEN DE 5 MINUTOS

### ¿Qué hace el programa?

Push_swap ordena números usando dos stacks (A y B) con un conjunto limitado de 11 operaciones.

**Operaciones permitidas:**
- **swap:** sa, sb, ss (intercambiar dos primeros)
- **push:** pa, pb (mover entre stacks)
- **rotate:** ra, rb, rr (rotar hacia arriba)
- **reverse rotate:** rra, rrb, rrr (rotar hacia abajo)

---

### Arquitectura del Código

```
push_swap/
├── src/
│   ├── main.c              → Entrada, validación, flujo principal
│   ├── parse/              → Parseo y validación de entrada
│   │   ├── parse_input.c   → Convierte argv en stack
│   │   ├── split.c         → Separa strings por espacios
│   │   ├── parse_utils.c   → Validaciones y creación de nodos
│   │   ├── atoi_utils.c    → Conversión string→int con overflow check
│   │   ├── string_utils.c  → strdup
│   │   └── free_utils.c    → Liberación de memoria
│   ├── movements/          → Operaciones del stack
│   │   ├── operations_utils.c  → Lógica core (swap, push, rotate)
│   │   ├── swap_ops.c      → sa, sb, ss
│   │   ├── push_ops.c      → pa, pb
│   │   ├── rotate_ops.c    → ra, rb, rr
│   │   └── reverse_rotate_ops.c → rra, rrb, rrr
│   └── algorithm/          → Lógica de ordenación
│       ├── sort.c          → Dispatcher por tamaño
│       ├── sort_small.c    → Algoritmos para 3 y 5 elementos
│       ├── chunk_sort.c    → Algoritmo principal (>5 elementos)
│       ├── assign_indexes.c → Normalización de valores
│       └── stack_utils.c   → Utilidades (stack_size)
└── include/
    └── push_swap.h         → Definiciones y prototipos
```

---

### Flujo del Programa

```
1. main()
   ↓
2. validate_args() → Rechazar strings vacíos
   ↓
3. parse_input() → Crear stack A
   │  ├── split_args() → Separar todos los números
   │  ├── add_arguments() → Crear nodos
   │  └── has_duplicates() → Validar unicidad
   ↓
4. is_sorted() → Si ya ordenado, salir
   ↓
5. sort_stack() → Seleccionar algoritmo
   │  ├── size == 2   → sa si necesario
   │  ├── size == 3   → sort_three()
   │  ├── size <= 5   → sort_five()
   │  └── size > 5    → assign_indexes() + chunk_sort()
   ↓
6. free_stack() → Liberar memoria
```

---

### Algoritmos por Tamaño

#### 2 elementos
```c
if (a->value > a->next->value)
    sa(a);
```
**Operaciones:** 0-1

#### 3 elementos (sort_three)
Hardcodeados los 6 casos posibles:
```
[1,2,3] → nada
[2,1,3] → sa
[3,2,1] → sa + rra
[3,1,2] → ra
[1,3,2] → sa + ra
[2,3,1] → rra
```
**Operaciones:** 0-2

#### 4-5 elementos (sort_five)
1. Mover los mínimos a B (push los 1 o 2 más pequeños)
2. Ordenar los 3 que quedan en A con sort_three
3. Devolver todo de B a A

**Operaciones:** ~10-12

#### >5 elementos (chunk_sort)
1. **assign_indexes:** Convertir valores en índices 0 a n-1
2. **push_chunks:** Mover a B procesando por rangos (chunks)
3. **push_back:** Devolver a A sacando siempre el máximo

**Operaciones para 500:** ~5000-6000

---

## 🎯 CONCEPTOS CLAVE

### 1. ¿Qué es un índice normalizado?

**Problema:** Valores arbitrarios dificultan el algoritmo
```
Valores: [-1000, 5, 999, -500]
```

**Solución:** Convertir a índices basados en orden
```
Array ordenado: [-1000, -500, 5, 999]
Índices:        [   0,    1,  2,   3]

Nodo con value=-1000 → index=0
Nodo con value=-500  → index=1
Nodo con value=5     → index=2
Nodo con value=999   → index=3
```

**Beneficio:** Trabajar con rangos predecibles (0 a n-1)

---

### 2. ¿Cómo funciona chunk_sort?

**Concepto:** Dividir en grupos y procesar por partes

**Ejemplo con 100 números, 5 chunks:**
```
chunk_size = 100 / 5 + 1 = 21

Fase 1 - Push Chunks:
  Límite 1: Mover a B los índices [0-20]   (valores más pequeños)
  Límite 2: Mover a B los índices [21-41]
  Límite 3: Mover a B los índices [42-62]
  Límite 4: Mover a B los índices [63-83]
  Límite 5: Mover a B los índices [84-99]  (valores más grandes)

Fase 2 - Push Back:
  Repetir hasta B vacío:
    - Encontrar máximo en B
    - Rotarlo hasta arriba
    - pa (mover a A)

  Resultado: A ordenado descendentemente por índice
            = ascendentemente por valor ✓
```

**Optimización rb:**
```c
if ((*b)->index >= limit - chunk / 2)
    rb(b);
```
- Elementos en mitad superior del chunk → rb
- Pre-ordena B: grandes abajo, pequeños arriba
- Facilita encontrar máximo después

---

### 3. Optimización de Rotaciones

**Decidir entre ra y rra:**

Si quiero mover el elemento en posición `pos` al tope:

```
Stack: [A, B, C, D, E]  (size = 5)
         0  1  2  3  4

pos=2 (elemento C):
  Opción 1: ra ra      → 2 operaciones
  Opción 2: rra rra rra → 3 operaciones
  Elegir: ra (2 <= 5/2)

pos=4 (elemento E):
  Opción 1: ra ra ra ra → 4 operaciones
  Opción 2: rra         → 1 operación
  Elegir: rra (4 > 5/2)
```

**Fórmula:**
```c
if (pos <= size / 2)
    usar ra;
else
    usar rra;
```

---

## 📊 ANÁLISIS DE COMPLEJIDAD

### Complejidad Temporal

| Caso | Complejidad | Explicación |
|------|-------------|-------------|
| **Mejor caso** | O(n) | Ya ordenado, solo verificar |
| **Caso promedio** | O(n²) | Chunk sort con búsquedas lineales |
| **Peor caso** | O(n²) | Chunk sort peor escenario |

**Cuellos de botella:**
1. `sort_array()` en assign_indexes: O(n²) bubble sort
2. `set_indexes()`: O(n²) búsquedas lineales
3. `push_back()`: O(n²) encontrar máximo repetidamente

---

### Complejidad Espacial

| Componente | Espacio | Notas |
|------------|---------|-------|
| Stack A | O(n) | n nodos |
| Stack B | O(n) | n nodos en peor caso |
| Array temporal (assign_indexes) | O(n) | Se libera después |
| **Total** | **O(n)** | Lineal |

---

## ⚠️ DEUDA TÉCNICA (Resumen)

### CRÍTICO
**Bubble sort en assign_indexes**
- Ubicación: `src/algorithm/assign_indexes.c:31-53`
- Complejidad actual: O(n²)
- Optimización: Quicksort → O(n log n)
- Impacto: Moderado (solo se ejecuta una vez)

### MEDIO
**Búsquedas repetidas en push_back**
- Ubicación: `src/algorithm/chunk_sort.c:68-87`
- Problema: `find_max_index()` se llama n veces
- Optimización: Track del máximo (max--)
- Impacto: Alto para listas grandes

### BAJO
**Números mágicos**
- Ubicación: `src/algorithm/sort.c:44-47`
- Problema: 5 y 11 chunks sin constantes
- Optimización: Definir CHUNKS_SMALL, CHUNKS_LARGE
- Impacto: Legibilidad

---

## 🔧 OPTIMIZACIONES SUGERIDAS

### 1. Quicksort en assign_indexes
**Beneficio:** 250,000 → 4,500 operaciones (500 elementos)

### 2. Tracking de máximo en push_back
**Beneficio:** Eliminar n búsquedas lineales

### 3. Cache de stack_size
**Beneficio:** Evitar recorridos innecesarios

### 4. Detección de duplicados en assign_indexes
**Beneficio:** Reutilizar array ordenado

---

## 💬 PREGUNTAS FRECUENTES

### P: ¿Por qué no usar quicksort directamente?

**R:** Push_swap tiene restricciones:
- Solo puedes operar en los extremos de los stacks
- Solo 11 operaciones permitidas
- No puedes acceder a elementos intermedios directamente

Quicksort necesita acceso aleatorio al array. Chunk sort está diseñado específicamente para las limitaciones de push_swap.

---

### P: ¿96/100 es buena nota?

**R:** Sí, muy buena. Según el subject:
- 500 números:
  - ≤5500 movimientos: 5 puntos
  - ≤7000 movimientos: 4 puntos
  - ≤8500 movimientos: 3 puntos

96/100 indica ~5500-6000 movimientos, dentro del rango óptimo.

---

### P: ¿Qué es mejor, 5 o 11 chunks?

**R:** Depende del tamaño:
- **5 chunks para ≤100:**
  - Chunk size ~20
  - Balance entre precisión y overhead
- **11 chunks para >100:**
  - Chunk size ~45 (para 500)
  - Más precisión para listas grandes

Demasiados chunks → overhead de gestión
Pocos chunks → chunks muy grandes, menos eficiente

---

### P: ¿Cómo manejo la memoria?

**R:** Todo malloc tiene su free:
```
parse_input:
  - split_args: malloc tokens → free_split
  - create_node: malloc nodos → free_stack
  - ft_split: malloc strings → free_split

assign_indexes:
  - stack_to_array: malloc array → free(arr)

main:
  - parse_input: crea stack_a → free_stack(&stack_a)
  - sort_stack: usa stack_b → free_stack(&stack_b)
```

Verificar con: `valgrind --leak-check=full ./push_swap ...`

---

### P: ¿Por qué hardcodear sort_three?

**R:** Porque:
1. Solo hay 6 permutaciones posibles (3! = 6)
2. Cada caso tiene solución óptima conocida (máximo 2 ops)
3. Es más rápido que cualquier algoritmo genérico
4. Garantiza mínimo de operaciones

---

## 🎓 CHECKLIST PRE-DEFENSA

**Conceptos Fundamentales:**
- [ ] Explicar las 11 operaciones
- [ ] Describir la estructura t_node
- [ ] Explicar qué es un índice normalizado
- [ ] Describir el flujo de main a sort_stack

**Algoritmos:**
- [ ] Los 6 casos de sort_three
- [ ] Estrategia de sort_five
- [ ] Fases de chunk_sort (push_chunks + push_back)
- [ ] Por qué usar chunks

**Implementación:**
- [ ] Cómo detectas duplicados
- [ ] Cómo detectas overflow
- [ ] Cómo decides entre ra y rra
- [ ] Por qué rb en mitad superior del chunk

**Análisis:**
- [ ] Complejidad temporal del algoritmo
- [ ] Cuellos de botella principales
- [ ] Posibles optimizaciones
- [ ] Trade-offs de las decisiones

**Práctica:**
- [ ] Trazar sort_three con [2,1,3]
- [ ] Trazar sort_five con [3,5,1,4,2]
- [ ] Explicar assign_indexes con [-1000, 5, 999]
- [ ] Explicar chunk_sort conceptualmente

---

## ⚡ TIPS DE ÚLTIMO MOMENTO

### 1. Empieza con un ejemplo
"Para explicar esto, déjame usar un ejemplo concreto..."

### 2. Dibuja si es necesario
Pide papel para visualizar el stack o las rotaciones

### 3. Sé honesto sobre limitaciones
"Este código funciona bien hasta 500 elementos, pero para millones necesitaría un algoritmo diferente"

### 4. Conecta con el subject
"Según el subject, el requisito es..."

### 5. Mantén la calma
Si no recuerdas algo exacto: "El concepto es X, aunque no recuerdo la implementación exacta de memoria"

---

## 📞 RESPUESTAS DE EMERGENCIA

### Si te preguntan algo que no sabes:

❌ "No lo sé"
✅ "No recuerdo los detalles exactos, pero el concepto general es..."

### Si te piden mejorar el código:

❌ "Ya está perfecto"
✅ "Podría optimizar X cambiando Y, lo que mejoraría Z pero añadiría complejidad en W"

### Si te señalan un bug:

❌ "No es un bug"
✅ "Tienes razón, eso es una limitación. Una forma de mejorarlo sería..."

---

## 🎯 LOS 5 PUNTOS CLAVE

1. **Push_swap ordena números usando solo dos stacks y 11 operaciones limitadas**

2. **Usa diferentes algoritmos según el tamaño: hardcoded para ≤5, chunk sort para >5**

3. **Assign_indexes normaliza valores a índices 0 a n-1 para simplificar chunk sort**

4. **Chunk sort divide en grupos, procesa por partes, y devuelve sacando el máximo**

5. **Complejidad O(n²) pero optimizado para el rango 100-500 elementos del subject**

---

¡Mucha suerte en tu defensa! 🚀

Recuerda: **Entender > Memorizar**

No intentes memorizar cada línea, entiende el flujo general y los conceptos clave. Las implementaciones específicas puedes explicarlas conceptualmente.
