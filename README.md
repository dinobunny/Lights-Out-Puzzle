## 📦 Lights-Out-Puzzle Solver

Solution "SecureBox" - opening a closed container (2D Boolean Grid) only with the help of a public API: `toggle`,` ISLOCKED ', `Getstate'.

---

### 🔧 Requirements to connect this program

- C++17 
- CMake ≥ (VERSION 3.14)
- Git
- G++ or Clang (на Linux/macOS)
- MinGW or MSVC (на Windows)
- (Optional) CLion / VSCode / Another editor

---


### 🔐 Мета:
Відкрити коробку, яка виглядає як **таблиця з клітинок**.  
Кожна клітинка може бути:
- `true` — **заблокована**
- `false` — **відкрита**
---
https://www.youtube.com/watch?v=1izbpSk3ays 
пояснює як грати 
---

## 🧩 Правила гри:
Коли ви натискаєте (toggle) на клітинку:
- Змінюється **сама клітинка**
- Змінюється **весь ряд** цієї клітинки
- Змінюється **вся колонка** цієї клітинки
---
https://www.logicgamesonline.com/lightsout/
Можна погратись 
---

## 🔧 Що робить `openBox(y, x)`:
1. Зчитує поточний стан коробки (де які клітинки заблоковані)
2. Будує **велику формулу**, яка описує:
   > "Які клітинки потрібно натиснути, щоб усе стало false"
3. Передає цю формулу у функцію `gauss_mod2`
4. Отримує відповідь: які клітинки треба натиснути
5. Тисне ці клітинки
6. Перевіряє: якщо всі `false` — ✅ коробку відкрито

---

## 🔬 Що робить `gauss_mod2(...)`:
Це математична формула, яка працює в **бінарній системі** (`0` і `1`).

- Вона бере формулу з `openBox`
- І рахує, які клітинки треба натиснути
- Все працює на базі **методу Гауса**, але з операцією XOR замість звичайного ділення

> Тобто, вона як **розумний калькулятор**, який підбирає комбінацію кліків, щоб усе розблокувалось

//Література де брати цю всю інфу: 
---
https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
це єдина годна ссилка усе друге сміття 
---


## 🧪 Що вже зроблено:
---
- Працює на розмірах від `3x3` до `100x100`
- Всі тести проходять ✅
- Можна запускати через термінал або в CLion
- Працює дуже швидко: великі розміри — за мілісекунди
---
це мій тест
---
![image](https://github.com/user-attachments/assets/1ca4deb0-8c20-4b3b-8f6f-e8f37ddc935e)
---


### 📥 How to set and run (Linux/macOS):

```bash
# 1. Clone repository
git clone https://github.com/your-username/Lights-Out-Puzzle.git
cd Lights-Out-Puzzle

# 2. We create a directory for assembly
mkdir build
cd build

# 3. We generate make files
cmake ..

# 4. Compile
make

# 5. Run (eg 5x5 box) Options are sure to be so not work
./Lights_Out_Puzzle 5 5 
```

---

###  If you have Clion 
![image](https://github.com/user-attachments/assets/4f05a3c9-9dea-400e-bee1-6126eef27008)
---
### Press Clone Repository 
![image](https://github.com/user-attachments/assets/e7071670-303f-4f30-aeab-a5584f886f58)

### URL -> https://github.com/dinobunny/Lights-Out-Puzzle.git
---
### This should be and then press -> Clone
![image](https://github.com/user-attachments/assets/a76ce317-2c2e-4af0-bdcb-393611eb9c64)
---
### Goes tight and then press Trust Project
![image](https://github.com/user-attachments/assets/c445bf94-c04b-47cf-9458-a6b2af48252e)
---
### Get out of the project setting up, click OK
![image](https://github.com/user-attachments/assets/f7d893c2-ec30-4ce0-ab94-402f8940548e)
---
### We see this Ecran
![image](https://github.com/user-attachments/assets/712a7558-1669-4378-a41a-c20df4188936)
---
### Click on 3 dots -> Edit -> (we find and fit) Program Arguments: 5 5
![image](https://github.com/user-attachments/assets/16bb03aa-4724-4ac0-ad26-d8ce45c1250c)
---
### Aplay -> Ok 
![image](https://github.com/user-attachments/assets/d00e8bf2-bf42-408b-97c6-76c089a022b6)
---
RUN  
---

📤 Вивід:
```
BOX: OPENED!
```
або
```
BOX: LOCKED!
```
---
### 👤 Автор:
Євген Рафальський
💡 Ентузіаст, який подружився з XOR, розібрався в Гауссі, і навчився відкривати коробки... в коді 😄
"Bitwise problems need bitwise minds."
