# Interactive Music Playground

![Interactive Music Playground](http://i.imgur.com/3tiTlWm.jpg)

Der **Interactive Music Playground** ist eine C++ Applikation, die mit *openCV* farbige Bausteine erkennt und dann zu den Bausteinen entsprechende Audiotracks abspielt. Verschieben der Bausteine (**Music Chips**) im Raum sorgt für die Anwendung verschiedene Soundeffekte auf den Audiotrack, wie Hoch-/Tiefpassfilter und Delay. 

![I(nteractive) M(usic) P(playground)](http://i.imgur.com/SAWqXL1.jpg)

Der Interactive Music Playground ist so konzipiert, dass jeder mit einer Kamera und einem Rechner ihn selbst nachbauen kann. Alles, was er dazu machen muss, ist, sich farbige Bausteine selbst zu bauen (z.B. auszudrucken oder aus Moosgummi oder Holz zu basteln). Perspektivisch soll die Applikation auf dem Smartphone laufen und die interne Kamera nutzen, um noch zugänglicher zu sein.

![Music Chips](http://imgur.com/qIg811W.jpg)

Es handelt sich um mit dem *Qt-Framework* erstellte Projekte. Die Projektstruktur ist so aufgebaut, dass sie aus zwei Unterprojekten besteht: Dem **Hauptprojekt** (InteractiveMusicPlayground) und einem **Unit-Test** Projekt.

![User Interface (Stand 10.01.2016)](http://i.imgur.com/P2lzNca.png)

Da es sich beim Interactive Music Playground um eine **Tangible Sound Control** handelt, ist das GUI hauptsächlich zur Konfiguration gedacht. Zunächst kann man mit **Start Camera** den Kamera-Input starten. Dann kann man für jeden Farbraum (Insgesamt sind 5 Farbräume eingestellt, die auf die Farben ROT, GELB, GRÜN, BLAU und LILA voreingstellt sind) im Bereich **Color Configuration** die Werte anpassen. Es handelt sich um Werte im *HSV-Farbraum*. Zusätzlich dazu kann man im Bereich **Detection Configuration** weitere Parameter einstellen, um die Erkennung zu optimieren. Dazu gehört die Mindestgröße für Music Chips, die Detection Tolerance in Frames, die dafür sorgt, dass kurze Aussetzer in der Erkennung keinen Einfluss haben, und die Position Changed Tolerance, die dafür sorgt, dass Kamerawackeln/Rauschen von wenigen Pixeln nicht dazu führt, dass die Effektstärken für einzelne Music Chips neu berechnet werden. Im Bereich **Morphology** können außerdem ein Median Blur, Opening und Closing Effekt eingestellt werden, die zur Verbesserung der Erkennung führen können (Achtung bzw. der Laufzeit). Im Bereich **Audio Configuration** kann der Path zu den Audiodateien angegeben werden. Wichtig: Qt ermöglicht auch auf Windows den Forward-Slash zur Path-Angabe. Da dieser deutlich weniger Probleme verursacht, bitte auch auf Windows diesen verwenden.

Sind alle Image Processing Einstellungen getroffen, kann mit **Start Audio** das Abspielen des Sounds starten. Der Interactive Music Playground ist so konzipiert, dass jeder Music Chip einem kleinen, geloopten Audiosample entspricht. So kann ein MusicChip z.B. einem Bass oder einem Schlagzeug entsprechen. Nun können beliebig Music Chips in die Kamerafläche gelegt werden, und es kann *interaktiv* **DJ** gespielt werden. Zur Laufzeitoptimierung kann der Videooutput mittels Checkbox **Disable Video Output** gestoppt werden.

![UML IMP](http://i.imgur.com/WSB9sD8.png)
Hier eine vereinfachte Darstellung der Projektstruktur als **UML-Diagramm**. (Erstellt mit www.draw.io)
