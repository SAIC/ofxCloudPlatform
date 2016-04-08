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


#include "ofx/CloudVision/VisionRequestItem.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/Base64Encoding.h"


namespace ofx {
namespace CloudVision {


const std::map<RequestItem::Feature::Type, std::string> RequestItem::Feature::TYPE_STRINGS =
{
    { Type::LABEL_DETECTION, "LABEL_DETECTION" },
    { Type::TEXT_DETECTION, "TEXT_DETECTION" },
    { Type::FACE_DETECTION, "FACE_DETECTION" },
    { Type::LANDMARK_DETECTION, "LANDMARK_DETECTION" },
    { Type::LOGO_DETECTION, "LOGO_DETECTION" },
    { Type::SAFE_SEARCH_DETECTION, "SAFE_SEARCH_DETECTION" },
    { Type::IMAGE_PROPERTIES, "IMAGE_PROPERTIES" }
};


RequestItem::Feature::Feature(Type type, std::size_t maxResults)
{
    _json["type"] = TYPE_STRINGS.find(type)->second;
    _json["maxResults"] = maxResults;
}


const ofJson& RequestItem::Feature::json() const
{
    return _json;
}


const std::vector<RequestItem::Feature> RequestItem::DEFAULT_FEATURES =
{
    Feature(Feature::Type::IMAGE_PROPERTIES)
};


RequestItem::RequestItem()
{
}
    

RequestItem::RequestItem(const ofPixels& pixels,
                         const std::vector<Feature>& features):

    RequestItem(pixels,
                OF_IMAGE_FORMAT_JPEG,
                OF_IMAGE_QUALITY_MEDIUM,
                features)
{
}


RequestItem::RequestItem(const ofPixels& pixels,
                         ofImageFormat format,
                         ofImageQualityType quality,
                         const std::vector<Feature>& features)
{
    setImage(pixels, format, quality);
    setFeatures(features);
}


RequestItem::RequestItem(const std::string& uri,
                         const std::vector<Feature>& features)
{
    setImage(uri);
    setFeatures(features);
}


RequestItem::RequestItem(const ofBuffer& buffer,
                         const std::vector<Feature>& features)
{
    setImage(buffer);
    setFeatures(features);
}


RequestItem::~RequestItem()
{
}


void RequestItem::setImage(const ofPixels& pixels,
                           ofImageFormat format,
                           ofImageQualityType quality)
{
    ofBuffer buffer;
    ofSaveImage(pixels, buffer, format, quality);
    setImage(buffer);
}


void RequestItem::setImage(const std::string& uri)
{
    if (uri.substr(0, 5).compare("gs://") == 0)
    {
        _json["image"].clear();
        _json["image"]["source"]["gcs_image_uri"] = uri;
    }
    else
    {
        setImage(ofBufferFromFile(uri));
    }
}


void RequestItem::setImage(const ofBuffer& buffer)
{
    _json["image"].clear();
    _json["image"]["content"] = IO::Base64Encoding::encode(IO::ByteBuffer(buffer));
}


void RequestItem::addFeature(const Feature& feature)
{
    _json["features"].push_back(feature.json());
}


void RequestItem::setFeatures(const std::vector<Feature>& features)
{
    _json["features"].clear();

    for (auto& feature: features)
    {
        addFeature(feature);
    }
}


void RequestItem::addAllFeatures()
{
    std::vector<Feature> features;

    for (auto& feature: Feature::TYPE_STRINGS)
    {
        features.push_back(Feature(feature.first));
    }

    setFeatures(features);
}


void RequestItem::setLatitudeLongitudeBounds(double minLatitude,
                                             double minLongitude,
                                             double maxLatitude,
                                             double maxLongitude)
{
    _json["imageContext"]["latLongRect"] = {
        "minLatLng", {
            { "latitude", minLatitude },
            { "longitude", minLongitude }
        },
        "maxLatLng", {
            { "latitude", maxLatitude },
            { "longitude", maxLongitude }
        }
    };
}

void RequestItem::setLanguageHints(const std::vector<std::string>& languages)
{
    _json["imageContext"]["languageHints"].clear();

    for (auto& language: languages)
    {
        addLanguageHint(language);
    }
}


void RequestItem::addLanguageHint(const std::string& language)
{
    _json["imageContext"]["languageHints"].push_back(language);
}


const ofJson& RequestItem::json() const
{
    return _json;
}


} } // namespace ofx::CloudPlatform
