//www.elegoo.com
//2016.12.08


int LED_ON = 1;
int LED_OFF = 0;
int PIN_LED = 5;
int PIN_BUTTON = 8;
int DELAY_TIME = 100;
int CHARA_S_FIRST = 0;
int CHARA_O = 1;
int CHARA_S_SECOND = 2;
int CHARA_BLANK = 3;
int characterPosition = CHARA_S_FIRST;
int switchStatus = 1;     //スイッチの状態。最初はLOWが入力されている
int ledStatus = LED_OFF;  //LEDの状態。最初は消灯している
int sosSignal = 0;
void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);  //8PINを受信用に設定、プルアップ抵抗付き
  pinMode(PIN_LED, OUTPUT);           //5PInを出力用に設定
}



void loop() {
  inputButton(DELAY_TIME);
  if (ledStatus == LED_ON) {
    sos();
  }
}
void initCharacter() {
  characterPosition = CHARA_S_FIRST;
  sosSignal = 0;
}
void sos() {
  if (characterPosition == CHARA_S_FIRST) {
    bool isSfinish = sCharacter();
    if (isSfinish) {
      sosSignal = 0;
      characterPosition = CHARA_O;
    }
    return;
  }
  if (characterPosition == CHARA_O) {
    bool isOfinish = oCharacter();
    if (isOfinish) {
      sosSignal = 0;
      characterPosition = CHARA_S_SECOND;
    }
    return;
  }
  if (characterPosition == CHARA_S_SECOND) {
    bool isSfinish = sCharacter();
    if (isSfinish) {
      sosSignal = 0;
      characterPosition = CHARA_BLANK;
    }
    return;
  }
  bool isBlankFinish = blankCharacter();
  if (isBlankFinish) {
    characterPosition = CHARA_S_FIRST;
    sosSignal = 0;
  }
}
bool blankCharacter() {
  if (sosSignal < 6) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else {
    return true;
  }
}
bool oCharacter() {
  if (sosSignal < 6) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 7) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 13) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 14) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 20) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 22) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else {
    return true;
  }
}



bool sCharacter() {
  if (sosSignal < 2) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 4) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 6) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 8) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 10) {
    digitalWrite(PIN_LED, HIGH);
    sosSignal = 1 + sosSignal;
    return false;
  } else if (sosSignal < 12) {
    digitalWrite(PIN_LED, LOW);
    sosSignal = 1 + sosSignal;
    return false;
  } else {
    return true;
  }
}



void inputButton(int delayTime) {
  if (digitalRead(PIN_BUTTON) != switchStatus && digitalRead(PIN_BUTTON) == 0) {  //スイッチの状態が変わった,かつスイッチが押されている状態
    if (ledStatus == LED_OFF) {
      ledStatus = LED_ON;
      initCharacter();
    } else if (ledStatus == LED_ON) {
      digitalWrite(PIN_LED, LOW);
      ledStatus = LED_OFF;
    }
  }
  switchStatus = digitalRead(PIN_BUTTON);  //8ピンの状態を変数に保存
  delay(delayTime);
}