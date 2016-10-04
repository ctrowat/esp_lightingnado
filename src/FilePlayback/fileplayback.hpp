#ifndef FILE_PLAYBACK_H
#define FILE_PLAYBACK_H

#include <NeoPixelBus.h>
#include "LightMode.hpp"

class FilePlayback: public LightMode {
public:
  FilePlayback(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip, char* data);
  ~FilePlayback();
  void update(char* data);
  void tick();
  char* description();
private:
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
  int delayDuration = 10;
  void processData(char* data);
  const char* name = "File Playback";
};

#endif
