# ArdClicker ✋🔴
Arduino Clicker tilraunarforrit til þess að geta notað einn takka til að keyra mismunandi skipanir á Arduino borði, búið til fyrir einfalda jólaseríu sem ég var að gera fyrir fjölskylduna, ég tók eftir því að það var ekki til kóði neinstaðar sem innihélt basic grunninn að því að nota takka sem multifucntional á Arduino bretti.

## Version 1.0
Notast við einfalt *state change*[^2] til þess að athuga hvort það sé búið að ýta á takkan eða ekki, þetta var gert í staðinn fyrir að nota lykkju til þess að athuga uppfærslur á takkanum (Hi, Lo state), bætti við *Debounce Delay* sem kemur í veg fyrir að borðið lesi noise eða of stutt button press.[^1] 

- Telur upp af 5 og fer aftur að 0
- Prentar út hvaða skipun þú ert á í *Serial Monitor*


[^1]: Debouncing [Arduino útskýring](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce)
[^2]: StateChange [Arduino útskýring](https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection)

### Void setup
```
int buttonState = 0;

int lastButtonState = 0;

int buttonPushCounter = 0;

void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}
``` 
