## 📦 Lights-Out-Puzzle Solver

Розв'язок задачі "SecureBox" — відкриття замкненого контейнера (2D boolean grid) лише за допомогою публічного API: `toggle`, `isLocked`, `getState`.

---

### 🔧 Вимоги для підключення даної програми

- C++17 або вище
- CMake ≥ (VERSION 3.30)
- Git
- G++ або Clang (на Linux/macOS)
- MinGW або MSVC (на Windows)
- (Опціонально) CLion / VSCode / інший редактор

---

### Логіка моєї програми 
---
СПОЧАТКУ -> створюється коробка з розмірами y × x, наприклад 3×3 = 9 клітинок.
---
ПОТІМ -> рахується скільки всього клітинок (наприклад, 9).
---
ДАЛІ -> перебираємо всі можливі комбінації натискань на ці клітинки (2^9 = 512 варіантів).
---
НА КОЖНОМУ КРОЦІ -> створюється копія коробки, щоб працювати з нею, не чіпаючи оригінал.
---
ПЕРЕВІРЯЄМО -> які клітинки треба натиснути згідно з поточною комбінацією (маскою).
---
ЯКЩО В МАСКІ 1 -> натискаємо на відповідну клітинку (перемикаємо її та весь рядок і стовпець).
---
ПІСЛЯ ВСІХ НАТИСКАНЬ -> перевіряємо, чи коробка стала повністю розблокована (всі клітинки false).
---
ЯКЩО ТАК -> повертаємо false — тобто коробка відкрилася.
---
ЯКЩО ЖОДНА КОМБІНАЦІЯ НЕ СПРАЦЮВАЛА -> повертаємо true — коробку не вдалося відкрити.
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
BOX: OPENED!
```
або
```
BOX: LOCKED!
```
---
### 🤝 Автора:
> Євген Рафальський — ентузіаст, який не боїться XOR-ів, рекурсій і стекових оверфлоу 😄 (😄😄😄😄😄не дуже впевнено😄😄😄😄😄😄)
---
