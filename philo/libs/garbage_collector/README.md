# 🗑️ Garbage Collector (libgb)

**[EN]** A linked list-based **automatic memory management library** written in C. It eliminates the need to manually track `free()` calls and prevents memory leaks by managing all allocated memory in two separate pools.

**[TR]** C dili için geliştirilmiş, linked list tabanlı bir **otomatik bellek yönetim kütüphanesi**dir. Manuel `free()` çağrılarını takip etme ihtiyacını ortadan kaldırarak, tüm tahsis edilen belleği iki ayrı havuzda yöneterek bellek sızıntılarını önler.

> Designed for use in 42 Istanbul projects. / 42 Istanbul projelerinde kullanılmak üzere tasarlanmıştır.

---

## 📋 Table of Contents / İçindekiler

- [Features / Özellikler](#-features--özellikler)
- [Architecture / Mimari](#-architecture--mimari)
- [Installation / Kurulum](#-installation--kurulum)
- [API Reference / API Referansı](#-api-reference--api-referansı)
  - [ft_malloc](#ft_malloc)
  - [sort_malloc](#sort_malloc)
  - [Helper Functions / Yardımcı Fonksiyonlar](#helper-functions--yardımcı-fonksiyonlar)
- [Usage / Kullanım](#-usage--kullanım)
- [File Structure / Dosya Yapısı](#-file-structure--dosya-yapısı)
- [Tests / Testler](#-tests--testler)
- [Authors / Yazarlar](#-authors--yazarlar)

---

## ✨ Features / Özellikler

**[EN]**
- **Two independent memory pools:** Long-term (`ft_malloc`) and sort-term (`sort_malloc`) memory management
- **Bulk cleanup in a single call:** Free all allocated memory at once via `destroy_list` parameter
- **Linked list backbone:** Each allocation is stored as a node; during cleanup the entire list is traversed and freed
- **GC-integrated string helpers:** `strdup`, `strjoin`, `itoa` variants that automatically register with the garbage collector
- **42 Norm compliant:** All code follows 42 coding standards
- **Static library output:** Compiles to `libgb.a` for easy integration into any project

**[TR]**
- **İki bağımsız bellek havuzu:** Uzun süreli (`ft_malloc`) ve kısa süreli / sıralama amaçlı (`sort_malloc`) bellek yönetimi
- **Tek çağrıda toplu temizlik:** `destroy_list` parametresi ile tüm tahsis edilmiş belleği tek seferde serbest bırakma
- **Linked list altyapısı:** Her tahsis bir düğüm olarak saklanır, temizlik sırasında tüm liste dolaşılarak serbest bırakılır
- **GC entegrasyonlu string yardımcıları:** `strdup`, `strjoin`, `itoa` fonksiyonlarının garbage collector'a otomatik kayıt olan versiyonları
- **42 Norm uyumlu:** Tüm kod 42 norm standartlarına uygundur
- **Statik kütüphane çıktısı:** `libgb.a` olarak derlenir, projelere kolayca entegre edilir

---

## 🏗️ Architecture / Mimari

**[EN]** The library operates on two completely independent memory pools. Each pool maintains its own linked list of allocations using `static` pointers, preserving internal state across function calls.

**[TR]** Kütüphane, birbirinden tamamen bağımsız iki bellek havuzu üzerinde çalışır. Her havuz, `static` pointer'lar sayesinde dahili durumunu koruyarak fonksiyon çağrıları arasında bağlam bilgisini muhafaza eder.

```
┌───────────────────────────────────────────────────┐
│              ft_malloc (Long-Term Pool)            │
│                                                   │
│  t_gb: [ptr|next] -> [ptr|next] -> [ptr|next] -> NULL  │
│                                                   │
│  EN: Data that lives until the end of the program │
│  TR: Programın sonuna kadar yaşayan veriler       │
└───────────────────────────────────────────────────┘

┌───────────────────────────────────────────────────┐
│            sort_malloc (Sort-Term Pool)            │
│                                                   │
│  t_sort_gb: [ptr|next] -> [ptr|next] -> NULL      │
│                                                   │
│  EN: Temporary data for sorting / short tasks     │
│  TR: Sıralama / kısa süreli işlemler için         │
│      geçici veriler                               │
└───────────────────────────────────────────────────┘
```

### Data Structures / Veri Yapıları

```c
// Long-term pool node / Uzun süreli havuz düğümü
typedef struct s_gb
{
    void        *address_pointer;
    struct s_gb *next;
}   t_gb;

// Sort-term pool node / Kısa süreli havuz düğümü
typedef struct s_sort_gb
{
    void                *address_pointer;
    struct s_sort_gb    *next;
}   t_sort_gb;
```

---

## 🔧 Installation / Kurulum

### Compiling the Library / Kütüphaneyi Derleme

```bash
# Compile the static library / Statik kütüphaneyi derle
make

# Remove object files / Object dosyalarını temizle
make clean

# Full cleanup (objects + library) / Tam temizlik
make fclean

# Rebuild from scratch / Sıfırdan yeniden derle
make re
```

### Integrating into Your Project / Projenize Entegre Etme

**1.** Clone or add as submodule / Klonlayın veya submodule olarak ekleyin:
```bash
git submodule add <repo-url> garbage_collector
```

**2.** Update your Makefile / Makefile'ınızı güncelleyin:
```makefile
LIBGB_DIR = ./garbage_collector
LIBGB_FLAGS = -L$(LIBGB_DIR) -lgb
INC_FLAGS = -I$(LIBGB_DIR)
```

**3.** Include the header / Header dosyasını dahil edin:
```c
#include "gb.h"
```

---

## 📖 API Reference / API Referansı

### `ft_malloc`

```c
void *ft_malloc(size_t size, int destroy_list);
```

**[EN]**
The **long-term** memory allocator. All memory allocated through `ft_malloc` is tracked in a single linked list using `static` pointers. This pool is designed for data that persists throughout the program's lifetime. Memory is only freed when you explicitly call `ft_malloc(0, 1)`.

**How it works:**
1. A new `t_gb` node is created via `malloc()`
2. The requested `size` bytes are allocated via `malloc()` and stored in `node->address_pointer`
3. The node is appended to the end of the linked list
4. The pointer to the usable memory is returned

**`destroy_list` parameter values:**

| Value | Behavior |
|-------|----------|
| `0`   | Normal allocation — allocates `size` bytes and returns a pointer |
| `1`   | **Destroy** — traverses the entire list, frees every `address_pointer` and every node, resets the list to `NULL` |
| `5`   | Returns the address of the root pointer (internal/debug use) |

---

**[TR]**
**Uzun süreli** bellek tahsis fonksiyonudur. `ft_malloc` ile tahsis edilen tüm bellek, `static` pointer'lar kullanılarak tek bir linked list'te takip edilir. Bu havuz, programın yaşam döngüsü boyunca kalıcı olacak veriler için tasarlanmıştır. Bellek yalnızca `ft_malloc(0, 1)` çağrıldığında serbest bırakılır.

**Nasıl çalışır:**
1. `malloc()` ile yeni bir `t_gb` düğümü oluşturulur
2. İstenen `size` byte `malloc()` ile tahsis edilir ve `node->address_pointer`'a kaydedilir
3. Düğüm, linked list'in sonuna eklenir
4. Kullanılabilir belleğe işaret eden pointer döndürülür

**`destroy_list` parametre değerleri:**

| Değer | Davranış |
|-------|----------|
| `0`   | Normal tahsis — `size` byte tahsis eder ve pointer döndürür |
| `1`   | **Yok et** — tüm listeyi dolaşır, her `address_pointer`'ı ve her düğümü serbest bırakır, listeyi `NULL`'a sıfırlar |
| `5`   | Root pointer'ın adresini döndürür (dahili/debug kullanımı) |

---

### `sort_malloc`

```c
void *sort_malloc(size_t size, int destroy_list);
```

**[EN]**
The **sort-term (short-term)** memory allocator. It works identically to `ft_malloc` but manages a completely **separate** linked list using its own `static` pointers and `t_sort_gb` nodes. This pool is intended for **temporary** or **intermediate** data — such as buffers created during sorting algorithms, temporary string manipulations, or any short-lived computation that should be cleaned up independently from the main (long-term) pool.

**How it works:**
1. A new `t_sort_gb` node is created via `malloc()`
2. The requested `size` bytes are allocated via `malloc()` and stored in `node->address_pointer`
3. The node is appended to the sort-term linked list
4. The pointer to the usable memory is returned

**`destroy_list` parameter values:**

| Value | Behavior |
|-------|----------|
| `0`   | Normal allocation — allocates `size` bytes and returns a pointer |
| `1`   | **Destroy** — traverses the entire sort-term list, frees every `address_pointer` and every node, resets the list to `NULL` |

**Why two separate pools?**
Having two pools allows you to free temporary/sorting data (`sort_malloc(0, 1)`) at any point during execution **without** affecting the long-term data managed by `ft_malloc`. For example, after a sorting pass you can clean up all intermediate buffers while keeping your main program data intact.

---

**[TR]**
**Kısa süreli / sıralama amaçlı (sort-term)** bellek tahsis fonksiyonudur. `ft_malloc` ile tamamen aynı mantıkta çalışır ancak kendi `static` pointer'larını ve `t_sort_gb` düğümlerini kullanan **ayrı** bir linked list yönetir. Bu havuz, **geçici** veya **ara** veriler için tasarlanmıştır — sıralama algoritmaları sırasında oluşturulan tamponlar, geçici string işlemleri veya ana (uzun süreli) havuzdan bağımsız olarak temizlenmesi gereken kısa ömürlü hesaplamalar gibi.

**Nasıl çalışır:**
1. `malloc()` ile yeni bir `t_sort_gb` düğümü oluşturulur
2. İstenen `size` byte `malloc()` ile tahsis edilir ve `node->address_pointer`'a kaydedilir
3. Düğüm, sort-term linked list'in sonuna eklenir
4. Kullanılabilir belleğe işaret eden pointer döndürülür

**`destroy_list` parametre değerleri:**

| Değer | Davranış |
|-------|----------|
| `0`   | Normal tahsis — `size` byte tahsis eder ve pointer döndürür |
| `1`   | **Yok et** — tüm sort-term listesini dolaşır, her `address_pointer`'ı ve her düğümü serbest bırakır, listeyi `NULL`'a sıfırlar |

**Neden iki ayrı havuz?**
İki ayrı havuz sayesinde, programın herhangi bir noktasında geçici/sıralama verilerini (`sort_malloc(0, 1)`) serbest bırakabilirsiniz — `ft_malloc` tarafından yönetilen uzun süreli verilere **dokunmadan**. Örneğin, bir sıralama işlemi sonrasında tüm ara tamponları temizleyebilir, ana program verilerinizi olduğu gibi koruyabilirsiniz.

---

### Helper Functions / Yardımcı Fonksiyonlar

#### Long-Term Pool Helpers / Uzun Süreli Havuz Yardımcıları

| Function / Fonksiyon | Description (EN) | Açıklama (TR) |
|----------------------|-------------------|---------------|
| `char *long_term_strdup(const char *s)` | Duplicates a string using `ft_malloc`. The copy lives in the long-term pool. | `ft_malloc` kullanarak string kopyalar. Kopya, uzun süreli havuzda yaşar. |
| `char *ft_long_term_itoa(int n)` | Converts an integer to a string using `ft_malloc`. Handles negative numbers and `INT_MIN`. | `ft_malloc` kullanarak integer'ı string'e çevirir. Negatif sayıları ve `INT_MIN`'i destekler. |

#### Sort-Term Pool Helpers / Kısa Süreli Havuz Yardımcıları

| Function / Fonksiyon | Description (EN) | Açıklama (TR) |
|----------------------|-------------------|---------------|
| `char *sort_term_strdup(const char *s)` | Duplicates a string using `sort_malloc`. The copy lives in the sort-term pool. | `sort_malloc` kullanarak string kopyalar. Kopya, kısa süreli havuzda yaşar. |
| `char *sort_term_strjoin(const char *s1, const char *s2)` | Concatenates two strings using `sort_malloc`. The result lives in the sort-term pool. | `sort_malloc` kullanarak iki stringi birleştirir. Sonuç, kısa süreli havuzda yaşar. |
| `char *ft_sort_term_itoa(int n)` | Converts an integer to a string using `sort_malloc`. Handles negative numbers and `INT_MIN`. | `sort_malloc` kullanarak integer'ı string'e çevirir. Negatif sayıları ve `INT_MIN`'i destekler. |

---

## 🚀 Usage / Kullanım

### Basic Example / Temel Örnek

```c
#include "gb.h"
#include <stdio.h>

int main(void)
{
    // EN: Allocate a string in the long-term pool
    // TR: Uzun süreli havuzda bir string tahsis et
    char *name = long_term_strdup("Garbage Collector");
    printf("Name: %s\n", name);

    // EN: Allocate temporary strings in the sort-term pool
    // TR: Kısa süreli havuzda geçici stringler tahsis et
    char *tmp1 = sort_term_strdup("Hello, ");
    char *tmp2 = sort_term_strjoin(tmp1, "World!");
    printf("Temp: %s\n", tmp2);

    // EN: Clean up sort-term pool (tmp1 and tmp2 are freed)
    // TR: Kısa süreli havuzu temizle (tmp1 ve tmp2 serbest bırakılır)
    sort_malloc(0, 1);

    // EN: 'name' is still valid — it's in the long-term pool
    // TR: 'name' hâlâ geçerli — uzun süreli havuzda
    printf("Name is still alive: %s\n", name);

    // EN: Clean up long-term pool at program end
    // TR: Program sonunda uzun süreli havuzu temizle
    ft_malloc(0, 1);

    return (0);
}
```

### Two-Pool Scenario / İki Havuzlu Senaryo

```c
#include "gb.h"

// EN: A function that uses temporary memory for sorting
// TR: Sıralama için geçici bellek kullanan bir fonksiyon
void process_data(void)
{
    // EN: These allocations go to the sort-term pool
    // TR: Bu tahsisler kısa süreli havuza gider
    char *buffer = sort_term_strdup("temporary data");
    char *index  = ft_sort_term_itoa(42);

    // ... processing / işlemler ...

    // EN: Free only the sort-term pool — long-term data untouched
    // TR: Sadece kısa süreli havuzu temizle — uzun süreli veri etkilenmez
    sort_malloc(0, 1);
}

int main(void)
{
    // EN: This allocation goes to the long-term pool
    // TR: Bu tahsis uzun süreli havuza gider
    char *config = long_term_strdup("persistent config");

    process_data();  // sort-term cleaned inside / sort-term içeride temizlenir

    // EN: config is still valid here
    // TR: config hâlâ burada geçerli

    // EN: Final cleanup
    // TR: Son temizlik
    ft_malloc(0, 1);
    return (0);
}
```

### Integer to String / Integer'dan String'e

```c
#include "gb.h"
#include <stdio.h>

int main(void)
{
    // EN: Long-term itoa
    // TR: Uzun süreli itoa
    char *num1 = ft_long_term_itoa(-2147483648);  // INT_MIN
    printf("%s\n", num1);  // Output: -2147483648

    // EN: Sort-term itoa
    // TR: Kısa süreli itoa
    char *num2 = ft_sort_term_itoa(12345);
    printf("%s\n", num2);  // Output: 12345

    sort_malloc(0, 1);
    ft_malloc(0, 1);
    return (0);
}
```

---

## 📁 File Structure / Dosya Yapısı

```
garbage_collector/
├── Makefile                 # Build file → libgb.a / Derleme dosyası → libgb.a
├── gb.h                     # Public API header / Genel API header
├── s_gb.h                   # Struct definitions (t_gb, t_sort_gb) / Yapı tanımları
├── gb.c                     # ft_malloc — Long-term memory pool / Uzun süreli bellek havuzu
├── sort_gb.c                # sort_malloc — Sort-term memory pool / Kısa süreli bellek havuzu
├── long_term_funcs.c        # long_term_strdup, ft_long_term_itoa
├── sort_gb_funcs.c          # sort_term_strjoin, sort_term_strdup
├── sort_gb_funcs_2.c        # ft_sort_term_itoa
└── test/
    ├── Makefile              # Test build file / Test derleme dosyası
    ├── ft_malloc_test.c     # Test program / Test programı
    └── trace.log            # Test output log / Test çıktı logu
```

---

## 🧪 Tests / Testler

**[EN]** To compile and run the test program:

**[TR]** Test programını derlemek ve çalıştırmak için:

```bash
cd test
make
./ft_malloc_test
```

**[EN]** The test program verifies the core functionality of both `ft_malloc` and `sort_malloc` pools.

**[TR]** Test programı hem `ft_malloc` hem de `sort_malloc` havuzlarının temel işlevselliğini doğrular.

---

## 👥 Authors / Yazarlar

- **muayna** — [42 Istanbul](https://42istanbul.com.tr/)
- **yademirk** — [42 Istanbul](https://42istanbul.com.tr/)

---

*This project was developed at [42 Istanbul](https://42istanbul.com.tr/).* / *Bu proje [42 Istanbul](https://42istanbul.com.tr/) bünyesinde geliştirilmiştir.*
