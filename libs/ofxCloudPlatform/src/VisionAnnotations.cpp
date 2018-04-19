//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/VisionAnnotations.h"
#include "ofx/CloudPlatform/VisionDeserializer.h"


namespace ofx {
namespace CloudPlatform {


const std::map<Likelihood::Type, std::string> Likelihood::LIKELIHOOD_STRINGS =
{
    { Type::UNKNOWN, "UNKNOWN" },
    { Type::VERY_UNLIKELY, "VERY_UNLIKELY" },
    { Type::UNLIKELY, "UNLIKELY" },
    { Type::POSSIBLE, "POSSIBLE" },
    { Type::LIKELY, "LIKELY" },
    { Type::VERY_LIKELY, "VERY_LIKELY" }
};


const std::map<std::string, Likelihood::Type> Likelihood::STRINGS_LIKELIHOOD =
{
    { "UNKNOWN", Type::UNKNOWN },
    { "VERY_UNLIKELY", Type::VERY_UNLIKELY },
    { "UNLIKELY", Type::UNLIKELY,  },
    { "POSSIBLE", Type::POSSIBLE,  },
    { "LIKELY", Type::LIKELY,  },
    { "VERY_LIKELY", Type::VERY_LIKELY }
};


const std::map<Likelihood::Type, float> Likelihood::LIKELIHOOD_VALUES =
{
    { Type::UNKNOWN, 0.0 },
    { Type::VERY_UNLIKELY, 0.0 },
    { Type::UNLIKELY, 0.25 },
    { Type::POSSIBLE, 0.5 },
    { Type::LIKELY, 0.75 },
    { Type::VERY_LIKELY, 1.0 }
};


Likelihood::Likelihood(): Likelihood(Type::UNKNOWN)
{
}


Likelihood::Likelihood(Type type):
    _type(type),
    _value(LIKELIHOOD_VALUES.find(_type)->second),
    _name(LIKELIHOOD_STRINGS.find(_type)->second)
{
}


Likelihood::~Likelihood()
{
}


Likelihood::Type Likelihood::type() const
{
    return _type;
}


std::string Likelihood::name() const
{
    return _name;
}


float Likelihood::value() const
{
    return _value;
}


Likelihood Likelihood::fromString(const std::string& text)
{
    const auto& iter = STRINGS_LIKELIHOOD.find(text);

    if (iter != STRINGS_LIKELIHOOD.cend())
    {
        return Likelihood(iter->second);
    }
    else
    {
        ofLogWarning("Likelihood::fromString") << "Unknown Likelihood: " << text;
        return Likelihood(Type::UNKNOWN);
    }
}


EntityAnnotation::EntityAnnotation()
{
}


EntityAnnotation::~EntityAnnotation()
{
}


std::string EntityAnnotation::mid() const
{
    return _mid;
}


std::string EntityAnnotation::locale() const
{
    return _locale;
}


std::string EntityAnnotation::description() const
{
    return _description;
}


float EntityAnnotation::score() const
{
    return _score;
}


float EntityAnnotation::confidence() const
{
    return _confidence;
}


float EntityAnnotation::topicality() const
{
    return _topicality;
}


ofPolyline EntityAnnotation::boundingPoly() const
{
    return _boundingPoly;
}


std::vector<std::pair<double, double>> EntityAnnotation::locations()
{
    return _locations;
}


std::unordered_multimap<std::string, std::string> EntityAnnotation::properties()
{
    return _properties;
}


EntityAnnotation EntityAnnotation::fromJSON(const ofJson& json)
{
    EntityAnnotation annotation;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "mid") annotation._mid = value;
        else if (key == "locale") annotation._locale = value;
        else if (key == "description") annotation._description = value;
        else if (key == "score") annotation._score = value;
        else if (key == "confidence") annotation._score = value;
        else if (key == "topicality") annotation._topicality = value;
        else if (key == "boundingPoly") VisionDeserializer::fromJSON(value, annotation._boundingPoly);
        else if (key == "locations")
        {
            for (const auto& location: value)
            {
                double latitude = location["latLng"]["latitude"];
                double longitude = location["latLng"]["longitude"];
                annotation._locations.push_back(std::make_pair(latitude, longitude));
            }
        }
        else if (key == "properties")
        {
            for (const auto& nameValue: value)
            {
                annotation._properties.insert(std::make_pair<std::string, std::string>(nameValue["name"], nameValue["value"]));
            }
        }
        else ofLogWarning("EntityAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);

        ++iter;
    }

    return annotation;
}


FaceAnnotation::Landmark::Landmark()
{
}


FaceAnnotation::Landmark::Landmark(Type type, const glm::vec3& position):
    _type(type),
    _name(LANDMARK_TYPE_STRINGS.find(Landmark::Type::UNKNOWN_LANDMARK)->second),
    _position(position)
{
}
    

FaceAnnotation::Landmark::Type FaceAnnotation::Landmark::type() const
{
    return _type;
}


std::string FaceAnnotation::Landmark::name() const
{
    return _name;
}


glm::vec3 FaceAnnotation::Landmark::position() const
{
    return _position;
}


FaceAnnotation::Landmark FaceAnnotation::Landmark::fromJSON(const ofJson& json)
{
    FaceAnnotation::Landmark landmark;
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        if (key == "type")
        {
            const auto& iter = STRINGS_LANDMARK_TYPE.find(value);

            if (iter != STRINGS_LANDMARK_TYPE.cend())
            {
                landmark._type = iter->second;
                landmark._name = iter->first;
            }
            else
            {
                landmark._type = Landmark::Type::UNKNOWN_LANDMARK;
                landmark._name = LANDMARK_TYPE_STRINGS.find(Landmark::Type::UNKNOWN_LANDMARK)->second;
                ofLogWarning("FaceAnnotation::Landmark::fromJSON") << "Unknown Landmark Type: " << value;
            }
        }
        else if (key == "position") VisionDeserializer::fromJSON(value, landmark._position);
        else ofLogWarning("FaceAnnotation::Landmark::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }
    return landmark;
}


const std::map<FaceAnnotation::Landmark::Type, std::size_t> FaceAnnotation::Landmark::LANDMARK_TYPE_INDEX =
{
    { Type::UNKNOWN_LANDMARK, 0 },
    { Type::LEFT_EYE, 1 },
    { Type::RIGHT_EYE, 2 },
    { Type::LEFT_OF_LEFT_EYEBROW, 3 },
    { Type::RIGHT_OF_LEFT_EYEBROW, 4 },
    { Type::LEFT_OF_RIGHT_EYEBROW, 5 },
    { Type::RIGHT_OF_RIGHT_EYEBROW, 6 },
    { Type::MIDPOINT_BETWEEN_EYES, 7 },
    { Type::NOSE_TIP, 8 },
    { Type::UPPER_LIP, 9 },
    { Type::LOWER_LIP, 10 },
    { Type::MOUTH_LEFT, 11 },
    { Type::MOUTH_RIGHT, 12 },
    { Type::MOUTH_CENTER, 13 },
    { Type::NOSE_BOTTOM_RIGHT, 14 },
    { Type::NOSE_BOTTOM_LEFT, 15 },
    { Type::NOSE_BOTTOM_CENTER, 16 },
    { Type::LEFT_EYE_TOP_BOUNDARY, 17 },
    { Type::LEFT_EYE_RIGHT_CORNER, 18 },
    { Type::LEFT_EYE_BOTTOM_BOUNDARY, 19 },
    { Type::LEFT_EYE_LEFT_CORNER, 20 },
    { Type::RIGHT_EYE_TOP_BOUNDARY, 21 },
    { Type::RIGHT_EYE_RIGHT_CORNER, 22 },
    { Type::RIGHT_EYE_BOTTOM_BOUNDARY, 23 },
    { Type::RIGHT_EYE_LEFT_CORNER, 24 },
    { Type::LEFT_EYEBROW_UPPER_MIDPOINT, 25 },
    { Type::RIGHT_EYEBROW_UPPER_MIDPOINT, 26 },
    { Type::LEFT_EAR_TRAGION, 27 },
    { Type::RIGHT_EAR_TRAGION, 28 },
    { Type::LEFT_EYE_PUPIL, 29 },
    { Type::RIGHT_EYE_PUPIL, 30 },
    { Type::FOREHEAD_GLABELLA, 31 },
    { Type::CHIN_GNATHION, 32 },
    { Type::CHIN_LEFT_GONION, 33 },
    { Type::CHIN_RIGHT_GONION, 34 }
};


const std::map<std::size_t, FaceAnnotation::Landmark::Type> FaceAnnotation::Landmark::INDEX_LANDMARK_TYPE =
{
    { 0, Type::UNKNOWN_LANDMARK },
    { 1, Type::LEFT_EYE },
    { 2, Type::RIGHT_EYE },
    { 3, Type::LEFT_OF_LEFT_EYEBROW },
    { 4, Type::RIGHT_OF_LEFT_EYEBROW },
    { 5, Type::LEFT_OF_RIGHT_EYEBROW },
    { 6, Type::RIGHT_OF_RIGHT_EYEBROW },
    { 7, Type::MIDPOINT_BETWEEN_EYES },
    { 8, Type::NOSE_TIP },
    { 9, Type::UPPER_LIP },
    { 10, Type::LOWER_LIP },
    { 11, Type::MOUTH_LEFT },
    { 12, Type::MOUTH_RIGHT },
    { 13, Type::MOUTH_CENTER },
    { 14, Type::NOSE_BOTTOM_RIGHT },
    { 15, Type::NOSE_BOTTOM_LEFT },
    { 16, Type::NOSE_BOTTOM_CENTER },
    { 17, Type::LEFT_EYE_TOP_BOUNDARY },
    { 18, Type::LEFT_EYE_RIGHT_CORNER },
    { 19, Type::LEFT_EYE_BOTTOM_BOUNDARY },
    { 20, Type::LEFT_EYE_LEFT_CORNER },
    { 21, Type::RIGHT_EYE_TOP_BOUNDARY },
    { 22, Type::RIGHT_EYE_RIGHT_CORNER },
    { 23, Type::RIGHT_EYE_BOTTOM_BOUNDARY },
    { 24, Type::RIGHT_EYE_LEFT_CORNER },
    { 25, Type::LEFT_EYEBROW_UPPER_MIDPOINT },
    { 26, Type::RIGHT_EYEBROW_UPPER_MIDPOINT },
    { 27, Type::LEFT_EAR_TRAGION },
    { 28, Type::RIGHT_EAR_TRAGION },
    { 29, Type::LEFT_EYE_PUPIL },
    { 30, Type::RIGHT_EYE_PUPIL },
    { 31, Type::FOREHEAD_GLABELLA },
    { 32, Type::CHIN_GNATHION },
    { 33, Type::CHIN_LEFT_GONION },
    { 34, Type::CHIN_RIGHT_GONION }
};


const std::map<std::string, FaceAnnotation::Landmark::Type> FaceAnnotation::Landmark::STRINGS_LANDMARK_TYPE =
{
    { "UNKNOWN_LANDMARK", Type::UNKNOWN_LANDMARK },
    { "LEFT_EYE", Type::LEFT_EYE },
    { "RIGHT_EYE", Type::RIGHT_EYE },
    { "LEFT_OF_LEFT_EYEBROW", Type::LEFT_OF_LEFT_EYEBROW },
    { "RIGHT_OF_LEFT_EYEBROW", Type::RIGHT_OF_LEFT_EYEBROW },
    { "LEFT_OF_RIGHT_EYEBROW", Type::LEFT_OF_RIGHT_EYEBROW },
    { "RIGHT_OF_RIGHT_EYEBROW", Type::RIGHT_OF_RIGHT_EYEBROW },
    { "MIDPOINT_BETWEEN_EYES", Type::MIDPOINT_BETWEEN_EYES },
    { "NOSE_TIP", Type::NOSE_TIP },
    { "UPPER_LIP", Type::UPPER_LIP },
    { "LOWER_LIP", Type::LOWER_LIP },
    { "MOUTH_LEFT", Type::MOUTH_LEFT },
    { "MOUTH_RIGHT", Type::MOUTH_RIGHT },
    { "MOUTH_CENTER", Type::MOUTH_CENTER },
    { "NOSE_BOTTOM_RIGHT", Type::NOSE_BOTTOM_RIGHT },
    { "NOSE_BOTTOM_LEFT", Type::NOSE_BOTTOM_LEFT },
    { "NOSE_BOTTOM_CENTER", Type::NOSE_BOTTOM_CENTER },
    { "LEFT_EYE_TOP_BOUNDARY", Type::LEFT_EYE_TOP_BOUNDARY },
    { "LEFT_EYE_RIGHT_CORNER", Type::LEFT_EYE_RIGHT_CORNER },
    { "LEFT_EYE_BOTTOM_BOUNDARY", Type::LEFT_EYE_BOTTOM_BOUNDARY },
    { "LEFT_EYE_LEFT_CORNER", Type::LEFT_EYE_LEFT_CORNER },
    { "RIGHT_EYE_TOP_BOUNDARY", Type::RIGHT_EYE_TOP_BOUNDARY },
    { "RIGHT_EYE_RIGHT_CORNER", Type::RIGHT_EYE_RIGHT_CORNER },
    { "RIGHT_EYE_BOTTOM_BOUNDARY", Type::RIGHT_EYE_BOTTOM_BOUNDARY },
    { "RIGHT_EYE_LEFT_CORNER", Type::RIGHT_EYE_LEFT_CORNER },
    { "LEFT_EYEBROW_UPPER_MIDPOINT", Type::LEFT_EYEBROW_UPPER_MIDPOINT },
    { "RIGHT_EYEBROW_UPPER_MIDPOINT", Type::RIGHT_EYEBROW_UPPER_MIDPOINT },
    { "LEFT_EAR_TRAGION", Type::LEFT_EAR_TRAGION },
    { "RIGHT_EAR_TRAGION", Type::RIGHT_EAR_TRAGION },
    { "LEFT_EYE_PUPIL", Type::LEFT_EYE_PUPIL },
    { "RIGHT_EYE_PUPIL", Type::RIGHT_EYE_PUPIL },
    { "FOREHEAD_GLABELLA", Type::FOREHEAD_GLABELLA },
    { "CHIN_GNATHION", Type::CHIN_GNATHION },
    { "CHIN_LEFT_GONION", Type::CHIN_LEFT_GONION },
    { "CHIN_RIGHT_GONION", Type::CHIN_RIGHT_GONION }
};


const std::map<FaceAnnotation::Landmark::Type, std::string> FaceAnnotation::Landmark::LANDMARK_TYPE_STRINGS =
{
    { Type::UNKNOWN_LANDMARK, "UNKNOWN_LANDMARK" },
    { Type::LEFT_EYE, "LEFT_EYE" },
    { Type::RIGHT_EYE, "RIGHT_EYE" },
    { Type::LEFT_OF_LEFT_EYEBROW, "LEFT_OF_LEFT_EYEBROW" },
    { Type::RIGHT_OF_LEFT_EYEBROW, "RIGHT_OF_LEFT_EYEBROW" },
    { Type::LEFT_OF_RIGHT_EYEBROW, "LEFT_OF_RIGHT_EYEBROW" },
    { Type::RIGHT_OF_RIGHT_EYEBROW, "RIGHT_OF_RIGHT_EYEBROW" },
    { Type::MIDPOINT_BETWEEN_EYES, "MIDPOINT_BETWEEN_EYES" },
    { Type::NOSE_TIP, "NOSE_TIP" },
    { Type::UPPER_LIP, "UPPER_LIP" },
    { Type::LOWER_LIP, "LOWER_LIP" },
    { Type::MOUTH_LEFT, "MOUTH_LEFT" },
    { Type::MOUTH_RIGHT, "MOUTH_RIGHT" },
    { Type::MOUTH_CENTER, "MOUTH_CENTER" },
    { Type::NOSE_BOTTOM_RIGHT, "NOSE_BOTTOM_RIGHT" },
    { Type::NOSE_BOTTOM_LEFT, "NOSE_BOTTOM_LEFT" },
    { Type::NOSE_BOTTOM_CENTER, "NOSE_BOTTOM_CENTER" },
    { Type::LEFT_EYE_TOP_BOUNDARY, "LEFT_EYE_TOP_BOUNDARY" },
    { Type::LEFT_EYE_RIGHT_CORNER, "LEFT_EYE_RIGHT_CORNER" },
    { Type::LEFT_EYE_BOTTOM_BOUNDARY, "LEFT_EYE_BOTTOM_BOUNDARY" },
    { Type::LEFT_EYE_LEFT_CORNER, "LEFT_EYE_LEFT_CORNER" },
    { Type::RIGHT_EYE_TOP_BOUNDARY, "RIGHT_EYE_TOP_BOUNDARY" },
    { Type::RIGHT_EYE_RIGHT_CORNER, "RIGHT_EYE_RIGHT_CORNER" },
    { Type::RIGHT_EYE_BOTTOM_BOUNDARY, "RIGHT_EYE_BOTTOM_BOUNDARY" },
    { Type::RIGHT_EYE_LEFT_CORNER, "RIGHT_EYE_LEFT_CORNER" },
    { Type::LEFT_EYEBROW_UPPER_MIDPOINT, "LEFT_EYEBROW_UPPER_MIDPOINT" },
    { Type::RIGHT_EYEBROW_UPPER_MIDPOINT, "RIGHT_EYEBROW_UPPER_MIDPOINT" },
    { Type::LEFT_EAR_TRAGION, "LEFT_EAR_TRAGION" },
    { Type::RIGHT_EAR_TRAGION, "RIGHT_EAR_TRAGION" },
    { Type::LEFT_EYE_PUPIL, "LEFT_EYE_PUPIL" },
    { Type::RIGHT_EYE_PUPIL, "RIGHT_EYE_PUPIL" },
    { Type::FOREHEAD_GLABELLA, "FOREHEAD_GLABELLA" },
    { Type::CHIN_GNATHION, "CHIN_GNATHION" },
    { Type::CHIN_LEFT_GONION, "CHIN_LEFT_GONION" },
    { Type::CHIN_RIGHT_GONION, "CHIN_RIGHT_GONION" }
};


const std::map<FaceAnnotation::Landmark::Type, std::string> FaceAnnotation::Landmark::LANDMARK_TYPE_DESCRIPTIONS =
{
    { Type::UNKNOWN_LANDMARK, "Unknown face landmark detected. Should not be filled." },
    { Type::LEFT_EYE, "Left eye." },
    { Type::RIGHT_EYE, "Right eye." },
    { Type::LEFT_OF_LEFT_EYEBROW, "Left of left eyebrow." },
    { Type::RIGHT_OF_LEFT_EYEBROW, "Right of left eyebrow." },
    { Type::LEFT_OF_RIGHT_EYEBROW, "Left of right eyebrow." },
    { Type::RIGHT_OF_RIGHT_EYEBROW, "Right of right eyebrow." },
    { Type::MIDPOINT_BETWEEN_EYES, "Midpoint between eyes." },
    { Type::NOSE_TIP, "Nose tip." },
    { Type::UPPER_LIP, "Upper lip." },
    { Type::LOWER_LIP, "Lower lip." },
    { Type::MOUTH_LEFT, "Mouth left." },
    { Type::MOUTH_RIGHT, "Mouth right." },
    { Type::MOUTH_CENTER, "Mouth center." },
    { Type::NOSE_BOTTOM_RIGHT, "Nose, bottom right." },
    { Type::NOSE_BOTTOM_LEFT, "Nose, bottom left." },
    { Type::NOSE_BOTTOM_CENTER, "Nose, bottom center." },
    { Type::LEFT_EYE_TOP_BOUNDARY, "Left eye, top boundary." },
    { Type::LEFT_EYE_RIGHT_CORNER, "Left eye, right corner." },
    { Type::LEFT_EYE_BOTTOM_BOUNDARY, "Left eye, bottom boundary." },
    { Type::LEFT_EYE_LEFT_CORNER, "Left eye, left corner." },
    { Type::RIGHT_EYE_TOP_BOUNDARY, "Right eye, top boundary." },
    { Type::RIGHT_EYE_RIGHT_CORNER, "Right eye, right corner." },
    { Type::RIGHT_EYE_BOTTOM_BOUNDARY, "Right eye, bottom boundary." },
    { Type::RIGHT_EYE_LEFT_CORNER, "Right eye, left corner." },
    { Type::LEFT_EYEBROW_UPPER_MIDPOINT, "Left eyebrow, upper midpoint." },
    { Type::RIGHT_EYEBROW_UPPER_MIDPOINT, "Right eyebrow, upper midpoint." },
    { Type::LEFT_EAR_TRAGION, "Left ear tragion." },
    { Type::RIGHT_EAR_TRAGION, "Right ear tragion." },
    { Type::LEFT_EYE_PUPIL, "Left eye pupil." },
    { Type::RIGHT_EYE_PUPIL, "Right eye pupil." },
    { Type::FOREHEAD_GLABELLA, "Forehead glabella." },
    { Type::CHIN_GNATHION, "Chin gnathion." },
    { Type::CHIN_LEFT_GONION, "Chin left gonion." },
    { Type::CHIN_RIGHT_GONION, "Chin right gonion." }
};


FaceAnnotation::FaceAnnotation()
{
}


FaceAnnotation::~FaceAnnotation()
{
}


ofPolyline FaceAnnotation::boundingPoly() const
{
    return _boundingPoly;
}


ofPolyline FaceAnnotation::fdBoundingPoly() const
{
    return _fdBoundingPoly;
}


std::vector<FaceAnnotation::Landmark> FaceAnnotation::landmarks() const
{
    return _landmarks;
}


float FaceAnnotation::rollAngle() const
{
    return _rollAngle;
}


float FaceAnnotation::panAngle() const
{
    return _panAngle;
}

    
float FaceAnnotation::tiltAngle() const
{
    return _tiltAngle;
}


float FaceAnnotation::detectionConfidence() const
{
    return _detectionConfidence;
}


float FaceAnnotation::landmarkingConfidence() const
{
    return _landmarkingConfidence;
}


Likelihood FaceAnnotation::joyLikelihood() const
{
    return _joyLikelihood;
}


Likelihood FaceAnnotation::sorrowLikelihood() const
{
    return _sorrowLikelihood;
}


Likelihood FaceAnnotation::angerLikelihood() const
{
    return _angerLikelihood;
}


Likelihood FaceAnnotation::surpriseLikelihood() const
{
    return _surpriseLikelihood;
}


Likelihood FaceAnnotation::underExposedLikelihood() const
{
    return _underExposedLikelihood;
}


Likelihood FaceAnnotation::blurredLikelihood() const
{
    return _blurredLikelihood;
}


Likelihood FaceAnnotation::headwearLikelihood() const
{
    return _headwearLikelihood;
}


FaceAnnotation FaceAnnotation::fromJSON(const ofJson& json)
{
    FaceAnnotation annotation;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "boundingPoly") VisionDeserializer::fromJSON(value, annotation._boundingPoly);
        else if (key == "fdBoundingPoly") VisionDeserializer::fromJSON(value, annotation._fdBoundingPoly);
        else if (key == "landmarks")
        {
            std::vector<FaceAnnotation::Landmark> landmarks;

            for (const auto& landmark : value)
                landmarks.push_back(FaceAnnotation::Landmark::fromJSON(landmark));

            annotation._landmarks = landmarks;
        }
        else if (key == "rollAngle") annotation._rollAngle = value;
        else if (key == "panAngle") annotation._panAngle = value;
        else if (key == "tiltAngle") annotation._tiltAngle = value;
        else if (key == "detectionConfidence") annotation._detectionConfidence = value;
        else if (key == "landmarkingConfidence") annotation._landmarkingConfidence = value;
        else if (key == "joyLikelihood") annotation._joyLikelihood = Likelihood::fromString(value);
        else if (key == "sorrowLikelihood") annotation._sorrowLikelihood = Likelihood::fromString(value);
        else if (key == "angerLikelihood") annotation._angerLikelihood = Likelihood::fromString(value);
        else if (key == "surpriseLikelihood") annotation._surpriseLikelihood = Likelihood::fromString(value);
        else if (key == "underExposedLikelihood") annotation._underExposedLikelihood = Likelihood::fromString(value);
        else if (key == "blurredLikelihood") annotation._blurredLikelihood = Likelihood::fromString(value);
        else if (key == "headwearLikelihood") annotation._headwearLikelihood = Likelihood::fromString(value);
        else ofLogWarning("FaceAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }

    return annotation;
}


SafeSearchAnnotation::SafeSearchAnnotation()
{
}


SafeSearchAnnotation::~SafeSearchAnnotation()
{
}


Likelihood SafeSearchAnnotation::adult() const
{
    return _adult;
}


Likelihood SafeSearchAnnotation::spoof() const
{
    return _spoof;
}


Likelihood SafeSearchAnnotation::medical() const
{
    return _medical;
}


Likelihood SafeSearchAnnotation::violence() const
{
    return _violence;
}

    
Likelihood SafeSearchAnnotation::racy() const
{
    return _racy;
}


SafeSearchAnnotation SafeSearchAnnotation::fromJSON(const ofJson& json)
{
    SafeSearchAnnotation annotation;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "adult") annotation._adult = Likelihood::fromString(value);
        else if (key == "spoof") annotation._spoof = Likelihood::fromString(value);
        else if (key == "medical") annotation._medical = Likelihood::fromString(value);
        else if (key == "violence") annotation._violence = Likelihood::fromString(value);
        else if (key == "racy") annotation._racy = Likelihood::fromString(value);
        else ofLogWarning("SafeSearchAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }

    return annotation;
}


ColorInfo::ColorInfo()
{
}


ColorInfo::~ColorInfo()
{
}

ofColor ColorInfo::color() const
{
    return _color;
}


float ColorInfo::score() const
{
    return _score;
}


float ColorInfo::pixelFraction() const
{
    return _pixelFraction;
}


ColorInfo ColorInfo::fromJSON(const ofJson& json)
{
    ColorInfo colorInfo;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "color") VisionDeserializer::fromJSON(value, colorInfo._color);
        else if (key == "score") colorInfo._score = value;
        else if (key == "pixelFraction") colorInfo._pixelFraction = value;
        else ofLogWarning("ColorInfo::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }

    return colorInfo;
}



ImagePropertiesAnnotation::ImagePropertiesAnnotation()
{
}


ImagePropertiesAnnotation::~ImagePropertiesAnnotation()
{
}


std::vector<ColorInfo> ImagePropertiesAnnotation::dominantColors() const
{
    return _dominantColors;
}


ImagePropertiesAnnotation ImagePropertiesAnnotation::fromJSON(const ofJson& json)
{
    ImagePropertiesAnnotation annotation;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "dominantColors")
        {
            for (const auto& color: value["colors"]) annotation._dominantColors.push_back(ColorInfo::fromJSON(color));
        }
        else ofLogWarning("ImagePropertiesAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }

    return annotation;
}
    
    
    
CropHint::CropHint()
{
}
    

CropHint::~CropHint()
{
}


ofPolyline CropHint::boundingPoly() const
{
    return _boundingPoly;
}
    

float CropHint::confidence() const
{
    return _confidence;
}

    
float CropHint::importanceFraction() const
{
    return _importanceFraction;
}

    
CropHint CropHint::fromJSON(const ofJson& json)
{
    CropHint annotation;
    
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        
        if (key == "confidence") annotation._confidence = value;
        else if (key == "importanceFraction") annotation._importanceFraction = value;
        else if (key == "boundingPoly") VisionDeserializer::fromJSON(value, annotation._boundingPoly);
        else ofLogWarning("CropHintsAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }
    
    return annotation;
}
    
    
    
CropHintsAnnotation::CropHintsAnnotation()
{
}


CropHintsAnnotation::~CropHintsAnnotation()
{
}
    

std::vector<CropHint> CropHintsAnnotation::cropHints() const
{
    return _cropHints;
}


CropHintsAnnotation CropHintsAnnotation::fromJSON(const ofJson& json)
{
    CropHintsAnnotation annotation;
    
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        
        if (key == "cropHints")
        {
            for (const auto& cropHint: value) annotation._cropHints.push_back(CropHint::fromJSON(cropHint));
        }
        else ofLogWarning("CropHintsAnnotation::fromJSON") << "Unknown key " << key << " - " << json.dump(4);

        ++iter;
    }
    
    return annotation;
}

    

} } // namespace ofx::CloudPlatform
