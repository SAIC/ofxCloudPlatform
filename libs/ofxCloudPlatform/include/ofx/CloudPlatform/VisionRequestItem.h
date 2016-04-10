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


#include "ofImage.h"


namespace ofx {
namespace CloudPlatform {


/// \brief A class representing a single request item.
///
/// Vision requests can consist of multiple individual requests items.
class VisionRequestItem
{
public:
    class Feature
    {
    public:
        /// \brief Image analysis features.
        enum class Type
        {
            /// \brief An unsepecified feature type.
            TYPE_UNSPECIFIED,

            /// \brief Execute Image Content Analysis on the entire image and return.
            LABEL_DETECTION,

            /// \brief 	Perform Optical Character Recognition (OCR) on text within the image.
            TEXT_DETECTION,

            /// \brief Detect faces within the image.
            FACE_DETECTION,

            /// \brief Detect geographic landmarks within the image.
            LANDMARK_DETECTION,

            /// \brief Detect company logos within the image.
            LOGO_DETECTION,

            /// \brief Determine image safe search properties on the image.
            SAFE_SEARCH_DETECTION,

            /// \brief Compute a set of properties about the image.
            ///
            /// These properties include things such as the image's dominant colors.
            IMAGE_PROPERTIES
        };

        enum
        {
            /// \brief The default number of maximum results.
            DEFAULT_MAX_RESULTS = 10
        };

        /// \brief Create a Feature with parameters.
        /// \param type The feature type to create.
        /// \param maxResults The maximum results to request.
        Feature(Type type = Type::IMAGE_PROPERTIES,
                std::size_t maxResults = DEFAULT_MAX_RESULTS);

        /// \returns the JSON representation.
        const ofJson& json() const;

        /// \brief A list of all the feature types and their strings for convenience.
        static const std::map<Type, std::string> TYPE_STRINGS;

    private:
        /// \brief The internal JSON.
        ofJson _json;

    };

    /// \brief Construct an empty request.
    VisionRequestItem();

    /// \brief Construct a request with parameters.
    /// \param pixels The pixels to set (encodes pixels with defaults).
    /// \param features The feature map to request.
    VisionRequestItem(const ofPixels& pixels,
                      const std::vector<Feature>& features = DEFAULT_FEATURES);

    /// \brief Construct a request with parameters.
    /// \param pixels The pixels to set.
    /// \param format The image format to encode.
    /// \param quality The compression quality.
    /// \param features The feature map to request.
    VisionRequestItem(const ofPixels& pixels,
                      ofImageFormat format,
                      ofImageQualityType quality,
                      const std::vector<Feature>& features = DEFAULT_FEATURES);

    /// \brief Construct a request with parameters.
    /// \param uri Can be file path or a Google Storage URI (e.g. gs://...).
    /// \param features The feature map to request.
    VisionRequestItem(const std::string& uri,
                      const std::vector<Feature>& features = DEFAULT_FEATURES);

    /// \brief Construct a request with parameters.
    /// \param buffer The buffered encoded image data.
    /// \param features The feature map to request.
    VisionRequestItem(const ofBuffer& buffer,
                      const std::vector<Feature>& features = DEFAULT_FEATURES);

    /// \brief Destroy the VisionRequestItem.
    ~VisionRequestItem();

    /// \brief Set the image from an image file.
    ///
    /// Setting the image in this way will remove any existing images set
    /// from a cloud storage URI.
    ///
    /// \param pixels The image pixels to send.
    /// \param format The image format to encode.
    /// \param quality The compression quality.
    void setImage(const ofPixels& pixels,
                  ofImageFormat format = OF_IMAGE_FORMAT_JPEG,
                  ofImageQualityType quality = OF_IMAGE_QUALITY_MEDIUM);

    /// \brief Set the image from an image file.
    /// \param uri Can be file path or a Google Storage URI (e.g. gs://...).
    void setImage(const std::string& uri);

    /// \brief Set the image from buffer.
    /// \param buffer The buffered encoded image data.
    void setImage(const ofBuffer& buffer);

    /// \brief Add a feature to this request.
    /// \param feature The feature to request.
    void addFeature(const Feature& feature);

    /// \brief Set the features for this request item.
    /// \param features The features to request.
    void setFeatures(const std::vector<Feature>& features);

    /// \brief Request all features with this request.
    /// \param maxResults The maximum result to be applied to all features.
    void addAllFeatures();

    /// \brief Set the coordinate bounds context.
    ///
    /// This is the Latitude / Longitude rectangle that specifies the location
    /// of the image.
    ///
    /// The values must conform to the WGS84 standard and be within normalized
    /// ranges.
    ///
    /// \param minLatitude The minimum latitude in normalized degrees.
    /// \param minLongitude The minimum longitude in normalized degrees.
    /// \param maxLatitude The maximum latitude in normalized degrees.
    /// \param maxLongitude The maximum longitude in normalized degrees.
    void setLatitudeLongitudeBounds(double minLatitude,
                                    double minLongitude,
                                    double maxLatitude,
                                    double maxLongitude);

    /// \brief A list of ISO639-1 codes languages to use for TEXT_DETECTION.
    /// \param languages The ISO639-1 language codes to add.
    /// \sa https://cloud.google.com/translate/v2/using_rest#language-params
    void setLanguageHints(const std::vector<std::string>& languages);

    /// \brief A ISO639-1 codes for languages to use for TEXT_DETECTION.
    /// \param language The ISO639-1 language code to add.
    /// \sa https://cloud.google.com/translate/v2/using_rest#language-params
    void addLanguageHint(const std::string& language);

    /// \returns the JSON representation.
    const ofJson& json() const;

    /// \brief The defaut features.
    static const std::vector<Feature> DEFAULT_FEATURES;

private:
    /// \brief The json data.
    ofJson _json;

};



} } // namespace ofx::CloudPlatform
