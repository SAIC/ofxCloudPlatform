//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/VisionResponse.h"


namespace ofx {
namespace CloudPlatform {


AnnotateImageResponse::AnnotateImageResponse()
{
}


AnnotateImageResponse::~AnnotateImageResponse()
{
}


const std::vector<FaceAnnotation>& AnnotateImageResponse::faceAnnotations() const
{
    return _faceAnnotations;
}


const std::vector<EntityAnnotation>& AnnotateImageResponse::landmarkAnnotations() const
{
    return _landmarkAnnotations;
}


const std::vector<EntityAnnotation>& AnnotateImageResponse::logoAnnotations() const
{
    return _logoAnnotations;
}


const std::vector<EntityAnnotation>& AnnotateImageResponse::labelAnnotations() const
{
    return _labelAnnotations;
}


const std::vector<EntityAnnotation>& AnnotateImageResponse::textAnnotations() const
{
    return _textAnnotations;
}


const SafeSearchAnnotation& AnnotateImageResponse::safeSearchAnnotation() const
{
    return _safeSearchAnnotation;
}


const ImagePropertiesAnnotation& AnnotateImageResponse::imagePropertiesAnnotation() const
{
    return _imagePropertiesAnnotation;
}

    
const CropHintsAnnotation& AnnotateImageResponse::cropHintsAnnotation() const
{
    return _cropHintsAnnotation;
}
    

AnnotateImageResponse AnnotateImageResponse::fromJSON(const ofJson& json)
{
    AnnotateImageResponse annotation;
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "faceAnnotations")
        {
            for (const auto& _annotation: value)
                annotation._faceAnnotations.push_back(FaceAnnotation::fromJSON(_annotation));
        }
        else if (key == "landmarkAnnotations")
        {
            for (const auto& _annotation: value)
                annotation._landmarkAnnotations.push_back(EntityAnnotation::fromJSON(_annotation));
        }
        else if (key == "logoAnnotations")
        {
            for (const auto& _annotation: value)
                annotation._logoAnnotations.push_back(EntityAnnotation::fromJSON(_annotation));
        }
        else if (key == "labelAnnotations")
        {
            for (const auto& _annotation: value)
                annotation._labelAnnotations.push_back(EntityAnnotation::fromJSON(_annotation));
        }
        else if (key == "textAnnotations")
        {
            for (const auto& _annotation: value)
                annotation._textAnnotations.push_back(EntityAnnotation::fromJSON(_annotation));
        }
        else if (key == "safeSearchAnnotation")
        {
            annotation._safeSearchAnnotation = SafeSearchAnnotation::fromJSON(value);
        }
        else if (key == "imagePropertiesAnnotation")
        {
            annotation._imagePropertiesAnnotation = ImagePropertiesAnnotation::fromJSON(value);
        }
        else if (key == "cropHintsAnnotation")
        {
            annotation._cropHintsAnnotation = CropHintsAnnotation::fromJSON(value);
        }
        else ofLogWarning("AnnotateImageResponse::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return annotation;
}


} } // namespace ofx::CloudPlatform
