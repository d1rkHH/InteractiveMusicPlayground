# InteractiveMusicPlayground
Projektstruktur: <br>
Entweder: <br>
OPENCV249 + VS2013 + Qt (MediaSystems/avprg/ColorKeyer als Grundlage) <br>
Oder: <br>
OPENCV243 + VS2010 + Qt (MS_IMP Projekt als Grundlage) <br>
<br>
HSV Raum in 4-6 Farbbereiche aufteilen (Eventuell Hautfarbenähnlich ausgeschlossen), jeder Farbbereich bekommt eine Art von Sound zugewiesen<br>
Aus Input-Image Binärbilder für jeden Farbbereich machen <br>
Mit FindContours folgende Formen erkennen: Kreis, Qudarat, Dreick, Sechseck <br>
Das ergibt 4 * 4 bis 4 * 6 verschiedene Audiotracks (16 - 24) <br>
Theoretische Möglichkeit, Soundprofile zu wechseln z.B. durch sehr große, spezielle Bausteine <br>
Für jeden Baustein eine Binärmatrix <br>
Mittelpunkt berechnen (Center of Mass) <br>
4 fest definierte Effektbausteine an den 4 Seiten des Playgrounds (Position height/2, 0; 0, width/2 etc.) -> Abstand berechnen -> Faktor <br>
Dieser Faktor wird an die Audioverarbeitungsfunktion übergeben und bestimmt, wie stark der Effekt auf den Audiotrack angewandt wird <br>
Die Audiotracks liegen als .wav im Projekt enthalten <br>
Für jeden erkannten Baustein wird der entsprechende Audiotrack als Binärstrom geladen, und es wird der Effekt je nach Abstand auf den Binärstrom angewandt <br>
Der Binärstrom wird dann als AudioOutput abgespielt <br>
Außerdem: Fehlervermeidung -> Hand nicht erkennen, bei kurzen Bildaussetzern/Lag einfach letztes valides Signal weiter abgspielen, keine Aussetzer <br>
Außerdem: Playground-Erkennung: Ganzes Kamerabild vs. DIN A4?<br>
Außerdem: Laufzeitoptimierung -> Was schlägt auf die Laufzeit, Multithreading? Auflösung der Kamera? 1080p 720p 480p?<br>
Dazu: Halterung für Kamera -> Richtige Höhe, für verschiedene Kameras<br>
Dazu: Playground DIN A4 mit vorgedruckten Effektbausteinen/GUI<br>
In Action: Live-Verschieben: Hand so gut wie möglich ignorieren, Bausteine mit weißem Rand, damit man die Kanten nicht überdeckt<br>
Falls Hand mitten im Bild -> Invalider State, dann wird der letzte Valid State benutzt, bis es wieder einen validen State gibt<br>
