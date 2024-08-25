- Link to task: https://www.uni-muenster.de/AISystems/courses/CPP/site/html/sections/final_task/final_task.html

- Compile and run the Code on the WSL Kernel (Linux Subsystem on Windows) for easier library linking.
  For help: https://code.visualstudio.com/docs/remote/wsl

Anforderungen:
- Raumschiff über Tastatureingabe (oder andere Eingabemethoden?) bewegen
- Schüsse abfeuern, Aliens zerstören und dafür Punkte erhalten
- Aliens schießen gelegentlich zurück, Lebensabzug wenn man getroffen wird
- Bewegungsmuster Aliens (zum Rand, eine Zeile tiefer, in die andere Richtung)
- Level vorbei wenn alle Aliens getroffen wurden, neues Level mit höherer Geschwindigkeit und Häufigkeit der Alien-Schüsse
- Spiel beendet, wenn Aliens den Spieler erreichen oder der Spieler keine Leben mehr hat
Model:
- Methoden beschreiben als Kommentar und 3 Testfälle (pro Methode?)
- PowerUp
View:
- Spielstand, anzeigen und Ausgabe sobald das Level gelöst ist
- ncurses nutzen, Programm auf dem Jupyterhub testen
Control:
- Spezielle Kommandos übergeben (allgemeine Aufrufe, die das Raumschiff bewegen), nicht die aufgerufene Taste übergeben
- Alternative Control-Möglichkeit überlegen, sodass dieses auch umgesetzt wird (z.B. Steuerung über Trackpad)
- Diese abstrakten Controll-Komandos einführen -> Tastatursteuerung implementieren -> Alternative Umsetzung als Kommentar oder Implementierung
- Automatischer Controller, welcher das Level löst und per Tastaturbefehl aktiviert werden kann
Abgabe:
- zip Datei mit allen notwendigen Dateien inklusive README
- Beschreibung zur Kompilierung, Ausführung und zum Ablauf in der README
- Programm auf dem Hub testen! Einsatz von KI in der README angeben, Promts angeben? Abgabe 31.08.2024
