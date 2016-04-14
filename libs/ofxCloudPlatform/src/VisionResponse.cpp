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
        else ofLogWarning("VisionResponse::bufferStream") << "Unknown key: " << key;

        ++iter;
    }

    return annotation;
}


VisionResponse::~VisionResponse()
{
}


std::vector<AnnotateImageResponse> VisionResponse::responses() const
{
    return _responses;
}


std::vector<AnnotateImageResponse> VisionResponse::fromJSON(const ofJson& json)
{
    std::vector<AnnotateImageResponse> responses;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "responses")
        {
            for (const auto& response: value)
            {
                responses.push_back(AnnotateImageResponse::fromJSON(response));
            }
        }
        else ofLogWarning("VisionResponse::bufferStream") << "Unknown key: " << key;

        ++iter;
    }

    return responses;;
}



void VisionResponse::parseBuffer()
{
    ofJson json;

    try
    {
        json = ofJson::parse(HTTP::BufferedResponse<VisionRequest>::getBuffer());
        parseJSON(json);
    }
    catch (const std::exception& exc)
    {
        ofLogError("VisionResponse::parseBuffer") << "Unable to interpret data as json: " << exc.what();
    }

}

void VisionResponse::parseJSON(const ofJson& json)
{
    _responses = fromJSON(json);
}


} } // namespace ofx::CloudPlatform
