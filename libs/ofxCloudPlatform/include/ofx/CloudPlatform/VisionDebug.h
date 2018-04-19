//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/CloudPlatform/VisionAnnotations.h"
#include "ofx/CloudPlatform/VisionResponse.h"


namespace ofx {
namespace CloudPlatform {


/// \brief Utilities for drawing Annotations.
class VisionDebug
{
public:
    static void draw(const std::string& label,
                     float value,
                     float x = 0,
                     float y = 0,
                     float width = 300,
                     float height = 20);

    static void draw(const std::string& label,
                     const Likelihood& likelihood,
                     float x = 0,
                     float y = 0,
                     float width = 300,
                     float height = 20);

    static void draw(const FaceAnnotation::Landmark& landmark);

    static void draw(const FaceAnnotation& annotation);
    static void draw(const EntityAnnotation& annotation);
    static void draw(const SafeSearchAnnotation& annotation);
    static void draw(const ImagePropertiesAnnotation& annotation);
    static void draw(const std::vector<FaceAnnotation>& annotations);
    static void draw(const std::vector<EntityAnnotation>& annotations);
    static void draw(const AnnotateImageResponse& response);
private:
    VisionDebug() = delete;
    ~VisionDebug() = delete;
};



} } // namespace ofx::CloudPlatform
