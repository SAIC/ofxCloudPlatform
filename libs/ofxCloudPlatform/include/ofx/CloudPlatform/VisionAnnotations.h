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


#include "json.hpp"
#include "ofColor.h"
#include "ofPolyline.h"


namespace ofx {
namespace CloudPlatform {


class ImageAnnotation
{
public:

    /// \brief A bucketized representation of likelihood.
    ///
    /// Meant to give highly stable results across model upgrades.
    enum class Likelihood
    {
        UNKNOWN, ///< Unknown likelihood.
        VERY_UNLIKELY, ///< The image very unlikely belongs to the vertical specified.
        UNLIKELY, ///< The image unlikely belongs to the vertical specified.
        POSSIBLE, ///< The image possibly belongs to the vertical specified.
        LIKELY, ///< The image likely belongs to the vertical specified.
        VERY_LIKELY ///< The image very likely belongs to the vertical specified.
    };

    static const std::map<Likelihood, std::string> LIKELIHOOD_STRINGS;
    static const std::map<std::string, Likelihood> STRINGS_LIKELIHOOD;
    static const std::map<Likelihood, float> LIKELIHOOD_VALUES;

    ImageAnnotation(const ofJson& json);

    virtual ~ImageAnnotation();

    bool isLoaded() const;

    const ofJson& json() const;
    
private:
    ofJson _json;

};


/// \sa https://cloud.google.com/vision/reference/rest/v1/images/annotate#EntityAnnotation
class EntityAnnotation: public ImageAnnotation
{
public:
    using ImageAnnotation::ImageAnnotation;

    virtual ~EntityAnnotation();

    /// \brief Knowledge Graph entity ID.
    ///
    /// Maps to a freebase entity ID. (for example, "Google" maps to:
    /// mid /m/045c7b).
    ///
    /// \returns the mid.
    std::string mid() const;

    /// \brief Description locale.
    ///
    /// The language code for the locale in which the entity textual
    /// description is expressed.
    ///
    /// \returns the locale.
    std::string locale() const;

    /// \returns the entity textual description, expressed in its locale language.
    std::string description() const;

    /// \returns the overall score of the result. Range [0, 1].
    float score() const;

    /// \brief The accuracy of the entity detection in an image.
    ///
    /// For example, for an image containing 'Eiffel Tower,' this field
    /// represents the confidence that there is a tower in the query image.
    /// Range [0, 1].
    ///
    /// \returns the accuracy of the entity detection in an image.
    float confidence() const;

    /// \brief The relevancy of the ICA (Image Content Annotation) label to the image.
    ///
    /// For example, the relevancy of 'tower' to an image containing
    /// 'Eiffel Tower' is likely higher than an image containing a distant
    /// towering building, though the confidence that there is a tower may be
    /// the same. Range [0, 1].
    ///
    /// \returns the relevancy of the Image Content Annotation.
    float topicality() const;

    /// \brief Image region to which this entity belongs.
    ///
    /// Not filled currently for LABEL_DETECTION features. For TEXT_DETECTION
    /// (OCR), boundingPolys are produced for the entire text detected in an
    /// image region, followed by boundingPolys for each word within the
    /// detected text.
    ///
    /// \returns the image region to which this entity belongs.
    ofPolyline boundingPoly() const;

    /// \brief The location information for the detected entity.
    ///
    /// Multiple location elements can be present since one location may
    /// indicate the location of the scene in the query image, and another the
    /// location of the place where the query image was taken. Location
    /// information is usually present for landmarks.
    ///
    /// \returns a set of latitude / longitude pairs.
    std::vector<std::pair<double, double>> locations();

    /// \brief Some entities can have additional optional Property fields.
    ///
    /// For example a different kind of score or string that qualifies the entity.
    ///
    /// \returns additional name/value properties.
    std::unordered_map<std::string, std::string> properties();


};


class FaceAnnotation: public ImageAnnotation
{
public:
    class Landmark
    {
    public:
        /// \brief Face landmark (feature) type.
        ///
        /// Left and right are defined from the vantage of the viewer of the
        /// image, without considering mirror projections typical of photos. So,
        /// LEFT_EYE, typically is the person's right eye.
        enum class Type
        {
            UNKNOWN_LANDMARK, ///< Unknown face landmark detected. Should not be filled.
            LEFT_EYE, ///< Left eye.
            RIGHT_EYE, ///< Right eye.
            LEFT_OF_LEFT_EYEBROW, ///< Left of left eyebrow.
            RIGHT_OF_LEFT_EYEBROW, ///< Right of left eyebrow.
            LEFT_OF_RIGHT_EYEBROW, ///< Left of right eyebrow.
            RIGHT_OF_RIGHT_EYEBROW, ///< Right of right eyebrow.
            MIDPOINT_BETWEEN_EYES, ///< Midpoint between eyes.
            NOSE_TIP, ///< Nose tip.
            UPPER_LIP, ///< Upper lip.
            LOWER_LIP, ///< Lower lip.
            MOUTH_LEFT, ///< Mouth left.
            MOUTH_RIGHT, ///< Mouth right.
            MOUTH_CENTER, ///< Mouth center.
            NOSE_BOTTOM_RIGHT, ///< Nose, bottom right.
            NOSE_BOTTOM_LEFT, ///< Nose, bottom left.
            NOSE_BOTTOM_CENTER, ///< Nose, bottom center.
            LEFT_EYE_TOP_BOUNDARY, ///< Left eye, top boundary.
            LEFT_EYE_RIGHT_CORNER, ///< Left eye, right corner.
            LEFT_EYE_BOTTOM_BOUNDARY, ///< Left eye, bottom boundary.
            LEFT_EYE_LEFT_CORNER, ///< Left eye, left corner.
            RIGHT_EYE_TOP_BOUNDARY, ///< Right eye, top boundary.
            RIGHT_EYE_RIGHT_CORNER, ///< Right eye, right corner.
            RIGHT_EYE_BOTTOM_BOUNDARY, ///< Right eye, bottom boundary.
            RIGHT_EYE_LEFT_CORNER, ///< Right eye, left corner.
            LEFT_EYEBROW_UPPER_MIDPOINT, ///< Left eyebrow, upper midpoint.
            RIGHT_EYEBROW_UPPER_MIDPOINT, ///< Right eyebrow, upper midpoint.
            LEFT_EAR_TRAGION, ///< Left ear tragion.
            RIGHT_EAR_TRAGION, ///< Right ear tragion.
            LEFT_EYE_PUPIL, ///< Left eye pupil.
            RIGHT_EYE_PUPIL, ///< Right eye pupil.
            FOREHEAD_GLABELLA, ///< Forehead glabella.
            CHIN_GNATHION, ///< Chin gnathion.
            CHIN_LEFT_GONION, ///< Chin left gonion.
            CHIN_RIGHT_GONION ///< Chin right gonion.
        };

        static const std::map<Type, std::string> LANDMARK_TYPE_STRINGS;
        static const std::map<std::string, Type> STRINGS_LANDMARK_TYPE;
        static const std::map<Type, std::string> LANDMARK_TYPE_DESCRIPTIONS;


        Landmark(const ofJson& json):
            _type(STRINGS_LANDMARK_TYPE.find(json["type"])->second),
            _position(json["position"]["x"],
                      json["position"]["y"],
                      json["position"]["z"])
        {
        }

        Type type() const
        {
            return _type;
        }

        ofVec3f position() const
        {
            return _position;
        }

    private:
        Type _type = Type::UNKNOWN_LANDMARK;
        ofVec3f _position;

    };

    using ImageAnnotation::ImageAnnotation;

    virtual ~FaceAnnotation();

    /// \brief The bounding polygon around the face.
    ///
    /// The coordinates of the bounding box are in the original image's scale,
    /// as returned in ImageParams. The bounding box is computed to "frame" the
    /// face in accordance with human expectations. It is based on the
    /// landmarker results. Note that one or more x and/or y coordinates may not
    /// be generated in the BoundingPoly (the polygon will be unbounded) if only
    /// a partial face appears in the image to be annotated.
    ///
    /// \returns the bounding poly.
    ofPolyline boundingPoly() const;

    /// \brief The face's bounding polygon based on initial face detection.
    ///
    /// This bounding polygon is tighter than the previous boundingPoly, and
    /// encloses only the skin part of the face. Typically, it is used to
    /// eliminate the face from any image analysis that detects the "amount of
    /// skin" visible in an image. It is not based on the landmarker results,
    /// only on the initial face detection, hence the fd (face detection)
    /// prefix.
    ///
    /// \returns the fb bounding poly.
    ofPolyline fdBoundingPoly() const;

    /// \returns the detected face landmarks.
    std::vector<Landmark> landmarks() const;

    /// \brief Roll angle.
    ///
    /// Indicates the amount of clockwise/anti-clockwise rotation of the face
    /// relative to the image vertical, about the axis perpendicular to the
    /// face. Range [-180,180].
    ///
    /// \returns the roll angle
    float rollAngle() const;

    /// \brief Yaw angle.
    ///
    /// Indicates the leftward/rightward angle that the face is pointing,
    /// relative to the vertical plane perpendicular to the image. Range
    /// [-180,180].
    ///
    /// \returns the yaw angle.
    float panAngle() const;

    /// \brief Pitch angle.
    ///
    /// Indicates the upwards/downwards angle that the face is pointing relative
    /// to the image's horizontal plane. Range [-180,180].
    ///
    /// \returns the tilt angle.
    float tiltAngle() const;

    /// \returns the detection confidence. Range [0, 1].
    float detectionConfidence() const;

    /// \returns the face landmarking confidence. Range [0, 1].
    float landmarkingConfidence() const;

    /// \returns Joy likelihood.
    Likelihood joyLikelihood() const;

    /// \returns Sorrow likelihood.
    Likelihood sorrowLikelihood() const;

    /// \returns Anger likelihood.
    Likelihood angerLikelihood() const;

    /// \returns Surprise likelihood.
    Likelihood surpriseLikelihood() const;

    /// \returns Under-exposed likelihood.
    Likelihood underExposedLikelihood() const;

    /// \returns Blurred likelihood.
    Likelihood blurredLikelihood() const;

    /// \returns Headwear likelihood.
    Likelihood headwearLikelihood() const;
};


class LandmarkAnnotation: public EntityAnnotation
{
public:
    using EntityAnnotation::EntityAnnotation;

    virtual ~LandmarkAnnotation();

};


class LogoAnnotation: public EntityAnnotation
{
public:
    using EntityAnnotation::EntityAnnotation;

    virtual ~LogoAnnotation();

};



class LabelAnnotation: public EntityAnnotation
{
public:
    using EntityAnnotation::EntityAnnotation;

    virtual ~LabelAnnotation();

};


class TextAnnotation: public EntityAnnotation
{
public:
    using EntityAnnotation::EntityAnnotation;

    virtual ~TextAnnotation();
    
};


class SafeSearchAnnotation: public ImageAnnotation
{
public:
    using ImageAnnotation::ImageAnnotation;

    virtual ~SafeSearchAnnotation();

    /// \brief Represents the adult contents likelihood for the image.
    /// \returns the Likelihood.
    Likelihood adult() const;

    /// \brief A spoofed image.
    ///
    /// The likelihood that an obvious modification was made to the image's
    /// canonical version to make it appear funny or offensive.
    ///
    /// \returns the Likelihood.
    Likelihood spoof() const;

    /// \brief Likelihood this is a medical image.
    /// \returns the Likelihood.
    Likelihood medical() const;

    /// \brief Violence likelihood.
    /// \returns the Likelihood.
    Likelihood violence() const;

};


class ImagePropertiesAnnotation: public ImageAnnotation
{
public:
    struct ColorInfo
    {
        ofColor color;
        float score;
        float pixelFraction;
    };

    using ImageAnnotation::ImageAnnotation;

    virtual ~ImagePropertiesAnnotation();

    std::vector<ColorInfo> colors() const;
};


} } // namespace ofx::CloudPlatform
