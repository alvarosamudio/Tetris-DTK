# Tetris-DTK 🎮

![Qt Badge](https://img.shields.io/badge/Qt-5.15+-41CD52?logo=qt&logoColor=white)
![Deepin Badge](https://img.shields.io/badge/Deepin-DTK-0078D7?logo=linux&logoColor=white)
![License](https://img.shields.io/badge/License-GPLv3-blue.svg)

Una implementación nativa y moderna del clásico **Tetris** construida específicamente para el ecosistema **Deepin Linux** utilizando **DTK (Deepin Tool Kit)** y C++/Qt.

Este proyecto ha sido reconstruido desde cero para abandonar el antiguo motor web (wrapper) y ofrecer una experiencia de juego ligera, fluida y perfectamente integrada con la estética de Deepin.

## ✨ Características

- **Motor Nativo:** Desarrollado íntegramente en C++ con Qt para un rendimiento óptimo.
- **Integración DTK:** Utiliza `DMainWindow`, `DTitlebar` y widgets nativos de Deepin para una apariencia premium.
- **Ligero:** Sin dependencias de motores web pesados (QtWebEngine eliminado).
- **Control Fluido:** Respuesta inmediata al teclado para una experiencia de juego clásica.
- **Soporte de Tema:** Compatible con el modo oscuro y claro de Deepin.

## 🛠️ Requisitos de Compilación

Para compilar este proyecto en Deepin o cualquier sistema con soporte DTK, necesitarás:

- `qtbase5-dev`
- `dtkwidget-dev`
- `qt5-default` (o equivalente)
- `pkg-config`

## 🚀 Instalación y Compilación

1. **Clona el repositorio:**

   ```bash
   git clone https://github.com/alvarosamudio/Tetris-DTK.git
   cd Tetris-DTK
   ```

2. **Genera el Makefile con qmake:**

   ```bash
   qmake
   ```

3. **Compila el proyecto:**

   ```bash
   make
   ```

4. **Ejecuta el juego:**
   ```bash
   ./Tetris
   ```

## 🎮 Controles

| Tecla     | Acción                               |
| :-------- | :----------------------------------- |
| `←` / `→` | Mover pieza a la izquierda / derecha |
| `↑`       | Rotar pieza                          |
| `↓`       | Caída suave                          |
| `Espacio` | Caída instantánea (Hard Drop)        |
| `P`       | Pausar / Reanudar el juego           |

## 🤝 Créditos

- Desarrollo original impulsado por la comunidad de **Deepin en Español**.
- Reconstrucción nativa diseñada para **Deepin Latin Code**.

---

_Hecho con ❤️ para la comunidad de Deepin._

## 📄 Licencia

Este proyecto está bajo la licencia **GNU General Public License v3.0**. Consulta el archivo [LICENSE](file:///Users/ghost/Documents/Proyectos/GitHub/Tetris-DTK/LICENSE) para más detalles.
