# Snake
This is the classical Snake game written in C++. However, I implemented all core features (key event handling, multithreading, animation, ...) without relying on external libraries.

https://github.com/user-attachments/assets/ed295655-8404-49a6-bcb3-24dd25c6675d

## How to play?

## Installation
**NOTE: Currently only Windows is supported. TUTORIAL is not yet available <br>
        There may be display issues with Windows 11. A workaround is to deliberately loose the game (by hitting the wall) and choose **TRY AGAIN****.
1. Navigate to **/prebuilt** folder
2. Download **game.exe** file
3. Run **game.exe**

## Controls
1. Use either **W/A/S/D** or **Up/Down/Left/Right Arrows** to control the Snake.
2. Use **Space** to pause/resume the game. *Upon stat, the game is in **PAUSED** state*

## Project Architect
There are 4 main components in the project: **Game Model**, **Game Renderer**, **Key Handler** and **Snake**. Each of them is initialised in a separate thread 
<img width="631" height="625" alt="image" src="https://github.com/user-attachments/assets/f7295707-cfea-4e54-85b5-a0e183782fd4" />

### Game Model
This component controls states of the game (current score, GAME OVER, PAUSED, PLAYING, …) using a simple state machine
<img width="730" height="577" alt="image" src="https://github.com/user-attachments/assets/6e099fa0-5f91-4908-9c8d-fc9211fe0cea" />
<br>It also maintains a 2D array that represents the game area, including walls, snake segments, and food. Each element type is assigned a predefined constant value, allowing the **Game Renderer** to display the scene accurately.
<img width="490" height="819" alt="image" src="https://github.com/user-attachments/assets/98cfea4a-875f-4b94-8817-2972f89c308e" />

Last but not least, this component is responsible for delivering key eventsto corresponding components based on the current game state.

### Game Renderer
Displays game objects based on data from the 2D array in **Game Model**.
<img width="937" height="653" alt="image" src="https://github.com/user-attachments/assets/a255daa7-d121-4cb8-b531-6ab19cbba3eb" />

### Key Handler
Maintains a hashmap that maps each received key to a corresponding function pointer, enabling dynamic invocation of the appropriate handler.

<img width="468" height="381" alt="image" src="https://github.com/user-attachments/assets/804cc0eb-5606-40b8-8d28-270764faa648" />

Key handlers are registered in **main()**

<img width="536" height="486" alt="image" src="https://github.com/user-attachments/assets/85a72aa2-caaf-429a-a4cf-9d4d19771b22" />

### Snake
Tracks the positions of all snake segments and updates them based on received key events (up, right, down, left). After each update, it notifies the Game Model with the new segment positions.

<img width="630" height="419" alt="image" src="https://github.com/user-attachments/assets/6e256098-bf6a-41e1-ac67-d50cdb5eee1f" />



