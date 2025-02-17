#pragma once

#include <glm/glm.hpp>

//#include "data/BlockMapLoader2.hh"
#include "opengl/MultiShape2D.hh"
#include "opengl/MultiText.hh"
#include "maps/MapNames.hh"
#include "util/BLHashMap.hh"

class BlockMapLoader;
class MapViewer;
class Style;
class MapView2D : public Shape {
 private:
  uint32_t startSegment;
  uint32_t endSegment;

  uint32_t startLineIndex; // used to draw only some of the edges
  uint32_t endLineIndex;   // set in initOutline

  uint32_t vaoFill;
  uint32_t vboFill;

  uint32_t startFillIndex; // used to fill only some of the polygons (start)
  uint32_t endFillIndex;   // used to fill only some of the polygons (end) set in initFill


  const Style* style;
  float textScale;
  //float centerX, centerY, shiftX, shiftY, scaleX, scaleY;
  //glm::mat4 originalTransform;
  //glm::mat4 transform;
  // pointer to map loader object has advantage of opaqueness in header file
  // and we can have a null map and draw nothing, and change maps
  BlockMapLoader* bml;
  BLHashMap<MapEntry>* bdl;
  uint32_t numLineIndicesToDraw;
  uint32_t numFillIndicesToDraw;
  MultiText* mt;

 public:
  MapView2D(MapViewer* parent, const Style* s, MultiText* mt,
   BlockMapLoader* bml = nullptr, BLHashMap<MapEntry>* bdl = nullptr, float textScale = 1);
  ~MapView2D();
  MapView2D(const MapView2D& orig) = delete;
  MapView2D& operator= (const MapView2D& orig) = delete;
  void init() override;
  void initOutline(); // draw outlines of the map borders
  void initLabels(); // draw text labels for counties
  void initFill();    // draw solid color outlines using (eventually) data to colorize


  void render(glm::mat4& trans) override;
  void renderOutline(glm::mat4& trans);
  void renderLabels(glm::mat4& trans);
  void renderFill(glm::mat4& trans);

  void setTextScale(float textScale);
  void update() override;
  void dump();
  void displayAllSegments();
  void incSegment();
  void decSegment();
  void incNumSegments();
  void decNumSegments();
  void setWhichSegmentsToDisplay(uint32_t start, uint32_t end);
  void displayFirst();
};
