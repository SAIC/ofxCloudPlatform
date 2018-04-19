//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/VisionDebug.h"
#include "ofGraphics.h"



namespace ofx {
namespace CloudPlatform {


void VisionDebug::draw(const std::string& label,
                       float value,
                       float x,
                       float y,
                       float width,
                       float height)
{
    draw(label, ofToString(value, 2), x, y, width, height);
}

    
void VisionDebug::draw(const std::string& label,
                       const std::string& value,
                       float x,
                       float y,
                       float width,
                       float height)
{
    ofPushStyle();
    
    ofFill();
    ofSetColor(0, 200);
    ofDrawRectangle(x, y, width, height);

//    ofFill();
//    ofSetColor(127, 200);
//    ofDrawRectangle(x, y, width * value, height);

    ofSetColor(255);
    ofDrawBitmapStringHighlight(label + "(" + value + ")", x + 5, y + 14);

    ofNoFill();
    ofSetColor(255, 200);
    ofDrawRectangle(x, y, width, height);

    ofPopStyle();
}


void VisionDebug::draw(const std::string& label,
                       const Likelihood& likelihood,
                       float x,
                       float y,
                       float width,
                       float height)
{
    draw(label + ": " + likelihood.name(), likelihood.value(), x, y, width, height);
}


void VisionDebug::draw(const FaceAnnotation::Landmark& landmark)
{
    ofColor background= ofColor(0, 80);
    ofColor foreground = ofColor(0, 0);

    if (glm::distance(glm::vec3(ofGetMouseX(), ofGetMouseY(), 0), landmark.position()) < 5)
    {
        foreground = ofColor(255);
        background = ofColor(0);
    }

    ofDrawBitmapStringHighlight(landmark.name(), landmark.position(), foreground, background);
    ofNoFill();
    ofDrawEllipse(landmark.position().x, landmark.position().y, 10, 10);
}


void VisionDebug::draw(const FaceAnnotation& annotation)
{
    ofRectangle r = annotation.boundingPoly().getBoundingBox();


    annotation.boundingPoly().draw();
    annotation.fdBoundingPoly().draw();

    for (auto& landmark : annotation.landmarks())
    {
        draw(landmark);
    }

//    /// \sa rollAngle()
//    float _rollAngle;
//
//    /// \sa panAngle()
//    float _panAngle;
//
//    /// \sa tiltAngle()
//    float _tiltAngle;

    if (r.inside(ofGetMouseX(), ofGetMouseY()))
    {
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(ofGetMouseX(), ofGetMouseY());

        int height = 25;
        int yPosition = 10;

        draw("         JOY", annotation.joyLikelihood(), 10, yPosition+=height);
        draw("      SORROW", annotation.sorrowLikelihood(), 10, yPosition+=height);
        draw("       ANGER", annotation.angerLikelihood(), 10, yPosition+=height);
        draw("    SURPRISE", annotation.surpriseLikelihood(), 10, yPosition+=height);
        draw("UNDEREXPOSED", annotation.underExposedLikelihood(), 10, yPosition+=height);
        draw("     BLURRED", annotation.blurredLikelihood(), 10, yPosition+=height);
        draw("    HEADWARE", annotation.headwearLikelihood(), 10, yPosition+=height);

        yPosition += height;

        draw("   Detection confidence: ", annotation.detectionConfidence(), 10, yPosition+=height);
        draw(" Landmarking confidence: ", annotation.landmarkingConfidence(), 10, yPosition+=height);

        ofPopStyle();
        ofPopMatrix();
    }
}


void VisionDebug::draw(const EntityAnnotation& annotation)
{
    ofRectangle r = annotation.boundingPoly().getBoundingBox();
    annotation.boundingPoly().draw();
    
    int height = 25;
    int yPosition = 10;

    draw("DESCRIPTION", annotation.description(), 10, yPosition+=height);
    draw("     LOCALE", annotation.locale(), 10, yPosition+=height);
    draw("        MID", annotation.mid(), 10, yPosition+=height);
    draw("      SCORE", annotation.score(), 10, yPosition+=height);
    draw(" TOPICALITY", annotation.topicality(), 10, yPosition+=height);


    
    ofDrawBitmapStringHighlight(annotation.description(), r.x + 14, r.y + 14);
    
}


void VisionDebug::draw(const SafeSearchAnnotation& annotation)
{
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetMouseX(), ofGetMouseY());
    
    int height = 25;
    int yPosition = 10;
    
    draw("   ADULT", annotation.adult(), 10, yPosition+=height);
    draw("   SPOOF", annotation.spoof(), 10, yPosition+=height);
    draw(" MEDICAL", annotation.medical(), 10, yPosition+=height);
    draw("    RACY", annotation.racy(), 10, yPosition+=height);
    draw("VIOLENCE", annotation.violence(), 10, yPosition+=height);
    
    ofPopStyle();
    ofPopMatrix();
}


void VisionDebug::draw(const ImagePropertiesAnnotation& annotation)
{
}


void VisionDebug::draw(const std::vector<FaceAnnotation>& annotations)
{
    for (auto& annotation: annotations) draw(annotation);
}


void VisionDebug::draw(const std::vector<EntityAnnotation>& annotations)
{
    for (auto& annotation: annotations) draw(annotation);
}


void VisionDebug::draw(const AnnotateImageResponse& response)
{
    draw(response.faceAnnotations());
    draw(response.landmarkAnnotations());
    draw(response.logoAnnotations());
    draw(response.labelAnnotations());
    draw(response.textAnnotations());
    draw(response.safeSearchAnnotation());
    draw(response.imagePropertiesAnnotation());
}

    
void VisionDebug::draw(const std::vector<AnnotateImageResponse>& responses)
{
    for (auto& response: responses) draw(response);
}

    
void VisionDebug::draw(const AnnotateImageResponse& response,
                       VisionRequestItem::Feature::Type filterType)
{
    switch (filterType)
    {
        case VisionRequestItem::Feature::Type::TYPE_UNSPECIFIED:
            std::cout << "TYPE_UNSPECIFIED" << std::endl;
            break;
        case VisionRequestItem::Feature::Type::FACE_DETECTION:
            std::cout << "FACE_DETECTION" << std::endl;
            draw(response.faceAnnotations());
            break;
        case VisionRequestItem::Feature::Type::LANDMARK_DETECTION:
            std::cout << "LANDMARK_DETECTION" << std::endl;
            draw(response.landmarkAnnotations());
            break;
        case VisionRequestItem::Feature::Type::LOGO_DETECTION:
            std::cout << "LOGO_DETECTION" << std::endl;
            draw(response.logoAnnotations());
            break;
        case VisionRequestItem::Feature::Type::LABEL_DETECTION:
            std::cout << "LABEL_DETECTION" << std::endl;
            draw(response.labelAnnotations());
            break;
        case VisionRequestItem::Feature::Type::TEXT_DETECTION:
            std::cout << "TEXT_DETECTION" << std::endl;
            draw(response.textAnnotations());
            break;
        case VisionRequestItem::Feature::Type::DOCUMENT_TEXT_DETECTION:
            std::cout << "DOCUMENT_TEXT_DETECTION" << std::endl;
            break;
        case VisionRequestItem::Feature::Type::SAFE_SEARCH_DETECTION:
            std::cout << "SAFE_SEARCH_DETECTION" << std::endl;
            draw(response.safeSearchAnnotation());
            break;
        case VisionRequestItem::Feature::Type::IMAGE_PROPERTIES:
            std::cout << "IMAGE_PROPERTIES" << std::endl;
            draw(response.imagePropertiesAnnotation());
            break;
        case VisionRequestItem::Feature::Type::CROP_HINTS:
            
            std::cout << "CROP_HINTS" << std::endl;
            break;
        case VisionRequestItem::Feature::Type::WEB_DETECTION:
            std::cout << "WEB_DETECTION" << std::endl;
            break;
    }
}


void VisionDebug::draw(const std::vector<AnnotateImageResponse>& responses,
                       VisionRequestItem::Feature::Type filterType)
{
    for (auto& response: responses)
        draw(response, filterType);
}


} } // namespace ofx::CloudPlatform

