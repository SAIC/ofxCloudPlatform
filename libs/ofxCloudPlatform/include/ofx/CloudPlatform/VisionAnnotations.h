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


namespace ofx {
namespace CloudPlatform {


/// \brief A bucketized representation of likelihood.
///
/// Meant to give highly stable results across model upgrades.
class Likelihood
{
public:
    /// \brief Likelihood types.
    enum class Type
    {
        UNKNOWN, ///< Unknown likelihood.
        VERY_UNLIKELY, ///< The image very unlikely belongs to the vertical specified.
        UNLIKELY, ///< The image unlikely belongs to the vertical specified.
        POSSIBLE, ///< The image possibly belongs to the vertical specified.
        LIKELY, ///< The image likely belongs to the vertical specified.
        VERY_LIKELY ///< The image very likely belongs to the vertical specified.
    };

    /// \brief Create an unknown Likelihood.
    Likelihood();

    /// \brief Create a Likelihood with the given Type.
    Likelihood(Type type);

    /// \brief Destroy the given Likelihood.
    ~Likelihood();

    /// \returns the Likelihood type.
    Type type() const;

    /// \returns the Likelihood name.
    std::string name() const;

    /// \returns the Likelihood value (0-1);
    float value() const;

    /// \brief Map Likelihood Types to strings.
    static const std::map<Type, std::string> LIKELIHOOD_STRINGS;

    /// \brief Map strings to Likelihood Types.
    static const std::map<std::string, Type> STRINGS_LIKELIHOOD;

    /// \brief Map Likelihood Type to normalized values.
    static const std::map<Type, float> LIKELIHOOD_VALUES;

    /// \brief Create an instance from a string.
    /// \param text The text to use.
    /// \returns an instance of the object.
    static Likelihood fromString(const std::string& text);

private:
    /// \brief The Likelihood Type.
    Type _type = Type::UNKNOWN;

    /// \brief The Likelihood name string.
    std::string _name;

    /// \brief The Likelihood noramlized value.
    float _value = 0.0f;

};


/// \brief Set of detected entity features.
/// \sa https://cloud.google.com/vision/reference/rest/v1/images/annotate#EntityAnnotation
class EntityAnnotation
{
public:
    /// \brief Create a default EntityAnnotation;
    EntityAnnotation();

    /// \brief Destroy the EntityAnnotation.
    ~EntityAnnotation();

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
    std::unordered_multimap<std::string, std::string> properties();

    /// \brief Create an instance from JSON.
    /// \param json The JSON to use.
    /// \returns an instance of the object.
    static EntityAnnotation fromJSON(const ofJson& json);

private:
    std::string _mid;
    std::string _locale;
    std::string _description;
    float _score = 0.0f;
    float _confidence = 0.0f;
    float _topicality = 0.0f;
    ofPolyline _boundingPoly;
    std::vector<std::pair<double, double>> _locations;
    std::unordered_multimap<std::string, std::string> _properties;

};


/// \brief A face annotation object contains the results of face detection.
class FaceAnnotation
{
public:
    // \brief A face landmark.
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


        Landmark();
        Landmark(Type type, const ofVec3f& position);
        Type type() const;
        std::string name() const;
        ofVec3f position() const;

        /// \brief Create an instance from JSON.
        /// \param json The JSON to use.
        /// \returns an instance of the object.
        static Landmark fromJSON(const ofJson& json);

        static const std::map<Type, std::size_t> LANDMARK_TYPE_INDEX;
        static const std::map<std::size_t, Type> INDEX_LANDMARK_TYPE;
        static const std::map<Type, std::string> LANDMARK_TYPE_STRINGS;
        static const std::map<std::string, Type> STRINGS_LANDMARK_TYPE;
        static const std::map<Type, std::string> LANDMARK_TYPE_DESCRIPTIONS;
    private:
        Type _type = Type::UNKNOWN_LANDMARK;
        std::string _name;
        ofVec3f _position;

    };

    /// \brief Create a default FaceAnnotation.
    FaceAnnotation();

    /// \brief Destroy the FaceAnnotation.
    ~FaceAnnotation();

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

    /// \brief Create an instance from JSON.
    /// \param json The JSON to use.
    /// \returns an instance of the object.
    static FaceAnnotation fromJSON(const ofJson& json);

private:
    /// \sa boundingPoly()
    ofPolyline _boundingPoly;

    /// \sa fdBoundingPoly()
    ofPolyline _fdBoundingPoly;

    /// \sa landmarks()
    std::vector<Landmark> _landmarks;

    /// \sa rollAngle()
    float _rollAngle;

    /// \sa panAngle()
    float _panAngle;

    /// \sa tiltAngle()
    float _tiltAngle;

    /// \sa detectionConfidence()
    float _detectionConfidence;

    /// \sa landmarkingConfidence()
    float _landmarkingConfidence;

    /// \brief Joy likelihood.
    Likelihood _joyLikelihood;

    /// \brief Sorrow likelihood.
    Likelihood _sorrowLikelihood;

    /// \brief Anger likelihood.
    Likelihood _angerLikelihood;

    /// \brief Surprise likelihood.
    Likelihood _surpriseLikelihood;

    /// \brief Under-exposed likelihood.
    Likelihood _underExposedLikelihood;

    /// \brief Blurred likelihood.
    Likelihood _blurredLikelihood;

    /// \brief Headwear likelihood.
    Likelihood _headwearLikelihood;

};


/// \brief Set of features pertaining to the image, computed by various computer vision methods over safe-search verticals (for example, adult, spoof, medical, violence).
/// \sa https://cloud.google.com/vision/reference/rest/v1/images/annotate#SafeSearchAnnotation
class SafeSearchAnnotation
{
public:
    /// \brief Create a default SafeSearchAnnotation.
    SafeSearchAnnotation();

    /// \brief Destroy the SafeSearchAnnotation.
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

    /// \brief Create an instance from JSON.
    /// \param json The JSON to use.
    /// \returns an instance of the object.
    static SafeSearchAnnotation fromJSON(const ofJson& json);

private:
    /// \brief Represents the adult contents likelihood for the image.
    Likelihood _adult;

    /// \brief A spoofed image.
    Likelihood _spoof;

    /// \brief Likelihood this is a medical image.
    Likelihood _medical;

    /// \brief Violence likelihood.
    Likelihood _violence;

};


/// \brief Color information consists of RGB channels, score and fraction of image the color occupies in the image.
class ColorInfo
{
public:
    /// \brief Create a default ColorInfo.
    ColorInfo();

    /// \brief Destroy the ColorInfo.
    ~ColorInfo();

    /// \returns the RGB components of the color.
    ofColor color() const;

    /// \returns the image-specific score for this color. Value in range [0, 1].
    float score() const;

    /// \returns the fraction of pixels the color occupies in the image. Value in range [0, 1].
    float pixelFraction() const;

    /// \brief Create an instance from JSON.
    /// \param json The JSON to use.
    /// \returns an instance of the object.
    static ColorInfo fromJSON(const ofJson& json);

private:
    /// \brief RGB components of the color.
    ofColor _color;

    /// \brief Image-specific score for this color. Value in range [0, 1].
    float _score = 0.0f;

    /// \brief Stores the fraction of pixels the color occupies in the image. Value in range [0, 1].
    float _pixelFraction = 0.0f;

};


/// \brief Stores image properties (e.g. dominant colors).
/// \sa https://cloud.google.com/vision/reference/rest/v1/images/annotate#ImageProperties
class ImagePropertiesAnnotation
{
public:
    /// \brief Create a default ImagePropertiesAnnotation.
    ImagePropertiesAnnotation();

    /// \brief Destroy the ImagePropertiesAnnotation.
    virtual ~ImagePropertiesAnnotation();

    /// \returns the of dominant colors and their corresponding scores.
    std::vector<ColorInfo> dominantColors() const;

    /// \brief Create an instance from JSON.
    /// \param json The JSON to use.
    /// \returns an instance of the object.
    static ImagePropertiesAnnotation fromJSON(const ofJson& json);

private:
    /// \brief dominant colors and their corresponding scores.
    std::vector<ColorInfo> _dominantColors;

};


} } // namespace ofx::CloudPlatform
