# mpu6050-driver
Driver voor de mpu6050 (comments in NL)

Voor gebruik van de driver #include "mpu6050-driver.hpp"

<h1>Hoofdfuncties</h1>

```
start();
```
Deze functie zal de mpu opstarten en controleren of er een verbinding is. De functie geeft een boolean terug. Als de connectie gelukt is dan zal het true teruggeven. Als de connectie mislukt is dan zal de functie false teruggeven.
Deze functie is goed te combineren met een if-statement zodat je zeker weet dat als je de mpu gebruikt, de connectie in ieder geval werkt.

```
read_gyro(); 
```
Dit zal de gyroscoop uitlezen en een sensordata teruggeven. Om te gebruiken moet er dus een variabele gemaakt moeten worden van het type </b>sensordata</b>. Hierna zijn de x, y en z waarden te gebruiken door bijvoorbeeld: variabelenaam.x te doen. Je zal dan de x waarde van de gyroscoop te zien krijgen in het format int16_t. Dit is een 16 bits integer waarde en zal dus tussen 0 en 65,536 zitten.
De gyroscoop geeft de waarde tussen de vorige stand terug en is dus handig voor de hoekverschillen.
De waarde in °/s kan berekent worden met de formule: ```waarde / 131 = ... °/s.```

```
read_acc(); 
```
Het gebruik van de functie is hetzelfde als <b>read_gyro()</b>. De accelerometer geeft de stand van de chip terug in de x, y en z. Hiermee kun je dus weten in welke hoek de chip staat. 
De g krachten kunnen berekent worden met de formule: ```waarde / 16384 = ... g```

```
read_temp(); 
```
Deze functie geeft een int16_t waarde terug dat de temperatuur representeert. 
De graden kunnen berekent worden door middel van de volgende formule: ```waarde / 340 + 36.53 = ... °/c```.

<h1>Configuratiefuncties</h1>

```
filter_gyro(int value);
```
Bij deze functie kan de gebruiker een low pass filter op de gyroscoop zetten. Dit gebeurt in de chip digitaal. Het filter zal ervoor zorgen dat de metingen minder erg zullen schokken. Het filter kun je instellen met waarden van 0 tot en met 6.

```
filter_acc(int value);
```
Het nut en gebruik van de functie is hetzelfde als die van de gyroscoop maar dan voor de accelerometer.
```
filter_temp(int value);
```
Het nut en gebruik van de functie is hetzelfde als die van de gyroscoop maar dan voor de temperatuursensor.
