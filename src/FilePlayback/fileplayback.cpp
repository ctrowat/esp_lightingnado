#include "fileplayback.hpp"
#include <ArduinoJson.h>

FilePlayback::FilePlayback(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip, char* data) {
  this->strip = strip;
  this->processData(data);
}

void FilePlayback::update(char* data) {
  this->processData(data);
}

void FilePlayback::tick() {
  this->strip->Show();
  this->strip->RotateRight(1);
  delay(this->delayDuration);
}

char* FilePlayback::description() {
  char* description = (char*) malloc(strlen(this->name));
  sprintf(description, "%s", this->name);
  return description;
}

void FilePlayback::processData(char* data) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);

  if (root.containsKey("delay")) {
    this->delayDuration = root["delay"];
  }

  if (root.containsKey("right")) {
    //this->directionRight = root["right"];
  }

  if (this->delayDuration < 1) {
    this->delayDuration = 1;
  }

  int colorCount = root["colors"].size();
  RgbColor colors[colorCount];
  for(int i=0; i<colorCount; i++) {
    colors[i] = RgbColor(root["colors"][i][0], root["colors"][i][1], root["colors"][i][2]);
  }

  for(int i=0; i<this->strip->PixelCount(); i++) {
    this->strip->SetPixelColor(i, colors[i % colorCount]);
  }
}

FilePlayback::~FilePlayback() {
}
