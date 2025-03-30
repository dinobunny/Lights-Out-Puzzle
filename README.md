Окей! 👇 Ось готовий **Markdown-опис логіки** твоєї програми для `README.md`:

---

```markdown
# 🔦 Lights-Out Puzzle Solver

Рішення класичної задачі **"Lights Out"** з використанням методу Гаусса по модулю 2.

---

## 🎯 Мета

Знайти **послідовність натискань** кнопок у матриці (кожна клітинка — лампочка), щоб **вимкнути всі світла**.

---

## 🧠 Логіка роботи

### 1. Побудова моделі

- Кожна лампочка — це **рівняння**.
- Кожна кнопка — це **змінна**.
- Побудову моделі виконує функція `createEquationSystem(...)`:

> `A * x = b (mod 2)`

- `A` — матриця впливу: які кнопки змінюють які клітинки.
- `x` — які кнопки потрібно натиснути (шукаємо).
- `b` — поточний стан лампочок (1 — увімкнено, 0 — вимкнено).

---

### 2. Розв’язання системи

Функція `solveWithGauss(...)` застосовує **метод Гаусса по модулю 2**:
- Працює з бітами (0 і 1)
- Використовує XOR для елімінації
- Повертає розв’язок або сигналізує, що розв’язку немає

---

### 3. Застосування рішення

Функція `openBox(...)`:
- Отримує поточний стан поля
- Створює систему рівнянь
- Знаходить план натискань
- Послідовно натискає кнопки через публічний метод `toggle(...)`
- Перевіряє фінальний стан через `isLocked()`

---

## 🔍 Структура проєкту

```
📂 Lights-Out-Puzzle/
├── main.cpp               # Запуск програми
├── OpenBox.cpp/.h         # Основна логіка вирішення
├── SecureBox.h            # Емуляція гри (наданий інтерфейс)
├── openbox_test.cpp       # Юніт-тести (GoogleTest)
├── CMakeLists.txt         # Збірка
```

---

## ✅ Особливості

- Підтримка розмірів від **3x3 до 100x100**
- Повна модульність
- Юніт-тести покривають основні сценарії
- Виводить **послідовність натискань** для розв’язку

---


## 📚 Алгоритм

Метод Гаусса по модулю 2 працює в полі `GF(2)`, тобто:
- `1 + 1 = 0`
- `0 + 1 = 1`
- `XOR` (`^`) використовується замість `+`

---

Хочеш — можу залити це як `README.md` готовим файлом або дати тобі `.md` окремо 💡

### 🔧 Вимоги для підключення даної програми

- C++17 або вище
- CMake ≥ (VERSION 3.30)
- Git
- G++ або Clang (на Linux/macOS)
- MinGW або MSVC (на Windows)
- (Опціонально) CLion / VSCode / інший редактор

---

### 📥 Як встановити і запустити (Linux/macOS):

```bash
# 1. Клонуємо репозиторій
git clone https://github.com/your-username/Lights-Out-Puzzle.git
cd Lights-Out-Puzzle

# 2. Створюємо директорію для збірки
mkdir build
cd build

# 3. Генеруємо Make-файли
cmake ..

# 4. Компілюємо
make

# 5. Запускаємо (наприклад, 5x5 коробка) параметри обов'язково бо так не буде працювати 
./Lights_Out_Puzzle 5 5 
```

---

###  Якщо у вас Clion 
![image](https://github.com/user-attachments/assets/4f05a3c9-9dea-400e-bee1-6126eef27008)
---
### Натискаємо Clone Repository 
![image](https://github.com/user-attachments/assets/e7071670-303f-4f30-aeab-a5584f886f58)

### URL -> https://github.com/dinobunny/Lights-Out-Puzzle.git
### Directory це ми обираємо сховище для данної копії
---
### Таке повинно бути і після цього натискаємо  Clone
![image](https://github.com/user-attachments/assets/a76ce317-2c2e-4af0-bdcb-393611eb9c64)
---
### Йде загрузка і після чого натискаємо Trust Project
![image](https://github.com/user-attachments/assets/c445bf94-c04b-47cf-9458-a6b2af48252e)
---
### Вилазить настройка проекта, клацаємо ОК 
![image](https://github.com/user-attachments/assets/f7d893c2-ec30-4ce0-ab94-402f8940548e)
---
### Бачимо цей єкран 
![image](https://github.com/user-attachments/assets/712a7558-1669-4378-a41a-c20df4188936)
---
### натискаємо на 3 крапочки -> Edit -> (Знаходимо та вписуємо) Program arguments: 5 5
![image](https://github.com/user-attachments/assets/16bb03aa-4724-4ac0-ad26-d8ce45c1250c)
---
### Aplay -> Ok 
![image](https://github.com/user-attachments/assets/d00e8bf2-bf42-408b-97c6-76c089a022b6)
---
Тепер можна RUN  
---
### 🧪 Приклад використання:

```bash
./Lights_Out_Puzzle 4 4
```

📤 Вивід:
```
> ```
> toggle(0, 1)
> toggle(2, 3)
> toggle(4, 0)
> BOX: OPENED!
> ```
---

## 🧪 Запуск тестів

```bash
ctest
# або напряму
./test_runner
```

---
### 🤝 Автора:
> Євген Рафальський — ентузіаст, який не боїться XOR-ів, рекурсій і стекових оверфлоу 😄 (😄😄😄😄😄не дуже впевнено😄😄😄😄😄😄)
---
