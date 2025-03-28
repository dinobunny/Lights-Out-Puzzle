## 📦 Lights-Out-Puzzle Solver

Solution "SecureBox" - opening a closed container (2D Boolean Grid) only with the help of a public API: `toggle`,` ISLOCKED ', `Getstate'.

---

### 🔧 Requirements to connect this program

- C++17 
- CMake ≥ (VERSION 3.30)
- Git
- G++ or Clang (на Linux/macOS)
- MinGW or MSVC (на Windows)
- (Optional) CLion / VSCode / Another editor

---

### The logic of my program
---
First -> creates a box with dimensions Y × x, for example, 3 × 3 = 9 cells.
---
Then -> count how many cells (for example, 9). 
--- 
Next-> Select all possible combinations of clicks on these cells (2^9 = 512 options). 
---
at every step-> a copy of the box is created to work with it without touching the original. 
---
Check-> What cells should be pressed according to the current combination (mask). 
---
If in the mask 1-> click on the appropriate cell (switch it and the entire row and column). 
---
After all the clicks-> check whether the box has become fully unlocked (all False cells). 
---
If yes-> return False-that is, the box opened. 
---
If no combination worked-> return True-the box failed to open. 
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
### 🤝 Author:
> Євген Рафальський — ентузіаст, який не боїться XOR-ів, рекурсій і стекових оверфлоу 😄 (😄😄😄😄😄не дуже впевнено😄😄😄😄😄😄)
---
