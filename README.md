
# 🚀 TypeRush

A terminal-based **Typing Speed Test** game built in **C++**. TypeRush displays a paragraph in chunks, tracks your typing speed, and calculates accuracy in real-time. Great for improving typing skills or just having some fun with friends!

---

## 📂 Project Structure

```

TYPERUSH/
│
├── .vscode/               # VSCode settings (optional)
│   ├── settings.json
│   └── tasks.json
│
├── src/                   # Main source files
│   ├── main.cpp           # Core logic for the typing game
│   └── main.exe           # Compiled executable (Windows)
│
├── testParagraphs/
│   └── paragraphs.txt     # Preloaded typing passages
│
├── .gitignore             # Ignored files and folders
├── .gitattributes         # Git line-ending configs
└── README.md              # Project documentation

````

---

## 💡 Features

- ✅ Clean terminal interface
- ✍️ Displays paragraph in **scrolling chunks** for better readability
- ⏱️ Measures **typing speed (WPM)** and **accuracy**
- 🧠 Tracks **total characters**, **correct/incorrect keystrokes**
- 🔁 Compare your performance after every test
- 🔗 Easy to expand with custom paragraphs

---

## ⚙️ How to Run

### 💻 Compile

Use g++ or any C++ compiler:

```bash
g++ src/main.cpp -o typerush
````

### ▶️ Run

```bash
./typerush
```

Or on Windows:

```cmd
main.exe
```

---

## 📝 Input Paragraphs

Typing text is loaded from:
`testParagraphs/paragraphs.txt`

* Each paragraph is split into chunks and displayed sequentially.
* You can customize or add your own paragraphs in the file.

---

## 🧠 How It Works

1. A random paragraph is selected.
2. Text is shown **chunk-by-chunk** for better visual flow.
3. The user types, and the app:

   * Tracks each keystroke
   * Compares typed vs expected character
   * Calculates speed and error count
4. Final stats like **WPM**, **accuracy**, and **mistakes** are displayed.

---
🧠 Sample Output
```
Typing Test - Chunk Mode Activated
💡 Type each chunk. Timer starts on first key press. You have 100 seconds.

🧩 Chunk 1/50:
The train station was unusually quiet that morning. A thin layer of mist floated
...

==============================
📝 TYPING TEST RESULTS 📝
==============================
📄 Characters typed     : 233
🎯 Target characters     : 3997
✅ Accuracy              : 81.1%
🚀 Gross WPM (standard) : 28.0
🧠 Net WPM (accuracy)   : 22.7
```
---

## 📌 Dependencies

* Standard C++ libraries only.
* No external dependencies required.

---

## 📦 Future Improvements

* [ ] Add a GUI version (using Qt or SFML)

---

## 🤝 Contributing

1. Fork this repo 🍴
2. Make your changes 🔧
3. Submit a pull request 🚀


---
