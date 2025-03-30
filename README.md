
# 🔦 Lights-Out-Puzzle

An implementation of the classic "Lights Out" puzzle using C++ and Gaussian elimination in GF(2).

---

## 🧩 About

You are given a locked grid (SecureBox) with lights (on/off).  
The goal is to find the sequence of button presses that will turn off all the lights.

Each button toggles:
- Its entire **row**
- Its entire **column**  
*(excluding the center cell, which gets toggled 3 times → stays the same)*

---

## 🧠 How It Works

The puzzle is modeled as a linear system of equations:

```
A * x = b   (mod 2)
```

- `A` — matrix of influences (which button affects which light)
- `b` — current state of the grid (1 = on, 0 = off)
- `x` — solution vector: which buttons to press

The system is solved using **Gaussian elimination in GF(2)**.

---

## 🗂 File Structure

```
Lights-Out-Puzzle/
├── main.cpp              # Entry point
├── OpenBox.h / .cpp      # Matrix solver and system builder
├── SecureBox.h           # Logic of the toggle box
├── openbox_test.cpp      # Unit tests using GoogleTest
├── CMakeLists.txt        # CMake project file
└── README.md             # Project description
```

---
You will see the initial state and a list of button presses to solve the puzzle.

---

## ✅ Features

- Clean matrix-based logic
- Fast and reliable solver
- Modular codebase (divided by logic and UI)
- Fully covered with unit tests
- Solves any N x N size grid


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
