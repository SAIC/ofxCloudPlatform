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


#include "ofx/CloudPlatform/VisionAnnotations.h"


namespace ofx {
namespace CloudPlatform {


const std::map<ImageAnnotation::Likelihood, std::string> ImageAnnotation::LIKELIHOOD_STRINGS =
{
    { Likelihood::UNKNOWN, "UNKNOWN" },
    { Likelihood::VERY_UNLIKELY, "VERY_UNLIKELY" },
    { Likelihood::UNLIKELY, "UNLIKELY" },
    { Likelihood::POSSIBLE, "POSSIBLE" },
    { Likelihood::LIKELY, "LIKELY" },
    { Likelihood::VERY_LIKELY, "VERY_LIKELY" }
};


const std::map<std::string, ImageAnnotation::Likelihood> ImageAnnotation::STRINGS_LIKELIHOOD =
{
    { "UNKNOWN", Likelihood::UNKNOWN },
    { "VERY_UNLIKELY", Likelihood::VERY_UNLIKELY },
    { "UNLIKELY", Likelihood::UNLIKELY,  },
    { "POSSIBLE", Likelihood::POSSIBLE,  },
    { "LIKELY", Likelihood::LIKELY,  },
    { "VERY_LIKELY", Likelihood::VERY_LIKELY }
};


const std::map<ImageAnnotation::Likelihood, float> ImageAnnotation::LIKELIHOOD_VALUES =
{
    { Likelihood::UNKNOWN, 0.0 },
    { Likelihood::VERY_UNLIKELY, 0.0 },
    { Likelihood::UNLIKELY, 0.25 },
    { Likelihood::POSSIBLE, 0.5 },
    { Likelihood::LIKELY, 0.75 },
    { Likelihood::VERY_LIKELY, 1.0 }
};

ImageAnnotation::ImageAnnotation(const ofJson& json): _json(json)
{
}


ImageAnnotation::~ImageAnnotation()
{
}


bool ImageAnnotation::isLoaded() const
{
    return !_json.is_null();
}


const ofJson& ImageAnnotation::json() const
{
    return _json;
}


EntityAnnotation::~EntityAnnotation()
{
}


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



FaceAnnotation::~FaceAnnotation()
{
}


LandmarkAnnotation::~LandmarkAnnotation()
{
}


LogoAnnotation::~LogoAnnotation()
{
}


LabelAnnotation::~LabelAnnotation()
{
}


TextAnnotation::~TextAnnotation()
{
}


SafeSearchAnnotation::~SafeSearchAnnotation()
{
}


ImagePropertiesAnnotation::~ImagePropertiesAnnotation()
{
}


} } // namespace ofx::CloudPlatform
