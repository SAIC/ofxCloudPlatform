//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "json.hpp"
#include "ofColor.h"
#include "ofPolyline.h"
#include "ofLog.h"
#include "ofx/CloudPlatform/VisionAnnotations.h"
#include "ofx/CloudPlatform/VisionResponse.h"


namespace ofx {
namespace CloudPlatform {


class VisionDeserializer
{
public:
    static bool fromJSON(const ofJson& json, ofPolyline& polyline);
    static bool fromJSON(const ofJson& json, ofVec2f& position);
    static bool fromJSON(const ofJson& json, ofVec3f& position);
    static bool fromJSON(const ofJson& json, ofColor& color);
private:
    VisionDeserializer() = delete;
    ~VisionDeserializer() = delete;
    
};




} } // namespace ofx::CloudPlatform
