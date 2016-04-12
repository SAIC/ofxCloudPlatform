// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
