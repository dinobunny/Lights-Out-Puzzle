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
```натискаємо Clone Repository 
![image](https://github.com/user-attachments/assets/e7071670-303f-4f30-aeab-a5584f886f58)
```переходимо на сторінку ГітХаба шукаємо URL а це саме -> https://github.com/dinobunny/Lights-Out-Puzzle.git
```Directory це наше сховище данної копії 
![image](https://github.com/user-attachments/assets/a76ce317-2c2e-4af0-bdcb-393611eb9c64)
```таке повинно бути і після цього натискаємо  Clone
![image](https://github.com/user-attachments/assets/c445bf94-c04b-47cf-9458-a6b2af48252e)
```Йде загрузка і після чого натискаємо Trust Project
![image](https://github.com/user-attachments/assets/f7d893c2-ec30-4ce0-ab94-402f8940548e)
```Вилазить настройка проекта, клацаємо ОК 
![image](https://github.com/user-attachments/assets/712a7558-1669-4378-a41a-c20df4188936)
```Бачимо цей єкран 
![image](https://github.com/user-attachments/assets/16bb03aa-4724-4ac0-ad26-d8ce45c1250c)
натискаємо на 3 крапочки -> Edit -> (Знаходимо та вписуємо) Program arguments: 5 5
![image](https://github.com/user-attachments/assets/d00e8bf2-bf42-408b-97c6-76c089a022b6)
``` Aplay -> Ok 
тепер можна ранити 
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
