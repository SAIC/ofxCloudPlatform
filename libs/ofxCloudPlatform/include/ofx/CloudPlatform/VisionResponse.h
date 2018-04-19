//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/HTTP/BaseClient.h"
#include "ofx/HTTP/BaseResponse.h"
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

    static AnnotateImageResponse fromJSON(const ofJson& json);

private:
    std::vector<FaceAnnotation> _faceAnnotations;
    std::vector<EntityAnnotation> _landmarkAnnotations;
    std::vector<EntityAnnotation> _logoAnnotations;
    std::vector<EntityAnnotation> _labelAnnotations;
    std::vector<EntityAnnotation> _textAnnotations;
    SafeSearchAnnotation _safeSearchAnnotation;
    ImagePropertiesAnnotation _imagePropertiesAnnotation;

};


class VisionResponse: public HTTP::BufferedResponse<VisionRequest>
{
public:
    using BufferedResponse<VisionRequest>::BufferedResponse;

    /// \brief Destroy a VisionResponse.
    virtual ~VisionResponse();

    std::vector<AnnotateImageResponse> responses() const;

    static std::vector<AnnotateImageResponse> fromJSON(const ofJson& json);

protected:
    virtual void parseBuffer() override;

    /// \brief Subclasses can further parse JSON data.
    /// \param json The JSON Data to parse.
    virtual void parseJSON(const ofJson& json);

private:
    std::vector<AnnotateImageResponse> _responses;

    friend class HTTP::BaseClient;

};



} } // namespace ofx::CloudPlatform
