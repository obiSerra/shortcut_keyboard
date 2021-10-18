#include <Keyboard.h>

using namespace std;

typedef struct
{
  int pin;
  String keyName;
  uint8_t lastRead;
} button;

button buttons[12] = {
    {4, "Button1", HIGH},
    {3, "Button2", HIGH},
    {2, "Button3", HIGH},
    {15, "Button4", HIGH},
    {5, "Button5", HIGH},
    {6, "Button6", HIGH},
    {7, "Button7", HIGH},
    {8, "Button8", HIGH},
    {9, "Button9", HIGH},
    {10, "Button10", HIGH},
    {16, "Button11", HIGH},
    {14, "Button12", HIGH},
};

uint8_t lastReads[12] = {};

void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void openApp(String appName)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  Keyboard.releaseAll();

  delay(400);

  Keyboard.print(appName);

  delay(300);

  typeKey(KEY_RETURN);

  delay(300);
}

//https://www.arduino.cc/en/Reference/KeyboardModifiers

void missionControl()
{
  Keyboard.press(KEY_F3);
  Keyboard.releaseAll();
}

void dittoStackOpen()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('v');
  Keyboard.releaseAll();
}

void vsCodeBeauty()
{
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('f');
  Keyboard.releaseAll();
}

void vsCodeSave()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('s');
  Keyboard.releaseAll();
}

void leftDesktop()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
}

void rightDesktop()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.releaseAll();
}

void hideApplication()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('m');
  Keyboard.releaseAll();
}

void spectacleFullScreen()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('f');
  Keyboard.releaseAll();
}

void spectacleCenterScreen()
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('c');
  Keyboard.releaseAll();
}

void spectacleLeftScreen()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_ARROW);

  Keyboard.releaseAll();
}

void spectacleRightScreen()
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_RIGHT_ARROW);

  Keyboard.releaseAll();
}

void setup()
{

  Serial.begin(9600); // open the serial port at 9600 bps:
  Keyboard.begin();
  for (int i = 0; i < 12; i++)
  {
    button btn = buttons[i];
    int pin = btn.pin;
    pinMode(pin, INPUT_PULLUP);
    lastReads[i] = digitalRead(pin);
  }
}

void loop()
{

  for (int i = 0; i < 12; i++)
  {
    button btn = buttons[i];
    int pin = btn.pin;
    uint8_t currentRead = digitalRead(pin);
    if (currentRead == LOW && lastReads[i] == HIGH)
    {

      if (btn.keyName == "Button1")
      {
        vsCodeBeauty();
      }
      else if (btn.keyName == "Button2")
      {
        vsCodeSave();
      }
      else if (btn.keyName == "Button3")
      {
        dittoStackOpen();
      }
      else if (btn.keyName == "Button4")
      {
        missionControl();
      }
      else if (btn.keyName == "Button6")
      {
        spectacleFullScreen();
      }
      else if (btn.keyName == "Button5")
      {
        spectacleLeftScreen();
      }
      else if (btn.keyName == "Button8")
      {
        spectacleRightScreen();
      }
      else if (btn.keyName == "Button7")
      {
        //hideApplication();
        spectacleCenterScreen();
      }
      else if (btn.keyName == "Button9")
      {
        leftDesktop();
      }
      else if (btn.keyName == "Button12")
      {
        rightDesktop();
      }

      Serial.println("PRESSED " + btn.keyName);
    }

    lastReads[i] = currentRead;
  }
}
