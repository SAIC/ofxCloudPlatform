//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/CloudPlatform/VisionAnnotations.h"
#include "ofx/CloudPlatform/VisionRequest.h"


namespace ofx {
namespace CloudPlatform {


class AnnotateImageResponse
{
public:
    AnnotateImageResponse();
    ~AnnotateImageResponse();

    const std::vector<FaceAnnotation>& faceAnnotations() const;
    const std::vector<EntityAnnotation>& landmarkAnnotations() const;
    const std::vector<EntityAnnotation>& logoAnnotations() const;
    const std::vector<EntityAnnotation>& labelAnnotations() const;
    const std::vector<EntityAnnotation>& textAnnotations() const;
    const SafeSearchAnnotation& safeSearchAnnotation() const;
    const ImagePropertiesAnnotation& imagePropertiesAnnotation() const;
    const CropHintsAnnotation& cropHintsAnnotation() const;

    /// \returns the raw json.
    ofJson json() const;

    static AnnotateImageResponse fromJSON(const ofJson& json);
private:
    std::vector<FaceAnnotation> _faceAnnotations;
    std::vector<EntityAnnotation> _landmarkAnnotations;
    std::vector<EntityAnnotation> _logoAnnotations;
    std::vector<EntityAnnotation> _labelAnnotations;
    std::vector<EntityAnnotation> _textAnnotations;
    SafeSearchAnnotation _safeSearchAnnotation;
    ImagePropertiesAnnotation _imagePropertiesAnnotation;
    CropHintsAnnotation _cropHintsAnnotation;

    /// \brief The raw json.
    ofJson _json;
};



} } // namespace ofx::CloudPlatform
