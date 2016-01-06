# InteractiveMusicPlayground
<br>
HSV Raum in 4 Farbbereiche aufteilen (Eventuell Hautfarbenähnlich ausgeschlossen), jeder Farbbereich bekommt eine Art von Sound zugewiesen<br>
Aus Input-Image Binärbilder für jeden Farbbereich machen <br>
Mit FindContours folgende Formen erkennen: Dreieck, Viereck, Fünfeck, Sechseck <br>
Das ergibt 4 * 4 (16) Audiotracks <br>
Dazu: Halterung für Kamera -> Richtige Höhe, für verschiedene Kameras<br>
In Action: Live-Verschieben: Hand so gut wie möglich ignorieren, Bausteine mit weißem Rand, damit man die Kanten nicht überdeckt<br>
Falls Hand mitten im Bild -> Invalider State, dann wird der letzte Valid State benutzt, bis es wieder einen validen State gibt<br>
