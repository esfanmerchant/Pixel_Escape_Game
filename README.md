# 🎮 Pixel Escape

Pixel Escape is a thrilling 2D platformer game built in **C++** using the **Raylib** graphics library. The game combines classic arcade-style mechanics with modern features like login & registration, monster battles, scoreboards, level selection, and smooth animations — all wrapped in a beginner-friendly C++ OOP codebase!

---

## 🧩 Game Features

- 🔐 **User Authentication** – Login & Register system to save progress.
- 🎮 **Multi-Level Gameplay** – Select from different levels via the Level Selector.
- 👾 **Monster Battles** – Dodge, defeat or escape from monsters on each level.
- ⭐ **Score & Lives** – Points system and limited lives to add challenge.
- 🗺️ **Background Animation** – Engaging animated backgrounds for each level.
- 💾 **Save Data** – User data is stored locally with high scores.

---

## 📸 Screenshots

> *(Add images here if available – gameplay, level selector, monster battle, etc.)*

---

## 🚀 Getting Started

### 🔧 Prerequisites

- C++ Compiler (e.g., g++, clang++)
- Raylib C++ Library
- Git (optional)

---

### 🛠️ Installing Raylib

#### 🔹 Windows (using MSYS2 – recommended)

1. Download and install [MSYS2](https://www.msys2.org/).
2. Open MSYS2 terminal and run:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-raylib
```
3. Add the path to mingw64/bin in your environment variables.
#### 🔹 Linux

```bash
sudo apt update
sudo apt install build-essential
sudo apt install libraylib-dev
```

#### 🔹 macOS (with Homebrew)

```bash
brew install raylib
```

---

### 🧪 How to Run the Project
1. Clone this Repository

```bash
git clone https://github.com/your-username/pixel-escape.git
cd pixel-escape
```

2. Compile the Code

```bash
g++ main.cpp -o PixelEscape -lraylib -lopengl32 -lgdi32 -lwinmm
```

3. Run the Game

```bash
./PixelEscape
```

---

## 🧑‍💻 Developed By
- **Esfan Merchant** – GUI Developer & game logic contributor.
- **Ansh Kumar** – Backend Developer & Core logic Designer.
- **Hashir Vohra** – Graphic Designer & Handling Documentation & Presentation.

## ⭐ Future Improvements
Add sound effects and background music
Introduce new enemy types and boss fights
Power-ups and bonus collectibles
Improved UI using textures and spritesheets

## 📃 License
This project is for educational purposes and is licensed under the [MIT License](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository).

## 🤝 Contribute
Pull requests are welcome! For major changes, please open an issue first to discuss what you’d like to change.




